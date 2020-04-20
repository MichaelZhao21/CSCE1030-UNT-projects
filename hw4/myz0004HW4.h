#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

#define RESET "\033[0m"
#define RED "\033[91m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"

using namespace std;

// Size constants
const int SIZE = 10;
const int SAVES = 5;

// Declare struct for holding save states
struct SaveState {
	bool valid;
	time_t time;
};

// function prototypes
void printHeader();
void printDescription();
void initColonies(int**& colonies, int& numAnts);
void printColonies(int** colonies, int currCol, bool advanced);
void printColonies(int** colonies, int currCol);
void printStart(int numAnts);
int getInput(int currCol);
bool isValidStatus(int input, int currCol, int& numAnts, int**& colonies);
void advanceArmy(int input, int& currCol, int& numAnts, int**& colonies);
void printWin(int numAnts);
void printLose(int** colonies);
bool isSaved(SaveState*& states);
bool getContinue();
void printSaveMenu(SaveState* states);
bool getSaveSlot(int& currCol, int& numAnts, int**& colonies, SaveState* states);
bool save(int currCol, int numAnts, int** colonies, SaveState* states, bool emptySaveFile);
string getDateAndTime(time_t now);
void addToStates(SaveState* states, bool emptySaveFile);
void intInput(int& var, string prompt);
