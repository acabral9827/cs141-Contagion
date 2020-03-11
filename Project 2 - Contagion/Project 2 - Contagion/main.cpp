/* Prog2Contagion.cpp

   Program #2: Play the game of Contagion against another person
			   This is a variation of Ataxx, a version of which can
			   be played online at: http://www.classikgames.com/ataxx.html
   Class: CS 141
   Date: 1/27/2019
   Author: Alejandro Cabral

   Grading Rubric:
	 55% Passes Codio run-time tests (some cases below are split into multiple tests)
		  5 Handles both upper and lower case user input
		  5 Handles making adjacent move for each player
		 10 Handles making jump move for each player
		  5 Handles pass move
		  2 Error message and retry when source position does not belong to player
		  2 Error message and retry when destination position is not empty
		  6 Error message and retry when destination is not one or two squares away
			in horizontal, vertical, or diagonal line
		 15 Flips opponent pieces adjacent to move destination
		  5 When board is filled correctly identifies winner and exits program

	 45% Programming Style:
		 10 Meaningful Identifier Names.
		 10 Comments, header, and meaningful variable names
		 10 Functional Decomposition
		 10 Appropriate data and control structures
		  5 Code Layout
*/
#include <iostream>
#include <cstdlib>   // for exit() and abs()
using namespace std;

// The 25 board position variables may be global variables, but no other variables may be global.
char  p1, p2, p3, p4, p5,
p6, p7, p8, p9, p10,
p11, p12, p13, p14, p15,
p16, p17, p18, p19, p20,
p21, p22, p23, p24, p25;


//-----------------------------------------------------------------------------------------
// Display the game instructions
void displayInstructions()
{
	cout << " \n"
		<< "Welcome to the 2-player game of Contagion, where the point of the game is    \n"
		<< "to capture as much of the board as possible.  On each move you must enter \n"
		<< "the row and column position of one of your current pieces (e.g. a1) and   \n"
		<< "the row and column of an empty destination, which must be one or two      \n"
		<< "squares away.  Moves can be made horizontally, vertically, or diagonally. \n"
		<< " \n"
		<< "If the destination is one square away, then an additional piece for you   \n"
		<< "is placed in the destination square.  If the destination is two squares   \n"
		<< "away (a jump move), then the original piece is moved to that destination. \n"
		<< "jumping over a single square or any player's piece.                       \n"
		<< " \n"
		<< "After a piece has been moved, all opponent pieces adjacent to the         \n"
		<< "destination are changed to match the piece of the user making the move.   \n"
		<< "Player X moves first.     \n"
		<< " \n"
		<< "A valid first move, for instance, could be: a1 a2  which since it is just \n"
		<< "one square away, would put an additional X on square a2.  Alternatively   \n"
		<< "if the first move is:  a1 c3  then since it is two squares away, the piece\n"
		<< "currently at a1 would be moved to destination c3.                         \n"
		<< endl;
}


//-----------------------------------------------------------------------------------------
// Display the board, using the global board variables
// For reference here are the board row, col and board variable values:
//       1  2  3  4  5
//    ----------------
//  A |  1  2  3  4  5
//  B |  6  7  8  9 10
//  C | 11 12 13 14 15
//  D | 16 17 18 19 20
//  E | 21 22 23 24 25
//
void displayBoard()
{
	cout << "    1   2   3   4   5  \n"
		<< "  ---------------------\n"
		<< "A | " << p1 << " | " << p2 << " | " << p3 << " | " << p4 << " | " << p5 << " | A \n"
		<< "  |---|---|---|---|---| \n"
		<< "B | " << p6 << " | " << p7 << " | " << p8 << " | " << p9 << " | " << p10 << " | B \n"
		<< "  |---|---|---|---|---| \n"
		<< "C | " << p11 << " | " << p12 << " | " << p13 << " | " << p14 << " | " << p15 << " | C \n"
		<< "  |---|---|---|---|---| \n"
		<< "D | " << p16 << " | " << p17 << " | " << p18 << " | " << p19 << " | " << p20 << " | D \n"
		<< "  |---|---|---|---|---| \n"
		<< "E | " << p21 << " | " << p22 << " | " << p23 << " | " << p24 << " | " << p25 << " | E \n"
		<< "  ---------------------\n"
		<< "    1   2   3   4   5  \n"
		<< endl;
}

char getValueAt(char row, char col)
{
	// Retrieve the character stored at that particular piece index
	if (row == 'A' && col == '1') return p1;
	else if (row == 'A' && col == '2') return p2;
	else if (row == 'A' && col == '3') return p3;
	else if (row == 'A' && col == '4') return p4;
	else if (row == 'A' && col == '5') return p5;

	else if (row == 'B' && col == '1') return p6;
	else if (row == 'B' && col == '2') return p7;
	else if (row == 'B' && col == '3') return p8;
	else if (row == 'B' && col == '4') return p9;
	else if (row == 'B' && col == '5') return p10;

	else if (row == 'C' && col == '1') return p11;
	else if (row == 'C' && col == '2') return p12;
	else if (row == 'C' && col == '3') return p13;
	else if (row == 'C' && col == '4') return p14;
	else if (row == 'C' && col == '5') return p15;

	else if (row == 'D' && col == '1') return p16;
	else if (row == 'D' && col == '2') return p17;
	else if (row == 'D' && col == '3') return p18;
	else if (row == 'D' && col == '4') return p19;
	else if (row == 'D' && col == '5') return p20;

	else if (row == 'E' && col == '1') return p21;
	else if (row == 'E' && col == '2') return p22;
	else if (row == 'E' && col == '3') return p23;
	else if (row == 'E' && col == '4') return p24;
	else if (row == 'E' && col == '5') return p25;
}


void setValueAt(char row, char col, char newValue)
{
	if (row == 'A' && col == '1') p1 = newValue;
	else if (row == 'A' && col == '2') p2 = newValue;
	else if (row == 'A' && col == '3') p3 = newValue;
	else if (row == 'A' && col == '4') p4 = newValue;
	else if (row == 'A' && col == '5') p5 = newValue;

	else if (row == 'B' && col == '1') p6 = newValue;
	else if (row == 'B' && col == '2') p7 = newValue;
	else if (row == 'B' && col == '3') p8 = newValue;
	else if (row == 'B' && col == '4') p9 = newValue;
	else if (row == 'B' && col == '5') p10 = newValue;

	else if (row == 'C' && col == '1') p11 = newValue;
	else if (row == 'C' && col == '2') p12 = newValue;
	else if (row == 'C' && col == '3') p13 = newValue;
	else if (row == 'C' && col == '4') p14 = newValue;
	else if (row == 'C' && col == '5') p15 = newValue;

	else if (row == 'D' && col == '1') p16 = newValue;
	else if (row == 'D' && col == '2') p17 = newValue;
	else if (row == 'D' && col == '3') p18 = newValue;
	else if (row == 'D' && col == '4') p19 = newValue;
	else if (row == 'D' && col == '5') p20 = newValue;

	else if (row == 'E' && col == '1') p21 = newValue;
	else if (row == 'E' && col == '2') p22 = newValue;
	else if (row == 'E' && col == '3') p23 = newValue;
	else if (row == 'E' && col == '4') p24 = newValue;
	else if (row == 'E' && col == '5') p25 = newValue;

}

int indexAt(char row, char col)
{
	int index;
	if (row == 'A' && col == '1') index = 1;
	else if (row == 'A' && col == '2') index = 2;
	else if (row == 'A' && col == '3') index = 3;
	else if (row == 'A' && col == '4') index = 4;
	else if (row == 'A' && col == '5') index = 5;

	else if (row == 'B' && col == '1') index = 6;
	else if (row == 'B' && col == '2') index = 7;
	else if (row == 'B' && col == '3') index = 8;
	else if (row == 'B' && col == '4') index = 9;
	else if (row == 'B' && col == '5') index = 10;

	else if (row == 'C' && col == '1') index = 11;
	else if (row == 'C' && col == '2') index = 12;
	else if (row == 'C' && col == '3') index = 13;
	else if (row == 'C' && col == '4') index = 14;
	else if (row == 'C' && col == '5') index = 15;

	else if (row == 'D' && col == '1') index = 16;
	else if (row == 'D' && col == '2') index = 17;
	else if (row == 'D' && col == '3') index = 18;
	else if (row == 'D' && col == '4') index = 19;
	else if (row == 'D' && col == '5') index = 20;

	else if (row == 'E' && col == '1') index = 21;
	else if (row == 'E' && col == '2') index = 22;
	else if (row == 'E' && col == '3') index = 23;
	else if (row == 'E' && col == '4') index = 24;
	else if (row == 'E' && col == '5') index = 25;

	return index;
}

/*void flip( char baseRow, char baseCol, char adjRow, char adjCol, char playerToMove )
{
	setValueAt( )
}*/

// Make a move
void moveFrom(char oldRow, char oldCol,   // row,col position of where we're moving from
	char newRow, char newCol,   // row,col position of where we're moving TO
	char playerToMove)         // The player to move: 'X' or 'O'
{
	// checking if valid move
	int rowDifference = abs(oldRow - newRow);   //For valid move should be 0 or 1
	int colDifference = abs(oldCol - newCol);

	// Validate adjacent move
	if ((rowDifference == 0 && colDifference == 1) ||
		(rowDifference == 1 && colDifference == 0) ||
		(rowDifference == 1 && colDifference == 1))
	{
		// make the adjacent move
		setValueAt(newRow, newCol, playerToMove);
	}
	else        // jump move or error
	{
		if (getValueAt(oldRow, oldCol) != playerToMove)
		{
			cout << "*** Invalid move.  Current piece must belong to you. Please retry." << endl;
		}
		else if (getValueAt(newRow, newCol) != ' ')
		{
			cout << "*** Invalid move.  Destination must be empty. Please retry." << endl;
		}
		else if ((rowDifference >= 3) && (colDifference >= 3))
		{
			cout << "*** Invalid move.  A move must be one or two squares away. Please retry." << endl;
		}

		else if ((rowDifference < 3) && (colDifference < 3))
		{
			getValueAt(oldRow, oldCol);

			setValueAt(oldRow, oldCol, ' ');
			setValueAt(newRow, newCol, playerToMove);

		}
	}
}

int checkScore(char startRow, char startCol)
{
	int numberOfX = 0;
	int numberOfO = 0;
	for (startRow = 'A'; startRow <= 'E'; startRow++)
	{
		for (startCol = '1'; startCol <= '5'; startCol++)
		{
			if (getValueAt(startRow, startCol) == 'X')
			{
				numberOfX++;
			}
			else if (getValueAt(startRow, startCol) == 'O')
			{
				numberOfO++;
			}
		}
	}

	if (numberOfX > numberOfO)
	{
		cout << "X Wins!" << endl << endl;
	}
	else if (numberOfO > numberOfX)
	{
		cout << "O Wins!" << endl << endl;
	}
	else
	{
		cout << "Tie game." << endl << endl;
	}

	return 0;
}

//-----------------------------------------------------------------------------------------
int main() {
	// Set initial values for the global board variables to all be blank
	p1 = p2 = p3 = p4 = p5 = p6 = p7 = p8 = p9 = p10 = p11 = p12 = p13 = p14 = p15 = p16 = p17 = p18 = p19 = p20 = p21 = p22 = p23 = p24 = p25 = ' ';
	// Set corner starting positions
	p1 = p25 = 'X';
	p5 = p21 = 'O';

	// Variables to store user input for current row and column, and destination row and column
	char currentRow;
	char currentCol;
	char destRow;
	char destColumn;

	cout << "Welcome to the 2-player game of Contagion. \n"
		<< endl;

	int moveNumber = 1;
	char playerToMove = ' ';           // Used for when round is X or O
	// Main loop to play game
	while (true) {

		// Display board and handle first character of user input
		displayBoard();
		// Checks if moveNumber is odd so then round is for X, else round is for O
		if (moveNumber % 2 != 0)
		{
			playerToMove = 'X';  // odd numbered moves
		}
		else
		{
			playerToMove = 'O';  // even numbered moves
		}
		cout << moveNumber << ". Enter 'i' for instructions, 'x' to exit, or move for " << playerToMove << ": " << endl;
		cin >> currentRow;
		// convert currentRow to capital if lowercase
		currentRow = toupper(currentRow);

		// Check to see if user input was 'i' for instructions or 'x' to exit
		if (currentRow == 'I')
		{
			displayInstructions();
			continue;       // Loop back up to retry move
		}
		else if (currentRow == 'X')
		{
			displayBoard();
			checkScore(currentRow, currentCol);
			cout << "Exiting program... \n";
			break;  // Break out of enclosing loop, to exit the game.
		}
		else if (currentRow == 'P')
		{
			moveNumber++;
			continue;
		}
		else
		{
			// User input was not 'i' for instructions or 'x' to exit, so a move is being made
			cin >> currentCol;
			currentCol = toupper(currentCol);
			// destination move
			cin >> destRow;
			destRow = toupper(destRow);
			cin >> destColumn;
			destColumn = toupper(destColumn);

			moveFrom(currentRow, currentCol, destRow, destColumn, getValueAt(currentRow, currentCol));
		}
		moveNumber++;
	} //end while( true)


	return 0;
} // end main()
