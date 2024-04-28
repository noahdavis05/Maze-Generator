/**
 * @file mazeGenerator.c
 * @author Noah Davis sc23nd@leeds.ac.uk
 * @brief 
 * @version 3
 * @date 2024-03-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * @brief This struct will represent my maze as an array of this struct
 *
 */
typedef struct
{
    int xPosition;
    int yPosition;
    char value;
} Square;

// I will use these values as globals for ease of use.
int width;
int height;
int length;

//functions

/**
 * @brief returns a file with the specified filename
 *
 * @param filename a string which is the name of the file
 * @param mode a char which specifies how the file will be opened e.g. 'r' for read
 * @return FILE*
 */
static FILE *openFile(char filename[], char mode[])
{
    FILE *file = fopen(filename, mode);
    if (file == NULL)
    {
        printf("Invalid file\n");
        exit(2);
    }
    return file;
}

/**
 * @brief This function is used to generate a random integer between two numbers.
 * 
 * @details Note rand must be seeded in the function this is called in.
 * 
 * @param min integer for the lower number
 * @param max intger for the higher number
 * @return int returns a random int between params.
 */
int randint(int min, int max)
{
    if (max <= min)
    {
        exit(1);
    }
    return (rand() % (max - min + 1)) + min;
}

/**
 * @brief Takes a maze parameter and fills all the Squares inside with the correct X,Y and '#' for value
 * 
 * @param maze A pointer to an array of Squares.
 */
void createMaze(Square *maze)
{
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            maze[count].value = '#';
            maze[count].xPosition = j;
            maze[count].yPosition = i;
            count++;
        }
    }
}

/**
 * @brief prints the maze into the terminal with spaces between characters to make it more readable.
 * 
 * @details This function isn't needed for the program but was used during development for testing.
 * 
 * @param maze 
 */
void displayMaze(Square *maze)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                printf("%c ", maze[width * i + j].value);

        }
        printf("\n");
    }
}

void saveMaze(Square *maze, char filename[]){
    FILE *myFile = openFile(filename,"w");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {


            fprintf(myFile,"%c", maze[width * i + j].value);

        }
        fprintf(myFile,"\n");
    }
}


/**
 * @brief This function returns the index of a Square with the given x and y parameters.
 * 
 * @param maze A pointer to an array of Squares.
 * @param x An integer for x co-ordinate.
 * @param y An integer for y co-ordinate.
 * @return int Returns the index of the square.
 */
int getPos(Square *maze, int x, int y){

    for (int i = 0; i < length; i++){
        if (maze[i].xPosition == x && maze[i].yPosition == y){
            return i;
        }
    }
    return -1;
}

/**
 * @brief This function checks that a given set of co-ordinates is within the maze
 * 
 * @param x Integer for an x co-ordinate.
 * @param y Integer for a y co-ordinate.
 * @return int Returns 1 if in maze and 0 if not.
 */
int inMaze(int x, int y){
    if (x < 0 || x > width -1 || y < 0 || y > height -1){
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if a given set of co-ordinates can be moved to.
 * 
 * @details For example if the value of the Square is ' ' you can't move there, or if the co-ordinate is outside the maze.
 * 
 * @param maze A pointer to an array of Squares.
 * @param x An integer for x co-ordinate.
 * @param y An integer for y co-ordinate.
 * @return int Returns 1 if valid and 0 if not.
 */
int isValidMove(Square *maze, int x, int y){
    // check destination cell is a wall and that it is within boundaries
    int tempPos = getPos(maze, x, y);
    if (maze[tempPos].value == ' '){
        return 0;

    }
    if (x < 0 || x > (width - 1) || y < 0 || y > (height -1) ){
        return 0;
    }
    return 1;
}

/**
 * @brief This function carves out a maze.
 * 
 * @details This is done using a recursive backtracking algorithm. Which I learnt about from here: https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
 * 
 * @param maze A pointer to an array of Squares.
 * @param x An integer for x co-ordinate.
 * @param y An integer for y co-ordinate.
 */
void generateMaze(Square *maze,int x, int y){
    // mark cell as visited
    int pos = getPos(maze,x,y);
    if (pos >= 0){
        maze[pos].value = ' ';
    }

    // define the directions the player could go
    // Define the directions to move (up, down, left, right)
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    // Randomly shuffle the directions
    for (int i = 0; i < 4; ++i) {
        int j = rand() % 4;
        int tempX = directions[i][0];
        int tempY = directions[i][1];
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = tempX;
        directions[j][1] = tempY;
    }

    // explore each direction
    for (int i = 0; i < 4; i++){
        int newX = x + directions[i][0] * 2;
        int newY = y + directions[i][1] * 2;

        if (isValidMove(maze,newX,newY) == 1) {
            // make the space infront a path
            int tempPos = getPos(maze,(x + directions[i][0]),(y + directions[i][1]));
            if (tempPos != -1){
                maze[tempPos].value = ' ';

                generateMaze(maze, newX, newY);
            }
        } 
    }
}

/**
 * @brief This function is used to work out the furthest point in the maze from the start to be made the end.
 * 
 * @details To do this a depth first search is implemented using recursion.
 * 
 * @param maze A pointer to an array of Squares.
 * @param x An integer to show the current x position.
 * @param y An integer to show the current y position.
 * @param maxDistance A pointer to an integer variable which is used to count how far away a square is from the start.
 * @param endX A pointer to an integer which is used to store the x co-ord of the current furthest point.
 * @param endY A pointer to an integer which is used to store the y co-ord of the current furthest point.
 * @param startX The x co-ord of the position where the maze starts.
 * @param startY The y co-ord of the position where the maze starts.
 */
void furthestPoint(Square *maze, int x, int y, int *maxDistance, int *endX, int *endY, int startX, int startY) {
    // Check if current position is within maze bounds and if so return
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    // Check
    int pos = y * width + x;
    if (maze[pos].value == '#' || maze[pos].value == 'V') {
        return;  
    }

    // Mark current square as visited
    maze[pos].value = 'V';  // Mark as visited

    // Check if current position is further than previous furthest point
    int distance = abs(x - startX) + abs(y - startY);  // Distance from starting point
    if (distance > *maxDistance) {
        *maxDistance = distance;
        *endX = x;
        *endY = y;
    }

    // Explore neighboring squares
    furthestPoint(maze, x + 1, y, maxDistance, endX, endY, startX, startY);  // Right
    furthestPoint(maze, x - 1, y, maxDistance, endX, endY, startX, startY);  // Left
    furthestPoint(maze, x, y + 1, maxDistance, endX, endY, startX, startY);  // Down
    furthestPoint(maze, x, y - 1, maxDistance, endX, endY, startX, startY);  // Up
}

/**
 * @brief This function turns some random walls into paths.
 * 
 * @details Currently there is only one path through the maze, this makes it easy to solve although the path may be long.
 *          Therefore, this function is used to make more paths for the user to follow and will lead them to some dead ends.
 *          And may also provide a shortcut, but overall it increases difficulty.
 *  
 * @param maze A pointer to an array of Squares.
 * @param changes An integer to choose how many walls will be turned into paths.
 */
void randomPaths(Square *maze,int changes){
    int changeCount = 0;
    while (changeCount < changes){
        //generate a random position
        int randNum = randint(0,length - 1);
        if (maze[randNum].value == '#'){
            changeCount++;
            maze[randNum].value = ' ';
        }
    }
}

/**
 * @brief This function adds some difficulty to the start of the maze by guranteeing that there are multiple moves the player can start with.
 * 
 * @param maze A pointer to an array of squares.
 * @param startX Integer for the starting x co-ordinate.
 * @param startY Integer for the starting y co-ordinate.
 */
void addDificulty(Square *maze, int startX, int startY){
    if (inMaze(startX + 1, startY) == 1){
        int tempPos = getPos(maze, startX + 1, startY);
        maze[tempPos].value = ' ';
    }
        if (inMaze(startX - 1, startY) == 1){
        int tempPos = getPos(maze, startX - 1, startY);
        maze[tempPos].value = ' ';
    }
        if (inMaze(startX , startY + 1) == 1){
        int tempPos = getPos(maze, startX, startY + 1);
        maze[tempPos].value = ' ';
    }
        if (inMaze(startX, startY - 1) == 1){
        int tempPos = getPos(maze, startX, startY - 1);
        maze[tempPos].value = ' ';
    }
}

int main(int argc, char *argv[]){
    // seed random
    srand(time(NULL));
    if (argc != 4)
    {
        return 1;
    }
    char *filename = argv[1];
    width = atoi(argv[2]);
    height = atoi(argv[3]);
    if (width < 2 || height < 2){
        printf("Number too small");
        return 1;
    }
    length = width * height;

    // fill the maze with walls
    Square *maze = malloc(length * sizeof(Square));
    if (maze == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
     return 1;
    }

    createMaze(maze);

    int startPos = randint(0,length - 1);


    generateMaze(maze,maze[startPos].xPosition,maze[startPos].yPosition);

    //only do these steps if maze length greater than 64 otherwise not affective
    if (length >= 64){
        double paths = randint(1, ceil(length*0.02));
        int path = paths;
        randomPaths(maze,paths);
        addDificulty(maze,maze[startPos].xPosition,maze[startPos].yPosition);
    }

    // Find the furthest point in the maze using DFS
    int maxDistance = 0;
    int endX = 0;
    int endY = 0;
    furthestPoint(maze, maze[startPos].xPosition, maze[startPos].yPosition, &maxDistance, &endX, &endY,maze[startPos].xPosition,maze[startPos].yPosition);

    maze[startPos].value = 'S';
    int endPos = getPos(maze, endX, endY);
    maze[endPos].value = 'E';

    // go through maze and change all 'V' to ' '
    for (int i = 0; i < length; i++){
        if (maze[i].value == 'V'){
            maze[i].value = ' ';
        }
    }

    displayMaze(maze);
    saveMaze(maze, filename);

    free(maze);
    return 0;

}