#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "print_functions.h"

/**
 * \file hw3.c
 * \brief The main driver function of HW 3
 *
 * \details This source file implements the main function for HW 3. It checks the input command line arguments and calls the corresponding modules.
 */

int main(int argc, char* argv[]) {
  int return_code = 0;
  
  // check input arguments
  // solve maze: ./hw3 <maze_file>
  // gen maze: ./hw3 <maze_file> <width> <height> [threshold = 0.5] [seed = 0]

  //check number of arguments
  if (argc != 2 && argc != 4 && argc != 5 && argc != 6) {
    return_code = 2;
  }
  else {
    char maze[200][200];
    int maze_width = 0;
    int maze_height = 0;
    if (argc == 2) { // solve maze if maze file provided
      // read maze file if possible
      return_code = readMaze(argv[1], maze, &maze_width, &maze_height);
      if (!return_code) {
        // print maze
        printMaze(maze, maze_width, maze_height);
        // solve maze
        char soln[200][200];  
        return_code = solveMaze(maze, maze_width, maze_height, soln);
        // if maze solved print solution
        if (return_code == 0) {
          printSolution(maze, maze_width, maze_height, soln);
        }
      }
    }
    else { // gen maze
      // parse input arguments
      int seed = 0;
      double threshold = 0.5;
      maze_width = atoi(argv[2]);
      maze_height = atoi(argv[3]);
      if (argc == 6) {
        seed = atoi(argv[5]);
        threshold = atof(argv[4]);
      }
      else if (argc == 5) {
        threshold = atof(argv[4]);
      }
      // check for input errors
      if (maze_width < 0 || maze_width > 200 || maze_height < 0 || maze_height > 200) {
        return_code = -3;
      }
      else {
        // gen maze
        genMaze(maze, maze_width, maze_height, threshold, seed);
        // print maze
        printMaze(maze, maze_width, maze_height);        // write maze
        return_code = writeMaze(argv[1], maze, atoi(argv[2]), atoi(argv[3]));
      }
    }
  }
  
  // print error if necessary
  if (return_code) printError(return_code);
  
  return return_code;
}
