/*  Author: Jessica Quynh Tran
    Description: room.c 
    - A room begins with 10 gold pieces and 10 manna that is behind
      a challenge. A player who completes the challenge can at most
      take 5 units combined (3 gold, 2 manna; 5 gold, 0 manna, etc.)
    - The amount taken will be deducted from the hidden resource, and
      the next player to enter the room will encounter the updated amount.
    - It takes 1 manna to transport into a new room, this deduction must be
      calculated by this prgoram. If the player has no manna, then it is game
      over. 
    - If the desintation room is occupied, then it will be acknolwedged and ping
      the User and they shall stay where they are.
    - Mana is not used in doing the challenge. It can take as long as they want.
    - Players can convert 2 gold pieces to gain 1 manna from the universe.
    - To win, a player gets 100 gold pieces and is given a victory screen.
    - To exit, type the command EXIT/QUIT.
    - Upon exit, a player's manna and gold is added to the room's resources. 
    - If a player dies, then the game also ends.
    - If the player wins, then the room DOES NOT gain its resources. 

    - On enter, the room is marked as occupied. You may type PLAY to engage with
      the program. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "challenge.h"

// macros
#define BUFFER_SIZE 1024
#define EXIT_SCREEN "<!DOCTYPE html><html><body style=\"background-image: url(\'/assets/seeyou.jpg\')\"></body></html>"
#define INVENTORY_PATH ".././inventory.csv"
#define RESOURCES_PATH ".././resources.csv"
// TODO: make definition for victory screen
// #define VICTORY_SCREEN

// TODO: Is this function necessary?
void initialize_room()
{
  // intialize amount of stuff in resources.csv and make room occupied
  // refresh the page and update the users inventory
  return;
}

/**
 * Utility function to parse the form input data.
 * @param q   Pointer array to store strings
 * @param cmd User stdin command
 */
void parse_query( char** q, char *cmd ) {
  char *query = strtok(cmd, "=&");

  for (int i = 0; query != NULL; i++) {
    q[i] = malloc(strlen(query));
    strcpy(q[i], query);
    query = strtok(NULL, "=&");
  }
}

/**
 * Utility function to print a standard html string with standard
 * variables.
 */
void print_inp_field( char* name, char* type, char* value )
{
  printf("<input name=\"%s\" type=\"%s\" value=\"%s\"/>\n", name, type, value);
}

/**
 * Retrieve requested item from the inventory.
 * 
 * @param  item String that is either "gold"|"manna"
 * @return      amount of the requested item
 */
int get_inventory_item( char* item )
{
  FILE* inventory = fopen(INVENTORY_PATH, "r");
  
  if (inventory == NULL) {
    printf("Error in opening inventory.csv.");
    exit(1);
  }

  int manna, gold;

  fscanf(inventory, "%d,%d", &manna, &gold);
  fclose(inventory);

  return ( strcmp(item, "gold") == 0 ) ? gold : manna;
}

/**
 * Update inventory with values to add or subtract to
 * current player's inventory.
 * 
 * @param manna amount of manna to add/subtract
 * @param gold  amount of gold to add/subtract
 */
void update_inventory( int manna, int gold )
{
  FILE* inventory = fopen(INVENTORY_PATH, "r+");
  
  int manna_r, gold_r;
  fscanf(inventory, "%d,%d", &manna_r, &gold_r);

  manna += manna_r;
  gold += gold_r;

  rewind(inventory);
  fprintf(inventory, "%d,%d \n", manna, gold);
  fclose(inventory);
}

/**
 * Update the room's resource csv file by accepting 3 different 
 * integers to add to the existing file. You can substract 
 * numbers from the integers by passing a negative integer.
 * 
 * @param gold     amount of gold to add/subtract
 * @param manna    amount of gold to add/subtract
 * @param occupied must be binary 1|0 (true|false)
 */
void update_resource( int manna, int gold, int occupied )
{
  FILE* resources = fopen(RESOURCES_PATH, "r+");

  int manna_r, gold_r, occupied_r;
  fscanf(resources, "%d,%d,%d", &manna_r, &gold_r, &occupied_r);

  manna += manna_r; 
  gold += gold_r;

  rewind(resources);
  fprintf(resources, "%d,%d,%d\n", manna, gold, occupied);
  fclose(resources);
}

/**
 * Refresh game while preserving player inventory.
 */
void refresh_game()
{
  // In the browser, the path directory is a little weird?
  FILE *index = fopen(".././index.html", "r+");
  char html[BUFFER_SIZE];

  while( fgets (html, 120, index) != NULL ) {
    if ( strncmp(html, "      <!-- Inventory -->", 24) == 0 ) {

      printf(html);
      fgets(html, 120, index);

      char invent_str[80];
      int manna = get_inventory_item("manna");
      int gold = get_inventory_item("gold");
      sprintf(invent_str, "%d,%d", manna, gold);

      print_inp_field("inventory", "hidden", invent_str);
    } else {
      printf(html);
    }
  }

  fclose(index);
}

/**
 * Drop amount of gold to convert to manna.
 * 
 * @param gold_n number of gold the user wants to convert.
 */
void drop( int gold_n )
{
  // If player tries to drop less than 2 gold.
  if (gold_n < 2) {
    printf("You must drop at least 2 gold to recieve 1 manna.");
    return;
  }

  // If player does not have enough gold.
  if (get_inventory_item("gold") < gold_n) {
    printf("You do not have that much gold to drop.");
    return;
  }

  // If player drops an odd amount of gold.
  if (gold_n % 2 != 0) {
    gold_n--;
  }

  // Calculate manna to subtract from user
  int manna_n = (gold_n / 2);

  update_inventory( manna_n, (gold_n * -1) );
  refresh_game();
  // TODO: notify user that they successfully converted
}



/**
 * Empties players inventory to room resources and shows
 * the exit screen.
 */
void exit_game()
{
  int manna_p = get_inventory_item("manna");
  int gold_p = get_inventory_item("gold");
  update_resource(manna_p,gold_p,0);
  update_inventory(-manna_p,-gold_p);
  printf("%s", EXIT_SCREEN);
}

// TODO: print out errors and output to user in nice format!
// error handling 
// void print_from_server()
// {
  
// }

/**
 * Function to delegate command functions.
 * @param cmd User input stdin.
 */
void execute_command( char* cmd ) 
{
  if (strncmp(cmd, "play", 4) == 0) {

    printf("Welcome to Ferenginar, space explorer! Enter heads or tails on that bit of gold-pressed latinum (i.e. let's flip a coin) and see if the Rules of Acquisition are in your favour!\n");
    
    int userResult = challenge( char* cmd );
    if (userResult == 0) {
        printf("Your guess was incorrect. You lose.\n");
        //Don't have to do anything to inventory
    }
    else {
        printf("Your guess was correct! You win!\n");
        //Update user's inventory with two gold or whatever
    }

  } else if (strncmp(cmd, "drop", 4) == 0) {

    char *amount = strtok(cmd, "+");      /* Copy pointer over with delimiter */    
    amount = strtok(NULL, "+");           /* Get second item in string */
    drop(atoi(amount));                   /* Call function to drop amount */
  
  } else if (strncmp(cmd, "refresh", 7) == 0) {

    refresh_game();

  } else if (strncmp(cmd, "quit", 4) == 0 ||
             strncmp(cmd, "exit", 4) == 0) {

    exit_game();

  } else {
    // TODO: warn as opposed to exit(1)
    printf("Invalid input command\n");
    exit(1);
  }
}

/** Main function */
int main()
{
  char cmd[BUFFER_SIZE];
  int length = atoi(getenv("CONTENT_LENGTH")) + 1;

  fgets(cmd, length, stdin);

  // Print content header
  printf("Content-type: text/html\n\n");

  // Parse the form input string
  char* query[30];
  parse_query(query, cmd);

  // Figure out what do with the input string
  for (int i = 0; query[i] != NULL; i++) {
    if (strcmp(query[i], "user-command") == 0) {
      i++;
      execute_command(query[i]);
    } 
    // TODO: ????
    // else if (strcmp(query[i], "inventory") == 0) {
    //   printf("</br>Do something with inventory!");
    // }
  }

  exit(0);
}

