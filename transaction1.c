#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
int length(unsigned long long x) {

	if (x > 999999999999999 && x < 10000000000000000)
		return 16;
	else if (x > 99 && x < 1000)
		return 3;
	else return -1;

}
int transaction(float amount_total)
{	unsigned long long cd_number;
	int len;
	char cd_name[20];
	unsigned int cd_cvv;
	char ch_trans;
	int OTP;
	system("clear");
	printf("\n\n   Bill Amount: %f", amount_total);
	printf("\n   Do you want to proceed to payment (y/n): ");
	scanf("\n%c", &ch_trans);
	//printf("AMOUNT %f\npress (y|Y) to complete transaction\npress (n|N) to exit",amount_total);

	if (ch_trans == 'Y' || ch_trans == 'y')
	{	system("clear");
		do
		{
			printf("\n  Enter 16 digit credit card number:");
			scanf("%llu", &cd_number);
			len = length(cd_number);
			//printf("%d\n",len);
		} while (len != 16);
		printf("\n  Enter card holder name");
		scanf("%s", cd_name);
		do
		{	printf("\n  Enter CVV number");
			scanf("%d", &cd_cvv);
			len = length(cd_cvv);
		} while (len != 3);
		printf("\n  Enter OTP");
		scanf(" %d", &OTP);
		getchar();
		//system("clear");
		printf("\n\t\tTRANSACTION IN PROGRESS...\n");
		sleep(5);
		printf("\n\t\tTRANSACTION SUCCESSFUL\n \n%f RS is deducted from your card.", amount_total);
		getchar();
		return 1;
	}
	else
		return -1;
}

