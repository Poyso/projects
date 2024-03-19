#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define ROW 20
#define COL 40

char field[ROW][COL];
int game_state = 1, food_state = 1;
int start_r = 1, start_c = 1, flag;

void field_init();
void spawn_food();
void print_field();
void logic();
void input();

int main() {
  system("clear");
  field_init();
  while (game_state == 1) {
    print_field();
    if (food_state == 1)
      spawn_food();
    sleep(1);
    system("clear");
  }
}

void field_init() {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1)
        field[i][j] = '#';
      else
        field[i][j] = ' ';
    }
  }
}

void print_field() {
  for (int i = 0; i < ROW; i++) {
    for (int f = 0; f < COL; f++) {
      if (f % COL == 0)
        printf("\n");
      printf("%c", field[i][f]);
    }
  }
  printf("\n");
}

void spawn_food() {
  srand(time(NULL));
  int rrow = ROW - 1, rcol = COL - 1;
  while (field[rrow][rcol] == '#') {
    rrow = rand() % ROW;
    rrow++;
    rcol = rand() % COL;
    rcol++;
  }
  field[rrow][rcol] = 'x';
}
