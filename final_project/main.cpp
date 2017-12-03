#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "config.h"

using namespace std;

int main() {
	// Initalize configurations
	Config config;

	// Set up random seed
	srand(config.random_seed);

	// Create a board
	Board map(config);

	// Perform Q-learning
	map.q_learning();

	// Print direction graph, value graph, type graph
	map.print_direction();
	cout << endl;
	map.print_value();
	cout << endl;
	map.print_type();

	// Save board to file
	map.save_board_to_file();

	return 0;
}