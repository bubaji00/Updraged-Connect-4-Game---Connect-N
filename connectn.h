
#ifndef MAIN_C__CONNECTN_H_
#define MAIN_C__CONNECTN_H_
  #include <stdbool.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  void command_line_validation(int argc);
  char** blank_grid(char * argv[], int* num_row_ptr, int* num_col_ptr);
  void print_grid(char** grid, int num_row, int num_col);
  bool user_input_validation(char** grid, int user_entered);
  int get_user_input(char** grid, int num_col);
  char player_turn(int num_turn);
  char** new_grid(char** grid, int user_move, char which_player, int dot_col_pos);
  int new_dot_col_pot (char** grid, int num_row, int user_move);
  bool vertical_condition(char** grid, int num_row, int num_to_win, int user_move, int dot_col_pos, char which_player);
  bool horizontal_condition(char** grid, int num_col, int num_to_win, char which_player, int dot_col_pos);
  bool diagonal_condition(char** grid, int num_row, int num_col, int num_to_win, int user_move, char which_player, int dot_col_pos);
  bool condition(char** grid, int num_row, int num_col, int num_to_win, int user_move, char which_player, int dot_col_pos);
  void action(char** grid, int num_to_win, int num_row, int num_col);
  void free_grid(char** grid, int num_row);

#endif //MAIN_C__CONNECTN_H_
