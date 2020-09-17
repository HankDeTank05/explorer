// A game about exploring

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//constants
const bool DEBUG = false;

const int CMD_SIZE = 10;
const int NUM_CMDS = 7;
const char CMDS[7][10] = {"help", "quit", "look", "check", "move", "attack", "take"};
const int HELP = 0;
const int QUIT = 1;
const int LOOK = 2;
const int CHECK = 3;
const int MOVE = 4;
const int ATTACK = 5;
const int TAKE = 6;

const int NUM_ENEMY_NAMES = 3;
const char ENEMY_NAMES[3][10] = {"bat", "monster", "skeleton"};
const float ENEMY_HEALTH[3] = {1.0f, 4.0f, 2.0f};
const int BAT = 0;
const int MONSTER = 1;
const int SKELETON = 2;

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

struct enemy
{
	const char name[20];
	int location; //NOTE: -1 means it's in the player's inventory, [0-9] means it's in a room
	float health;
};

//global variables
int numRooms = 10;
struct room gMap[10];

int lenDoorways = 10;
bool gDoorways[10][10];

struct player gPlayer;

char gCommand[10];

bool gQuitFlag = false;

int numItems = 1;
struct item gItems[1];

int numEnemies = 5;
struct enemy gEnemies[5];

int main(void)
{
	//functions used
	void init(void);
	void handleCommand(void);

	init();

	while(!gQuitFlag)
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
			gDoorways[i][randomID] = true;
			gDoorways[randomID][i] = true;
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
				if(gDoorways[this][other])
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
		gMap[this].id = this;
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
			gDoorways[this][other] = false;
		}
	}
}

void initItems(void)
{
	//local variables
	int i, location;
	time_t t;

	//assign names to the items
	gItems[0] = (struct item){"crystal", 0};

	//seed the random number generator
	srand((unsigned) time(&t));

	do
	{
		location = rand() % 10;
	} while(location == 0);

	gItems[0].location = location;
}

void initEnemies(void)
{
	//TODO: implement initEnemies() method
}

//initialize the player
void initPlayer(void)
{
	gPlayer.weapon = 1.0f;
	gPlayer.protection = 0.1f;
	gPlayer.maxHealth = 3.0f;
	gPlayer.health = 3.0f;
	gPlayer.currentRoom = 0;
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

//read a command
void readCommand(void)
{
	printf("\n-> ");
	scanf("%s", gCommand);
}

//verify that the command is valid
bool verifyCommand(void)
{
	//local variales
	int i;

	for(i = 0; i < NUM_CMDS; i++)
	{
		if(strcmp(gCommand, CMDS[i]) == 0) return true;
	}
	if(DEBUG) printf("\"%s\" is not a recognized command!\n", gCommand);
	return false;
}

//process the command
void processCommand(void)
{
	//pre-condition: gCommand is valid
	
	//functions used
	void cmd_quit(void);
	void cmd_help(void);
	void cmd_look(void);
	void cmd_check(void);
	void cmd_move(void);
	void cmd_attack(void);
	void cmd_take(void);

	if(DEBUG) printf("%s\n", gCommand);

	//quit command
	if(strcmp(gCommand, CMDS[QUIT]) == 0) cmd_quit();

	//help command
	else if(strcmp(gCommand, CMDS[HELP]) == 0) cmd_help();

	//look command
	else if(strcmp(gCommand, CMDS[LOOK]) == 0) cmd_look();

	//check command
	else if(strcmp(gCommand, CMDS[CHECK]) == 0) cmd_check();

	//move command
	else if(strcmp(gCommand, CMDS[MOVE]) == 0) cmd_move();

	//attack command
	else if(strcmp(gCommand, CMDS[ATTACK]) == 0) cmd_attack();

	//take command
	else if(strcmp(gCommand, CMDS[TAKE]) == 0) cmd_take();
}

void cmd_quit(void)
{
	if(DEBUG) printf("cmd_quit()\n");
	gQuitFlag = true;
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

//display contents of room and available gDoorways
void cmd_look(void)
{
	if(DEBUG) printf("cmd_look()\n");
	//TODO: implement cmd_look() method
	
	//local variables
	int i;

	//check the items array to see what's in the current room
	printf("--ITEMS--\n");
	for(i = 0; i < numItems; i++)
	{
		if(gItems[i].location == gPlayer.currentRoom)
		{
			printf("\t%s\n", gItems[i].name);
		}
	}
	printf("\n");

	//check the enemies array to see what's in the current room
	printf("--ENEMIES--\n");
	for(i = 0; i < numEnemies; i++)
	{
		if(gEnemies[i].location == gPlayer.currentRoom)
		{
			//printf("\t%s\t%f HP\n", gEnemies[i].name, gEnemies[i].health);
		}
	}
	printf("\n");

	//check the doorways lookup table to see what doorways are here
	printf("--DOORWAYS--\n");
	for(i = 0; i < lenDoorways; i++)
	{
		if(gDoorways[gPlayer.currentRoom][i])
		{
			printf("\tRoom %d\n", i);
		}
	}
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
	printf("Location: Room %d\n", gPlayer.currentRoom);
	printf("Sword strength: %.2f\n", gPlayer.weapon);
	printf("Shield strength: %.2f\n", gPlayer.protection);
	printf("\n");
}

void showHealthBar(void)
{
	//TODO: implement showHealthBar() method
	//functions used
	void hearts(float health);

	float h;

	printf("[");
	for(h = 0.0f; h < gPlayer.maxHealth; h += 0.25f)
	{
		if(h <= gPlayer.health) printf("=");
		else printf("-");
	}
	printf("]\t");
	printf("%.2f/%.2f\n", gPlayer.health, gPlayer.maxHealth);
	
	hearts(gPlayer.health);
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
	//local variables
	int i;

	printf("--INVENTORY--\n");
	for(i = 0; i < numItems; i++)
	{
		if(gItems[i].location == -1)
		{
			printf("\t%s\n", gItems[i].name);
		}
	}
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

	if(moveTo == gPlayer.currentRoom)
	{
		printf("You are already in room %d.\n", gPlayer.currentRoom);
	}
	else if(moveTo > 9 || moveTo < 0)
	{
		printf("\"%d\" is not a valid room number!\n", moveTo);
	}
	else if(gDoorways[gPlayer.currentRoom][moveTo] == false)
	{
		printf("You cannot get to room %d from here! (You're in room %d)\n", moveTo, gPlayer.currentRoom);
	}
	else
	{
		gPlayer.currentRoom = moveTo;
		printf("You are now in room %d.\n", gPlayer.currentRoom);
	}
}

void cmd_attack(void)
{
	if(DEBUG) printf("cmd_attack()\n");
	//TODO: implement cmd_attack() method
}

void cmd_take(void)
{
	if(DEBUG) printf("cmd_take()\n");
	//TODO: implement cmd_take() method
	//local variables
	int i;
	const int SIZE = 100;
	char takeItem[SIZE];

	//read the argument of the take command
	fgets(takeItem, SIZE, stdin);
	sscanf(takeItem, "%s", takeItem);

	if(DEBUG) printf("takeItem = %s\n", takeItem);
	
	//loop over the items list to see if the specified item exists in this room
	for(i = 0; i < numItems; i++)
	{
		if(strcmp(gItems[i].name, takeItem) == 0 && gItems[i].location == gPlayer.currentRoom)
		{
			gItems[i].location = -1;
			printf("%s is now in your inventory!\n", gItems[i].name);
			break;
		}
	}
}