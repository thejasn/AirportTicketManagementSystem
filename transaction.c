#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int  transaction(float amount_total)
{	double cd_number;
	char cd_name[20];
	int cd_cvv;
	char ch_trans;
	int OTP;
	//system("clear");
	printf("AMOUNT %f\npress (y|Y) to complete transaction\npress (n|N) to exit", amount_total);
	scanf(" %c", &ch_trans);
	if (ch_trans == 'Y' || ch_trans == 'y')
	{	system("clear");
		printf("\nenter credit card number:");
		scanf("%d", &cd_number);
		printf("\nenter card holder name");
		scanf("%s", cd_name);
		printf("\nenter CVV number");
		scanf(" %d", &cd_cvv);
		printf("\nenter OTP");
		scanf(" %d", &OTP);
		system("clear");
		printf("\n\t\tTRANSACTION IN PROGRESS...\n");
		sleep(5);
		printf("\n\t\tTRANSACTION SUCCESSFUL\n \n%f$ is deducted from your card\n", amount_total);
		return 1;
	}
	else
		return -1;
}

