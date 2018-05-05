# Copyright (C) 2018  Koz Ross <koz.ross@retro-freedom.nz>
# Copyright (C) 2018  ic2000 <ic2000@live.co.uk>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=gcc
CFLAGS=-c -I./include -std=gnu11 -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers

OBJECTS=qpakman.o argparse.o file.o

qpakman: $(OBJECTS)
	$(CC) -Wall -Wextra -o qpakman $(OBJECTS)
	
qpakman.o: src/qpakman.c
	$(CC) $(CFLAGS) src/qpakman.c

argparse.o: src/argparse.c
	$(CC) $(CFLAGS) src/argparse.c

file.o: src/file.c
	$(CC) $(CFLAGS) src/file.c

clean:
	rm qpakman $(OBJECTS)
