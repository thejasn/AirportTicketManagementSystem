#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "flights_relation.c"
#include "show_cal.c"


int get_search_parameters()
{
  timing user_dep;
  char *dep_date;
  struct flight obj_to_display;
  char user_carrier[15], user_destination[15], user_departure[15];

  printf(" \n Enter User Departure:");
  scanf("\n%[^\n]s", user_departure);
  printf("\n Enter Departure Date:");
  getchar();
  dep_date = move_cal();
  sscanf(dep_date, "%d/%d/%d", &user_dep.dd, &user_dep.mm, &user_dep.yyyy);
  time_t user_time;
  time(&user_time);
  char * u_time = (char*)calloc(30, sizeof(char));
  strcpy(u_time, ctime(&user_time));
  sscanf(u_time, "%*s %*s %*d %d:%d:%d %*s %*d", &user_dep.hrs, &user_dep.min, &user_dep.sec);
  //printf("%d/%d/%d",user_dep.hrs,user_dep.min,user_dep.sec);
  int return_val = recieve_search_parameters(user_departure, user_dep);
  return return_val;
}
int search()
{

  system("clear");
  return get_search_parameters();

}