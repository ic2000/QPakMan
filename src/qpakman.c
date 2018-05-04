#include "headers.h"
#include "argparse.h"

#define VERSION "0.67"
#define TITLE "\n**** QPAKMAN v" VERSION " (C) 2008 Andrew Apted ****\n"
#define LICENSE "\nThis program is free software, under the terms of the GNU General\n" \
                "Public License, and comes with ABSOLUTELY NO WARRANTY. See the\n"    \
                "accompanying documentation for more details. USE AT OWN RISK."

void list(int argc, const char **argv) {
  if (argc == 0) {
    FATAL_ERROR("Missing input file to list\n");
  } else if (argc > 1) {
    FATAL_ERROR("Can only list one input file\n");
  }

  const char *filename = argv[0];
}

void extract(int argc, const char **argv) {
  if (argc == 0) {
    FATAL_ERROR("Missing input file to extract\n");
  } else if (argc > 1) {
    FATAL_ERROR("Can only extract one input file\n");
  }

  const char *filename = argv[0];
}

void maketex(int argc, const char **argv) {
  if (argc == 0)
    FATAL_ERROR("Missing input files for maketex\n");
}

int main(int argc, const char **argv) {
  puts(TITLE);
  const char *usage[] = {
    "qpakman  [OPTIONS...]  FILES...",
    "qpakman  [OPTIONS...]  IMAGES..",
    "qpakman  [OPTIONS...]  INPUT.pak/wad",
    NULL,
  };
  char *opt_output = NULL;
  int opt_list = 0;
  int opt_extract = 0;
  int opt_maketex = 0;
  struct argparse_option options[] = {
    OPT_HELP(),
    OPT_STRING('o', "output", &opt_output, "specify output name or dir"),
    OPT_BOOLEAN('l', "list", &opt_list, "list contents of PAK/WAD file"),
    OPT_BOOLEAN('e', "extract", &opt_extract, "extract PAK/WAD contents into current dir"),
    OPT_BOOLEAN('m', "maketex", &opt_maketex, "make a texture WAD from BSP files"),
    OPT_END()
  };
  struct argparse argparse;
  argparse_init(&argparse, options, usage, 0);
  argparse_describe(&argparse, NULL, LICENSE);
  argc = argparse_parse(&argparse, argc, argv);

  if (opt_list) {
    list(argc, argv);
  } else if (opt_extract) {
    extract(argc, argv);
  } else if (opt_maketex) {
    maketex(argc, argv);
  } else { // need to implement ACT_Create
    argparse_usage(&argparse);
  }

  return EXIT_SUCCESS;
}