#include "connectn.h"

int main(int argc, char* argv[]) {
  command_line_validation(argc);
  char** grid, *p;
  int num_row, num_col;
  grid = blank_grid(argv, &num_row, &num_col);
  print_grid(grid, num_row, num_col);
  action(grid, strtol(argv[3], &p, 10), num_row, num_col);
  free_grid(grid, num_row);
  return 0;
}