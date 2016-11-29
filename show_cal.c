#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
//#include "getch.c"
void cal(char cal[])
{
  //system("clear");
  //gotoxy(20,20);
  system(cal);
}
int init_no_days(int month)
{
  int no_days_in_month;
  //TODO independence of leap year

  if (month == 1)
    no_days_in_month = 28;
  else if (month <= 6) {
    if (month % 2 == 0)
      no_days_in_month = 31;
    else no_days_in_month = 30;
  }
  else if (month > 6) {
    if (month % 2 == 0)
      no_days_in_month = 30;
    else no_days_in_month = 31;
  }
  return no_days_in_month;
}
char * move_cal()
{
  void gotoxy(int x, int y)
  {
    printf("%c[%d;%df", 0x1B, x, y);
  }

  int redo_status = -1;

  int count_month = 0, in_day;
  char day_in;
  char str_month[2], str_year[4], cal_arg[12];

  time_t now;
  struct tm*today_month;
  int no_days_in_month, month, year;
  int in_key;
redo:
  now = time(NULL);
  today_month = localtime(&now);
  month = today_month->tm_mon;
  year = today_month->tm_year + 1900;
  count_month = 0;
  if (redo_status == 1)
    getch(0);
  do {
    no_days_in_month = init_no_days(month + count_month + 1);
    sprintf(str_month, "%d", month + 1 + count_month);
    sprintf(str_year, "%d", year);
    strcpy(cal_arg, "cal");
    strcat(cal_arg, " ");
    strcat(cal_arg, str_month);
    strcat(cal_arg, " ");
    strcat(cal_arg, str_year);
    printf("\n");
again:
    cal(cal_arg);
    printf("\n Press 'd' to go to next month / Press 'r' to reset calender / Enter date to select :");
    in_key = getch(0);
    if (in_key == 127)
    {
      goto again;
    }
    if (in_key == 100 || in_key == 68)
    { in_key = 100;
      if (month + 1 + count_month == 11) {
        ++year;
        count_month = 0;
        month = 0;
      }
      else  ++count_month;
      gotoxy(4, 2);
    }
    if (in_key == 114 || in_key == 82) {
      in_key = 114;
      gotoxy(4, 2);
      goto redo;
    }
  } while (in_key == 100 || in_key == 114);
  //if (in_key < 48 || in_key > 57 )
  //goto again;
  printf("%c", in_key);
  scanf("%c", &day_in);
  if (isspace(day_in))
    in_day = in_key - '0';
  else  in_day = (int)(in_key - '0') * 10 + (day_in - '0');
  month = month + 1 + count_month;
  if ( (in_day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 )) || (in_day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)))
  {
    redo_status = 1;
    goto redo;
  }
  char *date = (char*)malloc(15 * sizeof(char));
  sprintf(date, "%d/%d/%d", in_day, month, year);
  return date;
}


