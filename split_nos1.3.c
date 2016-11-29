#include<math.h>
#include<stdlib.h>
#include<stdio.h>
//#include"manual_entry1.3.c"
FILE * fptr ;
#define MAX_ROW 3
#define MAX_COL 10
int no_of_seats;
/*
 *IMPORTANT
 *
 * TODO check ratio of filled to empty to verify if all seats are occupied,
 * else run a linear search for single seats
 */

void compute_split(int,int,int []);
int *split_up(int,short int);
int resolve_combinations(int*,char,int *[]);
int search_seat(int,char,int *a[10]);


//function to compute the div,quotient and the reminder of the arg 'no'
//seat_combo array holds the reminder,quotien and the divisor respectively
void compute_split(int no,int pass,int seat_combo[])
{
    seat_combo[0]=no%pass;                         //no%pass is stored as rem in seat_combo[0]
    seat_combo[1]=(no-seat_combo[0])/pass;         //seat_combo[1] holds the quotient
    seat_combo[2]=pass;                            //seat_combo[2] holds the divisor
}
//int seats_booked[30] = { -1,2,-1,4,5,-1,-1,8,-1,-1,-1,12,-1,14,15,16,-1,-1,19,20,21,-1,23,24,-1,-1,27,-1,29,-1 };

/*
 * function to split the seats based on the no_seats and the trial no.
 * trial no denotes the number of cobinations that have been tried.
 * function returns the base pointer of an array containing the reminder,
 * quotient and the reminder in that specific order.
 *
 * eg:-
 * the combinations are read as follows :
 * if the returned array has the values 1,1,2 for no_seats=3
 * then 1=rem,1=qnt and 2=div. We need to search of div^qnt no of seats i.e here
 * 2 and 1(rem) seperate seat.
 *
 * if array = 0,2,2, then idiv^qnt = 4 this means 2 sets of seats to be booked
 * with both seats being couples.
 */
int * split_up(int no_seats,short int trial_no)
{
    int * seat_combo = (int*)calloc(no_seats,sizeof(int));
    switch(no_seats)
    {
    case 1:
        seat_combo[0]=0;
        seat_combo[1]=1;
        seat_combo[2]=1;
        break;
    case 2:
        if(trial_no==0)
            trial_no=0;
        else trial_no=no_seats-1;
        compute_split(no_seats,no_seats-trial_no,seat_combo);
        break;
    case 3:
        if(trial_no==0)
            trial_no=0;
        else if(trial_no==1)
            trial_no=no_seats/2;
        else if(trial_no==2)
            trial_no=no_seats-1;
        compute_split(no_seats,no_seats-trial_no,seat_combo);
        break;
    case 4:
        if(trial_no==0)
            trial_no=0;
        else if(trial_no==1)
            trial_no=no_seats/2;
        else if(trial_no==2)
            trial_no=1;
        else if(trial_no==3)
            trial_no = no_seats-1;
        compute_split(no_seats,no_seats-trial_no,seat_combo);
        break;
    }
    return seat_combo;
}
/*
 * function to resolve the combinations and call needed fuction to search the
 * seat combo.
 *
 * eg: if the returned values from the function split are 1,1,2 for 2 seats
 *
 * 1 if fails 2 else if is true
 * this calls the search_seat() with the arg as 1
 *
 * 2.1 if is true, this calls the search_seat() with arg as 2
 *
 */
int resolve_combinations(int *ar,char preference,int *seat_mtx[10])
{
    int i,j;
    int status=-1,no_seat;
    
    if(ar[0]==0)                          // 1 if
    {
        if(ar[1]==1)                        // 1.1 if
        {
            no_seat=ar[2];
            if(no_seat==1)
                status= search_seat(no_seat,preference,seat_mtx);
            else if(no_seat==2)
                status = search_seat(no_seat,preference,seat_mtx);
            else    status = search_seat(no_seat,'\0',seat_mtx);
        }
        else if(ar[2]==1)                   //1.1 else if
        {
            int i;
            for(i=0; i<ar[1]; i++)
            {
                status=search_seat(ar[2],preference,seat_mtx);
                if(status==-1)
                {
                    return -1;
                }
                else 	no_of_seats-=ar[1];
            }
        }
        else                                //1.1 else
        {
            int i;
            for(i=0; i<ar[1]; i++)
            {
                status =  search_seat(ar[2],preference,seat_mtx);
                if(status ==-1)
                {
                    return -1;
                }
                else
                    no_of_seats-=ar[1];
            }
        }
    }
    else if(ar[0]==1)                     // 2 else if
    {
        status = search_seat(ar[0],preference,seat_mtx);
        if(status == -1)
        {
            return -1;
        }
        else
        {
            no_of_seats-=ar[0];
        }

        if(ar[1]==1)                      //2.1 if
        {
            status =  search_seat(ar[2],preference,seat_mtx);

        }
    }
    if(status==-1)
        return -1;
    if(status==1)
        return 1;
}
int search_seat(int no_seat,char preference,int *seats_booked[10])
{
    int i,j,status=-1;
    
    fptr = fopen("temp_seat","w");
    switch(no_seat)
    {
    case 1:

        for(i=1; i<MAX_ROW; i++)
            for(j=0; j<MAX_COL; j+=6)
            {
            
                if(seats_booked[j][i]!=-1)
                {
                    fprintf(fptr,"%d\n",((i*10)+(j+1)));
                    seats_booked[j][i]=-1;
                    return 1;
                }
                else if(seats_booked[j+3][i]!=-1)
                {
                    fprintf(fptr,"%d\n",((i*10)+(j+4)));
                    //change later TODO:add with others code
                    seats_booked[j+3][i]=-1;
                    return 1;
                }
            }
        break;
    case 2:
        for(i=1; i<MAX_ROW; i++)
            for(j=1; j<MAX_COL-2; j+=6)
            {
               
                if(seats_booked[j][i]!=-1&&seats_booked[j+1][i]!=-1)
                {
                    fprintf(fptr,"%d\n%d\n",(i*10)+(j+1),(i*10)+(j+2));
                    seats_booked[j][i]=seats_booked[j+1][i]=-1;
                    return 1;
                }
            }
        break;//*/
    case 3:
        for(i=1; i<MAX_ROW; i++)
            for(j=3; j<MAX_COL; j+=10)
            {
                
                if(seats_booked[j][i]!=-1&&seats_booked[j+1][i]!=-1&&seats_booked[j+2][i]!=-1)
                {
                    fprintf(fptr,"%d\n%d\n%d\n",(i*10)+(j+1),(i*10)+(j+2),(i*10)+(j+3));
                    seats_booked[j][i]=seats_booked[j+1][i]=seats_booked[j+2][i]=-1;
                    return 1;
                }
                else if(seats_booked[j+1][i]!=-1&&seats_booked[j+2][i]!=-1&&seats_booked[j+3][i]!=-1)
                {
                    fprintf(fptr,"%d\n%d\n%d\n",(i*10)+(j+1),(i*10)+(j+3),(i*10)+(j+4));
                    seats_booked[j+1][i]=seats_booked[j+2][i]=seats_booked[j+3][i]=-1;
                    return 1;
                }
            }
        break;
    case 4:
        for(i=1; i<MAX_ROW; i++)
            for(j=3; j<MAX_COL; j+=10)
            {
                
                if(seats_booked[j][i]!=-1&&seats_booked[j+1][i]!=-1&&seats_booked[j+2][i]!=-1&&seats_booked[j+3][i]!=-1)
                {
                    fprintf(fptr,"%d\n%d\n%d\n%d\n",(i*10)+(j+1),(i*10)+(j+2),(i*10)+(j+3),(i*10)+(j+4));
                    seats_booked[j][i]=seats_booked[j+1][i]=seats_booked[j+2][i]=seats_booked[j+3][i]=-1;
                    return 1;
                }
            }
        break;
    }
    return -1;
}

int run_algorithm(int seats,int *seat_mtx[10])
{
    int try=0;
    int original_seats=seats;
    no_of_seats=seats;
    //transpose(seat_mtx);
    /*
		 * TODO Add preference only for single seat and double seat even in the
		 * combinations !!!!!!!!!!!
		 */
		//p.name_list=(struct passenger_names*)calloc(p.no_of_seats,sizeof(struct passenger_names));
   // 
         char pref='w'; //= p.name_list[0].seat_preference='w';
    int * hold;
    int status;
    for(;try<no_of_seats;try++)
    {
       hold = split_up(no_of_seats,try);
       status = resolve_combinations(hold,pref,seat_mtx);
       printf("%d seats",no_of_seats);
       printf("try %d \n",try);
       if(status==1){
            fclose(fptr);
          break;
       }
       if(original_seats!=no_of_seats)
       {
          try=0;
          original_seats=no_of_seats;
       }
    }

    if(status ==1)
        return 1;
}
