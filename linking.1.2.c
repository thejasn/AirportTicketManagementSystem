#include <stdio.h>
#include <stdlib.h>

#include "layout1.2.c"
#include "split_nos1.3.c"
#include <math.h>
int *seat_mtx[10];
void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, x, y);
}

int split_algorithm(int booked_seats, int tot_seats, int to_book_seats,int busi)
{
    int price_flag;
    if (busi == 0 && tot_seats ==100)
    {
        price_flag = run_algorithm(to_book_seats, seat_mtx);

    }
    else 
    {   if(tot_seats==100)
        price_flag =  international(seat_mtx, to_book_seats);
        else price_flag =  domestic(seat_mtx, to_book_seats);
        //if(tot_seats==100)
    }
    return price_flag;
}
void flight_layout_inter()
{

    /*
      3,28 - A
      */
    printf("\t              ________________________________________________________________________________________________   \n\t");
    printf("            ~~                                                                                                    \n\t");
    printf("        ~~       A                                                                                                \n\t");
    printf("     ~~          B                                                                                                \n\t");
    printf("   ~~            C                                                                                                 \n\t");
    printf(" ~~                                                                                                               \n\t");
    printf("~~               D                                                                                                \n\t");
    printf("~                E                                                                                                \n\t");
    printf("~                F                                                                                                \n\t");
    printf("~~               G                                                                                                \n\t");
    printf(" ~~                                                                                                               \n\t");
    printf("   ~~            H                                                                                                \n\t");
    printf("     ~~          J                                                                                                \n\t");
    printf("        ~~       K                                                                                                 \n\t");
    printf("           ~~ ____________________________________________________________________________________________________\n\t");

}
void flight_layout_domes()
{

    /*
      3,28 - A
      */
    printf("\t              ________________________________________________________________________________________________   \n\t");
    printf("            ~~                                                                                                    \n\t");
    printf("        ~~       A                                                                                                \n\t");
    printf("     ~~          B                                                                                                \n\t");
    printf("   ~~                                                                                                             \n\t");
    printf(" ~~                                                                                                               \n\t");
    printf("~~               C                                                                                                \n\t");
    printf("~                D                                                                                                \n\t");
    printf("~                E                                                                                                \n\t");
    printf("~~                                                                                                               \n\t");
    printf(" ~~                                                                                                               \n\t");
    printf("   ~~            F                                                                                                \n\t");
    printf("     ~~          G                                                                                                \n\t");
    printf("        ~~                                                                                                        \n\t");
    printf("           ~~ ____________________________________________________________________________________________________\n\t");

}
//display_information();
void write_seats_on_layout(int no_of_seats)
{
    int i, j, x = 4, y = 32, row_limit, space;
    gotoxy(3, 32);
    if (no_of_seats == 70) {
        space = 5;
        row_limit = 7;
    }
    else {
        space = 6;
        row_limit = 10;
    }
    for (i = 0; i < row_limit ; i++, x++)
    {
        for (j = 0; j < 10; j++)
        {
            if (*(*(seat_mtx + i) + j) == 0)
                printf("\t\t");
            else printf("%d\t", *(*(seat_mtx + i) + j));
        }
        printf("\n");

        if ( x == space  || x == space+5 )
        {
            if (no_of_seats == 70)
                x += 2;
            else        x++;
        }
        gotoxy(x, 32);
    }


}
void seats(char *flight, int tot_seats)
{
    struct passenger psg;
    int i, j, ctr = 1,k=0;
    if (tot_seats == 70) {
        ctr = 1;
        for (i = 0; i < 7; i++)
            *(seat_mtx + i) = (int*)calloc(10, sizeof(int));

        /*for (i=0;i<7;i++)
        {
            if( i==0 || i==3 || i==9)
                ctr++;
            else seat_mtx[i][0] = ctr++;
        }
        ctr=11;
        */
        for (i = 0; i < 10; i++)
            for (j = 0; j < 7; j++) {
                *(*(seat_mtx + j) + i) = ctr++;
            }
    }
    else {
        ctr = 1;
        for (i = 0; i < 10; i++)
            *(seat_mtx + i) = (int*)calloc(10, sizeof(int));

        for (i = 0; i < 10; i++)
        {
            if ( i == 0 || i == 3 || i == 9)
                ctr++;
            else seat_mtx[i][0] = ctr++;
        }
        ctr = 11;

        for (i = 1; i < 10; i++)
            for (j = 0; j < 10; j++) {
                *(*(seat_mtx + j) + i) = ctr++;
            }
    }
    //printf("hello\n");
    if(tot_seats == 100){
    FILE * fptr = fopen(flight,"r");
    //printf("hello\n");
    int seat_no, temp;
    while (fread(&psg, sizeof(struct passenger), 1, fptr))
    {

        for (i = 0; i < psg.no_of_seats; i++) {
            seat_no = psg.name_list[i].seat_no;
            //printf("%d\n",psg.name_list[i].seat_no );
            if (seat_no % 10 == 0)
                temp = ((seat_no - (seat_no % 10)) / 10) - 1  ;
            else
                temp = (seat_no - (seat_no % 10)) / 10  ;

            if (seat_no % 10 == 0)
                *(*(seat_mtx + 9) + temp) = -1;
            else
                *(*(seat_mtx + (seat_no % 10) - 1) + temp ) = -1;
        }

    }
    fclose(fptr);
    }
    else{

        FILE * fptr = fopen(flight,"r");
    //printf("hello\n");
    int seat_no, temp;
    while (fread(&psg, sizeof(struct passenger), 1, fptr))
    {

        for (i = 0; i < psg.no_of_seats; i++) {
            seat_no = psg.name_list[i].seat_no;
            //printf("%d\n",psg.name_list[i].seat_no );
            for (k = 0; k < 10; k++)
            for (j = 0; j < 7; j++) {
                if( *(*(seat_mtx + j) + k) == seat_no)
                    *(*(seat_mtx + j) + k) = -1;
            }
        }

    }
    fclose(fptr);

    }


}
