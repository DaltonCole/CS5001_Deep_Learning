#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "point.h"
#include "config.h"

using namespace std;

class Board {
	public:
		vector<vector<Point> > board;
		vector<Point> tiles;
		vector<Point> donuts;
		Point* tinny_tim;
		Point* donut_point;
		Config config;

		Board(const Config& c);
		void print_direction();
		void print_value();
		void print_type();
		void q_learning();
		void place_donut();
		void move_tinny_tim();
		void save_board_to_file();
};

// [y][x]
Board::Board(const Config& c) {
	// Set config
	config = c;

	// Initalize random state;
	for(int i = 0; i < 10; i++) {
		board.push_back(vector<Point>());
		for(int j = 0; j < 10; j++) {
			board[i].push_back(Point(j, i));
		}
	}

	// Initalize walls
	for(int i = 0; i < 10; i++) {
		board[0][i].type = wall;
		board[9][i].type = wall;
		board[i][0].type = wall;
		board[i][9].type = wall;
	}
	board[2][2].type = wall;
	board[3][2].type = wall;
	board[4][2].type = wall;
	board[6][4].type = wall;
	board[7][4].type = wall;
	board[8][4].type = wall;
	board[2][4].type = wall;
	board[2][5].type = wall;
	board[2][6].type = wall;
	board[4][6].type = wall;
	board[5][6].type = wall;
	board[6][6].type = wall;

	// Initalize tile squares
	board[1][3].type = tile;
	board[2][7].type = tile;
	board[3][4].type = tile;
	board[5][2].type = tile;
	board[6][5].type = tile;
	board[6][7].type = tile;
	board[7][2].type = tile;

	// Donut tile
	board[1][1].type = donut;
	board[1][8].type = donut;
	board[8][1].type = donut;
	board[8][8].type = donut;
	donut_point = nullptr;
}

void Board::print_direction() {
	try {
		Direction d;
		for(auto x : board) {
			for(auto y : x) {
				if(y.type == wall) {
					cout << "W ";
				} else {
					d = y.max_dir();
					if(d == north) {
						cout << "↑ ";
					} else if(d == east) {
						cout << "→ ";
					} else if(d == south) {
						cout << "↓ ";
					} else if(d == west) {
						cout << "← ";
					}
				}
			}
			cout << endl;
		}
	} catch(...) {
		cout << "Unicode is better!" << endl;
	}
}

void Board::print_value() {
	cout << fixed;
	for(auto x : board) {
		for(auto y : x) {
			if(y.type == wall) {
				cout << "W\t";
			} else {
				cout << setprecision(3) << y.max_value() << "\t";
			}
		}
		cout << endl;
	}
}

// Print type of each point
void Board::print_type() {
	for(auto x : board) {
		for(auto y : x) {
			if(y.type == empty) {
				cout << "  ";
			} else if(y.type == wall) {
				cout << "w ";
			} else if(y.type == tile) {
				cout << "t ";
			} else if(y.type == donut) {
				cout << "d ";
			}
		}
		cout << endl;
	}
}

void Board::q_learning() {
	// Randomly place tinny tim
	while(true) {
		tinny_tim = &board[rand() % 10][rand() % 10];
		// Make sure Tim is not in a wall
		if(tinny_tim -> type != wall) {
			break;
		}
	}

	for(unsigned long long i = 0; i < config.evalutations; i++) {
		// Print progress
		if(i % 100000 == 0) {
			cout << i << " / " << config.evalutations << "\r" << flush;
		}

		// Select an Action
		place_donut();
		// Do Action, calculate new Q
		move_tinny_tim();
	}

	cout << endl;

	return;
}

void Board::place_donut() {
	// If there is no donut currently on the board
	if(donut_point == nullptr) {
		// Probability of placing a donut
		if(rand() % 100 <= config.new_donut * 100) {
			// Randomly select one of the four corners;
			int rand_num = rand() % 4;
			if(rand_num == 0) {
				donut_point = &board[1][1];
			} else if(rand_num == 1) {
				donut_point = &board[1][8];
			} else if(rand_num == 2) {
				donut_point = &board[8][1];
			} else {
				donut_point = &board[8][8];
			}
		}
	}

	return;
}

void Board::move_tinny_tim() {
	int rand_num = rand() % 4;
	float reward = 0;
	Direction d;

	// Spot Tinny Tim will move to
	Point* new_tinny_tim;

	// Move in a random direction
	if(rand_num == 0) { // Go North
		d = north;
		new_tinny_tim = &board[tinny_tim -> y - 1][tinny_tim -> x];
	} else if(rand_num == 1) { // Go East
		new_tinny_tim = &board[tinny_tim -> y][tinny_tim -> x + 1];
		d = east;
	} else if(rand_num == 2) { // Go South
		new_tinny_tim = &board[tinny_tim -> y + 1][tinny_tim -> x];
		d = south;
	} else if(rand_num == 3) { // Go West
		new_tinny_tim = &board[tinny_tim -> y][tinny_tim -> x - 1];
		d = west;
	}

	// If move fails, move New Tim in a random direction
	if(rand() * 100 >= config.move_succed) {
		rand_num = rand() % 4;
		if(rand_num == 0) {
			new_tinny_tim = &board[tinny_tim -> y - 1][tinny_tim -> x];
		} else if(rand_num == 1) {
			new_tinny_tim = &board[tinny_tim -> y][tinny_tim -> x + 1];
		} else if(rand_num == 2) {
			new_tinny_tim = &board[tinny_tim -> y + 1][tinny_tim -> x];
		} else {
			new_tinny_tim = &board[tinny_tim -> y][tinny_tim -> x - 1];
		}
	}

	// If Tim gets a donut
	if(new_tinny_tim -> type == donut && new_tinny_tim == donut_point) {
		reward += config.donut_reward;
		donut_point = nullptr;
	}

	// If Tim gets hit by a tile
	if(new_tinny_tim -> type == tile) {
		// Probability of getting hit by a tile
		if(rand() % 100 <= config.tile_fall * 100) {
			reward += config.tile_reward;
		}
	}

	// If Tim runs into a wall
	if(new_tinny_tim -> type == wall) {
		reward += config.wall_reward;
		// Move Tim back
		new_tinny_tim = tinny_tim;
	}

	// Calculate new Q value
	tinny_tim -> value[d] += (config.td_step_size * (reward + config.discount_rate * 
		(new_tinny_tim -> max_value()) - (tinny_tim -> value[d])));

	// Move Tim
	tinny_tim = new_tinny_tim;

	return;
}

ostream& operator <<(ostream& os, Board b) {
	// Direction Value Type
	for(auto i : b.board) {
		for(auto j : i) {
			os << j.max_dir() << " " << setprecision(4) << j.max_value() << " " << j.type << "\t";
		}
	}

	return os;
}

void Board::save_board_to_file() {
	ofstream file("./graph/" + to_string(config.random_seed));

	if(file.is_open()) {
		file << *this << endl;
	} else {
		cout << "Error opening file './graph'" + to_string(config.random_seed) << endl;
	}

	return;
}

#endif