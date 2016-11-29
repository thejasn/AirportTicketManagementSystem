#include<stdio.h>
#include<string.h>
#include<ctype.h>

struct time_dat
{
	short int hr:5;
	short int min:6;
};
struct passenger_names{

	char first_name[30];
	char last_name[30];
	char middle_name[30];
	char seat_preference;
};
struct passenger
{
	struct passenger_names * name_list;
	char destination[3];
	unsigned int booked_flight_no;
	char PNR[6],gender;
	unsigned int age;
	long passport_no;
	int no_of_seats;
};
