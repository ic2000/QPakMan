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

#include "utils.h"

char letter_for_type(uint8_t type) {
  switch (type) {
    case TYP_NONE: return 'x';
    case TYP_LABEL: return 'L';
    case TYP_PALETTE: return 'C';
    case TYP_QTEX: return 'T';
    case TYP_QPIC: return 'P';
    case TYP_SOUND: return 'S';
    case TYP_MIPTEX: return 'M';
    default: return '?';
  }
}