#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Grid.h"

using namespace std;;

bool find_maze_path(Grid& maze, int row, int col, int level, vector<string>& solution)
{
    if (row < 0 || row >= maze.height()|| col < 0 || col >= maze.width() || level < 0 || level >= maze.depth()) {
        return false;
    }
    if (maze.at(row, col, level) != 1) {
        return false;
    }

    maze.at(row, col, level) = 2;
    solution.push_back(to_string(row) + " " + to_string(col) + " " + to_string(level));
    if (row == maze.height() - 1 && col == maze.width() - 1 && level == maze.depth() - 1) {
        return true;
    }

    if (find_maze_path(maze, row + 1, col, level, solution)) {
        return true;
    }
    if (find_maze_path(maze, row - 1, col, level, solution)) {
        return true;
    }
    if (find_maze_path(maze, row, col + 1, level, solution)) {
        return true;
    }
    if (find_maze_path(maze, row, col - 1, level, solution)) {
        return true;
    }
    if (find_maze_path(maze, row, col, level + 1, solution)) {
        return true;
    }
    if (find_maze_path(maze, row, col, level - 1, solution)) {
        return true;
    }

    solution.pop_back();
    return false;
}


int main(int argc, char* argv[])
{
    Grid maze;
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    in >> maze;


    vector<string> solution;

    bool found = find_maze_path(maze, 0, 0, 0, solution);

    if (found == true)
    {
        out << "SOLUTION" << endl;
        for (size_t i = 0; i < solution.size(); i++) {
            out << solution[i] << endl;
        }
    }
    else{
        out << "NO SOLUTION" << endl;
    }
    return 0;
}
