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

#include "wad.h"
#include "endian.h"

bool open_wad(wad2_t *wad, const char *filename) {
  wad->r_fp = fopen(filename, "rb");

  if (! wad->r_fp)
    return false;

  printf("Opened WAD2 file: %s\n", filename);

  if (fread(&wad->r_header, sizeof(wad->r_header), 1, wad->r_fp) != 1) {
    printf("WAD2_OpenRead: failed reading header\n");
    fclose(wad->r_fp);
    return false;
  }

  if (memcmp(wad->r_header.magic, WAD2_MAGIC, 4) != 0) {
    printf("WAD2_OpenRead: not a WAD2 file!\n");
    fclose(wad->r_fp);
    return false;
  }

  wad->r_header.num_lumps = LE_U32(wad->r_header.num_lumps);
  wad->r_header.dir_start = LE_U32(wad->r_header.dir_start);

  // read directory
  if (wad->r_header.num_lumps >= 5000) { // sanity check
    printf("WAD2_OpenRead: bad header (%d entries?)\n", wad->r_header.num_lumps);
    fclose(wad->r_fp);
    return false;
  }

  if (fseek(wad->r_fp, wad->r_header.dir_start, SEEK_SET) != 0) {
    printf("WAD2_OpenRead: cannot seek to directory (at 0x%08x)\n", wad->r_header.dir_start);
    fclose(wad->r_fp);
    return false;
  }

  wad->r_dir = malloc(sizeof(raw_wad2_lump_t)*(wad->r_header.num_lumps + 1));

  for (size_t i = 0; i < wad->r_header.num_lumps; i++) {
    raw_wad2_lump_t *L = &wad->r_dir[i];
    size_t res = fread(L, sizeof(raw_wad2_lump_t), 1, wad->r_fp);

    if ((int)res == EOF || res != 1 || ferror(wad->r_fp)) {
      if (i == 0) {
        printf("WAD2_OpenRead: could not read any dir-entries!\n");
        free(wad->r_dir);
        wad->r_dir = NULL;
        fclose(wad->r_fp);
        return false;
      }

      printf("WAD2_OpenRead: hit EOF reading dir-entry %zu\n", i);
      wad->r_header.num_lumps = i; // truncate directory
      break;
    }

    L->name[WAD_NAME_LEN-1] = '\0'; // make sure name is NUL terminated.
    L->start = LE_U32(L->start);
    L->length = LE_U32(L->length);
    L->u_len = LE_U32(L->u_len);
  }

  return true; // OK
}

void close_wad(wad2_t *wad) {
  fclose(wad->r_fp);
  printf("Closed WAD2 file\n");
  free(wad->r_dir);
  wad->r_dir = NULL;
}

void list_wad_entries(wad2_t *wad) {
  printf("--------------------------------------------------\n");
  
  if (wad->r_header.num_lumps == 0)
    printf("WAD2 file is empty\n");
  else {
    for (size_t i = 0; i < wad->r_header.num_lumps; i++) {
      raw_wad2_lump_t *L = &wad->r_dir[i];
      printf("%4zu: +%08x %08x %c : %s\n", i+1, L->start, L->length, letter_for_type(L->type), L->name);
    }
  }

  printf("--------------------------------------------------\n");
}