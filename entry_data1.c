#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#define MAX_ROW_SEAT 20
#define MAX_COL_SEAT 10
#define MAX_PASS 100

struct passenger_names {

	char first_name[30];
	char last_name[30];
	char middle_name[30];
	char PNR[10], gender;
	unsigned int age;
	char passport_no[8];
	int seat_no;
};
struct passenger
{

	char destination[15];
	unsigned int booked_flight_no;
	int no_of_seats;
	struct passenger_names name_list[MAX_PASS];
} psng;
void store_information(int seats, char * flight_name)
{	FILE *p;
	//printf("%s\n",flight_name );
	p = fopen(flight_name, "a");
	fwrite(&psng, sizeof(struct passenger), 1, p);
	fclose(p);
}
void display_information(char * flight_name)
{	FILE *p;
	int i = 0;
	struct passenger psng2;
	p = fopen(flight_name, "r");
	if (p != NULL)
	{
		while (fread(&psng2, sizeof(struct passenger), 1, p))
		{

			for (i = 0; i < psng2.no_of_seats; i++)
			{
				printf("\n\n\nFIRST NAME : ");
				printf("%s", psng2.name_list[i].first_name);
				printf("\nMIDDLE NAME : ");
				printf("%s", psng2.name_list[i].middle_name);
				printf("\nLAST NAME : ");
				printf("%s", psng2.name_list[i].last_name);
				printf("\nGENDER(M/F/O) : ");
				printf(" %c", psng2.name_list[i].gender);
				printf("\nAGE : ");
				printf("%d", psng2.name_list[i].age);
				printf("\nPASSPORT NO. : ");
				printf("%s", psng2.name_list[i].passport_no);
				printf("\nSeat : ");
				printf("%d", psng2.name_list[i].seat_no);
				printf("\nPNR. : ");
				printf("%s", psng2.name_list[i].PNR);

			}
		}
	}
	fclose(p);
}
char * generate_pnr(char *flight)
{
	int pnr;
	char pnr_str[26], *flight_name = (char*)malloc(7 * sizeof(char));
	strcpy(flight_name, flight);

	FILE * fp = fopen("PNR", "r");

	fscanf(fp, "%d", &pnr);
	fclose(fp);
	fp = fopen("PNR", "w");
	fprintf(fp, "%d", pnr - 1);
	fclose(fp);
	sprintf(pnr_str, "%d", pnr);
	strcat(flight_name, pnr_str);
	return flight_name;

}
struct passenger data_entry(int seats, char * flight, int a[])
{
	int i;
	//printf("%d\n",seats);
	char *pnr;

	psng.no_of_seats = seats;
	printf("Press enter to enter details !! ");
	getch(0);
	getch(0);
	fflush(stdout);
	fflush(stdin);
	for (i = 0; i < psng.no_of_seats; i++)
	{
		printf("\n\n\nFIRST NAME :");
		scanf("\n%s", psng.name_list[i].first_name);
		printf("\nMIDDLE NAME : ");
		scanf("\n%s", psng.name_list[i].middle_name);
		printf("\nLAST NAME : ");
		scanf("\n%s", psng.name_list[i].last_name);

		printf("\nGENDER(M/F) : ");
		scanf("\n%c", &psng.name_list[i].gender);
		printf("\nAGE : ");
		scanf("%d", &psng.name_list[i].age);
		printf("\nPASSPORT NO. : ");
		scanf("\n%s", psng.name_list[i].passport_no);
		psng.name_list[i].seat_no = a[i];
		pnr = generate_pnr(flight);
		strcpy(psng.name_list[i].PNR, pnr);
		printf("%s\n", psng.name_list[i].PNR);
		//i++;
	}
	store_information(psng.no_of_seats, flight);
	//display_information();
	return psng;
}
