#ifndef KONSOLA_H
#define KONSOLA_H

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static struct termios old, new;

void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

char getch(void)
{
  return getch_(0);
}

char getche(void)
{
  return getch_(1);
}

void clearScreen()
{
  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
  printf("\033c          \n");
  //printf(CLEAR_SCREE_ANSI);
}

#endif // KONSOLA_H
