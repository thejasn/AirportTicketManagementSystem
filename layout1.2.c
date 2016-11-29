#include <stdio.h>
//For domestic flight layout
//void international(int *a1[10]);//For international flight layout
/*Variable Description
i=to iterate rows of seat
j=to iterate coloumns of seat
k=to initialize all seat with integers
parameter=to check whether it is domestic or international
count=to check if the seat is booked or available
choice=to provide the user to book another seat
seat_no=to accept the seat_no from the user
*/


int  international(int *a1[10],int no_of_seats)
{
	int i, j, k = 0, seat_no, count = 0;
	int ctr=0;
	FILE * fptr = fopen("temp_seat","w");
	do
	{
		printf("\nEnter the seat number to be booked\n");
		scanf("%d", &seat_no);
		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				if (a1[i][j] != -1 && a1[i][j] == seat_no) //check if seat is booked or not
				{
					a1[i][j] = -1;
					count=1;
					break;
				}
		if (count ==1)
		{	printf("\nSeat is successfully booked\n");
			ctr++;
			fprintf(fptr,"%d\n",seat_no);
			count = 0;
		}
		else
			printf("\nThis seat is already booked\n");


	} while (ctr<no_of_seats);
	fclose(fptr);
	return 1;
}

int domestic(int *b1[10], int no_of_seats)
{
	int i, j, k = 0, seat_no, count = 0;
	int ctr=0;
/*	char choice = 'y';
	for (i = 0; i < 10; i++)
		for (j = 0; j < 7; j++)
			b1[i][j] = ++k;
			*/
		printf("sdfasd\n");
	FILE * fptr = fopen("temp_seat","w");
	do
	{
		printf("\nEnter the seat number to be booked\n");
		scanf("%d", &seat_no);
		for (i = 0; i < 7; i++)
			for (j = 0; j < 10; j++)
				if (b1[i][j] != -1 && b1[i][j] == seat_no)
				{
					b1[i][j] = -1;
					count=1;
					break;
				}
		if (count == 1)
		{	printf("\nSeat is successfully booked\n");
			ctr++;
			fprintf(fptr,"%d\n",seat_no);
			count =0;
		}
		else
			printf("\nThis seat is already booked\n");

	} while(ctr<no_of_seats);
	fclose(fptr);
	return 1;
}

