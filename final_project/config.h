#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

class Config {
	public:
		// Configurations
		int random_seed;
		float discount_rate;
		float td_step_size;
		unsigned long long evalutations;

		// Probabilities
		float new_donut;
		float tile_fall;
		float move_succed;

		// Rewards
		float donut_reward;
		float tile_reward;
		float wall_reward;

		Config() {
			// Initialize Probabilities
			new_donut = 0.25;
			tile_fall = 0.5;
			move_succed = 0.82;

			// Initialize Rewards
			donut_reward = 10;
			tile_reward = -10;
			wall_reward = -1;

			// Default values
			random_seed = time(NULL);
			discount_rate = 0.1;
			td_step_size = 0.1;
			evalutations = 99999999;

			// Open file
			ifstream file("configuration.txt");

			string type, value;

			// If file is open
			if(file.is_open()) {
				// While there is input
				while(file >> type >> value) {
					// If value is null, use default value
					if(value == "null") {
						continue;
					} else if(type == "Random_Seed") {
						random_seed = stoi(value);
					} else if(type == "Discount_Rate") {
						discount_rate = stof(value);
					} else if(type == "TD_Step_Size") {
						td_step_size = stof(value);
					} else if(type == "Evaluations") {
						evalutations = stoull(value);
					}
				}
			} else {
				cout << "Error opening configuration.txt" << endl;
			}
		}
};

#endif