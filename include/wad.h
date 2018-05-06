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

#ifndef WAD_H
#define WAD_H

#include "utils.h"

#define WAD2_MAGIC "WAD2"
#define WAD_NAME_LEN 16

// wad2 structures
typedef struct
{
  char magic[4];
  uint32_t num_lumps;
  uint32_t dir_start;
} raw_wad2_header_t;

typedef struct {
  uint32_t start;
  uint32_t length; // compressed
  uint32_t u_len; // uncompressed
  uint8_t type;
  uint8_t compression;
  uint8_t _pad[2];
  char name[16]; // must be null terminated
} raw_wad2_lump_t;

typedef struct {
  FILE *r_fp;
  raw_wad2_header_t r_header;
  raw_wad2_lump_t *r_dir;
} wad2_t;

// wad reading
bool open_wad(wad2_t *wad, const char *filename);
void close_wad(wad2_t *wad);
void list_wad_entries(wad2_t *wad);

#endif // WAD_H