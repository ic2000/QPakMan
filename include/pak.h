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

#ifndef PAK_H
#define PAK_H

#include "utils.h"

#define PAK_MAGIC "PACK"
#define PAK_NAME_LEN 56

// pak structures
typedef struct {
  char magic[4];
  uint32_t dir_start;
  uint32_t entry_num;
} raw_pak_header_t;

typedef struct {
  char name[PAK_NAME_LEN];
  uint32_t offset;
  uint32_t length;
} raw_pak_entry_t;

typedef struct {
  FILE *r_fp;
  raw_pak_header_t r_header;
  raw_pak_entry_t *r_directory;
} pak_t;

// pak reading
bool open_pak(pak_t *pak, const char *filename);
void close_pak(pak_t *pak);
void list_pak_entries(pak_t *pak);

#endif // PAK_H