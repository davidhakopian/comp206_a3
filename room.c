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

void initialize_game()
{

}

int drop(int n)
{

}

void play_game()
{

}

void exit_game()
{

}

void refresh_game()
{

}

int main(void)
{
  // FILE *resources;
  printf("Content-type: text/html\n\n");
  printf("Hi from the CGI!\n");

  char string[200];
  char *data = getenv("QUERY_STRING");
  int n = atoi(getenv("CONTENT_LENGTH"));
  fgets(string,n,stdin);

  return 0;
}
