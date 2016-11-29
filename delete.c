#include<stdio.h>
//#include"flight_input_v3.c"

void deleteseat(char *pnr)
{


	char confirmation;
	char *flight = (char*)calloc(5, sizeof(char));
	strncpy(flight, pnr, 5);
	int i, j, flag = 0;
	long int p, pos;
	struct passenger obj, obj2;



	FILE *fp = fopen(flight, "r+");
	//printf("\n Enter the seat number to be cancelled\n");
	//int sno;
	//scanf(" %d", &sno);
	while (fread((&obj), sizeof(struct passenger), 1, fp))
	{
		p = ftell(fp);
		for (i = 0; i < obj.no_of_seats; i++)
		{
			if (strcasecmp(pnr, obj.name_list[i].PNR) == 0)
			{
				printf("\n %d will be cancelled\n Confirm(Y/N)\n", obj.name_list[i].seat_no);
				scanf(" %c", &confirmation);
				if (confirmation == 'y' || confirmation == 'Y')
				{
					for (j = i; j < obj.no_of_seats - i; j++)
						obj.name_list[j] = obj.name_list[j + 1];
					obj.no_of_seats -= 1;
					flag = 1;
					pos = p;
					obj2 = obj;
					break;
				}
			}
		}
	}
	/*
	FILE *fp2=fopen("flight.dat","r");
	struct flight f1,f2;
	while(fread(&f1,sizeof(struct flight),1,fp2))
	{
		if(strcasecmp(flight,f1.flight_no)==0)
		{
			pos=ftell(fp2);
			f1.total_booked_seats--;
			f1.empty_seats_in_flight++;
			f2=f1;
			break;
		}
	}
	fseek(fp2,pos-sizeof(struct flight),SEEK_SET);
	fwrite(&f2,sizeof(struct flight),1,fp2);
	*/
	update_booking(flight, -1);
	if (flag == 1)
	{
		fseek(fp, pos - sizeof(struct passenger), SEEK_SET);
		fwrite((&obj2), sizeof(struct passenger), 1, fp);
	}
	else printf("\n Not found\n\n");

	fclose(fp);
}

/*main()
{
	display_information("aw 123");
	deleteseat();
	display_information("aw 123");
}*/
