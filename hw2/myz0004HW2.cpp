/* Author:      Michael Zhao
 * Co-Author:   Rishin Kesarla
 * Course:      CSCE 1030.002
 * Date:        9/30/2019
 * Description: This program is for a package delivery service. The
 * 				user will enter a service type, a starting zip code,
 * 				and ending zip code, and the weight of the package, and
 * 				this program will check if the numbers are valid. The
 * 				Program will then calculate the total cost and output 
 * 				it to the user. Then, it will loop back and display the
 * 				menu, allowing the user to send another package. This
 * 				loop is ended when the user inputs the exit number.
 */

#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

// Enumerator for each service type
enum Service {AIR = 1, TRUCK = 2, COURIER = 3, EXIT = 4};

int main() {
	// Print out the standard header
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
    cout << "|        CSCE 1030 - Computer Science I        |" << endl;
    cout << "|  Michael Zhao   myz0004  myz0004@my.unt.edu  |" << endl;
    cout << "+----------------------------------------------+" << endl;
	cout << endl;

	// Declare constants for the price of each service
	const double AIR_COST = .295;
	const double TRUCK_COST = .165;
	const double COURIER_COST = .085;

	int service, startZip, endZip, zipCodeCost;
	double transportCost, weight, totalCost;
	string serviceName;

	// Loop while user has not exited
	do {
		// While the input isn't between 1 and 4
		// print out the menu for the user and get the input
		do {
			service = 0;
			cout << "+****************** M E N U *******************+" << endl;
			cout << "| Choose a Service for Package Delivery:       |" << endl;
    		cout << "| 1. FastShip Air            (EXPEDITED)       |" << endl;
			cout << "| 2. FastShip Freight Truck  (PRIORITY)        |" << endl;
			cout << "| 3. FastShip Local Courier  (STANDARD)        |" << endl;
			cout << "| 4. Exit                                      |" << endl;
    		cout << "+**********************************************+" << endl;
			cout << "----> ";
			cin >> service;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// Test for the input range and output the incorrect inputs
			if (service < 1 || service > 4) {
				cout << "Invalid selection (" << service << "). Enter options 1 - 4.\n" << endl;
			}
		} while (service < 1 || service > 4);
		
		// Check if the user exited
		if (service != 4) {
			// Evaluate the cost multiplier of the service
			Service serviceType = static_cast<Service>(service);
			switch (serviceType) {
				case AIR:
					transportCost = AIR_COST;
					serviceName = "EXPEDITED";
					break;
				case TRUCK:
					transportCost = TRUCK_COST;
					serviceName = "PRIORITY";
					break;
				case COURIER:
					transportCost = COURIER_COST;
					serviceName = "STANDARD";
					break;
			}
			
			// Get the ZIP code of the origin
			// and make sure it is in the range
			// Any non-integer input will evaluate to 0
			startZip = 0;
			do {
				cout << "Enter ZIP code of origin: ";
				cin >> startZip;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (startZip < 0 || startZip > 99999) {
					cout << "Invalid entry. ";
				}
			} while (startZip < 0 || startZip > 99999);

			// Get the ZIP code of the destination
			// and make sure it is in the range
			// Any non-integer input will evaluate to 0
			endZip = 0;
			do {
				cout << "Enter ZIP code of destination: ";
				cin >> endZip;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				if (endZip < 0 || endZip > 99999) {
					cout << "Invalid entry. ";
				}
			} while (endZip < 0 || endZip > 99999);

			// Get the weight of the parcel in pounds
			// and make sure it isn't negative
			weight = 0;
			do {
				cout << "Enter weight of parcel in pounds: ";
				cin >> weight;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if (weight <= 0) {
					cout << "Invalid entry. ";
				}
			} while (weight <= 0);

			// Calculate the cost based on the distance
			zipCodeCost = fabs(startZip - endZip);
			zipCodeCost /= 1000;

			// Compute the final cost and output it
			cout << zipCodeCost;
			cout << weight;
			totalCost = zipCodeCost * weight * transportCost;
			printf("FastShip %s Service: $%.2lf\n\n", serviceName.c_str(), totalCost);
		}
		
	} while (service != 4);

	// Print exit message
	cout << "Thank you for using FastShip Services!" << endl;

	return 0;
}
