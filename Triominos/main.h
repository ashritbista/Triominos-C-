#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <windows.h>

void allocate_grid(std::vector<std::vector<int>> &grid, int dimension);
void deallocate_grid(std::vector<std::vector<int>> &grid, int dimension);
void initialize_grid(std::vector<std::vector<int>> &grid, int dimension, int initializer);
void print_grid(std::vector<std::vector<int>> &grid, int dimension, int width);
void set_hole(std::vector<std::vector<int>> &grid, int hole_x, int hole_y, int hole_value);
bool has_hole(std::vector<std::vector<int>> &grid, int dimension, int start_x, int start_y, int initializer);
int count_digits(int number);
int divide_and_conquer(std::vector<std::vector<int>> &grid, int dimension, int start_x, int start_y, int initializer, int value);