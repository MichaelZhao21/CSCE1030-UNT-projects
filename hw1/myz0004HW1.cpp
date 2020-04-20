/* Author:      Michael Zhao
 * Course:      CSCE 1030.002
 * Date:        9/7/2019
 * Description: This program will take a user-specified height and weight
 *              of an object, and it will compute the amount of time for
 *              the object to reach the ground, the velocity that it has
 *              when it reaches the ground, and the kinetic energy at that
 *              moment.
 */

#include <iostream>
#include <cmath>
using namespace std;

double const ACC_TO_GRAVITY = 9.8; // Acceleration due to gravity
double const FEET_TO_METERS = 0.3048; // Conversion factor for feet to meters

int main() {
    // Print out the standard header
    cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
    cout << "|        CSCE 1030 - Computer Science I        |" << endl;
    cout << "|  Michael Zhao   myz0004  myz0004@my.unt.edu  |" << endl;
    cout << "+----------------------------------------------+" << endl;

    // Initialize variables
    int height;
    double mass, time, velocity, energy;

    // Gets the height in feet
    cout << "Enter height from which the object is being dropped (in ft): ";
    cin >> height;

    // Gets the mass in kg
    cout << "Enter mass of the object (in kg): ";
    cin >> mass;

    // Calculates the time it takes to reach the ground
    time = sqrt(2 * (height * FEET_TO_METERS) / ACC_TO_GRAVITY);

    // Calculates the velocity when it hits the ground
    velocity = time * ACC_TO_GRAVITY;

    // Calculates the Kinetic energy when it hits the ground
    energy = .5 * mass * pow(velocity, 2);

    // Print out the calculated values to specific decimal values
    printf("The time taken by the object to reach the ground is %.3lf seconds.\n", time);
    printf("The velocity at which the object strikes the ground is %.2lf meters per second.\n", velocity);
    printf("The kinetic energy at the moment of impact with the ground is %.4lf Joules.\n", energy);

    return 0;
}
