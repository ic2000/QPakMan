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

#include "file.h"
#include <ctype.h>

const char *get_file_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot+1;
}

bool check_file_ext(const char *filename, const char *ext) { 
  const char *file_ext = get_file_ext(filename);
  for (size_t i = 0;; i++) {
    if (!file_ext[i])
      return !ext[i];

    if (tolower(file_ext[i]) != tolower(ext[i]))
      return false;
  }
}

/*
bool change_file_ext(const char *filename, const char *ext) {
  size_t filename_len = strlen(filename);
  char *file_ext = get_file_ext(filename);
  size_t file_ext_len = strlen(file_ext);
  size_t ext_len = strlen(ext);
  char *buff = malloc(strlen(filename) + ((int)ext_len - file_ext_len))
  memcpy(buff, filename, )

  return true;
}
*/