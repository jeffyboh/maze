#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

char **screen;

int main() {
  int ch;     // character input is stored here
  int x = 0;  // cursor coordinate
  int y = 0;  // cursor coordinate

  int obstacle_x = 20;
  int obstacle_y = 10;
  int obstacle_width = 10;
  int obstacle_height = 5;

  initscr();  // initialize ncurses

  noecho();   // don't echo the user input
  cbreak();   // disable line buffering
  curs_set(0); // hide the terminal's cursor

  // get the screen size before we enter the loop. We will use this size in case the
  // player resizes the terminal
  getmaxyx(stdscr, SCREEN_HEIGHT, SCREEN_WIDTH);  // get the terminal size before we enter the loop
  keypad(stdscr, TRUE); // enables the keypad which will allow us to use arrow keys

  // allocate the 2D array for the screen 
  screen = (char **)malloc(SCREEN_HEIGHT * sizeof(char *));
  if (screen == NULL) {
    mvprintw(3, 0, "Unable to allocate memmory for the screen buffer");
  }
  for (int i; i < SCREEN_HEIGHT; i++) {
    screen[i] = (char *)malloc(SCREEN_WIDTH * sizeof(char));
    if (screen[i] == NULL) {
       mvprintw(3, 0, "Unable to allocate memory for screen");
       break;
    }
  }
  
  // main input loop
  while ((ch = getch()) != 'q') {
    initialize_screen_buffer();
    write_string_to_buffer(0, 0, "Text Based Cursor Movement - Press q to quit.");
    write_string_to_buffer(1, 0, "Use arrow keys to move the @ cursor.");

    for (int i=0; i<obstacle_height; i++) {
      for (int j=0; j<obstacle_width; j++) {
        mvprintw(obstacle_y + i, obstacle_x + j, "#");
      }
    }

    int next_x = x;
    int next_y = y;

    switch (ch) {
      case KEY_UP:
      case 'k':
      case 'w':
        next_y--;
        break;       
      case KEY_DOWN:
      case 'l':
      case 's':
        next_y++;
        break;
      case KEY_LEFT:
      case 'j':
      case 'a':
        next_x--;
        break;
      case KEY_RIGHT:
      case ';':
      case 'd':
        next_x++;
        break;
      default:
        break;
    }

    if (next_y < 2) next_y = 2;
    if (next_y >= SCREEN_HEIGHT) next_y = SCREEN_HEIGHT - 1;
    if (next_x < 0) next_x = 0;
    if (next_x >= SCREEN_WIDTH) next_x = SCREEN_WIDTH - 1;

    if (next_x >= obstacle_x && next_x < obstacle_x + obstacle_width &&
      next_y >= obstacle_y && next_y < obstacle_y + obstacle_height) {
      // we are blocked
      write_status("We are blocked!");
    } else {
      // update the coordinates so movement can happen
      x = next_x;
      y = next_y;
    }

    //mvprintw(y, x, "@");  // move to the coordinates set in the switch statement
    screen[y][x] = '@';

    // draw the screen
    for (int i=0; i<SCREEN_HEIGHT; i++) {
      for (int j=0; j<SCREEN_WIDTH; j++) {
        mvaddch(i, j, screen[i][j]);
      }
    }

    refresh();
  }

  // clean up the screen buffwr
  for (int i=0; i<SCREEN_HEIGHT; i++) {
    free(screen[i]);
  }
  free(screen);

  endwin();   // restore the terminal before exiting

  return 0;
}

void write_status(char *message)
{
  write_string_to_buffer(SCREEN_HEIGHT - 1, 0, message);
}

void initialize_screen_buffer() {
  for (int i=0; i<SCREEN_HEIGHT; i++) {
    for (int j=0; j<SCREEN_WIDTH; j++) {
      screen[i][j] = ' ';
    }
  }
}

void write_string_to_buffer(int y, int x, const char *str) {
  int len = strlen(str);
  for (int i; i<len; i++) {
    write_char_to_buffer(y, y+i, str[i]);
  }
}

void write_char_to_buffer(int y, int x, char ch)
{
  if (y >= 0 && y < SCREEN_HEIGHT && x >= 0 && x < SCREEN_WIDTH) {
    screen[y][x] = ch;
  }
}

