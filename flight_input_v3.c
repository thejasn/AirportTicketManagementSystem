#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
//#include "entry_data1.c"
typedef struct time
{
    int dd;
    int mm;
    int yyyy;
    int sec;
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

};
void enter_flight_details(struct flight *F)
{
    FILE *fp;
    fp = fopen("flights.dat", "a");
    fwrite(F, sizeof(struct flight), 1, fp);
    fclose(fp);
    //fp=fopen("flights.dat", "r");
    //fread((char*)&A, sizeof(struct flight), 1, fp);
    //printf("\n The flight no is: %s \n %s", A.flight_no, F->flight_no);

}
void displayall()
{
    struct flight obj1;
    int i = 0;
    FILE *fp = fopen("flights.dat", "r");
    fread(&obj1, sizeof(struct flight), 1, fp);
    printf("\n %-10s\t%-7s\t%-12s%-15s %-12s\t %-12s\t %3s", "Airline", "Flight no", "Source", "Destination", "Departure", "Arrival", "Total Booked Seats");
    printf("\n----------------------------------------------------------------------------------------------------------");
    while (!feof(fp))
    {
        i++;
        //fread((char*)&A, sizeof(struct flight), 1, fp);
        printf("\n %-15s", obj1.flight_carrier);
        printf("%-15s", obj1.flight_no);
        printf("%-15s", obj1.flight_departure);
        printf("%-14s", obj1.flight_destination);
        printf("%d:%d:%d %d/%d/%d", obj1.dep_time.hrs, obj1.dep_time.min, obj1.dep_time.sec, obj1.dep_time.dd, obj1.dep_time.mm, obj1.dep_time.yyyy);
        printf("\t%d:%d:%d %d/%d/%d", obj1.arr_time.hrs, obj1.arr_time.min, obj1.arr_time.sec, obj1.arr_time.dd, obj1.arr_time.mm, obj1.arr_time.yyyy);
        printf("\t%-4d\n", obj1.total_booked_seats);
        fread(&obj1, sizeof(struct flight), 1, fp);
    }
}

struct flight* flight_data()
{
    struct flight *temp_flight;
    temp_flight = (struct flight*)calloc(1, sizeof(struct flight));
    printf("\n Enter the Airline Carrier:\t");
    scanf(" %[^\n]", temp_flight->flight_carrier);
    printf("\n Enter the flight number:\t");
    scanf(" %[^\n]", temp_flight->flight_no);
    printf("\n Enter source:\t");
    scanf(" %[^\n]", temp_flight->flight_departure);
    printf("\n Enter flight_destination:\t");
    scanf(" %[^\n]", temp_flight->flight_destination);
    printf("\n Enter departure date(dd/mm/yyyy)\t");
    scanf(" %d/%d/%d", &temp_flight->dep_time.dd, &temp_flight->dep_time.mm, &temp_flight->dep_time.yyyy);
    printf("\n Enter departure hh:mm:ss\t");
    scanf(" %d:%d:%d", &temp_flight->dep_time.hrs, &temp_flight->dep_time.min, &temp_flight->dep_time.sec);
    printf("\n Enter arrival date(dd/mm/yyyy)\t");
    scanf(" %d/%d/%d", &temp_flight->arr_time.dd, &temp_flight->arr_time.mm, &temp_flight->arr_time.yyyy);
    printf("\n Enter arrival hh:mm:ss\t");
    scanf(" %d:%d:%d", &temp_flight->arr_time.hrs, &temp_flight->arr_time.min, &temp_flight->arr_time.sec);
    printf("\n Enter total seats in flight\t");
    scanf(" %d", &temp_flight->total_seats_in_flight);
    if (temp_flight->total_seats_in_flight != 70 && temp_flight->total_seats_in_flight != 100)
    {
        printf("\n Invalid dimensions..");
        exit(0);
    }
    printf("\n Enter total booked seats\t");
    scanf(" %d", &temp_flight->total_booked_seats);
    if (temp_flight->total_booked_seats > temp_flight->total_seats_in_flight)
    {
        printf("\n\n Invalid\n");
        exit(1);
    }
    temp_flight->empty_seats_in_flight = temp_flight->total_seats_in_flight - temp_flight->total_booked_seats;
    return temp_flight;
}
void update_booking(char * flight_name, int book_seats)
{

    FILE *fp1, *fp2;
    struct flight obj, obj2;
    struct passenger ob;


    int pos, flag = 0;

    fp2 = fopen("flights.dat", "r+");
    while (fread(&obj, sizeof(struct flight), 1, fp2))
    {
        if (strcmp(obj.flight_no, flight_name) == 0)
        {
            //printf("gejkg\n");
            flag = 1;
            pos = ftell(fp2);
            if (obj.total_booked_seats + book_seats <= obj.total_seats_in_flight)
            {
                fp1 = fopen(flight_name, "r");
                if (fread(&ob, sizeof(struct passenger), 1, fp1 ) == 0)
                {
                    book_seats = -1 * obj.total_booked_seats;
                    fclose(fp1);
                }
                //printf("hel%d\n",book_seats );
                obj.total_booked_seats += book_seats;
            }
            obj.empty_seats_in_flight = obj.total_seats_in_flight - obj.total_booked_seats;
            obj2 = obj;
            break;
        }
    }

    if (flag == 1)
    {
        fseek(fp2, pos - sizeof(struct flight), SEEK_SET);
        fwrite(&obj2, sizeof(struct flight), 1, fp2);
        fclose(fp2);
    }
}


void modifyentries(char fno[7])
{

    FILE *fp = fopen("flights.dat", "r+");
    struct flight obj, obj2;
    int pos, ch, flag = 0;
    while (fread(&obj, sizeof(struct flight), 1, fp))
    {
        if (strcmp(obj.flight_no, fno) == 0)
        {
            //printf("gejkg\n");
            flag = 1;
            pos = ftell(fp);
            printf("\n Re-Enter flight details for modification\n 1.Carrier\t2.Source\t3.Destination\t4.Dep Date\t5.Arr Date\t6.Total Seats\t7.Total booked seats\n");
            scanf("\n%d", &ch);
            switch (ch)
            {
            case 1:
                printf("\n Enter the Airline Carrier:\t");
                scanf(" %[^\n]", obj.flight_carrier);
                break;
            case 2:
                printf("\n Enter source:\t");
                scanf(" %[^\n]", obj.flight_departure);
                break;
            case 3:
                printf("\n Enter flight_destination:\t");
                scanf(" %[^\n]", obj.flight_destination);
                break;
            case 4:
                printf("\n Enter departure date(dd/mm/yyyy)\t");
                scanf("%d/%d/%d", &obj.dep_time.dd, &obj.dep_time.mm, &obj.dep_time.yyyy);
                printf("\n Enter departure hh:mm:ss\t");
                scanf("%d:%d:%d", &obj.dep_time.hrs, &obj.dep_time.min, &obj.dep_time.sec);
                break;
            case 5:
                printf("\n Enter arrival date(dd/mm/yyyy)\t");
                scanf("%d/%d/%d", &obj.arr_time.dd, &obj.arr_time.mm, &obj.arr_time.yyyy);
                printf("\n Enter arrival hh:mm:ss\t");
                scanf("%d:%d:%d", &obj.arr_time.hrs, &obj.arr_time.min, &obj.arr_time.sec);
                break;
            case 6:
                printf("\n Enter total seats in flight\t");
                scanf(" %d", &obj.total_seats_in_flight);
                if (obj.total_seats_in_flight != 70 && obj.total_seats_in_flight != 100)
                {
                    printf("\n Invalid dimensions..");
                    exit(0);
                }
                break;
            case 7:
                printf("\n Enter total booked seats\t");
                scanf(" %d", &obj.total_booked_seats);
                if (obj.total_booked_seats > obj.total_seats_in_flight)
                {
                    printf("\n\n Invalid\n");
                    exit(1);
                }
                obj.empty_seats_in_flight = obj.total_seats_in_flight - obj.total_booked_seats;
                break;
            default:
                printf("\n Enter right option\t");
                break;
            }
            obj2 = obj;
        }
    }
    if (flag == 1)
    {
        fseek(fp, pos - sizeof(struct flight), SEEK_SET);
        fwrite(&obj2, sizeof(struct flight), 1, fp);
        fclose(fp);
    }
}

void admin()
{
    displayall();
    //update_booking("aw 123", 3);
    int ch;
    char fno[7];
    char choice = 'n';
    do
    {
        printf("\n 1.Enter\t2.Modify\t3.Display\t4.Exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            do
            {
                printf("\n Enter next flights details... ");
                enter_flight_details(flight_data());
                printf("\n Enter more?? ");
                scanf(" %c", &choice);
            }
            while (choice == 'y' || choice == 'Y');
            break;
        case 2:
            printf("\n Enter flight number to be modified\n");
            scanf("\n%[^\n]s", fno);
            modifyentries(fno);
            break;
        case 3:
            displayall();
            break;
        case 4:
            getch(0);
            return;
        default:
            printf("\n Right option please");
        }
    }
    while (1);
}
/*
struct time* difference(struct time *t, struct tm *now)
{
    struct time *temp;
    temp->dd = abs(t->dd-now->tm_mday);
    temp->mm = abs (t->mm-now->tm_mon-1);
    temp.yyyy = abs(t->yyyy-(now->tm_year-1900));
    temp.hrs = abs(t->hrs-now->tm_hour);
    temp.min = abs(t->min-now->tm_min);
    temp.sec = abs(t->sec-now->tm_sec);

    return temp;

};
*/
/*
main()
{

  //displayall();
   char choice='n';
    do{
        printf("\n Enter next flights details... ");
        enter_flight_details(flight_data());
        printf("\n Enter more?? ");
        scanf(" %c", &choice);
    }while(choice=='y'||choice=='Y');

    printf("\n All the flights in the file are:\n\n");
    displayall();
}
}*/

//struct flight *F;
//A={"534IC","sdgasdfg","Me"};
//F=&A;
// enter_flight_details(F);

//time_t t, t1;
//t1 = time(NULL);
//t= time(&t1);
//printf(" %d %d", t, t/3600);
//}
/*
struct tm *localtime(const time_t *timer)
timer -- This is the pointer to a time_t value representing a calendar time.

This function returns a pointer to a tm structure with the time information filled in. Following is the tm structure information:

struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          /
   int tm_min;         /* minutes, range 0 to 59           /
   int tm_hour;        /* hours, range 0 to 23            /
   int tm_mday;        /* day of the month, range 1 to 31  /
   int tm_mon;         /* month, range 0 to 11             /
   int tm_year;        /* The number of years since 1900   /
   int tm_wday;        /* day of the week, range 0 to 6
   int tm_yday;        /* day in the year, range 0 to 365
   int tm_isdst;       /* daylight saving time
};

*/
