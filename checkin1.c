#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
/*typedef struct time
{df
    int dd;
    int mm;
    int yyyy;
    int sec;asd
    int min;
    int hrs;
} timing;

struct flight
{
    char flight_no[7];
    char flight_carrier[15];
    char flight_destination[15];
    char flight_departure[15];
    timing dep_time;
    timing arr_time;
    int total_seats_in_flight;
    int total_booked_seats;
    int empty_seats_in_flight;

}*/
    void print_tick(char * pnr)
{
	char * flight_file = (char*)calloc(5, sizeof(char));
	strncpy(flight_file,pnr,5);
	print_ticket(flight_file,pnr);
	sleep(10);
	
}


struct flight flight_search(char * flight_name)
{	struct flight f2;

	FILE *fp;
	fp = fopen("flights.dat", "r");

	while (fread(&f2, sizeof(struct flight), 1, fp))
	{	//r(i=0;i<7;i++)
		//printf("%s,%s\n", flight_name, f2.flight_no);
		if (strcmp(flight_name, f2.flight_no) == 0) {
			//printf("%d\n", f2.dep_time.dd );
			return f2;
		}

	}
}

// struct flight obj1;
int checkin(struct flight obj1)
{
	int checkin_status = 0;

	time_t currenttime;
	time(&currenttime);
	struct tm *mytime = localtime(&currenttime);
	if ((mytime->tm_year + 1900) == obj1.dep_time.yyyy)
		if ((mytime->tm_mon + 1) == obj1.dep_time.mm)
		{	if ((obj1.dep_time.dd) - (mytime->tm_mday) == 2)
			{	if (obj1.dep_time.hrs <= mytime->tm_hour)
					checkin_status = 1;
				else
					checkin_status = 0;

			}
			else if (((obj1.dep_time.dd) - (mytime->tm_mday) < 2) && ((obj1.dep_time.dd) - (mytime->tm_mday) >= 0))
				checkin_status = 1;

			else
				checkin_status = 0;
		}

		else
			checkin_status = 0;
	else
		checkin_status = 0;


	return checkin_status;

}

void check_in(char pnr[])
{	int status = 0;

	char f_name[7];
	strncpy(f_name, pnr, 5);
	//printf("%s\n",f_name );
	struct flight obj = flight_search(f_name);

	status = checkin(obj);
	if(status == 1)
		print_tick(pnr);
	else printf("\nNO ticket found");
}
