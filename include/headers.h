#pragma once

#include <stdio.h>
#include <stdlib.h>

#define FATAL_ERROR(...) {          \
  fprintf(stderr, "FATAL ERROR: "); \
  fprintf(stderr, __VA_ARGS__);     \
  fprintf(stderr, "\n");            \
  exit(EXIT_FAILURE);               \
}
