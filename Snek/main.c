#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define GRID_SIZE 25

void print_grid(char grid[GRID_SIZE][GRID_SIZE])
{
	// Clear the console
	system("cls");

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			printf(" %c ", grid[i][j]);
		}
		printf("\n");
	}
}

int try_move(int new_x, int new_y, char grid[GRID_SIZE][GRID_SIZE])
{
	if (new_x >= GRID_SIZE || new_y >= GRID_SIZE)
	{
		return 0;
	}

	if (new_x < 0 || new_y < 0)
	{
		return 0;
	}

	if (grid[new_y][new_x] != '.')
	{
		return 0;
	}

	return 1;
}

int main()
{
	// Seed the random number generator with the current time.
	srand((unsigned)time(NULL));

	char grid[GRID_SIZE][GRID_SIZE];

	// Initialize grid
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			grid[i][j] = '.';
		}
	}

	// Get the starting location of the snake
	char snake = 'A';
	int x_location = rand() % GRID_SIZE;
	int y_location = rand() % GRID_SIZE;

	grid[y_location][x_location] = snake;

	// Loop the walking
	while (1)
	{
		// Display the current grid
		print_grid(grid);

		// Calculate the snake's next position
		int next_move = rand() % 4;
		int snake_moved = 0;
		for (int i = 0; i < 4; ++i)
		{
			int new_x = x_location;
			int new_y = y_location;
			switch (next_move)
			{
			case 0:
				// Move up
				--new_y;
				break;
			case 1:
				// Move right
				++new_x;
				break;
			case 2:
				// Move down
				++new_y;
				break;
			case 3:
				// Move left
				--new_x;
				break;
			}

			// Try to move the snake. If the move attempt is successful,
			// move the snake.
			if (try_move(new_x, new_y, grid))
			{
				++snake;
				if (snake > 'Z')
				{
					snake = 'A';
				}

				grid[new_y][new_x] = snake;
				x_location = new_x;
				y_location = new_y;
				snake_moved = 1;
				break;
			}

			// Otherwise, get ready for the next loop.
			++next_move;
			if (next_move > 3)
			{
				next_move = 0;
			}
		}

		// If the snake didn't move, we're done.
		if (!snake_moved)
		{
			break;
		}

		// Sleep the thread.
		Sleep(500);
	}

	return 0;
}