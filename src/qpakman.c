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
#include "argparse.h"
#include "file.h"
#include "pak.h"
#include "wad.h"

#define VERSION "0.1"

void list(int argc, char **argv) {
  if (argc == 0) {
    FATAL_ERROR("Missing input file to list\n");
  } else if (argc > 1) {
    FATAL_ERROR("Can only list one input file\n");
  }

  const char *filename = argv[0];

  if (check_file_ext(filename, "pak")) {
    pak_t pak;
    
    if (!open_pak(&pak, filename))
      FATAL_ERROR("Could not open PAK file: %s\n", filename);

    list_pak_entries(&pak);
    close_pak(&pak);
  } else if (check_file_ext(filename, "wad")) {
    wad2_t wad;
    
    if (!open_wad(&wad, filename))
      FATAL_ERROR("Could not open WAD2 file: %s\n", filename);

    list_wad_entries(&wad);
    close_wad(&wad);
  } else
    FATAL_ERROR("Unknown input file format: %s\n", filename);
}

void extract(int argc, char **argv, char *output) {
  if (argc == 0) {
    FATAL_ERROR("Missing input file to extract\n");
  } else if (argc > 1) {
    FATAL_ERROR("Can only extract one input file\n");
  }

  const char *filename = argv[0];
}

void maketex(int argc, char **argv, char *output) {
  if (argc == 0)
    FATAL_ERROR("Missing input files for maketex\n");
}

void create(int argc, char **argv, char *output) {

}

int main(int argc, char **argv) {
  const char *usage[] = {
    "qpakman [options] files -o output.pak",
    "qpakman [options] images -o output.wad",
    "qpakman [options] input.{pak,wad} -o dir",
    NULL,
  };
  char *output = NULL;
  int opt_list = 0;
  int opt_extract = 0;
  int opt_maketex = 0;
  struct argparse_option options[] = {
    // OPT_HELP(),
    OPT_STRING('o', "output", &output, "specify output name/dir"),
    OPT_BOOLEAN('l', "list", &opt_list, "list contents of pak/wad file"),
    OPT_BOOLEAN('e', "extract", &opt_extract, "extract pak/wad contents into output dir"),
    OPT_BOOLEAN('m', "maketex", &opt_maketex, "make a texture wad from bsp files"),
    OPT_END()
  };
  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(&argparse, NULL, NULL);
  argc = argparse_parse(&argparse, argc, argv);

  if (opt_list)
    list(argc, argv);
  else if (opt_extract)
    extract(argc, argv, output);
  else if (opt_maketex)
    maketex(argc, argv, output);
  else if (output)
    create(argc, argv, output);
  else
    argparse_usage(&argparse);

  return EXIT_SUCCESS;
}
