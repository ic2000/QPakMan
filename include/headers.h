/*
 * Copyright (C) 2018  Koz Ross <koz.ross@retro-freedom.nz>
 * Copyright (C) 2018  ic2000 <ic2000@fix-my-email-please.uk>
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

#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include <stdlib.h>

#define FATAL_ERROR(...) {          \
  fprintf(stderr, "FATAL ERROR: "); \
  fprintf(stderr, __VA_ARGS__);     \
  fprintf(stderr, "\n");            \
  exit(EXIT_FAILURE);               \
}

#endif /* HEADERS_H */
