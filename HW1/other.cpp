#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const double learning_rate = 0.001;
const double number_of_iterations = 150000000;

int main() {
	srand (time(NULL));

	int x0 = 1;
	double w0 = rand() % 20000;
	double w1 = rand() % 20000;

	vector<int> x1;
	vector<int> y;
	vector<double> error_list;

	int temp_x1;
	int temp_y;

	double error0;
	double error1;

	double y_bar;

	double sum_of_squares;

	ifstream myfile("zdata.txt");
	if(myfile.is_open()) {
		while(myfile >> temp_x1 >> temp_y) {
			x1.push_back((temp_x1));
			y.push_back((temp_y));
		}
		myfile.close();
	}

	for(int i = 0; i < number_of_iterations; i++) {
		for(int j = 0; j < x1.size(); j++) {
			y_bar = (x0 * w0) + (x1[j] * w1);

			error0 = error0 + ((y[j] - y_bar) * x0);
			error1 = error1 + ((y[j] - y_bar) * x0);
		}

		error0 /= x1.size();
		error1 /= x1.size();

		w0 = w0 + (learning_rate * error0);
		w1 = w1 + (learning_rate * error1);
	}

	
	for(int i = 0; i < x1.size(); i++) {
		sum_of_squares += ((y[i] - ((x0 * w0) + x1[i] * w1)) * (y[i] - ((x0 * w0) + x1[i] * w1)));
	}

	cout << "CS-5001 : HW#1 : Regression with one variable." << endl;
	cout << "Programmer: Dalton Russell Cole" << endl << endl;
	cout << "Learning rate eta = " << learning_rate << endl;
	cout << "After " << number_of_iterations << " iterations:" << endl;
	cout << "Sum of Squares Errors = " << sum_of_squares << endl;
	cout << "Weights:" << endl;
	cout << "w0 = " << w0 << endl;
	cout << "w1 = " << w1 << endl;
}