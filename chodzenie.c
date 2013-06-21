#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE_X 20
#define SIZE_Y 10

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

const char board[SIZE_Y][SIZE_X] =
    {
      {178,177,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {177,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177},
      {176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,177,178}
    };

void draw_board()
{
    int x;
    int y;
    putchar('\e');

    for(y=0;y<SIZE_Y;y++)
    {
        for(x=0;x<SIZE_X;x++)
        {
            putchar(board[y][x]);
        }
        putchar('\n');
    }
}

struct player
{
    unsigned int pos_x;
    unsigned int pos_y;
    char look;
};


struct player play0;


/// UP.....-3272
/// DOWN...-3280
/// LEFT...-3275
/// RIGHT..-3277

void clearScreen()
{
  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
}

int main(int argc, char *argv[])
{

    printf("I wanna play a game...\n");
    clearScreen();
    draw_board();
    char ch;
    putchar('X');
    putchar('X');
    putchar('X');
    putchar('X');
    putchar('X');
    putchar('X');
    putchar('\r');
    while((ch = getch()) != 113)
    {
        draw_board();
    }
    printf("%i", ch);
    return 0;
}
