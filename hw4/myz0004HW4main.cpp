/* Author:      Michael Zhao
 * Course:      CSCE 1030.002
 * Date:        12/3/2019
 * Description: This program is a game, where an ant army tries to conquer all
 * 				of the colonies. The army goes through a randomly generated 2D
 * 				dynamic array in columns. In each column, they pick a colony to
 * 				attack. There is only one correct colony, and they can advance
 * 				to the next one if they pick correctly, plus the remaining ants
 * 				in the column will be added to the army. However, if the incorrect
 * 				colony is chosen, then that many ants will die and the army has
 * 				to choose again. The goal is to go through all colonies with at
 * 				least 1 ant remaining, winning the game!
 */

#include "myz0004HW4.h"

// Main function
int main() {
	// Print header and description
	printHeader();
	printDescription();

	// declare variables
	int **colonies, pos, currCol = 1, numAnts = 0;
	bool emptyStateFile, loaded = false, advanced = false, quit = false;
	SaveState* states = new SaveState[SAVES];

	// Load save state if it exists
	if (isSaved(states)) {
		emptyStateFile = false;
		
		// See if the player wants to load
		if (getContinue()) {
			printSaveMenu(states);
			loaded = getSaveSlot(currCol, numAnts, colonies, states);
		}
	}
	else {
		emptyStateFile = true;
	}

	// Initiate colonies if not loaded and print
	if (!loaded) {
		initColonies(colonies, numAnts);
	}
	printColonies(colonies, currCol);
	
	// Game loop
	printStart(numAnts);
	while(numAnts > 0 && currCol < 10 && !quit) {
		// Get and process the next move
		pos = getInput(currCol);
		
		// Check to see if the player wants to save
		if (pos == 10) {
			quit = save(currCol, numAnts, colonies, states, emptyStateFile);
		}
		// Test for whether or not it was the correct move,
		// then change the colonies array and print results
		else if(isValidStatus(pos, currCol, numAnts, colonies)) {
			advanceArmy(pos, currCol, numAnts, colonies);
			advanced = true;
		}

		// Redisplay the updated colonies array
		printColonies(colonies, currCol, advanced);
		advanced = false;
	}

	// Test for loss
	if (!quit) {
		if (numAnts <= 0) {
			printLose(colonies);
		}
		else {
			printWin(numAnts);
		}
	}
	
	// Free up memory
	for (int i = 0; i < SIZE; i++) {
		delete colonies[i];
	}
	delete [] colonies;
	delete [] states;

	return 0;
}
