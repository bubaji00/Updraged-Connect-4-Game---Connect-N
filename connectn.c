#include "connectn.h"

void command_line_validation(int argc) {
  if (argc == 4) {
    return;
  } else if (argc < 4) {
    printf("Not enough arguments entered\n");
  } else if (argc > 4) {
    printf("Too many arguments entered\n");
  }
  printf("Usage connectn.out num_rows num_columns ");
  printf("number_of_pieces_in_a_row_needed_to_win\n");
  exit(0);
}

char** blank_grid(char* argv[], int* num_row_ptr, int* num_col_ptr) {
  char* p;
  int num_row = strtol(argv[1], &p, 10), num_col = strtol(argv[2], &p, 10);
  *num_row_ptr = num_row;
  *num_col_ptr = num_col;
  char** grid = (char**)calloc(num_row, sizeof(char*));
  for (int i = 0; i < num_row; ++i) {
    grid[i] = (char*)calloc(num_col, sizeof(char));
  }
  for (int i = 0; i < num_row; ++i ) {
    for (int j = 0; j < num_col; ++j) {
      strcpy(&grid[i][j], "*");
    }
  }
  return grid;
}

void print_grid(char** grid, int num_row, int num_col) {
  for (int i = 0; i < num_row; ++i) {
    printf("%d ", num_row - 1 - i);
    for (int j = 0; j < num_col; ++j) {
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
  printf("  ");
  for (int k = 0; k < num_col; ++k) {
    printf("%d ", k);
  }
  printf("\n");
}

bool user_input_validation(char** grid, int user_entered) {
  return user_entered >= 0 && grid[0][user_entered] == '*';
}

int get_user_input(char** grid, int num_col) {
  int user_move;
  do {
    printf("Enter a column between 0 and %d to play in: \n", num_col - 1);
    scanf("%d", &user_move);
  } while (!user_input_validation(grid, user_move) || user_move > num_col);
  return user_move;
}

char player_turn(int num_turn) {
  return num_turn % 2 == 0 ? 'O' : 'X';
}

char** new_grid(char** grid, int user_move, char which_player, int dot_col_pos) {
  grid[dot_col_pos][user_move] = which_player;
  return grid;
}

int new_dot_col_pot (char** grid, int num_row, int user_move) {
  int i = num_row - 1;
  while (i >= 0 && grid[i][user_move] != '*') {
    --i;
  }
  return i;
}

bool vertical_condition(char** grid, int num_row, int num_to_win, int user_move, int dot_col_pos, char which_player) {
  int num_in_a_row = 0 ;
  for (int i = dot_col_pos; i < num_row; ++i) {
    if (grid[i][user_move] == which_player) {
      num_in_a_row += 1;
      if (num_in_a_row == num_to_win) { return true; }
    } else {
      return false;
    }
  }
  return false;
}

bool horizontal_condition(char** grid, int num_col, int num_to_win, char which_player, int dot_col_pos) {
  int num_in_a_row = 0;
  for (int i = 0; i < num_col; ++i) {
    if (grid[dot_col_pos][i] == which_player) {
      num_in_a_row += 1;
      if (num_in_a_row == num_to_win) { return true; }
    } else {
      num_in_a_row = 0;
    }
  }
  return false;
}
// row 5 c 10
bool diagonal_condition(char** grid, int num_row, int num_col, int num_to_win, int user_move, char which_player, int dot_col_pos) {
  int i, j, num_in_a_row = 0;
  dot_col_pos - num_to_win + 1 < 0 ? i = 0 : (i = dot_col_pos - num_to_win + 1);
  user_move - num_to_win + 1 < 0 ? j = 0 : (j = user_move - num_to_win + 1);

  for (; i < num_row && j < num_col; ++i, ++j) { // top left to bottom right
    if (grid[i][j] == which_player) {
      ++num_in_a_row;
      if (num_in_a_row == num_to_win) { return true; }
    } else {
      num_in_a_row = 0;
    }
  }
  num_in_a_row = 0;
  dot_col_pos - num_to_win + 1 < 0 ? i = 0 : (i = dot_col_pos - num_to_win + 1);
  user_move + num_to_win - 1 < 0 ? j = 0 : (j = user_move + num_to_win - 1);

  for (; i < num_row && j >= 0; ++i, --j) { // top right to bottom left
    if (grid[i][j] == which_player) {
      ++num_in_a_row;
      if (num_in_a_row == num_to_win) { return true; }
    } else {
      num_in_a_row = 0;
    }
  }
  return false;
}

bool condition(char** grid, int num_row, int num_col, int num_to_win, int user_move, char which_player, int dot_col_pos) {
  return vertical_condition(grid, num_row, num_to_win, user_move, dot_col_pos, which_player) ||
          horizontal_condition(grid, num_col, num_to_win, which_player, dot_col_pos) ||
          diagonal_condition(grid, num_row, num_col, num_to_win, user_move, which_player, dot_col_pos);
}

void action(char** grid, int num_to_win, int num_row, int num_col) {
  int dot_col_pos, user_move, num_turn = 1;
  char which_player;
  do {
    user_move = get_user_input(grid, num_col);
    which_player = player_turn(num_turn);
    dot_col_pos = new_dot_col_pot(grid, num_row, user_move);
    grid = new_grid(grid, user_move, which_player, dot_col_pos);
    print_grid(grid, num_row, num_col);
    ++num_turn;
  } while (!condition(grid, num_row, num_col, num_to_win, user_move, which_player, dot_col_pos) && num_turn - 1 != num_row * num_col);

  if (num_turn - 1 == num_row * num_col) {
    printf("Tie game!\n");
  } else if (which_player == 'O') {
    printf("Player 2 Won!\n");
  } else {
    printf("Player 1 Won!\n");
  }
}

void free_grid(char** grid, int num_row) {
  for (int i = 0; i < num_row; i++) {
    free((grid)[i]);
  }
  free(grid);
}
