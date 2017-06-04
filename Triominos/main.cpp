#include "main.h"

int main(int argc, char** argv)
{
	int dimension, hole_x, hole_y, initializer, value;
	std::vector<std::vector<int>> grid;

	std::cout << "Please note that any invalid input will restart the process." << std::endl;

	while (true)
	{
		initializer = value = -1;

		std::cout << "Please enter the grid dimension (has to be an integer, greater that 1, and a power of 2) > ";
		std::cin >> dimension;
		if (std::cin.fail() || dimension <= 1 || dimension & (dimension - 1) != 0)
		{
			std::cout << "The input is not a valid dimension!" << std::endl;
			continue;
		}

		std::cout << "Please enter the X coordinate of the hole (0 based index) > ";
		std::cin >> hole_x;
		if (std::cin.fail() || hole_x < 0 || hole_x > dimension - 1)
		{
			std::cout << "The input is not a valid coordinate!" << std::endl;
			continue;
		}

		std::cout << "Please enter the Y coordinate of the hole (0 based index) > ";
		std::cin >> hole_y;
		if (std::cin.fail() || hole_y < 0 || hole_y > dimension - 1)
		{
			std::cout << "The input is not a valid coordinate!" << std::endl;
			continue;
		}

		allocate_grid(grid, dimension);
		initialize_grid(grid, dimension, value++);
		set_hole(grid, hole_x, hole_y, value++);
		value = divide_and_conquer(grid, dimension, 0, 0, initializer, value);
		print_grid(grid, dimension, count_digits(value) + 1);
		deallocate_grid(grid, dimension);
	}

	return 0;
}

void allocate_grid(std::vector<std::vector<int>> &grid, int dimension)
{
	grid.resize(dimension);
	for (int height_index = 0; height_index < dimension; ++height_index)
	{
		grid[height_index].resize(dimension);
	}
}

void deallocate_grid(std::vector<std::vector<int>> &grid, int dimension)
{
}

void initialize_grid(std::vector<std::vector<int>> &grid, int dimension, int initializer)
{
	for (int height_index = 0; height_index < dimension; ++height_index)
	{
		for (int width_index = 0; width_index < dimension; ++width_index)
		{
			grid[height_index][width_index] = initializer;
		}
	}
}

void print_grid(std::vector<std::vector<int>> &grid, int dimension, int width)
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;

	for (int height_index = 0; height_index < dimension; ++height_index)
	{
		for (int width_index = 0; width_index < dimension; ++width_index)
		{
			SetConsoleTextAttribute(hConsole, (grid[height_index][width_index] % 14) + 2);

			std::cout << std::setw(width);
			std::cout << grid[height_index][width_index];
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	SetConsoleTextAttribute(hConsole, 7);
}

void set_hole(std::vector<std::vector<int>> &grid, int hole_x, int hole_y, int hole_value)
{
	grid[hole_y][hole_x] = hole_value;
}

bool has_hole(std::vector<std::vector<int>> &grid, int dimension, int start_x, int start_y, int initializer)
{
	bool has_hole = false;

	for (int height_index = 0; height_index < dimension; ++height_index)
	{
		for (int width_index = 0; width_index < dimension; ++width_index)
		{
			if (grid[start_y + height_index][start_x + width_index] != initializer)
			{
				has_hole = true;
				break;
			}
		}

		if (has_hole)
		{
			break;
		}
	}

	return has_hole;
}

int count_digits(int number)
{
	int digits = 0;

	do
	{
		number /= 10;
		digits++;
	} while (number != 0);

	return digits;
}

int divide_and_conquer(std::vector<std::vector<int>> &grid, int dimension, int start_x, int start_y, int initializer, int value)
{
	if (dimension == 2)
	{
		for (int height_index = 0; height_index < dimension; ++height_index)
		{
			for (int width_index = 0; width_index < dimension; ++width_index)
			{
				if (grid[start_y + height_index][start_x + width_index] == initializer)
				{
					grid[start_y + height_index][start_x + width_index] = value;
				}
			}
		}

		value++;
	}
	else
	{
		int
			new_dimension = dimension / 2,
			start_x_nw = start_x, start_y_nw = start_y,
			corner_x_nw = start_x_nw + new_dimension - 1, corner_y_nw = start_y_nw + new_dimension - 1,
			start_x_ne = start_x + new_dimension, start_y_ne = start_y,
			corner_x_ne = start_x_ne, corner_y_ne = start_y_ne + new_dimension - 1,
			start_x_sw = start_x, start_y_sw = start_y + new_dimension,
			corner_x_sw = start_x_sw + new_dimension - 1, corner_y_sw = start_y_sw,
			start_x_se = start_x + new_dimension, start_y_se = start_y + new_dimension,
			corner_x_se = start_x_se, corner_y_se = start_y_se;

		if (!has_hole(grid, new_dimension, start_x_nw, start_y_nw, initializer))
		{
			grid[corner_y_nw][corner_x_nw] = value;
		}

		if (!has_hole(grid, new_dimension, start_x_ne, start_y_ne, initializer))
		{
			grid[corner_y_ne][corner_x_ne] = value;
		}

		if (!has_hole(grid, new_dimension, start_x_sw, start_y_sw, initializer))
		{
			grid[corner_y_sw][corner_x_sw] = value;
		}

		if (!has_hole(grid, new_dimension, start_x_se, start_y_se, initializer))
		{
			grid[corner_y_se][corner_x_se] = value;
		}

		value++;

		value = divide_and_conquer(grid, new_dimension, start_x_nw, start_y_nw, initializer, value);
		value = divide_and_conquer(grid, new_dimension, start_x_ne, start_y_ne, initializer, value);
		value = divide_and_conquer(grid, new_dimension, start_x_sw, start_y_sw, initializer, value);
		value = divide_and_conquer(grid, new_dimension, start_x_se, start_y_se, initializer, value);
	}

	return value;
}