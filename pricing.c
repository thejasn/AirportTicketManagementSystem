#include <stdio.h>
#include <time.h>

float assign_basic_pay(int seat_no, int no_of_seats)
{
	//business class
	if (no_of_seats == 100) {

		if ( seat_no > 0 && seat_no < 10 && seat_no != 4)
			return 200;
		else if (seat_no >= 10 )
			return 130;
	}
	else {
		if ( seat_no > 0 && seat_no < 29 )
			return 200;
		else
			return 130;
	}

}
time_t difference(struct time t)
{
	struct tm * temp;
	temp->tm_mday = t.dd;
	temp->tm_mon = t.mm - 1;
	temp->tm_year = t.yyyy + 1900;
	temp->tm_hour = t.hrs;
	temp->tm_min = t.min;
	temp->tm_sec = t.sec;
	return mktime(temp);
}
float cheack_time_diff(time_t my_time, struct time flight)
{
	struct tm * now = localtime(&my_time);
	long int days = 0;
	if ((flight.yyyy - (now->tm_year + 1900)) == 0)
	{
		if ((flight.mm - (now->tm_mon + 1)) != 0) {
			days += ((flight.mm - (now->tm_mon + 1)) * 30);
		}
		if ((flight.dd - (now->tm_mday)) != 0) {
			days += (flight.dd - (now->tm_mday));
		}
	}
	else {
		if ((flight.mm - (now->tm_mon + 1)) <= 2) {
			days += (flight.mm) * 30;
			days += (12 - (now->tm_mon + 1)) * 30;
			days -= ((now->tm_mday));
			days += flight.dd;
		}
	}
	//printf("%d\n", days );
	//10 days
	if ( days <= 10) {
		return 100.0;
	}
	//20 days
	else if ( days <= 20)
		return 60;
	//30 days
	else if ( days <= 30)
		return 40;
	//40 days
	else if ( days <= 40)
		return 20;
	// more than 40 days
	else if ( days > 41)
		return 10;
}/*
main()
{
	timing flt;
	flt.dd		= 20;
	flt.mm		= 12;
	flt.yyyy	= 2016;
	flt.hrs		= 14;
	flt.min		= 30;
	flt.sec		= 20;
	//printf("%ld\n", time(NULL) );
	printf("%f\n", cheack_time_diff(time(NULL), flt));
}*/