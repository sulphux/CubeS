#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#define WINDOWS

#ifdef LINUX
#define CLR "clear"
#endif // LINUX

#ifdef WINDOWS
#define CLR "cls"
#endif // WINDOWS

#define SIZE_X 20
#define SIZE_Y 10

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
        putchar('Y');
    }
        printf("%i", ch);
    return 0;
}
