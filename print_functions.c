#include "print_functions.h"
#include <stdio.h>

/**
 * \file print_functions.c
 * \brief Provides print-related functionalities
 *
 * \details This source file implements all print-related functionalities for printing the maze, solution, and errors
 */

// The function to print the maze
void printMaze(char maze[][200], const int maze_width, const int maze_height) {
  printf("Maze: %d, %d\n", maze_width, maze_height);
  for (int i = 0; i < maze_height; i++) {
    for (int j = 0; j < maze_width; j++) {
      printf("%c", maze[i][j]);
    }
    printf("\n");
  }
}

// The function to print the maze's solution
void printSolution(char maze[][200], const int maze_width, const int maze_height, char sol[][200]) {
  printf("Solution path (*):\n");
  for (int i = 0; i < maze_height; i++) {
    for (int j = 0; j < maze_width; j++) {
      // print "*" if path, otherwise print maze
      if (sol[i][j] == '*' && maze[i][j] != '@') {
          printf("%c", sol[i][j]);
      }
      else {
        printf("%c", maze[i][j]);
      }
    }
    printf("\n");
  }
}

// The function to print the error message
void printError(const int return_code) {
  switch (return_code) {
    case 1:
      printf("Info: No solution found for the input maze\n");
      break;
    case 2:
      printf("Generate maze usage: ./hw3 <maze file> <width> <height> [threshold = 0.5] [seed = 0]\n");
      printf("Solve maze usage: ./hw3 <maze file>\n");
      break;
    case -1:
      printf("Cannot open the file to read\n");
      break;
    case -2:
      printf("File read errors\n");
      break;
    case -3:
      printf("Invalid parameters\n");
      break;
    case -4:
      printf("Cannot open the file to write\n");
      break;
    case -5:
      printf("File write errors\n");
      break;
  }

}
