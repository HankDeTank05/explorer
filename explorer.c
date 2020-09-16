// A game about exploring

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//constants
const bool DEBUG = true;

const int CMD_SIZE = 10;
const int NUM_CMDS = 6;
const char CMDS[6][10] = {"help", "quit", "look", "check", "move", "attack"};
const int HELP = 0;
const int QUIT = 1;
const int LOOK = 2;
const int CHECK = 3;
const int MOVE = 4;
const int ATTACK = 5;

//structs
struct room
{
	int id;
};

struct player
{
	float weapon;
	float protection;
	float maxHealth;
	float health;
	int currentRoom;
};

struct item
{
	char name[20];
	int location; //NOTE: -1 means it's in the player's inventory, [0-9] means it's in a room
};

struct weapon
{
	char name[20];
	int location; //NOTE: -1 means it's in the player's inventory, [0-9] means it's in a room
	float damage; //the amount of damage it does to enemies
};

struct protection
{
	char name[20];
	int location; //NOTE: -1 means it's in the player's inventory, [0-9] means it's in a room
	float protection; //the PERCENT damage it blocks
};

//global variables
struct room map[10];
bool doorways[10][10];
struct player plr;
char command[10];
bool quitFlag = false;
struct weapon sword;
struct protection shield;
struct item items[1];

int main(void)
{
	//functions used
	void init(void);
	void handleCommand(void);

	init();

	while(!quitFlag)
	{
		handleCommand();
	}

	return 0;
}

void init(void)
{
	//functions used
	void generateMap(void);
	void initPlayer(void);

	generateMap();
	initPlayer();
}

void generateMap(void)
{
	//functions used
	void initRooms(void);
	void initItems(void);
	void initEnemies(void);

	//local variables
	int numbers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i, c, d;
	time_t t;

	initRooms();

	//seed the random number generator
	srand((unsigned) time(&t));

	for(i = 0; i < 10; i++)
	{
		if(DEBUG) printf("Room ID: %d\n", i);
		for(c = 0; c < 2; c++)
		{
			//generate random number in the range [0, 9]
			int randomID = rand() % 10;
			//printf("%i\n", randomID);
			//if the id is the same as the current room OR the room ID has been
			//used more than twice...
			while(randomID == i || numbers[randomID] > 2)
			{
				randomID = rand()%10;
			}
			doorways[i][randomID] = true;
			doorways[randomID][i] = true;
		}
	}

	if(DEBUG)
	{
		int this, other;
		printf("   0  1  2  3  4  5  6  7  8  9\n");
		for(this = 0; this < 10; this++)
		{
			printf("%d ", this);
			for(other = 0; other < 10; other++)
			{
				if(doorways[this][other])
				{
					printf(" x ");
				}
				else
				{
					printf("   ");
				}
			}
			printf("\n");
		}
	}

	initItems();
	initEnemies();
}

//initialize the rooms by giving them each a unique id number and setting their connections to -1
void initRooms(void)
{
	//functions used
	void initDoorways(void);

	int this;
	for(this = 0; this < 10; this++)
	{
		map[this].id = this;
	}
}

void initDoorways(void)
{
	//local variables
	int this, other;

	for(this = 0; this < 10; this++)
	{
		for(other = 0; other < 10; other++)
		{
			doorways[this][other] = false;
		}
	}
}

void initItems(void)
{
	//local variables
	int i, location;
	time_t t;

	//assign names to the items
	items[0] = (struct item){"crystal", 0};

	//seed the random number generator
	srand((unsigned) time(&t));

	do
	{
		location = rand() % 10;
	} while(location == 0);

	items[0].location = location;
}

void initEnemies(void)
{
	//TODO: implement initEnemies() method
}

//initialize the player
void initPlayer(void)
{
	plr.weapon = 1.0f;
	plr.protection = 0.1f;
	plr.maxHealth = 3.0f;
	plr.health = 3.0f;
	plr.currentRoom = 0;
}

//handle command processing
void handleCommand(void)
{
	//functions used
	void readCommand(void);
	bool verifyCommand(void);
	void processCommand(void);

	do{
		readCommand();
	} while(!verifyCommand());
	processCommand();
}

//read command
void readCommand(void)
{
	printf("\n-> ");
	scanf("%s", command);
}

//verify command is valid
bool verifyCommand(void)
{
	//local variales
	int i;

	for(i = 0; i < NUM_CMDS; i++)
	{
		if(strcmp(command, CMDS[i]) == 0) return true;
	}
	if(DEBUG) printf("\"%s\" is not a recognized command!\n", command);
	return false;
}

//process the command
void processCommand(void)
{
	//pre-condition: command is valid
	
	//functions used
	void cmd_quit(void);
	void cmd_help(void);
	void cmd_look(void);
	void cmd_check(void);
	void cmd_move(void);
	void cmd_attack(void);

	if(DEBUG) printf("%s\n", command);
	
	//quit command
	if(strcmp(command, CMDS[QUIT]) == 0) cmd_quit();

	//help command
	else if(strcmp(command, CMDS[HELP]) == 0) cmd_help();

	//look command
	else if(strcmp(command, CMDS[LOOK]) == 0) cmd_look();

	//check command
	else if(strcmp(command, CMDS[CHECK]) == 0) cmd_check();

	//move command
	else if(strcmp(command, CMDS[MOVE]) == 0) cmd_move();

	//attack command
	else if(strcmp(command, CMDS[ATTACK]) == 0) cmd_attack();
}

void cmd_quit(void)
{
	if(DEBUG) printf("cmd_quit()\n");
	quitFlag = true;
}

void cmd_help(void)
{
	if(DEBUG) printf("cmd_help()\n");

	//local variables
	int i;
	
	for(i = 0; i < NUM_CMDS; i++)
	{
		printf("\t%s\n", CMDS[i]);
	}
}

//display contents of room and available doorways
void cmd_look(void)
{
	if(DEBUG) printf("cmd_look()\n");
	//TODO: implement cmd_look() method
}

//display the player's inventory
void cmd_check(void)
{
	if(DEBUG) printf("cmd_check()\n");
	//TODO: implement cmd_check() method
	//functions used
	void checkPlayer(void);
	void checkInventory(void);

	checkPlayer();
	checkInventory();
}

void checkPlayer(void)
{//weapon, protection, health, location
	//functions used
	void showHealthBar(void);
	
	printf("--PLAYER--\n");
	showHealthBar();
	printf("Location: Room %d\n", plr.currentRoom);
	printf("Sword strength: %.2f\n", plr.weapon);
	printf("Shield strength: %.2f\n", plr.protection);
}

void showHealthBar(void)
{
	//TODO: implement showHealthBar() method
	//functions used
	void hearts(float health);

	float h;

	printf("[");
	for(h = 0.0f; h < plr.maxHealth; h += 0.25f)
	{
		if(h <= plr.health) printf("=");
		else printf("-");
	}
	printf("]\t");
	printf("%.2f/%.2f\n", plr.health, plr.maxHealth);
	
	hearts(plr.health);
}

void hearts(float health)
{
	//TODO: implement the hearts(float health) method
	
	/* full heart
	 *   __  __
	 *  /  \/  \
	 *  \      /
	 *   \____/
	 *
	 * 3/4 heart
	 *   __ 
	 *  /  \
	 *  \   |__
	 *   \____/
	 *
	 * 1/2 heart
	 *   __
	 *  /  \
	 *  \   |
	 *   \__|
	 *
	 * 1/4 heart
	 *   __
	 *  /  \
	 *  \___|
	 */
}

void checkInventory(void)
{
	//TODO: implement checkInventory() method
	printf("--INVENTORY--\n");
	printf("EMPTY");
	printf("\n");
}

void cmd_move(void)
{
	if(DEBUG) printf("cmd_move()\n");
	//TODO: implement cmd_move() method
	//local variables
	int moveTo, i;
	const int SIZE = 100;
	char input[SIZE];

	//printf("Which room would you like to move to? ");
	fgets(input, SIZE, stdin);

	sscanf(input, "%d", &moveTo);
	if(DEBUG) printf("%d\n", moveTo);

	if(moveTo == plr.currentRoom)
	{
		printf("You are already in room %d.\n", plr.currentRoom);
	}
	else if(moveTo > 9 || moveTo < 0)
	{
		printf("\"%d\" is not a valid room number!\n", moveTo);
	}
	else if(doorways[plr.currentRoom][moveTo] == false)
	{
		printf("You cannot get to room %d from here! (You're in room %d)\n", moveTo, plr.currentRoom);
	}
	else
	{
		plr.currentRoom = moveTo;
		printf("You are now in room %d.\n", plr.currentRoom);
	}
}

void cmd_attack(void)
{
	if(DEBUG) printf("cmd_attack()\n");
	//TODO: implement cmd_attack() method
}
