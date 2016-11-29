#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "getch.c"
char * get_pass_to_signup()
{
  void gotoxy(int x, int y)
{
  printf("%c[%d;%df", 0x1B, x, y);
}
  char * password = (char*)malloc(26 * sizeof(char));
  char c;
  printf("\n Password: ");
  c=getch(0);
  int a = 10, b = 20, count = 0;
  do
  {
    c = getch(0);
    if (c == '\n')
      break;
    printf("%c", '*');
    password[count++] = c;

  } while (c != '\n');
  password[count] = '\0';
  printf("%c\n",password[count]);
  return password;
}
char * get_pass_to_signin()
{
  char *password = (char*)malloc(sizeof(char) * 26);
  password = getpass(" Password: ");
 
  return password;
}
int check_strength(char * a)
{
  
  int i,digits=0,words=0,spcl=0,l;
  l=strlen(a);
  for(i=0;i<l;i++)
  {
    if(a[i]>='a'&&a[i]<='z'||a[i]>='A'&&a[i]<='Z')
    words++;
    else if(a[i]>='0'&&a[i]<='9')
    digits++;
    else
    spcl++;
  }
  printf("%d",spcl);
  if(l>=6&&digits>=3&&spcl>=1&&words>=4)
    return 1;
  else
    return 0;
}
