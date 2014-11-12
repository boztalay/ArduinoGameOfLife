#include "ledGrid.h"

#define GRID_SIZE 8
int cells[][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 1, 1, 0, 0, 0},
                  {0, 0, 0, 1, 0, 1, 0, 0},
                  {0, 0, 0, 1, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0}};

void setup() {
  // Nothing to do
}

void loop() {
  displayGame();
  gameTick();
}

void displayGame() {
  reset();
  
  int imageToDisplay = 0x0000;
  
  for(int i = 2; i < 6; i++) {
    for(int j = 2; j < 6; j++) {
      imageToDisplay = imageToDisplay << 1;
      imageToDisplay = imageToDisplay | cells[i][j];
    }
  }
  
  writeImage(imageToDisplay, 25);
}

void gameTick() {
  int updatedCells[GRID_SIZE][GRID_SIZE];
  
  for(int i = 0; i < GRID_SIZE; i++) {
    for(int j = 0; j < GRID_SIZE; j++) {
      int numNeighbors = calcNeighbors(i, j);
      int currentCell = cells[i][j];
      
      if(currentCell == 1) {
        if(numNeighbors == 2 || numNeighbors == 3) {
          updatedCells[i][j] = 1; 
        } else {
          updatedCells[i][j] = 0;
        }
      } else if(currentCell == 0) {
        if(numNeighbors == 3) {
          updatedCells[i][j] = 1; 
        } else {
          updatedCells[i][j] = 0;
        }
      }
    }
  }
  
  for(int i = 0; i < GRID_SIZE; i++) {
    for(int j = 0; j < GRID_SIZE; j++) {
      cells[i][j] = updatedCells[i][j];
    }
  }
}

int calcNeighbors(int x, int y) {
  int neighbors = 0;
 
  for(int i = (x - 1); i < (x + 2); i++) {
    for(int j = (y - 1); j < (y + 2); j++) {
      int neighborCellX = (i + GRID_SIZE) % GRID_SIZE;
      int neighborCellY = (j + GRID_SIZE) % GRID_SIZE;
      
      if(neighborCellX == x && neighborCellY == y) {
        continue; 
      }
      
      neighbors += cells[neighborCellX][neighborCellY];
    } 
  }
  
  return neighbors;
}
