#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * \file maze.c
 * \brief Provides maze-related functionalities
 *
 * \details This source file implements all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

/* The function to read the maze from a file given the filename, maze
   array, maze width and maze height: open file, read sizes, read maze, close file
*/
// TODO: write the entirety of this readMaze function
int readMaze(char fileName[], char maze[][200], int* width, int* height) {
  FILE* input = fopen(fileName, "r");
  char dump;
  // check that file opened
  if (input == NULL) {
    return -1;
  }
  // fill maze information from file
  fscanf(input, "%d", width);
  fscanf(input, "%d", height);
  fscanf(input, "%c", &dump);
  for (int i = 0; i < *height; i++) {
	  for (int j = 0; j < *width; j++) {
      // check if character was read
		  char check = fscanf(input, "%c", &maze[i][j]);
    	if (check != 1) {
        return -2;
		  }
	  }
	  fscanf(input, "%c", &dump);
  }
  if (ferror(input)) {
    return -2;
  }
  fclose(input);
  return 0;
}


/* The function to write the maze to a file given the filename, maze
   array, maze width and maze height: open file, write maze, close file
*/
// TODO: write the entirety of this writeMaze function
int writeMaze(char fileName[], char maze[][200], int width, int height) {
  FILE* output = fopen(fileName, "w");
  // check if file opened
  if (output == NULL) {
    return -4;
  }
  fprintf(output, "%d %d\n", width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // check if printing was successful
      if (fprintf(output, "%c", maze[i][j]) < 0) {
        return -5;
      }
    }
    fprintf(output, "\n");
  }
  if (ferror(output)) {
    return -5;
  }
  fclose(output);
  return 0;
}

// The function to solve a solution path recursively
int solvePath(char maze[][200], const int maze_width, const int maze_height, const int col, const int row, char sol[][200]) {
  // path found
  if (maze[row][col] == '<') {
    return 0;
  }
  else if (maze[row][col] == '#' || sol[row][col] == '1') {
    return 1;
  }
  // path visited = '1', non-visited = '0'
  sol[row][col] = '1';
  // map path if correct
  if (solvePath(maze, maze_width, maze_height, col - 1, row, sol) == 0) {
    sol[row][col] = '*';
    return 0;
  }
  else if (solvePath(maze, maze_width, maze_height, col + 1, row, sol) == 0) {
    sol[row][col] = '*';
    return 0;
  }
  else if (solvePath(maze, maze_width, maze_height, col, row - 1, sol) == 0) {
    sol[row][col] = '*';
    return 0;
  }
  else if (solvePath(maze, maze_width, maze_height, col, row + 1, sol) == 0) {
    sol[row][col] = '*';
    return 0;
  }
  // no solution found
  return 1;
}

// The function to solve a solution path for the maze
int solveMaze(char maze[][200], const int maze_width, const int maze_height, char sol[][200]) {
  int startHeight;
  int startWidth;
  // mark all of sol[][] as unvisited
  for (int i = 0; i < maze_height; i++) {
    for (int j = 0; j < maze_width; j++) {
      sol[i][j] = '0';
      // find entrance
      if (maze[i][j] == '@') {
        startHeight = i;
        startWidth = j;
      }
    }
  }
  // determine if a path exists
  return solvePath(maze, maze_width, maze_height, startWidth, startHeight, sol);
}


// The function to generate a maze (given)
void genMaze(char maze[][200], const int maze_width, const int maze_height, const double threshold, const int seed) {
  // set random seed
  srand(seed);
  // gen start and end positions
  int start_x = rand() % (maze_width - 2) + 1;
  int start_y = rand() % (maze_height - 2) + 1;
  int end_x = rand() % (maze_width - 2) + 1;
  int end_y = rand() % (maze_height - 2) + 1;
  // gen maze
  for (int r = 0; r < maze_height; ++r) {
    for (int c = 0; c < maze_width; ++c) {
      if (r == 0 || c == 0 || r == maze_height - 1 || c == maze_width - 1) maze[r][c] = '#';
      else if (c == start_x && r == start_y) maze[r][c] = '@';
      else if (c == end_x && r == end_y) maze[r][c] = '<';
      else {
        double rand_value = rand() / (double) RAND_MAX;
        if (rand_value >= threshold) maze[r][c] = '#';
        else maze[r][c] = ' ';
      }
    }
  }
}


