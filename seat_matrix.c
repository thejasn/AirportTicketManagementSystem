#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "entry_data1.c"
#include "flight_input_v3.c"
#include "transaction1.c"
#include "linking.1.2.c"
#include "pricing.c"
#define MAX_ROW_DOM 10
#define MAX_COL_DOM 7
#define MAX_ROW_INT 10
#define MAX_COL_INT 10

struct passenger read_passenger_details(char * flight_name)
{
    FILE * fptr = fopen("temp_seat", "r");
    int seats[8], i = 0;
    while (!feof(fptr)) {
        fscanf(fptr, "%d", &seats[i]);
        i++;
    }
    fclose(fptr);
    return data_entry(i - 1, flight_name, seats);

}

void print_ticket(char *flight_name, char *PNR)
{
    FILE *fp = fopen("flights.dat", "r");
    struct flight F2, F;
    struct passenger P;
    int i;
    struct passenger_names P2;
    int flag = 0;
    while (fread(&F2, sizeof(struct flight), 1, fp))
    {
        if (strcmp(flight_name, F2.flight_no) == 0)
        {   flag = 1;
            F = F2;
            break;
        }
    }
    if (flag == 1)
    {
        FILE *fp2 = fopen(F.flight_no, "r");
        while (fread(&P, sizeof(struct passenger), 1, fp2))
        {
            for (i = 0; i < P.no_of_seats; i++)
            {
                if (strcmp(PNR, P.name_list[i].PNR) == 0)
                {
                    P2 = P.name_list[i];
                    flag = 2;
                    break;
                }
            }
        }
    }
    if (flag != 2)
        printf("\n Invalid PNR");
    else {
        printf("\n Flight Number:\t\t %s", F.flight_no);
        printf("\n Source:\t\t %s", F.flight_departure);
        printf("\n Destination:\t\t %s", F.flight_destination);
        //printf("\n
        printf("\nDeparture date:\t\t %d:%d:%d %d/%d/%d", F.dep_time.hrs, F.dep_time.min, F.dep_time.sec, F.dep_time.dd, F.dep_time.mm, F.dep_time.yyyy);
        //printf("\nArrival date:\t\t %d:%d:%d %d/%d/%d", F.arr_time.hrs, F.arr_time.min, F.arr_time.sec, F.arr_time.dd, F.arr_time.mm, obj1.arr_time.yyyy);
        printf("\n PASSENGER DETAILS\n");
        printf("\n First Name:\t\t %s", P2.first_name);
        printf("\n First Name:\t\t %s", P2.middle_name);
        printf("\n Last Name:\t\t %s", P2.last_name);
        printf("\n Seat No:\t\t %d", P2.seat_no);
        printf("\n PNR:\t\t %s",     P2.PNR);
        printf("\n Gender:\t\t %c", P2.gender);
        printf("\n Passport number:\t\t %s", P2.passport_no);
    }
}
int init_seat(char *flight, int no_of_seats, int no_booked_seats, timing flight_time)
{
    system("clear");
    //d//isplayall();
    //getchar();
    // getchar();

    //display_information(flight);
    int to_book_seats, busi_pref, success;
    char busi, choice;
    float basic = 0, time_price;
    seats(flight, no_of_seats);
    //printf("%d\n",no_of_seats);
    if (no_of_seats == 100)
        flight_layout_inter();
    if (no_of_seats == 70)
        flight_layout_domes();
    write_seats_on_layout(no_of_seats);

    printf("\n");
    printf("\n\n\nSeat Layout for flight no: %s", flight);
    printf("\n\n Enter no of seats:");
    scanf("%d", &to_book_seats);
    printf("\n Do you want to fly business: ");
    scanf("\n%c", &busi);
    if (busi == 'y' || busi == 'Y')
        busi_pref = 1;
    else busi_pref = 0;
    //update_booking(flight,to_book_seats);
    printf("%d\n", no_of_seats);
    int price_status = split_algorithm(no_booked_seats, no_of_seats, to_book_seats, busi_pref);

    system("clear");
    if (no_of_seats == 100)
        flight_layout_inter();
    if (no_of_seats == 70)
        flight_layout_domes();
    write_seats_on_layout(no_of_seats);
    sleep(10);
    if (price_status == 1)
    {
        FILE * fptr = fopen("temp_seat", "r");
        int seats[8], i = 0;
        while (!feof(fptr)) {
            fscanf(fptr, "%d\n", &seats[i]);
            //printf("%d\n",seats[i] );
            if (seats[i] != 107)
                basic += assign_basic_pay(seats[i], no_of_seats);
            i++;
        }
        fclose(fptr);
        // basic=assign_basic_pay(to_book_seats);
        time_price = cheack_time_diff(time(NULL), flight_time);
        //printf("\n\n%f,%f\n",basic,time_price);
    }
    else {
        printf("\n Error in Booking. Please try again.");
        return -1;
    }
    // printf("\n Do you want to proceed with the payment:");
    //scanf("\n%c",&choice);
    //if(choice == 'y' || choice == 'Y')
    success = transaction(basic + time_price);
    if (success == -1)
        return -1;
    else if (success == 1)
    {
        //printf("asdf\n");
        struct passenger current = read_passenger_details(flight);
        update_booking(flight, to_book_seats);
        // print_ticket(read_passenger_details(flight));

        int ctr = 0;
        while (ctr < to_book_seats)
        {
            printf("\n Your PNR are :- ");
            printf("\n %s %s: %s",current.name_list[ctr].first_name, current.name_list[ctr].last_name,current.name_list[ctr].PNR );
            //print_ticket(flight, current.name_list[ctr].PNR);
            ctr++;

        }
        fflush(stdout);

        printf("\n Please provide PNR during online check in (48 hrs prior to departure) to print ticket !!!!!!!!!! ");
        sleep(15);
    }
    return 1;
}

