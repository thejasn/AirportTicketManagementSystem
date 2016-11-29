
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
static struct termios old,ne;
void initTermios(int echo)
{
    tcgetattr(0,&old);
    ne = old;
    ne.c_lflag &= ~ ICANON; //control modes
    ne.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0,TCSANOW,&ne);
}
void resetTermios(void)
{
    tcsetattr(0,TCSANOW,&old);
}
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}
char getch(int val)
{
    return getch_(val);
} 
