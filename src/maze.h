#ifndef MAZE_SRC_MAZE_H_
#define MAZE_SRC_MAZE_H_

// #include <iostream>
#include <vector>
#include <random>
#include <fstream>

#include "matrix_oop.h"

enum walls {
    kNothing,
    kRigthWall,
    kBottomWall,
    kBothWalls
};

class Maze{
public:

    Matrix &GenerateMaze(int height, int width);

    // Можно сделать вывод через std::cout << maze
    void PrintMaze();

    void SaveToFile(std::string filename);

    void LoadFromFile(std::string filename);

private:

    int GetRandomInt();

    Matrix matrix_{};

};

#endif // MAZE_SRC_MAZE_H_
