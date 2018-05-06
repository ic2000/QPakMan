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

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define FATAL_ERROR(...) {          \
  fprintf(stderr, "FATAL ERROR: "); \
  fprintf(stderr, __VA_ARGS__);     \
  fprintf(stderr, "\n");            \
  exit(EXIT_FAILURE);               \
}

enum {
  CMP_NONE = 0,
  CMP_LZSS = 1
};

enum {
  TYP_NONE = 0,
  TYP_LABEL = 1,
  TYP_PALETTE = 64,
  TYP_QTEX = 65,
  TYP_QPIC = 66,
  TYP_SOUND = 67,
  TYP_MIPTEX = 68,
  TYP_COMPRESSED = 256
};

char letter_for_type(uint8_t type);

#endif // UTILS_H