/*************************A3.c****************************
Student Name: Akhmed Rakhmati                Student Number:  0837661
Date: Mar 12, 2014                            Course Name: CIS*2500*0103
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct room
{
    int yDim;
    int xDim;
    int locOfEDoor;
    int locOfWDoor;
    int locOfSDoor;
    int locOfNDoor;
    char **stuff;
    int monsterY[100];
    int monsterX[100];
    int mCount;
    int thingCount;
    int thingY[200];
    int thingX[200];
    
    int yDimSave;
    int xDimSave;
    int locOfEDoorSave;
    int locOfWDoorSave;
    int locOfSDoorSave;
    int locOfNDoorSave;
    int thingYSave[200];
    int thingXSave[200];
    char thingSave[200];
    int monsterYSave[100];
    int monsterXSave[100];
    char monsterSave[100];
};

struct player
{
    int gold;
    int potion;
    /*weapon possesion*/
    int weaponPos;
    int wield;
    
    int weaponRand;
    int potionActive;
    int health;
    int orc;
    int ice;
    int gob;
    int orcTotal;
    int iceTotal;
    int gobTotal;
    int orcCount;
    int move;
    int repeat;
    char *weapon;
    
    int saved;
    int genRandom;
    int playAgain;
    
    int goldSave;
    int potionSave;
    int weaponPosSave;
    int wieldSave;
    int weaponRandSave;
    int potionActiveSave;
    int healthSave;
    int orcSave;
    int iceSave;
    int gobSave;
    int orcTotalSave;
    int iceTotalSave;
    int gobTotalSave;
    int orcCountSave;
    int moveSave;
    int repeatSave;
    char *weaponSave;
    
    int xSave;
    int ySave;
};


/*welcomes the player and prints out the controls*/
void begin();

/*opens the file and copies all 6 lines, each one into a separate pointer*/
void openInFile(char *pointer1, char *pointer2, char *pointer3, char *pointer4, char *pointer5, char *pointer6, int argc, char **argv);

/*breaks down the line into smaller parts*/
void parser(char *inpStr, struct room *data);

/*initializes ncurses and colors*/
void startCurses();

/*draws the room and the stuff inside in based on the values it got from parser()*/
void room(struct room *data, struct player *info, int y, int x);

/*prints out the things in the room*/
void printStuff(char thing, struct player *info);

/*gets the y-dimensions of the room and returns it to room()*/
int yDimension(char *dimensions);

/*gets x-dimensions of the room and returns it room()*/
int xDimension(char *dimensions);

/*gets y-coordinate of the east door and returns it to room()*/
int eastDoor(char *eDoor);

/*gets y-coordinate of the west door and returns it to room()*/
int westDoor(char *wDoor);

/*gets x-coordinate of the north door and returns it to room()*/
int southDoor(char *sDoor);

/*gets x-coordinate of the south door and returns it to room()*/
int northDoor(char *nDoor);

/*gets y-coordinate of the thing inside the room and returns it to room()*/
int yValue(char *string);

/*gets x-coordinate of the thing inside the room and returns it to room()*/
int xValue(char *string);

/*combines together all the functions responsible for a corridor*/
void mainCorridor();

/*connects the doors to the main corridor*/
void connect();

/*cuts out all the extra parts of the corridor*/
void perfect();

/*looks for the initial position of the hero, return is used to end the function once the hero is found*/
void findHero(struct room *data);

/*prints out inventory*/
void inventory(struct player *info);

/*decides what to do with the cursor and the stuff around it when the user presses movemenet keys*/
void check(struct player *info, int x, int y, char checkChar, int i, int j);

/*prints out messages at the end of the game or if the player dies*/
void endFunc(struct player *info);

/*takes the input from the user and changes the stuff accordingly to the input, returns '0' to main() to close the game*/
char control(struct player *info, struct room *data1, struct room *data2, struct room *data3, struct room *data4, struct room *data5, struct
 room *data6);
 
/*runs to see if the user want to play again or not*/
char again(struct player *info);

/*saves the info and achievement of the player*/
void saveInfo(struct player *info);

/*loads the info and the achievemnt of the player*/
void loadInfo(struct player *info);

/*loads the room and stuff inside the room*/
void roomLoad(struct room *data, struct player *info, int y, int x);

/*save the information about the room and stuff inside it*/
void saveFunc(struct room *data, int y, int x);

/*moves monsters randomly*/
void moveM(struct room *data, int y, int x);

/*gets the initial coordiantes of monsters*/
void findM(struct room *data);

/*gets the coordianted of all the things so that they can saved*/
void findThing(struct room *data, int y, int x);

/*generates random dimentions of the room and coordinates of the stuff inside the roooms*/
void random(struct room *data, int room , int door);


int main (int argc, char **argv)
{   
    char *pointer1;
    char *pointer2;
    char *pointer3;
    char *pointer4;
    char *pointer5;
    char *pointer6;
    char funcReturn;
    int i;
    
    struct room *data1;
    struct room *data2;
    struct room *data3;
    struct room *data4;
    struct room *data5;
    struct room *data6;
    struct player *info;
    
    
    i = 0;
    
    data1 = malloc(sizeof(struct room));
    data2 = malloc(sizeof(struct room));
    data3 = malloc(sizeof(struct room));
    data4 = malloc(sizeof(struct room));
    data5 = malloc(sizeof(struct room));
    data6 = malloc(sizeof(struct room));
    info = malloc(sizeof(struct player));
    
    pointer1 = malloc(sizeof(char)*150);
    pointer2 = malloc(sizeof(char)*150);
    pointer3 = malloc(sizeof(char)*150);
    pointer4 = malloc(sizeof(char)*150);
    pointer5 = malloc(sizeof(char)*150);
    pointer6 = malloc(sizeof(char)*150);
    
    info->weapon = malloc(sizeof(char)*50);
    strcpy(info->weapon, "No weapon yet");
    
    info->gobTotal = 0;
    info->iceTotal = 0;
    info->orcTotal = 0;
    info->orcCount = 0;
    info->health = 100;
    
    srand(time(NULL));
       
    openInFile(pointer1, pointer2, pointer3, pointer4, pointer5, pointer6, argc, argv);
    
    startCurses();
    
    parser(pointer1, data1);
    parser(pointer2, data2);
    parser(pointer3, data3);
    parser(pointer4, data4);
    parser(pointer5, data5);
    parser(pointer6, data6);
        
    begin();
    
    room(data1, info, 3, 5);
    room(data2, info, 3, 35);
    room(data3, info, 3, 65);
    room(data4, info, 31, 5);
    room(data5, info, 31, 35);
    room(data6, info, 31 ,65);
    info->orcCount = 0;
    
    mainCorridor();
    connect();
    perfect();
    
    refresh();    
    
    findHero(data1);
   
    
    do
    {
        funcReturn = control(info, data1, data2, data3, data4, data5, data6);
        if(info->playAgain == 1)
        {
            funcReturn = again(info);
        }
        
        if(funcReturn == 'S' && info->genRandom == 1)
        {
            erase();
            info->genRandom = 0;
            random(data1, 1, 1);
            random(data2, 0, 2);
            random(data3, 0, 3);
            random(data4, 0, 4);
            random(data5, 0, 5);
            random(data6, 6, 6);
            
            erase();
            room(data1, info, 3, 5);
            room(data2, info, 3, 35);
            room(data3, info, 3, 65);
            room(data4, info, 31, 5);
            room(data5, info, 31, 35);
            room(data6, info, 31, 65);
            info->orcCount = 0;
    
            mainCorridor();
            connect();
            perfect();
    
            refresh();    
          
            findHero(data1); 
        }   
    }
    while(funcReturn != '0');
    
    endFunc(info);
    endwin();
    
    while(i <= 100)
    {
        free(data1->stuff[i]);
        free(data2->stuff[i]);
        free(data3->stuff[i]);
        free(data4->stuff[i]);
        free(data5->stuff[i]);
        free(data6->stuff[i]);
        i++;
    }
    free(data1->stuff);
    free(data2->stuff);
    free(data3->stuff);
    free(data4->stuff);
    free(data5->stuff);
    free(data6->stuff);
    
    
    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);
    
    free(info->weaponSave);
    free(info->weapon);
    free(info);
    
    
    return(0);  
}  

void openInFile(char *pointer1, char *pointer2, char *pointer3, char *pointer4, char *pointer5, char *pointer6, int argc, char **argv)
{
    
    FILE *infile;
    
    infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        printf("File was not found or failed to open!\n");
        exit(0);
    }
    fgets(pointer1, 149, infile);
    fgets(pointer2, 149, infile);
    fgets(pointer3, 149, infile);
    fgets(pointer4, 149, infile);
    fgets(pointer5, 149, infile);
    fgets(pointer6, 149, infile);
    
    fclose(infile);
}

void parser(char *inpStr, struct room *data)
{
    char *token;
    char *dimensions;
    char *eDoor;
    char *sDoor;
    char *nDoor;
    char *wDoor;
    int i;
    int j;
    
    data->locOfNDoor = 0;
    data->locOfSDoor = 0;
    data->locOfEDoor = 0;
    data->locOfWDoor = 0;
    i = 0;
    j = 0;
    
    token = malloc(sizeof(char)*150);
    dimensions = malloc(sizeof(char)*150);
    nDoor = malloc(sizeof(char)*150);
    wDoor = malloc(sizeof(char)*150);
    sDoor = malloc(sizeof(char)*150);
    eDoor = malloc(sizeof(char)*150);
    
    data->stuff = malloc(sizeof(char*)*100);
    for(i = 0; i <= 100; i++)
    {
        data->stuff[i] = malloc(sizeof(char)*300);
    }
         
    /*breaks the line into smaller parts*/
    token = strtok(inpStr, " ");
    while(token != NULL)
    {
        for(i = 0; i < strlen(token); i++)
        {
            if(token[i] == 'X')
            {
               strcpy(dimensions, token);
               strcat(dimensions, "\0");
            }
            else if(token[i] == 'd' && token[i+1] == 'e')
            {
                strcpy(eDoor, token);
                strcat(eDoor, "\0");    
            }
            else if(token[i] == 'd' && token[i+1] == 's')
            {
                strcpy(sDoor, token);
                strcat(sDoor, "\0");
            }
            else if(token[i] == 'd' && token[i+1] == 'w')
            {
                strcpy(wDoor, token);
                strcat(wDoor, "\0");
            }
            else if(token[i] == 'd' && token[i+1] == 'n')
            {
                strcpy(nDoor, token);
                strcat(nDoor, "\0");
            }
           
            else if(token[i] == 'h' || (token[i] == 's' && i == 0) || (token[i] == 'w' && i == 0) || token[i] == 'p' || token[i] == 'm' || token[i] == 'g')
            {
               strcpy(data->stuff[j], token);
               j = j + 1;
            }                  
        }    
        token = strtok(NULL, " ");                
    }
    
    /*room dimensions are converted to integer values*/    
    data->yDim = yDimension(dimensions);
    data->xDim = xDimension(dimensions);
    
    /*door coordinates are converted to intger values*/
    data->locOfEDoor = eastDoor(eDoor);
    data->locOfWDoor = westDoor(wDoor);
    data->locOfSDoor = southDoor(sDoor);
    data->locOfNDoor = northDoor(nDoor);
    
    /*doors are set to zero if the do not exist*/
    if(eDoor[0] != 'd')
    {
		data->locOfEDoor = 0;
	}
	if(sDoor[0] != 'd')
    {
		data->locOfSDoor = 0;
	}
	if(wDoor[0] != 'd')
    {
		data->locOfWDoor = 0;
	}
	if(nDoor[0] != 'd')
    {
		data->locOfNDoor = 0;
	}
    
    free(dimensions);
    free(eDoor);
    free(wDoor);
    free(sDoor);
    free(nDoor);
    free(token); 
     
    
}

void room(struct room *data, struct player *info, int y, int x)
{
    int i;
    int j;
    int yCoor;
    int xCoor;
    char *buffer;
    char thing;
    i = 0;
    j = 0;
    yCoor = 0;
    xCoor = 0;
    
    buffer = malloc(sizeof(char)*10);
    
    /*checks for the correct dimeensions*/
    if(data->yDim > 21)
    {
        data->yDim = 20;
    }    
    if(data->xDim > 25)
    {
        data->xDim = 25;
    }
    
    /*prints out the borders of the room*/
    for(i = y; i < data->yDim + y; i++)
    {
        move(i, x);
        printw("|");
        move(i, data->xDim - 1 + x);
        printw("|");
    }
    for(i = x; i < data->xDim + x; i++)
    {
        move(y, i);
        printw("-");
        move(data->yDim - 1 + y, i);
        printw("-");
    }
    
    /*prints put the inside of the room*/
    for(i = y + 1; i < data->yDim - 1 + y; i++)
    {
        for(j = x + 1; j < data->xDim - 1 + x; j++)
        {
            move(i,j);
            printw(".");
        }
    }
    
    /*prints out the doors, if the values for doors are wrong corrects them*/
    if(x == 65)
    {
        if(data->locOfEDoor > 0 && data->locOfEDoor < data->yDim - 1)
        {
            move(data->locOfEDoor + y, data->xDim - 1 + x);
            printw("/");
        }   
    }
    else
    {
        if(data->locOfEDoor > 0 && data->locOfEDoor < data->yDim - 1)
        {
            move(data->locOfEDoor + y, data->xDim - 1 + x);
            printw("+");
        }
        else if( data->locOfEDoor >= data->yDim - 1)
        {
            move(1 + y, data->xDim - 1 + x);
            printw("+");
        }
    }
     
    if(x == 5)
    {
        if(data->locOfWDoor > 0 && data->locOfWDoor < data->yDim - 1)
        {
            move(data->locOfWDoor + y, x);
            printw("/");
        }
    }
    else
    {
        if(data->locOfWDoor > 0 && data->locOfWDoor < data->yDim - 1)
        {
            move(data->locOfWDoor + y, x);
            printw("+");
        }
        else
        {
            move(1 + y, x);
            printw("+");
        }
    }
    if(y == 3)
    {
        if(data->locOfNDoor > 0 && data->locOfNDoor < data->xDim - 1)       
        {
            move(y, data->locOfNDoor + x);
            printw("/");
        }
     }
     else
     {
        if(data->locOfNDoor > 0 && data->locOfNDoor < data->xDim - 1) 
        {
            move(y, data->locOfNDoor + x);
            printw("+");
        }
        else
        {
            move(y, 1 + x);
            printw("+");
        }
     }
        
    if(y == 31)
    {
        if(data->locOfSDoor > 0 && data->locOfSDoor < data->xDim - 1) 
        {
            move(data->yDim - 1 + y, data->locOfSDoor + x);
            printw("/");
        }
    }
    else
    {
        if(data->locOfSDoor > 0 && data->locOfSDoor < data->xDim - 1)
        {
            move(data->yDim - 1 + y, data->locOfSDoor + x);
            printw("+");
        }
        else
        {
            move(data->yDim - 1 + y, 1 + x);
            printw("+");
        }
    }
    
    
    /*prints out the stuff inside the room, corrects them if they are wrong*/
    for(i = 0; i < 100; i++)
    {
        strcpy(buffer, data->stuff[i]);
        if(buffer != NULL)
        {
            thing = buffer[0];
            yCoor = yValue(buffer);
            xCoor = xValue(buffer);
            if(yCoor == 0)
            {
                yCoor = 1;
            }
            if(xCoor == 0)
            {
                xCoor = 1;
            }
            if(yCoor >= data->yDim - 1)
            {
                yCoor = data->yDim - 2;
            }
            if(xCoor >= data->xDim - 1)
            {
                xCoor = data->xDim - 2;
            }
            
            move(yCoor + y, xCoor + x);
            printStuff(thing, info);                
        }
        else
        {
            i = 100;
        }
    }
    
    /*stores initial coordinates of the monsters*/
    findM(data);
    
    /*stores the coordinates of the things*/
    findThing(data, y, x);
    
    free(buffer);
}

int yValue(char *string)
{
    int number;
    int i;
    int j;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    
    /*finds the integer value before the coma and stores it*/
    for(i = 0; i < 100; i++)
    {
        if(string[i] == ',')
        {
            for(j = 0; j < i; j++)
            {
                buffer[j] = string[j];
            }
            i = 100;
        }
        else
        {
            number = 0;
        }
    }
    buffer[0] = '0';
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int xValue(char *string)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*finds the integer value after the coma and stores it*/
    for(i = 0; i < 100; i++)
    {
        if(string[i] == ',')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = string[j];
                k++;
            }
            i = 100;
        }
        else
        {
            number = 0;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
 
}

int yDimension(char *dimensions)
{
    int number;
    int i;
    int j;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    
    /*finds the integer value before the X and stores it*/
    for(i = 0; i < 100; i++)
    {
        if(dimensions[i] == 'X')
        {
            for(j = 0; j < i; j++)
            {
                buffer[j] = dimensions[j];
            }
            i = 100;
        }
    }
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int xDimension(char *dimensions)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*finds the integer value after the X and stores it*/
    for(i = 0; i < 100; i++)
    {
        if(dimensions[i] == 'X')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = dimensions[j];
                k++;
            }
            i = 100;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int eastDoor(char *eDoor)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*stores the x-coordinate of the door*/
    for(i = 0; i < 100; i++)
    {
        if(eDoor[i] == 'e')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = eDoor[j];
                k++;
            }
            i = 100;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int westDoor(char *wDoor)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*stores the x-coordinate of the door*/
    for(i = 0; i < 100; i++)
    {
        if(wDoor[i] == 'w')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = wDoor[j];
                k++;
            }
            i = 100;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int northDoor(char *nDoor)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*stores the y-coordinate of the door*/
    for(i = 0; i < 100; i++)
    {
        if(nDoor[i] == 'n')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = nDoor[j];
                k++;
            }
            i = 100;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

int southDoor(char *sDoor)
{
    int number;
    int i;
    int j;
    int k;
    char *buffer;
    buffer = malloc(sizeof(char)*100);
    number = 0;
    i = 0;
    j = 0;
    k = 0;
    
    /*stores the y-coordinate of the door*/
    for(i = 0; i < 100; i++)
    {
        if(sDoor[i] == 's')
        {
            for(j = (i + 1); j < (i + 5); j++)
            {
                buffer[k] = sDoor[j];
                k++;
            }
            i = 100;
        }
    }
    
    number = atoi(buffer);
    free(buffer);       
    return(number);
}

void findHero(struct room *data)
{
    int i;
    int y;
    int x;
    y = 0;
    x = 0;
    i = 0;
    
    /*finds the coordiantes of the hero and moves the cursor there*/
    for(i = 0; i < 100; i++)
    {
        if(data->stuff[i][0] == 'h')
        {
            y = yValue(data->stuff[i]);
            x = xValue(data->stuff[i]);
            if(x == 0)
            {
                x = 1;
            }
            if(y == 0)
            {
                y = 1;
            }
            y = y + 1;
            i = 100;
        }
    }
    move(0, 0);
    printw("Kill all the monsters and collect the gold!");
    move(y + 2, x + 5);
    refresh();
}

char control(struct player *info, struct room *data1, struct room *data2, struct room *data3, struct room *data4, struct room *data5, struct room *data6)
{
    char input;
    char stairs;
    char checkChar;
    char before;
    char noRepeat;
    char tryAgain;
    int y;
    int x;
    int yOrigin;
    int xOrigin;
    int i;
    int j;
    yOrigin = 0;
    xOrigin = 0;
    y = 0;
    x = 0;
    i = 0;
    j = 0;
    noRepeat = 0;
    
    inventory(info);
    
    /*runs if your health is zero or blow zero*/
    if(info->health <= 0)
    {
        move(0, 0);
        clrtoeol();
        move(0, 0);
        printw("Do you want to reload the game from the Savepoint? (y)es / (n)o");
        do
        {
            flushinp();
            tryAgain = getch();
            switch(tryAgain)
            {
                case 'y':
                {
                    if(info->saved == 1)
                    {
                        erase();
                        roomLoad(data1, info, 3, 5);
                        roomLoad(data2, info, 3, 35);
                        roomLoad(data3, info, 3, 65);
                        roomLoad(data4, info, 31, 5);
                        roomLoad(data5, info, 31, 35);
                        roomLoad(data6, info, 31, 65);
                        loadInfo(info);
        
                        mainCorridor();
                        connect();
                        perfect();
        
                        refresh(); 
                
                        y = info->ySave;  
                        x = info->xSave;
                        move(y, x);
                        refresh();
                        inventory(info);
                    }
                    else
                    {
                        erase();
                        move(0, 0);
                        printw("No saved file to load!\n\nPress any button to continue...");
                        getch();
                        info->playAgain = 1;
                        return('0');
                    }
                    break;
                }
                case 'n':
                {
                    info->playAgain = 1;
                    return ('0');
                    break;
                }
                default:
                {
                    move(0, 0);
                    clrtoeol();
                    move(0, 0);
                    printw("Do you want to reload the game from the Savepoint? (y)es / (n)o   ");
                    printw("Wrong Input! Only (y)es or (no) are allowed!");
                    move(y, x);
                    refresh();
                    break;
                }  
            } 
        } 
        while(tryAgain != 'y');
    }
    
    /*saves the initial position of the cursor and prints out the hero sign*/
    getsyx(y, x);
    before = mvinch(y, x);
    yOrigin = y;
    xOrigin = x;
    move(y, x);  
    attron(COLOR_PAIR(1)); 
    printw("@");
    attroff(COLOR_PAIR(1));
    
    
    /*moves monsters*/
    if(info->repeat == 1 && info->move == 0)
    {
        moveM(data1, 3, 5);
        moveM(data2, 3 ,35);
        moveM(data3, 3, 65);
        moveM(data4, 31, 5);
        moveM(data5, 31, 35);
        moveM(data6, 31, 65);    
    }
    move(y, x);
    refresh();
    
    flushinp();
    input = getch();
    move(0, 0);
    clrtoeol();
    switch(input)
    {
        case 'w':
        {
            i = 0 - 1;
            j = 0;
            checkChar = mvinch(y + i, x + j);
            check(info, x, y, checkChar, i, j);
            getsyx(y, x);
            break;
        }
        case 's':
        {
            i = 1;
            j = 0;
            checkChar = mvinch(y + i, x + j);
            check(info, x, y, checkChar, i, j);
            getsyx(y, x);
            break;
        }
        case 'a':
        {
            i = 0;
            j = 0 - 1;
            checkChar = mvinch(y + i, x + j);
            check(info, x, y, checkChar, i, j);
            getsyx(y, x);
            break;
        }
        case 'd':
        {
            i = 0;
            j = 1;
            checkChar = mvinch(y + i, x + j);
            check(info, x, y, checkChar, i, j);
            getsyx(y, x);
            break;
        }
        case 'q':
        {           
            info->playAgain = 1;     
            return('0');
            break;
        }
        case 'c':
        {       
            move(0, 0);
            printw("You saved the game!");       
            saveFunc(data1, 3, 5);
            saveFunc(data2, 3, 35);
            saveFunc(data3, 3, 65);
            saveFunc(data4, 31, 5);
            saveFunc(data5, 31, 35);
            saveFunc(data6, 31, 65);
            saveInfo(info);
            info->ySave = y;
            info->xSave = x;
            noRepeat = 1;
            info->saved = 1;
            
            break;
        }
        case 'l':
        {            
            if(info->saved == 1)
            {
                erase();   
                move(0, 0);
                printw("You loaded the game!");
                roomLoad(data1, info, 3, 5);
                roomLoad(data2, info, 3, 35);
                roomLoad(data3, info, 3, 65);
                roomLoad(data4, info, 31, 5);
                roomLoad(data5, info, 31, 35);
                roomLoad(data6, info, 31 ,65);
                loadInfo(info);
        
                mainCorridor();
                connect();
                perfect();
    
                refresh(); 
            
                y = info->ySave;  
                x = info->xSave;
            }
            else
            {
                move(0, 0);
                printw("No saved file found!");
            }
            noRepeat = 1;
            break;
        }
        case 'm':
        {
            if(info->move == 0)
            {
                info->move = 1;
                move(0, 0);
                printw("Monsters do not move anymore.");
            }
            else
            {
                info->move = 0;
                move(0, 0);
                printw("Monsters move again.");
            }
            noRepeat = 1;
            break;
        }
        case 'i':
        {
            move(0, 0);
            if(info->weaponPos == 1)
            {
                if(info->wield == 0)
                {
                    info->wield = 1;
                    printw("You drew a weapon!");
                }
                else
                {
                    info->wield = 0;
                    printw("You put your weapon away");
                }
            }
            else
            {
                printw("You don't have a weapon");
            }
            noRepeat= 1;
            break;
        }
        case 'o':
        {
            move(0, 0);
            if(info->potion > 0)
            {
                if(info->potionActive != 1)
                {
                    info->potion = info->potion - 1;
                    info->potionActive = 1;
                    move(0, 0);
                    printw("You drank a potion to kill an orc!");
                }
                else
                {
                    move(0, 0);
                    printw("You already drank a potion!");
                }
            }
            else
            {
                printw("You do not have any potion to use!");
            }
            noRepeat = 1;
            break;
        }
        case 'p':
        {
            if(info-> gold >= 100)
            {
                info->potion = info->potion + 1;
                move(0, 0);
                printw("You just bought a potion!");
                info->gold = info->gold - 100;
            }
            else
            {
                move(0, 0);
                printw("You don't have enough money to buy a potion!");
            }
            noRepeat = 1;
            break;
        }
        case 'h':
        {
            if(info->potion > 0)
            {
                if(info->health != 100)
                {
                    info->potion = info->potion - 1;
                    move(0, 0);
                    info->health = 100;
                    printw("You used a potion to regain the health!");
                }
                else
                {
                    move(0, 0);
                    printw("Your health is full already!");
                }
            }
            else
            {
                move(0, 0);
                printw("You don't have a potion!");
            }
            noRepeat = 1;
            break;
        }
        case 'u':
        {
            if(info->weapon[0] == 'T')
            {
                move(0, 0);
                printw("Can't upgrade this weapon!");
            }
            else if(info->weapon[0] == 'S')
            {
                if(info->gold >= 200)
                {
                    info->gold = info->gold - 200;
                    move(0, 0);
                    printw("Weapon upgraded!");
                    strcpy(info->weapon, "TwoSword");
                }
                else
                {
                    move(0, 0);
                    printw("You don't have enough money for upgrade!");
                }
            }
            else if(info->weapon[0] == 'M')
            {
                if(info->gold >= 200)
                {
                    info->gold = info->gold - 200;
                    move(0, 0);
                    printw("Weapon upgraded!");
                    strcpy(info->weapon, "Sword");
                }
                else
                {
                    move(0, 0);
                    printw("You don't have enough money for upgrade!");
                }
            }
             else if(info->weapon[0] == 'D')
            {
                if(info->gold >= 200)
                {
                    info->gold = info->gold - 200;
                    move(0, 0);
                    printw("Weapon upgraded!");
                    strcpy(info->weapon, "Mace");
                }
                else
                {
                    move(0, 0);
                    printw("You don't have enough money for upgrade!");
                }
            }
            else
            {
                move(0, 0);
                printw("No weapon to be upgraded!");
            }
            noRepeat = 1;
            break;
        }
        default:
        {
            move(0, 0);
            printw("Wrong input!\n");
            move(y, x);
            noRepeat = 1;
            break;
        }
        
    }
    
    if(input == 'w' || input == 's' || input == 'a' || input == 'd')
    {
        if(checkChar == '|' || checkChar == '-' || checkChar == ' ')
        {
            info->repeat = 0;
        }
        else
        {
            info->repeat = 1;
        }
    }
    else
    {
        info->repeat = 0;
    }
    
    if(noRepeat == 0)
    {
        if(checkChar == '%')
        {   
            move(0, 0);
            printw("You encountered the stairs! Do you want to go down the stairs? (y)es / (n)o");
            do
            {
                flushinp();
                stairs = getch();
                move(0, 0);
                clrtoeol();
                if(stairs == 'y')
                {
                    info->genRandom = 1;
                    return('S');
                } 
                else if(stairs =='n')
                {
                    stairs = 'n';
                    printw("You chose not to go down the stairs!");
                    info->genRandom = 0;
                }
                else
                {
                    printw("Wrong input! Only 'y' or 'n' is allowed!");
                    info->genRandom = 0;
                }     
             }
             while(stairs != 'n');
        }   
            
        if(checkChar == '*')
        {
            info->gold = info->gold + 100;
            move(0, 0);
            printw("You just picked up 100 gold!");
        }
        if(checkChar == '!')
        {
            info->potion = info->potion + 1; 
            move(0, 0);
            printw("You just picked a potion!");
        }
        if(checkChar == ')')
        {
            info->weapon[0] = '\0';
            info->weaponPos = 1;
           
            info->weaponRand = rand()%4;
            if(info->weaponRand == 0)
            {
                strcpy(info->weapon, "TwoSword");
            }
            else if(info->weaponRand == 1)
            {
                strcpy(info->weapon, "Sword");
            }
            else if(info->weaponRand == 2)
            {
                strcpy(info->weapon, "Mace");
            }
            else if(info->weaponRand == 3)
            {
                strcpy(info->weapon, "Dagger");
            }
            move(0, 0);
            printw("You picked up a %s!", info->weapon);
        }
    }    
    
    
    if(before == '%' || before == '#' || before == '+')
    {
        mvaddch(yOrigin, xOrigin, before);
    }
    
    move(y, x);
    refresh();
    
    return (0);
}

void mainCorridor()
{
    int i;
    i = 1;
    for(i = 3; i < 57; i = i + 1)
    {
        move(i, 32);
        printw("#");
        move(i, 62);
        printw("#");
    }
    for(i = 6; i < 89; i = i + 1)
    {
        move(29, i);
        printw("#");
    }
}

void connect()
{
    chtype *door;
    chtype check;
    int row;
    int i;
    int j;
    i = 0;
    j = 0;
    row = 0;
    door = malloc(sizeof(chtype)*300);
    move(0, 0);
    for(row = 1; row < 200; row++)
    {
        door[0] = '0';
        inchstr(door);
        for(i = 0; i < 300; i++)
        {
            move(row + 1, 0);
            check = door[i];
            switch(check)
            {
                case '+':
                {
                    if(mvinch(row, i + 1) == ' ')
                    {
                        for(j = i + 1; j < 200; j++)
                        {
                            if(mvinch(row, j) != '#')
                            {
                                move(row, j);
                                printw("#");
                                
                            }
                            else
                            {
                                j = 200;
                            }
                        }
                    }
                    if(mvinch(row, i - 1) == ' ')
                    {
                        for(j = i - 1; j > 0; j--)
                        {
                            if(mvinch(row, j) != '#')
                            {
                                move(row, j);
                                printw("#");
                            }
                            else
                            {
                                j = 0;
                            }
                        }
                    }
                    if(mvinch(row - 1, i) == ' ')
                    {
                        for(j = row - 1; j > 0; j--)
                        {
                            if(mvinch(j, i) != '#')
                            {
                                move(j, i);
                                printw("#");
                            }
                            else
                            {
                                j = 0;
                            }
                        }
                    }
                    if(mvinch(row + 1, i) == ' ')
                    {
                        for(j = row + 1; j < 200; j++)
                        {
                            if(mvinch(j, i) != '#')
                            {
                                move(j, i);
                                printw("#");
                            }
                            else
                            {
                                j = 200;
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    free(door);
}

void perfect()
{
    int row;
    int column;
    row = 0;
    column = 0;
    
    for(row = 56; row > 1; row--)
    {
        if(mvinch(row, 31) != '#' && mvinch(row, 33) != '#')
        {
            move(row, 32);
            printw(" ");
        }
        else
        {
            row = 0;
        }
    }
    
    for(row = 56; row > 1; row--)
    {
        if(mvinch(row, 61) != '#' && mvinch(row, 63) != '#')
        {
            move(row, 62);
            printw(" ");
        }
        else
        {
            row = 0;
        }
    }
    
    for(column = 89; column > 6; column--)
    {
        if(mvinch(28, column) != '#' && mvinch(30, column) != '#')
        {
            move(29, column);
            printw(" ");
        }
        else
        {
            column = 0;
        }
    } 

    for(row = 2; row < 29; row++)
    {
        if(mvinch(row, 31) != '#' && mvinch(row, 33) != '#')
        {
            move(row, 32);
            printw(" ");
        }
        else
        {
            row = 30;
        }
    }     
    
    for(row = 2; row < 29; row++)
    {
        if(mvinch(row, 61) != '#' && mvinch(row, 63) != '#')
        {
            move(row, 62);
            printw(" ");
        }
        else
        {
            row = 30;
        }
    }

    for(column = 5; column < 90; column ++)
    {
        if(mvinch(28, column) != '#' && mvinch(30, column) != '#')
        {
            move(29, column);
            printw(" ");
        }
        else
        {
            column = 90;
        }
    }  
}

void startCurses()
{
    initscr();
    cbreak();
    noecho();
    start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
}

void endFunc(struct player *info)
{
    erase();
    
    if(info->weapon[0] == 'N')
    {
        strcpy(info->weapon, "no weapon");
    }
    if(info->health < 0)
    {
        printw("Game Over! You died!\n\nPress any button to continue and wait for 2 seconds after that...");
        flushinp();
        getch();
        sleep(2);
    }
    erase();
    attron(COLOR_PAIR(2));
    printw("You had %d gold, %d potion(s) and %s as your weapon\n", info->gold, info->potion, info->weapon);
    printw("You killed %d out of %d HobGoblin(s),", info->gob, info->gobTotal);
    printw(" %d out of %d Ice Monster(s)", info->ice, info->iceTotal);
    printw(" and %d out of %d Orc(s)!\n", info->orc, info->orcTotal);
    printw("Your final health was %d\n\n", info->health);
    printw("Have a good day!\n\n\n");
    printw("Press any button to continue...");
    flushinp();
    getch();
    attroff(COLOR_PAIR(2));
}

void printStuff(char thing, struct player *info)
{
    int randomMonster;
    randomMonster = 0;
    randomMonster = rand()%3;
    if(thing == 'h')
    {
        printw("@");
    }
    else if(thing == 'm')
    {
        if(randomMonster == 0)
        {
            attron(COLOR_PAIR(5));
            printw("H"); 
            attroff(COLOR_PAIR(5));
            info->gobTotal = info->gobTotal + 1;
        }
        else if(randomMonster == 1)
        {
            attron(COLOR_PAIR(5));
            printw("I");
            attroff(COLOR_PAIR(5));
            info->iceTotal = info->iceTotal + 1;
        }
        else if(randomMonster == 2)
        {
            if(info->orcCount < 6)
            {
                attron(COLOR_PAIR(5));
                printw("O");
                attroff(COLOR_PAIR(5));
                info->orcTotal = info->orcTotal + 1;
                info->orcCount = info->orcCount + 1;
            }
            else
            {
                attron(COLOR_PAIR(5));
                printw("H");
                attroff(COLOR_PAIR(5));
                info->gobTotal = info->gobTotal + 1;
            }
        }
    }
    else if(thing == 's')
    {
        attron(COLOR_PAIR(6));
        printw("%c", 37);
        attroff(COLOR_PAIR(6));
    }
    else if(thing == 'p')
    {
        attron(COLOR_PAIR(3));
        printw("!");
        attroff(COLOR_PAIR(3));
    }
    else if(thing == 'g')
    {
		attron(COLOR_PAIR(4));
        printw("*");
        attroff(COLOR_PAIR(4));
    }
    else if(thing == 'w')
    {
        attron(COLOR_PAIR(2));
        printw(")");
        attroff(COLOR_PAIR(2));
    }
}

void check(struct player *info, int x, int y, char checkChar, int i, int j)
{
    if(checkChar == ')' || checkChar == '!' || checkChar == '*' || checkChar == '.' || checkChar == '%')
    {
        move(y, x);
        printw(".");
    }
    if(checkChar == '+' && mvinch(y + (2 * i), x + (2 * j)) != '.')
    {
         move(y, x);
         printw(".");
    }
            
    if(checkChar == '-' || checkChar == '|' || checkChar == ' ')
    {
         move(0, 0);
         printw("You cannot go there!");
    }
    else if(checkChar == '/')
    {
         move(0, 0);
         printw("The door is broken! You cannot go there!");
    }  
    else if(checkChar == '#')
    {
         y = y + i;
         x = x + j;
    }
    else if(checkChar == '%')
    {
         y = y + i;
         x = x + j;
    }
    else if(checkChar == '+')
    {
         y = y + i;
         x = x + j;
    }
    else if(checkChar == 'H')
    {
        if(info->wield == 1)
        {
            if(info->weapon[0] == 'T')
            {
                info->health = info->health;
            }
            else if(info->weapon[0] == 'S')
            {
                info->health = info->health - 5;
            }
            else if(info->weapon[0] == 'M')
            {
                info->health = info->health - 10;
            }
            else
            {
                info->health = info->health - 15;
            }
            move(0,0);
            printw("You killed the HobGoblin!");  
            move(y, x);
            printw("."); 
            y = y + i;
            x = x + j;
            move(y, x);
            printw("@"); 
            info->gob = info->gob + 1;
        }
        else 
        {
            move(0, 0);
            printw("There is a HobGoblin! Draw a weapon or get one if you don't have it!"); 
            info->health = info->health - 25;           
        }         
    }
    else if(checkChar == 'I')
    {
        if(info->wield == 1 && (info->weapon[0] == 'T' || info->weapon[0] == 'S' || info->weapon[0] == 'M'))
        {
            if(info->weapon[0] == 'T')
            {
                info->health = info->health - 5;
            }
            else if(info->weapon[0] == 'S')
            {
                info->health = info->health - 15;
            }
            else
            {
                info->health = info->health - 25;
            }
            move(0,0);
            printw("You killed the Ice Monster!");  
            move(y, x);
            printw("."); 
            y = y + i;
            x = x + j;
            move(y, x);
            printw("@");
            info->ice = info->ice + 1;
        }
        else if(info->weapon[0] == 'D')
        {
            move(0, 0);
            printw("Dagger is not good enough to kill the Ice Monster");
            info->health = info->health - 35;
        }
        else 
        {
            move(0, 0);
            printw("There is an Ice Monster! You need the Mace, Sword or TwoSword to kill him! Also, you need to draw your weapon!");          
            info->health = info->health - 50;  
        }
    }
    else if(checkChar == 'O')
    {
        if(info->wield == 1 && info->potionActive == 1 && (info->weapon[0] == 'T' || info->weapon[0] == 'S'))
        {
            if(info->weapon[0] == 'T')
            {
                info->health = info->health - 15;
            }
            else
            {
                info->health = info->health - 30;
            }
            move(0,0);
            printw("You killed Orc!");  
            move(y, x);
            printw("."); 
            y = y + i;
            x = x + j;
            move(y, x);
            printw("@"); 
            info->orc = info->orc + 1;
            info->potionActive = 0;
        }
        else if(info->weapon[0] == 'M')
        {
            move(0, 0);
            printw("Mace is not good enough to kill the Orc");
            info->health = info->health - 45;
        }
        else if(info->weapon[0] == 'D')
        {
            move(0, 0);
            printw("Dagger is not good enough to kill the Orc");
            info->health = info->health - 60;
        }
        else if(info->potionActive != 1)
        {
            move(0, 0);
            printw("There is an Orc! Your weapon has to be drawn! You need to have the TwoSword or the Sword and you have to activate a potion!");    
            info->health = info->health - 60;      
        } 
        else
        {
            move(0, 0);
            printw("There is an Orc! Your weapon has to be drawn! You need to have the TwoSword or the Sword and you have to activate a potion!");    
            info->health = info->health - 75;      
        }            
   }
   else
   {
        y = y + i;
        x = x + j;
   }
   move(y, x);
   refresh();
}

void begin()
{
    move(0, 0);
    attron(COLOR_PAIR(5));
    printw("Welcome to the game!\n\n");
    attroff(COLOR_PAIR(5));
    printw("Controls:\n\n");
    attron(COLOR_PAIR(6));
    printw("(w), (a), (s), (d) to move\n");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(2));
    printw("(i) to draw a weapon\n");
    printw("(u) to upgrade a weapon\n");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    printw("(p) to buy a potion\n");
    printw("(h) to regain health\n");
    printw("(o) to activate a potion to kill an orc\n");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    printw("(c) to save the game\n");
    printw("(l) to load the game\n");
    attroff(COLOR_PAIR(1));
    printw("(q) to quit\n\n");
    attron(COLOR_PAIR(4));
    printw("Cheat code: (m) to stop the monsters from moving\n\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("Press any button to continue...");
    attroff(COLOR_PAIR(6));
    getch();
    erase();
}

void random(struct room *data, int room, int door)
{
    int i;
    int randomThing;
    int randomX;
    int randomY;
    int bufferX;
    int bufferY;
    int hero;
    int stairs;
    char y[3];
    char x[3];
    
    randomY = 0;
    randomX = 0;
    i = 0;
    bufferX = 0;
    bufferY = 0;
    hero = 0;
    stairs = 0;
    
    data->yDim = 0;
    data->xDim = 0;
    data->locOfEDoor = 0;
    data->locOfWDoor = 0;
    data->locOfSDoor = 0;
    data->locOfNDoor = 0;
    
    data->yDim = rand()%15+10;
    data->xDim = rand()%15+10;
    
    bufferX = data->xDim - 2;
    bufferY = data->yDim - 2;
    
    data->locOfEDoor = rand()%bufferY+1;
    data->locOfWDoor = rand()%bufferY+1;
    data->locOfSDoor = rand()%bufferX+1;
    data->locOfNDoor = rand()%bufferX+1;
    
    for(i = 0; i < 100; i++)
    {
        data->stuff[i][0] = '\0';
    }
    
    if(door == 1)
    {
        data->locOfNDoor = 0;
        data->locOfWDoor = 0;
    }
    else if(door == 2)
    {
        data->locOfNDoor = 0;
    }
    else if(door == 3)
    {
        data->locOfNDoor = 0;
        data->locOfEDoor = 0;
    }
    else if(door == 4)
    {
        data->locOfSDoor = 0;
        data->locOfWDoor = 0;
    }
    else if(door == 5)
    {
        data->locOfSDoor = 0;
    }
    else if(door == 6)
    {
        data->locOfSDoor = 0;
        data->locOfEDoor = 0;
    }
    
    
    for(i = 0; i < 20; i++)
    {
        randomThing = rand()%7;
        randomY = rand()%bufferY+1;
        randomX = rand()%bufferX+1;
        sprintf(y, "%d", randomY);
        sprintf(x, "%d", randomX);
        if(randomThing == 0 && room == 1 && hero != 1)
        {
            strcpy(data->stuff[i], "h");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
            hero = 1;
        }
        else if(randomThing == 1)
        {
            strcpy(data->stuff[i], "m");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
        }
        else if(randomThing == 2)
        {
            strcpy(data->stuff[i], "p");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
        }
        else if(randomThing == 3)
        {
            strcpy(data->stuff[i], "w");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
        }
        else if(randomThing == 4 && room == 6 && stairs != 1)
        {
            strcpy(data->stuff[i], "s");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
            stairs = 1;
        }
        else if(randomThing == 5)
        {
            strcpy(data->stuff[i], "g");
            strcat(data->stuff[i], y);
            strcat(data->stuff[i], ",");
            strcat(data->stuff[i], x);
        }
        else
        {
            strcpy(data->stuff[i], "\0");
        }
    }
    if(stairs == 0 && room == 6)
    {
        strcpy(y, "1");
        strcpy(x, "1");
        strcpy(data->stuff[i], "s");
        strcat(data->stuff[i], y);
        strcat(data->stuff[i], ",");
        strcat(data->stuff[i], x);
    }  
    if(hero == 0 && room == 1)
    {
        strcpy(x, "1");
        strcpy(y, "2");
        strcpy(data->stuff[i], "h");
        strcat(data->stuff[i], y);
        strcat(data->stuff[i], ",");
        strcat(data->stuff[i], x);
    }     
}

void inventory(struct player *info)
{
    int y;
    int x;
    y = 0;
    x = 0;
    getsyx(y, x);
    move(1, 95);
    attron(COLOR_PAIR(3));
    if(info->potionActive == 1)
    {   
        clrtoeol();
        printw("Potion: %d ON", info->potion);
    }
    else
    {
        clrtoeol();
        printw("Potion: %d OFF", info->potion);
    }
    attroff(COLOR_PAIR(3));
    
    move(2, 95);
    clrtoeol();
    attron(COLOR_PAIR(4));
    printw("Gold: %d", info->gold);
    attroff(COLOR_PAIR(4));
    
    
    if(info->health < 0)
    {
        info->health = 0;
    }
    move(3, 95);
    clrtoeol();
    attron(COLOR_PAIR(2));
    printw("Health: %d", info->health);
    attroff(COLOR_PAIR(2));
    
    move(4, 95);
    attron(COLOR_PAIR(5));
    if(info->wield == 1)
    {  
        clrtoeol();
        printw("Weapon: %s ON", info->weapon);
    }
    else
    {
        clrtoeol();
        printw("Weapon: %s OFF", info->weapon);
    }
    attroff(COLOR_PAIR(5));
    move(y, x);
}
    
void findM(struct room *data)
{
    int i;
    int y;
    int x;
    y = 0;
    x = 0;
    i = 0;
    data->mCount = 0;
    for(i = 0; i < 100; i++)
    {
        if(data->stuff[i][0] == 'm')
        {
            y = yValue(data->stuff[i]);
            x = xValue(data->stuff[i]);
            data->monsterY[data->mCount] = y;
            data->monsterX[data->mCount] = x;
            data->mCount = data->mCount + 1;
        }
    }
    data->mCount = 0;
    refresh(); 
}  

void findThing(struct room *data, int y, int x)
{
    int i;
    i = 0;
    data->thingCount = 0;
    for(i = 0; i < 100; i++)
    {
        
        if(data->stuff[i][0] == 'p' || data->stuff[i][0] == 's' || data->stuff[i][0] == 'g' || data->stuff[i][0] == 'w')
        {
            data->thingY[data->thingCount] = yValue(data->stuff[i]);
            data->thingX[data->thingCount] = xValue(data->stuff[i]);            
            data->thingCount = data->thingCount + 1;
        }
    }
    data->thingCount = 0;
    refresh(); 
}   

void moveM(struct room *data, int y, int x)
{
    int i;
    int randomY;
    int randomX;
    char monster;
    
    i = 0;
    randomY = 0;
    randomX = 0;
    
    
    for(i = 0; i < 20; i++)
    {
        randomY = rand()%3; 
        randomX = rand()%3;        
                   
        
        
        monster = mvinch(data->monsterY[i] + y, data->monsterX[i] + x);
        
        refresh();
        
        if(monster != 'O' && monster != 'I' && monster != 'H')
        {
            data->monsterY[i] = 0;
            
        }
        
        if(data->monsterY[i] == 0 || data->monsterY[i] == 0)
        {
            randomY = 0;
            randomX = 0;
        }
        
        if(randomY == 1 && mvinch(data->monsterY[i] + y - 1, data->monsterX[i] + x) == '.')
        {
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x, '.');
            attron(COLOR_PAIR(5));
            mvaddch(data->monsterY[i] + y - 1, data->monsterX[i] + x, monster);
            data->monsterY[i] = data->monsterY[i] - 1; 
            attroff(COLOR_PAIR(5));
        }
        else if(randomY == 2 && mvinch(data->monsterY[i] + y + 1, data->monsterX[i] + x) == '.')
        {
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x, '.');
            attron(COLOR_PAIR(5));
            mvaddch(data->monsterY[i] + y + 1, data->monsterX[i] + x, monster);
            data->monsterY[i] = data->monsterY[i] + 1;
            attroff(COLOR_PAIR(5)); 
        }
        else if(randomX == 1 && mvinch(data->monsterY[i] + y, data->monsterX[i] + x - 1) == '.')
        {
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x, '.');
            attron(COLOR_PAIR(5));
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x - 1, monster); 
            data->monsterX[i] = data->monsterX[i] - 1; 
            attroff(COLOR_PAIR(5));
        }
        else if(randomX == 2 && mvinch(data->monsterY[i] + y, data->monsterX[i] + x + 1) == '.')
        {
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x, '.');
            attron(COLOR_PAIR(5));
            mvaddch(data->monsterY[i] + y, data->monsterX[i] + x + 1, monster);   
            data->monsterX[i] = data->monsterX[i] + 1;
            attroff(COLOR_PAIR(5));
        }
    }
} 

void saveFunc(struct room *data, int y, int x)
{
    int i;
    i = 0;
    
    for(i = 0; i < 100; i++)
    {    
        data->monsterYSave[i] = data->monsterY[i];
        data->monsterXSave[i] = data->monsterX[i];
        data->monsterSave[i] = mvinch(data->monsterYSave[i] + y, data->monsterXSave[i] + x);
        refresh();
    }
    
    for(i = 0; i < 200; i++)
    {    
        data->thingYSave[i] = data->thingY[i];
        data->thingXSave[i] = data->thingX[i];
        data->thingSave[i] = mvinch(data->thingYSave[i] + y, data->thingXSave[i] + x);
        refresh();
    }
    
    data->yDimSave = data->yDim;
    data->xDimSave = data->xDim;
    data->locOfEDoorSave = data->locOfEDoor; 
    data->locOfWDoorSave = data->locOfWDoor;
    data->locOfSDoorSave = data->locOfSDoor;
    data->locOfNDoorSave = data->locOfNDoor; 
}
        
void roomLoad(struct room *data, struct player *info, int y, int x)
{
    int i;
    int j;
    i = 0;
    j = 0;
    
    for(i = y; i < data->yDimSave + y; i++)
    {
        move(i, x);
        printw("|");
        move(i, data->xDimSave - 1 + x);
        printw("|");
    }
    for(i = x; i < data->xDimSave + x; i++)
    {
        move(y, i);
        printw("-");
        move(data->yDimSave - 1 + y, i);
        printw("-");
    }
    for(i = y + 1; i < data->yDimSave - 1 + y; i++)
    {
        for(j = x + 1; j < data->xDimSave - 1 + x; j++)
        {
            move(i,j);
            printw(".");
        }
    }
    
    if(x == 65)
    {
        if(data->locOfEDoorSave > 0 && data->locOfEDoorSave < data->yDimSave - 1)
        {
            move(data->locOfEDoorSave + y, data->xDimSave - 1 + x);
            printw("/");
        }   
    }
    else
    {
        if(data->locOfEDoorSave > 0 && data->locOfEDoorSave < data->yDimSave - 1)
        {
            move(data->locOfEDoorSave + y, data->xDimSave - 1 + x);
            printw("+");
        }
        else
        {
            move(1 + y, data->xDimSave - 1 + x);
            printw("+");
        }
    }
     
    if(x == 5)
    {
        if(data->locOfWDoorSave > 0 && data->locOfWDoorSave < data->yDimSave - 1)
        {
            move(data->locOfWDoorSave + y, x);
            printw("/");
        }
    }
    else
    {
        if(data->locOfWDoorSave > 0 && data->locOfWDoorSave < data->yDimSave - 1)
        {
            move(data->locOfWDoorSave + y, x);
            printw("+");
        }
        else
        {
            move(1 + y, x);
            printw("+");
        }
    }
    if(y == 3)
    {
        if(data->locOfNDoorSave > 0 && data->locOfNDoorSave < data->xDimSave - 1)       
        {
            move(y, data->locOfNDoorSave + x);
            printw("/");
        }
     }
     else
     {
        if(data->locOfNDoorSave > 0 && data->locOfNDoorSave < data->xDimSave - 1) 
        {
            move(y, data->locOfNDoorSave + x);
            printw("+");
        }
        else
        {
            move(y, 1 + x);
            printw("+");
        }
     }
        
    if(y == 31)
    {
        if(data->locOfSDoorSave > 0 && data->locOfSDoorSave < data->xDimSave - 1) 
        {
            move(data->yDimSave - 1 + y, data->locOfSDoorSave + x);
            printw("/");
        }
    }
    else
    {
        if(data->locOfSDoorSave > 0 && data->locOfSDoorSave < data->xDimSave - 1)
        {
            move(data->yDimSave - 1 + y, data->locOfSDoorSave + x);
            printw("+");
        }
        else
        {
            move(data->yDimSave - 1 + y, 1 + x);
            printw("+");
        }
    }
    
   
    attron(COLOR_PAIR(5));
    for(i = 0; i < 100; i++)
    {
        if(data->monsterSave[i] == 'O' || data->monsterSave[i] == 'H' || data->monsterSave[i] == 'I')
        {
            move(data->monsterYSave[i] + y, data->monsterXSave[i] + x);
            refresh();
            printw("%c", data->monsterSave[i]);
            data->monsterY[i] = data->monsterYSave[i];
            data->monsterX[i] = data->monsterXSave[i];
            refresh();
        }
    }
    attroff(COLOR_PAIR(5));
    
    for(i = 0; i < 100; i++)
    {
        move(data->thingYSave[i] + y, data->thingXSave[i] + x);
        
        refresh();
        if(data->thingSave[i] == ')')
        {
            attron(COLOR_PAIR(2));
            printw("%c", data->thingSave[i]);
            attroff(COLOR_PAIR(2));
        }
        else if(data->thingSave[i] == '*')
        {
            attron(COLOR_PAIR(4));
            printw("%c", data->thingSave[i]);
            attroff(COLOR_PAIR(4));
        }
        else if(data->thingSave[i] == '%')
        {
            attron(COLOR_PAIR(6));
            printw("%c", data->thingSave[i]);
            attroff(COLOR_PAIR(6));
        }
        else if(data->thingSave[i] == '!')
        {
            attron(COLOR_PAIR(3));
            printw("%c", data->thingSave[i]);
            attroff(COLOR_PAIR(3));
        }
        
        refresh();
    }
}   

void saveInfo(struct player *info)
{
    info->weaponSave = malloc(sizeof(char)*20);
    
    info->goldSave = info->gold;
    info->potionSave = info->potion;
    info->weaponPosSave = info->weaponPos;
    info->wieldSave = info->wield;
    info->weaponRandSave = info->weaponRand;
    info->potionActiveSave = info->potionActive;
    info->healthSave = info->health;
    info->orcSave = info->orc;
    info->iceSave = info->ice;
    info->gobSave = info->gob;
    info->orcTotalSave = info->orcTotal;
    info->iceTotalSave = info->iceTotal;
    info->gobTotalSave = info->gobTotal;
    info->orcCountSave = info->orcCount;
    info->moveSave = info->move;
    info->repeatSave = info->repeat;
    strcpy(info->weaponSave, info->weapon);
}
    
void loadInfo(struct player *info)    
{
    info->gold = info->goldSave;
    info->potion = info->potionSave;
    info->weaponPos = info->weaponPosSave;
    info->wield = info->wieldSave;
    info->weaponRand = info->weaponRandSave;
    info->potionActive = info->potionActiveSave;
    info->health = info->healthSave;
    info->orc = info->orcSave;
    info->ice = info->iceSave;
    info->gob = info->gobSave;
    info->orcTotal = info->orcTotalSave;
    info->iceTotal = info->iceTotalSave;
    info->gobTotal = info->gobTotalSave;
    info->orcCount = info->orcCountSave;
    info->move = info->moveSave;
    info->repeat = info->repeatSave;
    strcpy(info->weapon, info->weaponSave);
}     

char again(struct player *info)
{
    char answer;
    erase();
    move(0, 0);
    printw("Do you want to play again? (y)es / (n)o");
    
    do
    {
        flushinp();
        answer = getch();
        switch(answer)
        {
            case 'y':
            {
                info->genRandom = 1;
                info->playAgain = 0;
                info->health = 100;
                info->gold = 0;
                info->potion = 0;
                info->weaponPos = 0;
                info->wield = 0;
                info->potionActive = 0;
                info->orc = 0;
                info->ice = 0;
                info->gob = 0;
                info->orcTotal = 0;;
                info->iceTotal = 0;
                info->gobTotal = 0;
                info->orcCount = 0;
                info->move = 0;
                info->repeat = 0;
                strcpy(info->weapon, "No weapon yet");
                return 'S';
                break;
            }
            case 'n':
            {
                info->playAgain = 0;
                return '0';
                break;
            }
            default:
            {
                erase();
                printw("Wrong input! Only (y) or (n) allowed!\n\n");   
                printw("Do you want to play again? (y)es / (n)o");
                break;
            }
        }
    }
    while(answer != 'y' || answer != 'n');
    return (0);
} 

