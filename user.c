#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "password.c"
#include "Flight_search.c"
#include "checkin1.c"
#include "delete.c"
struct details
{
	char fname[20];
	char lname[20];
	char nation[20];
	unsigned int age;
	char gender;
	char email[40];
	char password[36];
};
void create_account(struct details *s)
{

	FILE *ptr;
	ptr = fopen("Account.dat", "a");
	int flag = 0, i = 0;
	printf("\nEnter the details\n");
	printf("\nEnter email ID: ");
	scanf("\n%s", s->email);

	while (s->email[i] != '\0')
	{
		if (s->email[i] == '@')
			flag++;
		if (flag == 1 && s->email[i] == '.')
			flag++;
		i++;
	}
	if (flag != 2)
	{
		printf("\n Invalid email ID");
		return;
	}
	printf("\nEnter First name: ");
	scanf("\n%s", s->fname);
	printf("\nEnter Last name:");
	scanf("\n%s", s->lname);
	printf("\nEnter Nationality: ");
	scanf("\n%s", s->nation);
	printf("\nEnter Age: ");
	scanf(" %d", &s->age);
	printf("\nEnter Gender:");
	scanf("\n%c", &s->gender);
	switch (s->gender)
	{
	case 'm':
	case 'M':
	case 'f':
	case 'F':
	case 'o':
	case 'O':
		break;
	default:
		printf("\n Invalid option");
		return;
	}
again:
	printf("\nEnter your password: ");
	strcpy(s->password, get_pass_to_signup());
	int check = check_strength(s->password);
	if (check == 0 )
		goto again;
	fwrite(s, sizeof(*s), 1, ptr);

	fclose(ptr);

}
void display(struct details *s)
{

	FILE *ptr = fopen("Account.dat", "r");
	while (fread(s, sizeof(*s), 1, ptr))
	{
		printf("\nFirst name:- \t%s", s->fname);
		printf("\nLast name:- \t%s", s->lname);
		printf("\nNationality:- \t%s", s->nation);
		printf("\nAge:-   \t%d", s->age);
		printf("\nGender:- \t%c", s->gender);
		printf("\nEmail ID:- \t%s\n", s->email);
	}
	fclose(ptr);
}
void delete(struct details *s)
{
	char del[20];
	int flag = 1;
	FILE *nptr;
	nptr = fopen("New.dat", "w");
	printf("\nEnter your email ID: ");
	scanf("\n%s", del);
	FILE *ptr = fopen("Account.dat", "r");
	while (fread(s, sizeof(*s), 1, ptr))
	{

		if (strcmp(s->email, del) == 0) {
			flag = 0;
			break;
		}
		else fwrite(s, sizeof(*s), 1, nptr);
	}
	fclose(ptr);
	fclose(nptr);
	remove("Account.dat");
	rename("New.dat", "Account.dat");
	if (flag != 1)
		printf("\nAccount deleted\n");
	else
		printf("\n No account");

}
int check_pass(char * user, char *pass)
{
	FILE * fptr = fopen("Account.dat", "r");
	struct details s;
	while (fread(&s, sizeof(struct details), 1, fptr))
	{
		if (strcasecmp(user, s.email) == 0)
		{
			if (strcmp(pass, s.password) == 0)
				return 1;
			else {
				//printf("%s,%sthe\n", pass, s.password);
				return -1;
			}
		}
	}

	return -1;
}
void main()
{
	//display_information("aw 123");
	/* ADD truccation of flight */
	struct details s;
	int ret_val;
	char pass[26];
	char pnr[12];
	int ch;
	int valid = 0;
	char username[20], password[24];
	
	do {
		system("clear");
		system("clear");
		printf("\n 1.Sign-In\n 2.Sign-UP\n 3.Exit");
		//scanf("%d", &ch);
		fflush(stdin);
		ch=getch(0);
		switch (ch)
		{
		case 49:	system("clear");  
				printf("\n\n Username: ");
			scanf("\n%s", username);
			getchar();
			if (strcasecmp("ADMIN", username) == 0) {

				strcpy(password, get_pass_to_signin());
				FILE *fptr = fopen("password.txt", "r");
				while (!feof(fptr))
				{
					fscanf(fptr, "%s", pass);
					if (strcmp(pass, password) == 0){
						admin();
						break;
					}
				}
			}
			else {
				strcpy(password, get_pass_to_signin());
				valid = check_pass(username, password);
				if (valid == -1) {
					printf("\n Incorrect Username or Passwword !!! ");
					printf("\n\n Press Any Key To Retry");
					getchar();
					getchar();
					system("clear");
					break;
				}
				else {
					redo:
					system("clear");

					printf("\n 1.Flight Search\n 2.Online Checkin\n 3.Delete Ticket");
					ch = getch(0);
					if (ch == 49)
						ret_val = search();
					else if (ch == 50)
					{
						printf("\n Enter PNR:");
						scanf("\n%[^\n]", pnr);
						check_in(pnr);
					}
					else if( ch == 51)
					{
						printf("\n Enter PNR:");
						scanf("%[^\n]", pnr);
						deleteseat(pnr);
					}
					else if(ch== 52)
						break;
					else goto redo;
				}
				if(ret_val == -1)
					goto redo;
			}
			break;
		case 50: printf("\n1.To create account\n2.Delete account\n3.Display\n");
			scanf("%d", &ch);
			switch (ch)
			{
			case 1:	create_account(&s);
				break;
			case 2:	delete(&s);
				break;
			case 3: display(&s);
					sleep(15);
				break;
			default: printf("\nWrong choice");
			}
			break;
		case 51: exit(1);
		}
	} while (1);

}

