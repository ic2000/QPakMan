/*
 * Copyright (C) 2018  Koz Ross <koz.ross@retro-freedom.nz>
 * Copyright (C) 2018  ic2000 <ic2000@live.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pak.h"
#include "endian.h"

bool open_pak(pak_t *pak, const char *filename) {
  pak->r_fp = fopen(filename, "rb");

  if (!pak->r_fp) {
    return false;
  }

  printf("Opened PAK file: %s\n", filename);
  
  if (fread(&pak->r_header, sizeof(pak->r_header), 1, pak->r_fp) != 1) {
    printf("PAK_OpenRead: failed reading header\n");
    fclose(pak->r_fp);
    return false;
  }

  if (memcmp(pak->r_header.magic, PAK_MAGIC, 4) != 0) {
    printf("PAK_OpenRead: not a PAK file!\n");
    fclose(pak->r_fp);
    return false;
  }

  pak->r_header.dir_start = LE_U32(pak->r_header.dir_start);
  pak->r_header.entry_num = LE_U32(pak->r_header.entry_num);
  pak->r_header.entry_num /= sizeof(raw_pak_entry_t); // convert directory length to entry count

  // read directory
  if (pak->r_header.entry_num >= 5000) { // sanity check
    printf("PAK_OpenRead: bad header (%d entries?)\n", pak->r_header.entry_num);
    fclose(pak->r_fp);
    return false;
  }

  if (fseek(pak->r_fp, pak->r_header.dir_start, SEEK_SET) != 0) {
    printf("PAK_OpenRead: cannot seek to directory (at 0x%08x)\n", pak->r_header.dir_start);
    fclose(pak->r_fp);
    return false;
  }

  pak->r_directory = malloc(sizeof(raw_pak_entry_t)*(pak->r_header.entry_num + 1));

  for (size_t i = 0; i < pak->r_header.entry_num; i++) {
    raw_pak_entry_t *E = &pak->r_directory[i];
    size_t res = fread(E, sizeof(raw_pak_entry_t), 1, pak->r_fp);

    if ((int)res == EOF || res != 1 || ferror(pak->r_fp)) {
      if (i == 0) {
        printf("PAK_OpenRead: could not read any dir-entries!\n");
        free(pak->r_directory);
        pak->r_directory = NULL;
        fclose(pak->r_fp);
        return false;
      }

      printf("PAK_OpenRead: hit EOF reading dir-entry %zu\n", i);
      pak->r_header.entry_num = i; // truncate directory
      break;
    }

    E->name[PAK_NAME_LEN-1] = '\0'; // make sure name is NUL terminated.
    E->offset = LE_U32(E->offset);
    E->length = LE_U32(E->length);
  }

  return true; // OK
}

void close_pak(pak_t *pak) {
  fclose(pak->r_fp);
  printf("Closed PAK file\n");
  free(pak->r_directory);
  pak->r_directory = NULL;
}

void list_pak_entries(pak_t *pak) {
  printf("--------------------------------------------------\n");
  if (pak->r_header.entry_num == 0)
    printf("PAK file is empty\n");
  else
    for (size_t i = 0; i < pak->r_header.entry_num; i++) {
      raw_pak_entry_t *E = &pak->r_directory[i];
      printf("%4zu: +%08x %08x : %s\n", i+1, E->offset, E->length, E->name);
    }

  printf("--------------------------------------------------\n");
}