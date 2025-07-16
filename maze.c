#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int max_x, max_y;

int write_status(char *message)
{
  mvprintw(max_y -1, 0, message);
}

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

  keypad(stdscr, TRUE); // enables the keypad which will allow us to use arrow keys

  // main input loop
  while ((ch = getch()) != 'q') {

    clear();
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(0, 0, "Text Based Cursor Movement - Press q to quit.");
    mvprintw(1, 0, "Use arrow keys to move the @ cursor.");

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
    if (next_y >= max_y) next_y = max_y - 1;
    if (next_x < 0) next_x = 0;
    if (next_x >= max_x) next_x = max_x - 1;

    if (next_x >= obstacle_x && next_x < obstacle_x + obstacle_width &&
      next_y >= obstacle_y && next_y < obstacle_y + obstacle_height) {
      // we are blocked
      write_status("We are blocked!");
    } else {
      // update the coordinates so movement can happen
      x = next_x;
      y = next_y;
    }

    mvprintw(y, x, "@");  // move to the coordinates set in the switch statement
    refresh();
  }

  endwin();   // restore the terminal before exiting

  return 0;
}

