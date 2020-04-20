#include "myz0004HW4.h"

/* Function: 	printHeader
 * Parameters:  none
 * Return: 		none
 * Description: Prints standard header
 */
void printHeader() {
	cout << "     +----------------------------------------------+" << endl;
	cout << "     |       Computer Science and Engineering       |" << endl;
    cout << "     |        CSCE 1030 - Computer Science I        |" << endl;
    cout << "     |  Michael Zhao   myz0004  myz0004@my.unt.edu  |" << endl;
    cout << "     +----------------------------------------------+" << endl;
	cout << endl;
}

/* Function: 	printDescription
 * Parameters:  none
 * Return: 		none
 * Description: Prints description
 */
void printDescription() {
	cout << "           Welcome to Anthony's Battle!" << endl << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Anthony the ant has decided that he wants to take over all" << endl;
	cout << "the adjacent ant colonies with his army of ants from colo-" << endl;
	cout << "ny 'A'. To do this, Anthony's army will attempt to capture" << endl;
	cout << "ants from columns 'B' through 'J', with at least 1 ant re-" << endl;
	cout << "maining when the column 'J' ant colony is found. Each col-" << endl;
	cout << "umn's ant colony is identified with a 0 in one of the rows" << endl;
	cout << "for that column, while patrols are represented by integers" << endl;
	cout << "between 1 and 10 for the number of ants in that particular" << endl;
	cout << "patrol. On the way to column 'J' if Anthony's army encoun-" << endl;
	cout << "ters a patrol, the number in the patrol is subtracted from" << endl;
	cout << "Anthony's army total. Once his army finds the colony, how-" << endl;
	cout << "ever, any patrols not confronted will be added to his army" << endl;
	cout << "total. If Anthony makes really good decisions, then he can" << endl;
	cout << "take over all of the adjacent ant colonies; otherwise, his" << endl;
	cout << "army will be defeated!" << endl;
	cout << "----------------------------------------------------------" << endl << endl;
}

/* Function: 	initColonies
 * Parameters:  a 2D dynamic array representing the colonies matrix
 * 				an integer, representing the number of ants in the army
 * Return: 		none
 * Description: Randomly generates the colonies matrix, assigning a number [1, 10] to each cell
 */
void initColonies(int**& colonies, int& numAnts) {
	// Print message
	cout << "Initializing board..." << endl << endl;

	// Seed random generator
	srand(time(NULL));

	// Initialize colonies and assign each cell a random number
	colonies = new int*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		colonies[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++) {
			colonies[i][j] = rand() % 10 + 1;
		}
	}

	// Randomly set one cell in each column to be 0, the correct colony
	for (int i = 1; i < SIZE; i++) {
		colonies[rand() % 10][i] = 0;
	}

	// Count ants in first colony
	for (int i = 0; i < SIZE; i++) {
		numAnts += colonies[i][0];
	}
}

/* Function: 	printColonies
 * Parameters:  A 2D dynamic array that represents the colonies matrix
 * 				An integer representing the current colony
 * 				A boolean representing if the colony has advanced previously
 * Return: 		none
 * Description: Prints the matrix, showing ** for unvisited colonies and XX for
 * 				visited but incorrect colonies, and colors the captured colonies yellow
 */
void printColonies(int** colonies, int currCol, bool advanced) {
	// Print out column letters
	cout << "    A  B  C  D  E  F  G  H  I  J" << endl;
	cout << "  +-------------------------------+" << endl;
	
	// Loop through the rows
	for (int i = 0; i < SIZE; i++) {
		// Print out row numbers
		cout << " " << i << "| ";
		
		// Loop through the columns
		for (int j = 0; j < SIZE; j++) {
			// Print out appropriate symbol or numbers
			if (colonies[i][j] == -1) {
				cout << "XX ";
			}
			else if (currCol <= j) {
				cout << "** ";
			}
			else {
				if (advanced && j == currCol - 1) {
					cout << YELLOW;
				}
				cout << (colonies[i][j] < 10 ? "0" : "") << colonies[i][j] << " " << RESET;
			}
		}

		// Print closing pipe
		cout << "|" << endl;
	}

	// Print closing line
	cout << "  +-------------------------------+" << endl << endl;
}

/* Function: 	printColonies
 * Parameters:  A 2D dynamic array that represents the colonies matrix
 * 				An integer representing the current colony
 * Return: 		none
 * Description: Prints the matrix, showing ** for unvisited colonies and XX for
 * 				visited but incorrect colonies
 */
void printColonies(int** colonies, int currCol) {
	printColonies(colonies, currCol, false);
}

/* Function: 	printStart
 * Parameters:  An integer representing the number of ants in the army
 * Return: 		none
 * Description: Prints starting message
 */
void printStart(int numAnts) {
	cout << "Now let's begin... Anthony's army is " << numAnts << " strong!" << endl << endl;
}

/* Function: 	getInput
 * Parameters:  An integer representing the current column
 * Return: 		An integer representing the user input
 * Description: Gets the input from the user in the range and returns it
 */
int getInput(int currCol) {
	int input = -1;
	while (input < 0 || input > 10) {
		// Prompt for user input
		intInput(input, "Enter row position in column " + string(1, (char)(65 + currCol)) + " to strike (10 to save): ");
		
		// Check for error and print valid message
		if (input < 0 || input > 10) {
			cout << "Not a valid position. Please enter a position in the range [0-9]." << endl;
		}
	}
	cout << endl;
	
	return input;
}

/* Function: 	isValidStatus
 * Parameters:  An integer representing the input
 * 				An integer representing the current column
 * 				An integer representing the number of ants remaining
 * 				A 2D dynamic array representing the colonies matrix
 * Return: 		A boolean value representing the status
 * Description: Checks to see if an input is already selected or needs to be selected
 * 				Based on the result, it will return true if it is the correct colony,
 * 				or it will show a patrol already visited message, or if the colony is
 * 				a patrol, the number of ants will be removed and it will be visited
 */
bool isValidStatus(int input, int currCol, int& numAnts, int**& colonies) {
	// Check if it is the correct colony
	if (colonies[input][currCol] == 0) {
		return true;
	}
	// Check if it is already visited
	else if (colonies[input][currCol] == -1) {
		cout << BLUE << "Ant patrol at this location has already been removed." << RESET << endl << endl;
	}
	else {
		// Else remove patrol's ants from anthony's army and set that colony to visited
		numAnts -= colonies[input][currCol];
		colonies[input][currCol] = -1;
		cout << RED << "Anthony's army suffered casualties and has " << numAnts << " ants remaining." << RESET << endl << endl;
	}
	return false;
}

/* Function: 	advanceColony
 * Parameters:  An integer representing the input
 * 				An integer representing the current column
 * 				An integer representing the number of ants remaining
 * 				A 2D dynamic array representing the colonies matrix
 * Return: 		none
 * Description: Increments the current colony and adds up the remaining patrols to
 * 				Anthony's army
 */
void advanceArmy(int input, int& currCol, int& numAnts, int**& colonies) {
	int newAnts = 0;

	// Loop through the column to find new ants to capture
	for (int i = 0; i < SIZE; i++) {
		if (colonies[i][currCol] != -1 && colonies[i][currCol] != 0) {
			newAnts += colonies[i][currCol];
		}
	}

	// Increment ants and current column
	numAnts += newAnts;
	currCol++;

	// Print the ants captured
	cout << YELLOW << "Anthony's army found ant colony in column " << (char)(currCol + 65) << ", captured " << newAnts << " ants. (" << numAnts << " Total)" << RESET << endl << endl;
}

/* Function: 	printWin
 * Parameters:  An integer representing the number of ants in the army
 * Return: 		none
 * Description: Prints winning message
 */
void printWin(int numAnts) {
	cout << YELLOW << "Congratulations! Anthony has taken over all ant colonies with " << numAnts << " remaining!" << RESET << endl << endl;
}

/* Function: 	printLose
 * Parameters:  An 2D dynamic array that represents the colonies matrix
 * Return: 		none
 * Description: Prints losing message and reveal board
 */
void printLose(int** colonies) {
	cout << RED << "Sorry, but Anthony's army has been defeated before taking over all ant colonies." << RESET << endl << endl;
	printColonies(colonies, SIZE);
}

/* Function: 	isSaved
 * Parameters:  An array of objects of type SaveState that represents the save states
 * Return: 		A boolean representing whether or not there are previous save states
 * Description: Check to see if there is a valid save states file
 */
bool isSaved(SaveState*& states) {
	// Open save file
	ifstream in;
	in.open("save_states");

	// Check to see if the file is empty
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return false;
	}

	// Get save file info
	for (int i = 0; i < SAVES; i++) {
		in >> states[i].valid;
		if (states[i].valid == 1) {
			in >> states[i].time;
		}
	}

	// There is a save states file created that isn't empty
	in.close();
	return true;
}

/* Function: 	getContinue
 * Parameters:  none
 * Return: 		A boolean value representing whether or not the player wants to load a save
 * Description: Asks the user if they want to load up an old game state
 */
bool getContinue() {
	string s;
	cout << "Continue Game? (Y/N): ";
	getline(cin, s);
	cout << endl;
	if (toupper(s.at(0)) == 'Y') {
		return true;
	}
	return false;
}

/* Function: 	printSaveMenu
 * Parameters:  An array of objects of type SaveState that represents the save states
 * Return: 		none
 * Description: Prints a menu listing all of the save slots
 */
void printSaveMenu(SaveState* states) {
	cout << " +---------SAVE MENU---------+" << endl;
	for (int i = 0; i < SAVES; i++) {
		cout << " | Slot " << i + 1 << ": ";
		if (states[i].valid) {
			time_t now = states[i].time;
			cout << getDateAndTime(now) << " |" << endl;
		}
		else {
			cout << "EMPTY             |" << endl;
		}
	}
	cout << " +---------------------------+" << endl << endl;
}

/* Function: 	getDateAndTime
 * Parameters:  A time object representing the time in seconds since Jan 1, 1970
 * Return: 		A string representing the date in MM/DD/YY format
 * Description: Takes a time object and converts it to MM/DD/YY
 */
string getDateAndTime(time_t now) {
	// Declare stringstream and localtime pointer
	stringstream ss;
	tm* ltm = localtime(&now);
	
	// Get dates and add to stream
	ss << setfill('0');
	ss << setw(2) << 1 + ltm->tm_mon << "/";
	ss << setw(2) << ltm->tm_mday << "/";
	ss << setw(2) << to_string(1900 + ltm->tm_year).substr(2, 2) << " ";
	ss << setw(2) << ltm->tm_hour << ":";
	ss << setw(2) << ltm->tm_min << ":";
	ss << setw(2) << ltm->tm_sec;
	
	return ss.str();
}

/* Function: 	getSaveSlot
 * Parameters:  An integer representing the current colony
 * 				An integer representing the number of ants remaining
 * 				A 2D dynamic array matrix representing the colonies matrix
 * Return: 		A boolean representing whether or not they want to load
 * Description: Prompts the user for what slot to open or starting a new game
 */
bool getSaveSlot(int& currCol, int& numAnts, int**& colonies, SaveState* states) {
	int n = -1;

	// Loop until valid input entered
	while (n < 0 || n > 5) {
		intInput(n, "Enter a save slot (1-5) or 0 to start new game: ");
		cout << endl;
	
		// Check for valid input and valid save slot
		if (n < 0 || n > 5) {
			cout << "Please enter a valid number." << endl << endl;
			printSaveMenu(states);
		}
		else if (n == 0) {
			return false;
		}
		else if (!states[n - 1].valid) {
			cout << "Save slot empty." << endl << endl;
			printSaveMenu(states);
			n = -1;
		}
	}

	// Print loading message
	cout << "Loading save slot " << n << "..." << endl << endl;

	// Open file
	ifstream in;
	in.open("save_" + to_string(n - 1));

	// Get the data from the file chosen
	in >> currCol >> numAnts;
	colonies = new int*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		colonies[i] = new int[SIZE];
		for (int j = 0; j < SIZE; j++) {
			in >> colonies[i][j];
		}
	}

	in.close();
	return true;
}

/* Function: 	save
 * Parameters:  An integer representing the current colony
 * 				An integer representing the number of ants remaining
 * 				A 2D dynamic array representing the colonies matrix
 * 				An array of object of type SaveState that represents the save states
 * 				A boolean representing whether or not a state file was created
 * Return: 		A boolean representing whether or not the game should exit
 * Description: Saves the current game state into the selected slot
 */
bool save(int currCol, int numAnts, int** colonies, SaveState* states, bool emptyStateFile) {
	int slot = -1;

	// Loop until correct input
	while (slot < 0 || slot > 5) {
		printSaveMenu(states);

		// Prompt for input
		intInput(slot, "Enter slot to save in (1-5) or 0 to cancel save: ");
		cout << endl;

		// Check if the input in the range
		if (slot < 0 || slot > 5) {
			cout << "Please enter a valid number" << endl << endl;
		}
		else if (slot == 0) {
			return false;
		}
		else if (states[slot - 1].valid) {
			// Check if the user wants to override a file
			char over = 'A';
			while (over != 'Y' && over != 'N') {
				cout << "Are you sure you want to override your save? (Y/N): ";
				cin >> over;
				cin.clear();
				cout << endl;
				over = toupper(over);
				if (over != 'Y' && over != 'N') {
					cout << "Please enter Y or N" << endl << endl;
				}
			}

			if (over == 'N') {
				return false;
			}
		}
	}
	
	// Write to state file
	states[slot - 1].valid = true;
	states[slot - 1].time = time(0);
	addToStates(states, emptyStateFile);

	// Open output file
	ofstream out;
	out.open("save_" + to_string(slot - 1), ios::trunc);

	// Write to file
	out << currCol << " " << numAnts << endl;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			out << colonies[i][j] << " ";
		}
		out << endl;
	}
	
	// See if the player wants to continue the game
	char cont;
	cout << "Saved game! Do you want to continue the game? (Y/N): ";
	cin >> cont;
	cin.clear();
	cout << endl;
	if (toupper(cont) == 'Y') {
		return false;
	}

	cout << "Save Slot " << slot << endl;
	cout << "----------" << endl;
	cout << "Num Ants: " << numAnts << endl;
	cout << "Game State: " << endl;
	out.close();
	return true;
}

/* Function: 	addToStates
 * Parameters:  An array of objects of type SaveState that represents the save states
 * 				A boolean representing whether or not a save state file was created
 * Return: 		none
 * Description: Writes to the save states file
 */
void addToStates(SaveState* states, bool emptyStateFile) {
	// Check for empty save file
	if (emptyStateFile) {
		for (int i = 0; i < SAVES; i++) {
			states[i].valid = false;
		}
	}

	// Open file
	ofstream out ("save_states", ios::trunc);

	// Save info for all files
	for (int i = 0; i < SAVES; i++) {
		if (states[i].valid) {
			out << 1 << " " << states[i].time << endl;
		}
		else {
			out << 0 << endl;
		}
	}

	out.close();
}

/* Function: 	intInput
 * Parameters:  An integer to store the input into
 * 				A string representing the prompt
 * Return: 		none
 * Description: Prompts for input, checks for an integer, clears the buffer
 */
void intInput(int& var, string prompt) {
	cout << prompt;
	cin >> var;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << prompt;
		cin >> var;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
