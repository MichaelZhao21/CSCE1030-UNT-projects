/* Author:      Michael Zhao
 * Course:      CSCE 1030.002
 * Date:        10/27/2019
 * Description: This program will create a randomly generated
 * 				map of pheromone levels between any colonies,
 * 				storing these values in a 2D array. The program will
 * 				also record the visited colonies using a normal
 * 				array. The program will visit each colony exactly
 * 				once, taking the shortest path (lowest phermone
 * 				level) each time. The program will then print out
 * 				the table of values with the path.
 */

#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cctype>
#include <ctime>
using namespace std;

// Declare global enumerator for each ant colony
enum Colony {A = 0, B, C, D, E, F, G, H, I, J};

// Declare constant integer for size
const int SIZE = 10;

// function prototypes
void printHeader();
void printDescription();
void getLevels(int levels[SIZE][SIZE]);
void printLevels(int levels[SIZE][SIZE]);
bool isVistied(int visited[SIZE], int colony);
int getLowestLevel(int levels[SIZE][SIZE], int visited[SIZE], int colony);
void printVisited(int visited[SIZE]);

// Main function
int main() {
	// declare variables
	int levels[SIZE][SIZE], visited[SIZE] = {0};

	// Fill matrix randomly
	getLevels(levels);

	// Until the ant has visited each colony, move to the colony with the lowest
	// pheromone levels
	visited[0] = 0;
	for (int i = 1; i < SIZE; i++) {
		visited[i] = getLowestLevel(levels, visited, visited[i - 1]);
	}

	// Prints header, description, colonies, and the path
	printHeader();
	printDescription();
	printLevels(levels);
	printVisited(visited);

	return 0;
}

/* Function: 	printHeader
 * Parameters:  none
 * Return: 		none
 * Description: Prints standard header
 */
void printHeader() {
	cout << "              +----------------------------------------------+" << endl;
	cout << "              |       Computer Science and Engineering       |" << endl;
    cout << "              |        CSCE 1030 - Computer Science I        |" << endl;
    cout << "              |  Michael Zhao   myz0004  myz0004@my.unt.edu  |" << endl;
    cout << "              +----------------------------------------------+" << endl;
	cout << endl;
}

/* Function: 	printDescription
 * Parameters:  none
 * Return: 		none
 * Description: Prints description
 */
void printDescription() {
	cout << "            W e l c o m e   t o   A n t h o n y ' s   h u n c h" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "This program will set up a matrix that represents the pheromone levels" << endl;
	cout << "between ant colonies. Anthony's objective is to find a path least" << endl;
	cout << "taken by the other ants in the hopes of finding food to last through the" << endl;
	cout << "winter." << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << endl;
}

/* Function: 	getLevels
 * Parameters:  a 2D int array that holds the pheromone levels
 * Return: 		None
 * Description: This function randomly assigns values to
 * 				a 2D array between [1-20], except when the column
 * 				and row numbers are equal (assigned 0)
 */
void getLevels(int levels[][SIZE]) {
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i != j) {
				levels[i][j] = (rand() % 20) + 1;
			}
			else {
				levels[i][j] = 0;
			}
		}
	}
	return;
}

/* Function: 	printLevels
 * Parameters:  a 2D int array that holds the pheromone levels
 * Return: 		None
 * Description: This function prints out the contents of a 2D array
 */
void printLevels(int levels[][SIZE]) {
	cout << "Ant Colonies:" << endl << endl;
	cout << "    A  B  C  D  E  F  G  H  I  J" << endl;
	cout << "   ------------------------------" << endl;
	for (int i = 0; i < SIZE; i++) {
		cout << (char)(65 + i) << " | ";
		for (int j = 0; j < SIZE; j++) {
			int currNum = levels[i][j];
			if (currNum < 10) {
				cout << 0;
			}
			cout << currNum << " ";
		}
		cout << endl;
	}
	return;
}

/* Function: 	isVisited
 * Parameters: 	an integer array that holds the visited colonies
 * 			   	a 2D integer array that holds the pheromone levels
 * Return: 		a boolean that signifies if the cell is visited or not
 * Description: This function returns if the colony has been visited before
 */
bool isVisited(int visited[], int colony) {
	for (int i = 0; i < SIZE; i++) {
		if (visited[i] == colony) {
			return true;
		}
	}
	return false;
}

/* Function: 	getLowestLevel
 * Parameters:  a 2D integer array that holds the pheomone levels
 * 				an integer array that holds the visited colonies
 * 				an integer that represents the colony number
 * Return: 		an integer representing the colony number that has the lowest level
 * Description: This function, given a row, finds the lowest number column's index
 * 				of the columns that haven't been visited before
 */
int getLowestLevel(int levels[][SIZE], int visited[], int colony) {
	int lowestNum = INT_MAX, lowestIndex = -1;
	for (int i = 0; i < SIZE; i++) {
		if (!isVisited(visited, i) && levels[colony][i] != 0 && levels[colony][i] < lowestNum) {
			lowestNum = levels[colony][i];
			lowestIndex = i;
		}
	}
	return lowestIndex;
}

/* Function: 	printVisited
 * Parameters:  an integer array that holds the visited colonies
 * Return: 		None
 * Description: This function prints out the visited colonies
 * 				in a single line, with an endline at the end
 */
void printVisited(int visited[]) {
	cout << endl << " The path followed by Anthony is:" << endl << endl;
	for (int i = 0; i < SIZE; i++) {
		char letter;
		switch (visited[i]) {
			case A:
				letter = 'A';
				break;
			case B:
				letter = 'B';
				break;
			case C:
				letter = 'C';
				break;
			case D:
				letter = 'D';
				break;
			case E:
				letter = 'E';
				break;
			case F:
				letter = 'F';
				break;
			case G:
				letter = 'G';
				break;
			case H:
				letter = 'H';
				break;
			case I:
				letter = 'I';
				break;
			default:
				letter = 'J';
				break;
		}
		if (i != 0) {
			cout << " ----> ";
		}
		cout << letter;
	}
	cout << endl;
	return;
}
