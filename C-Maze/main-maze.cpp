/* 
Edited by: Shageldi Ovezov
Using backtracking to find a treasure and an exit in a maze
*/

#include <iostream> // for i/o
#include <fstream> // for file handling
#include <vector>
#include <string>
#include "stdlib.h" // for the system command
#include "CTurtle.hpp"
namespace ct = cturtle;
using namespace std;


class Maze {
private:
	int rows = 0;
	int cols = 0;
	vector <vector <char>> mazeVect; // Matrix of chars
	int startRow;
	int startCol;

	// symbols for the first recursive search
	char PART_OF_PATH = ' ';
	char TRIED = '.';
	char OBSTACLE = '+';
	char DEAD_END = '-';

	// symbols for the second recursive search to find the exit
	char PART_OF_PATH2 = '-';
	char TRIED2 = '^';
	char DEAD_END2 = '#';

	vector<int> start;

	int treasure = 0;
	bool traversed = false;

	string wait;

public: 
	Maze() {
		cout << "Default constructor called.\n" << endl;
	}

	vector<int> findStart() {
		/*identify the starting position*/
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				if (mazeVect[i][j] == 'S') {
					startRow = i;
					startCol = j;
				}

			}
		}
		start.push_back(startRow);
		start.push_back(startCol);
		return start;
	}

	void readMaze(string fileName) {
		/*read the map file to a vector*/
		string line;
		ifstream readFile (fileName);
		int lineCount = 0;

		if (!readFile.is_open()) {// Checking for errors opening the file
			cout << ("Error opening file.");
			return;
		}
		while (getline(readFile, line)) {// Reading file until the end is reached or an error occurs
			vector <char> thisLine;
			for (unsigned int i = 0; i < line.length(); ++i) {
				thisLine.push_back(line[i]);
			}
			mazeVect.push_back(thisLine);
			lineCount++;
		}

		if (readFile.bad()) { // More error checking
			cout << ("Error reading file.");
			return;
		}

		readFile.close();
		rows = mazeVect.size();			// Updating class attributes "rows" and "cols"
		cols = mazeVect[0].size();
		cout << "There are " << rows << " rows, and " << cols << " columns.\n\n";
		return;
	}

	void printMaze() {
		/*print the maze*/
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				cout << mazeVect[i][j];
			}
			cout << endl;
		}
		cout << endl;

		return;
	}

	
	void updatePosition(int row, int col, int val = NULL) {
		/* move by updating the position*/

		if (val) {
			mazeVect[row][col] = val;  // set the symbol to current coordinate
		}

	}


	bool searchFrom(int startRow, int startCol) {
		/*traverse through whole maze and look for treasure*/
		
		Sleep(5);
		system("cls");
		printMaze();
		
		char currStep = mazeVect[startRow][startCol];
		
		if (currStep == 'T') {
			treasure++;          // increment if T was encountered

		}

		if (currStep == OBSTACLE || (isExit(startRow, startCol) && !traversed)) {  // check if it is a wall
			cout << "False" << endl;
			return false;
		}

		if (currStep == TRIED || currStep == DEAD_END) {  // check whether we already tried this position or dead end
			cout << "False" << endl;
			return false;
		}

		if (isExit(startRow, startCol)) {  // see if it is an exit
			if (traversed) {
				updatePosition(startRow, startCol, PART_OF_PATH);
				cout << "is exit" << endl;
				
				if (treasure) {
					cout << "Treasure found" << endl;
				}
				
				return true;
			}
		}
		
		mazeVect[startRow][startCol] = TRIED;

		bool found = false;
		found = (searchFrom(startRow - 1, startCol) || searchFrom(startRow + 1, startCol) || searchFrom(startRow, startCol - 1) || searchFrom(startRow, startCol + 1));
		
		if (found) {
			updatePosition(startRow, startCol, PART_OF_PATH);
		}
		else {
			updatePosition(startRow, startCol, DEAD_END);
		}

		return found;
	
	}


	bool isExit(int row, int col) {
		/*check if it reached the exit*/
		return (row == 0 || row == rows - 1 || col == 0 || col == cols - 1);

	}

	bool findExit(int startRow, int startCol) {
		/*find the exit recursively*/

		cout << "\nLet's go to exit" << endl;

		Sleep(10);
		system("cls");
		printMaze();

		char currStep = mazeVect[startRow][startCol];

		cout << "Row: " << startRow << " Col: " << startCol << " " << currStep << endl;
		if (currStep == OBSTACLE) {
			return false;
		}

		if (currStep == TRIED2 || currStep == DEAD_END2) {  // check whether we already tried this position or dead end
			return false;
		}

		if (isExit(startRow, startCol)) {   // see if it is an exit
		
				updatePosition(startRow, startCol, PART_OF_PATH2);
				
				return true;	
		}

		mazeVect[startRow][startCol] = TRIED2;
		bool found = false;
		found = (findExit(startRow - 1, startCol) || findExit(startRow, startCol - 1) || findExit(startRow + 1, startCol) || findExit(startRow, startCol + 1));

		if (found) {
			updatePosition(startRow, startCol, PART_OF_PATH2);
		}
		else {
			updatePosition(startRow, startCol, DEAD_END2);
		}

		return found;
	}

	int treasureFound() {
		/*return the number of treasures found*/
		return treasure;
	}

};



int main() {

	Maze myMaze;
	string mazeName;
	cout << "Enter the maze name: ";
	cin >> mazeName;

	myMaze.readMaze(mazeName);  // read the maze
	
	myMaze.printMaze();  // print the maze
	
	vector<int> start;
	start = myMaze.findStart();   // get starting points
	myMaze.searchFrom(start[0], start[1]);  // traverse the maze

	cout << "Done with the search!" << endl;
	
	Sleep(1000);  // pause for a second

	myMaze.findExit(start[0], start[1]);   // find the exit

	cout << "\nWe found " << myMaze.treasureFound() << " treasure(s)" << endl;

	cout << "\nPress Enter to exit... THE END";
	getchar();
	return 0;
};
