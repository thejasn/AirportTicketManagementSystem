
#include <string.h>
#include "seat_matrix.c"
//struct to depict the link data
struct flight_links
{
  //char departure_place[15];
  struct flight flight_obj;
  struct flight_links *source;      // source points at the departure_place of the link
  struct flight_links *next_in_level;   // next_in_level points at the next link in the same level

}*central, *level1, *level2;
// three ext pointer to point at three levels
typedef struct flight_links NODE;

//function to allocate memory for each link
NODE * create_node(struct flight obj)
{
  NODE * nptr = (NODE*)calloc(1, sizeof(NODE));
  nptr->source = NULL;
  nptr->next_in_level = NULL;
  strcpy(nptr->flight_obj.flight_no, obj.flight_no);
  strcpy(nptr->flight_obj.flight_carrier, obj.flight_carrier);
  strcpy(nptr->flight_obj.flight_destination, obj.flight_destination);
  strcpy(nptr->flight_obj.flight_departure, obj.flight_destination);
  nptr->flight_obj.dep_time.dd = obj.dep_time.dd;
  nptr->flight_obj.dep_time.mm = obj.dep_time.mm;
  nptr->flight_obj.dep_time.yyyy = obj.dep_time.yyyy;
  nptr->flight_obj.dep_time.sec = obj.dep_time.sec;
  nptr->flight_obj.dep_time.min = obj.dep_time.min;
  nptr->flight_obj.dep_time.hrs = obj.dep_time.hrs;
  nptr->flight_obj.total_seats_in_flight = obj.total_seats_in_flight;
  nptr->flight_obj.total_booked_seats = obj.total_booked_seats;
  nptr->flight_obj.empty_seats_in_flight = obj.empty_seats_in_flight;

  return nptr;
}

/*function insert links into level1
 * central source is the departure_place and the dest_place is the destination place read from the structure
 */
void insert_link_level1(struct flight obj, NODE * cental_source)
{
  NODE * ptr = create_node(obj);
  if (level1 == NULL)
  {
    level1 = ptr;
  }
  else {
    NODE *temp = level1;
    for (temp = level1; temp->next_in_level != NULL; temp = temp->next_in_level);
    temp->next_in_level = ptr;
  }
  ptr->source = cental_source;
}
/* function to insert links into level 2
 * Same logic as above
 */
void insert_link_level2(struct flight obj, NODE * cental_source)
{
  NODE * ptr = create_node(obj);
  if (level2 == NULL)
  {
    level2 = ptr;
  }
  else {
    NODE *temp = level2;

    for (temp = level2; temp->next_in_level != NULL; temp = temp->next_in_level);
    temp->next_in_level = ptr;
  }
  ptr->source = cental_source;
}
//function to assign value to the central link pointer
void assign_central(char dep_place[])
{

  NODE * ptr = (NODE*)calloc(1, sizeof(NODE));
  strcpy(ptr->flight_obj.flight_departure, dep_place);
  central = ptr;
}

/*
 * Function to assign values for links in level 1
 * Logic used : reads flights.dat file and links
 * all flight entries having departure same as input_place
 */
void assign_level1(NODE * cen, char input_place[])
{
  FILE *fp = fopen("flights.dat", "r");
  struct flight temp_obj;
  while (fread(&temp_obj, sizeof(struct flight), 1, fp) != 0)
  {
    if (strcasecmp(temp_obj.flight_departure, input_place) == 0) { //compare input_place and flights departure place

      insert_link_level1(temp_obj, cen);
    }// if true link flights departure place with central
  }
  fclose(fp);
}
/*
 * Function used to assign values for links in level 2
 * Logic used is as above with the exception that
 * that the flight's destination should not be same as the link in level1's source_departure_place
 */
void assign_level2(NODE * lev)
{
  NODE * cur = lev;
  char source_departure_place[15];
  //FILE *fp=fopen("flights.dat","r");
  struct flight temp_obj;
  while (cur != NULL) // travese the entire level1
  {
    strcpy(source_departure_place, cur->flight_obj.flight_departure); //store the level1's departure_place in source_departure_place
    FILE *fp = fopen("flights.dat", "r");
    while (fread(&temp_obj, sizeof(struct flight), 1, fp) != 0) //read flights.dat
    {
      /*
       * compares the source_departure_place(level1's) with the flights.dat data
       * and also compares flight_destination from flights.data and the current link in level1's source, which should not be same.
       */
      if (strcasecmp(temp_obj.flight_departure, source_departure_place) == 0 && strcasecmp(temp_obj.flight_destination, cur->source->flight_obj.flight_departure) != 0)
        insert_link_level2(temp_obj, cur);
    }
    cur = cur->next_in_level;
    fclose(fp);

  }

// fclose(fp);
}
void print_level1(NODE * lev)
{
  NODE *cur;
  if (lev == level1)
    printf("\n Direct Destination List");
  else
    printf("\n Indirect Destination List");
  for (cur = lev; cur != NULL; cur = cur->next_in_level)
  {
    printf("\n %s  ->", cur->source->flight_obj.flight_departure);
    printf(" %s", cur->flight_obj.flight_departure);
  }
}
int print_desired_flights(char user_dest[], timing user_date)
{
  NODE * curr = level2;
  int status = -1;
  int count_flights_found = 0;
  while (curr != NULL)
  {
    if (curr->flight_obj.dep_time.dd == user_date.dd && curr->flight_obj.dep_time.hrs - user_date.hrs > 4 && curr->flight_obj.dep_time.mm == user_date.mm && curr->flight_obj.dep_time.yyyy == user_date.yyyy)
      if (strcasecmp(curr->flight_obj.flight_destination, user_dest) == 0) {

        printf("\n %d. %s", ++count_flights_found, curr->source->source->flight_obj.flight_departure);
        printf(" \t->%s", curr->source->flight_obj.flight_departure);
        printf("\t -> %s", curr->flight_obj.flight_departure);
        printf(" \t( %s|%s )\n", curr->source->flight_obj.flight_carrier, curr->flight_obj.flight_carrier);
        status = count_flights_found;
        /*char *arr[2];
        strcpy(arr[0],curr->source->source->flight_obj.flight_no);
        strcpy(arr[1],curr->source->flight_obj.flight_no);*/
      }
    curr = curr->next_in_level;
  }

  if (status == -1) {
    curr = level1;
    while (curr != NULL)
    {

      if (curr->flight_obj.dep_time.dd == user_date.dd && curr->flight_obj.dep_time.hrs - user_date.hrs > 4 && curr->flight_obj.dep_time.mm == user_date.mm && curr->flight_obj.dep_time.yyyy == user_date.yyyy)
        if (strcasecmp(curr->flight_obj.flight_destination, user_dest) == 0) {
          printf("\n %d. %s", ++count_flights_found, curr->source->flight_obj.flight_departure);
          printf("\t -> %s", curr->flight_obj.flight_departure);
          printf(" \t( %s )\n", curr->flight_obj.flight_carrier);
          status = count_flights_found;
        }
      curr = curr->next_in_level;
    }
  }

  //if(status ==2){



  return status;
}
int recieve_search_parameters(char u_dep[], timing date)
{
  //displayall();

  int status_of_flight_found = -1, flight_choice, no_of_seats, no_of_booked_seats;
  //char *arr[2];
  char u_dest[15];
  int i = 0, return_status;
  NODE * temp;
  struct flight obj;
  central = level1 = level2 = NULL;
  assign_central(u_dep);
  assign_level1(central, u_dep);
  assign_level2(level1);
  print_level1(level1);
  print_level1(level2);

  printf("\n\n\n Enter User Destination:");
  scanf("\n%[^\n]s", u_dest);
  //strcpy(user_destination,"-");

  status_of_flight_found = print_desired_flights(u_dest, date);
  //printf("\n\n%d",status_of_flight_found);
  if (status_of_flight_found == -1) {

    printf("\nFlight not found");
    return -1;
  }
  else
  {
    printf("\n Enter your option:");
    scanf("%d", &flight_choice);
    temp = level2;
    int count_nodes = 0;
    while (temp != NULL)
    {
      if (temp->flight_obj.dep_time.dd == date.dd && temp->flight_obj.dep_time.mm == date.mm && temp->flight_obj.dep_time.yyyy == date.yyyy)
      { //printf("adfg\n");
        if (strcasecmp(temp->flight_obj.flight_destination, u_dest) == 0 && strcasecmp(temp->source->source->flight_obj.flight_departure, u_dep) == 0)
        { ++count_nodes;
          //printf("asd\n");
        }
        //else printf("adfg\n");
      }
      if (count_nodes == flight_choice) {
        printf("%s\n", temp->flight_obj.flight_no);
        no_of_seats = temp->flight_obj.total_seats_in_flight;
        printf("%d\n", no_of_seats );
        no_of_booked_seats = temp->flight_obj.total_booked_seats;
        goto label1;
      }
      temp = temp->next_in_level;
    }

    count_nodes = 0;
    temp = level1;
    while (temp != NULL) {
      if (temp->flight_obj.dep_time.dd == date.dd && temp->flight_obj.dep_time.mm == date.mm && temp->flight_obj.dep_time.yyyy == date.yyyy)
        if (strcasecmp(temp->flight_obj.flight_destination, u_dest) == 0 && strcasecmp(temp->source->flight_obj.flight_departure, u_dep) == 0) {
          printf("asdfaf\n");
          ++count_nodes;
        }

      if (count_nodes == flight_choice) {
        //printf("%s\n",temp->flight_obj.flight_destination);
        no_of_seats = temp->flight_obj.total_seats_in_flight;
        //printf("%d\n",no_of_seats );
        no_of_booked_seats = temp->flight_obj.total_booked_seats;
        break;
      }
      temp = temp->next_in_level;
    }
  }
label1:

  return_status = init_seat(temp->flight_obj.flight_no, no_of_seats, no_of_booked_seats, temp->flight_obj.dep_time);
  return return_status; 
}

