#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#define ROW 20
#define COL 40

static struct termios old, current;

char field[ROW][COL];
int game_state = 1, food_state = 1, flag = 1;
int start_r = 1, start_c = 1, flag;

void field_init();
void spawn_food();
void print_field();
void logic();
void input();

void initTermios(int);
void resetTermios(void);
char getch_(int);
char custom_getch();

int main() {
  system("clear");
  field_init();
  while (game_state == 1) {
    input();
    printf("flag: %d", flag);
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
  if (food_state == 1) {
    while (field[rrow][rcol] == '#') {
      rrow = rand() % ROW;
      rrow++;
      rcol = rand() % COL;
      rcol++;
    }
    field[rrow][rcol] = 'x';
  }
}

void input() {
  char c;
  c = custom_getch();
  printf("valore  di c: %c", c);
  switch (c) {
  case 'd':
    flag = 1;
    break;
  case 'a':
    flag = 2;
    break;
  case 'w':
    flag = 3;
    break;
  case 's':
    flag = 4;
    break;
  default:
    flag = flag;
    break;
  }
}
/* Initialize new terminal i/o settings */
void initTermios(int echo) {
  tcgetattr(0, &old);         /* grab old terminal i/o settings */
  current = old;              /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
    current.c_lflag |= ECHO; /* set echo mode */
  } else {
    current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) { tcsetattr(0, TCSANOW, &old); }

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char custom_getch() { return getch_(0); }
