#include <iostream>
using namespace std;

//connect 4 board
string arr[5][6];
//keep track of number of turns
int turnCount = 0;
//selected row
int colSelect = 0;
//number of states checked each round
int checkedStates = 0;

void printBoard()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void myTurn()
{
	//increase turn counter by 1
	turnCount++;

	//select a row 1-6 to place peice X
	cout << "select which row to place your peice." << endl;

	//repeat selection if row is not 1-6 or selected row is full
	do
	{
		cin >> colSelect;
		colSelect = colSelect - 1;

		if (colSelect < 0 || colSelect > 5)
		{
			cout << "Please select a row 1-6." << endl;
		}

		if (arr[0][colSelect] == "X" || arr[0][colSelect] == "O")
		{
			cout << "Row " << colSelect + 1 << " is full!" << endl;
		}
	} while (colSelect < 0 || colSelect > 5 || arr[0][colSelect] == "X" || arr[0][colSelect] == "O");

	//find the lowest . in row colSelect
	for (int i = 4; i >= 0; i--)
	{
		if (arr[i][colSelect] == ".")
		{
			//place peice in position checked before
			arr[i][colSelect] = "X";
			break;
		}
	}

	printBoard();
}

void aiTurn()
{
	int bestCol = 0;
	int bestMoveScore = 0;
	checkedStates = 0;
	//increase turn counter by 1
	turnCount++;

	//AI needs to decide which peice is the best for it to add a peice
	//assume max (me) is going to make best play
	//find mins best play
	//decide what play is best by how many peices are in a line 
	//check each column and where the peice would fall

	for (int i = 0; i <= 6; i++) //cycle thru columns
	{
		int moveScore = 0;
		checkedStates++;

		if (arr[0][i] == "X" || arr[0][i] == "O")
		{
			continue;
		}
		for (int j = 4; j >= 0; j--) //find lowest . in col
		{
			if (arr[j][i] == ".")
			{
				// decide score of the move
				//from point [j][i] see how many O are E, S, W, NE, SE, SW, and NW
				for (int k = 1; k <= 3; k++)
				{
					if (arr[j - k][i + k] == "O" && j - k >= 0 && i + k <= 5) // North East
					{
						moveScore++;
					}

					if (arr[j][i + k] == "O" && i + k <= 5) // East
					{
						moveScore++;
					}

					if (arr[j + k][i + k] == "O" && j + k <= 4 && i + k <= 5) // South East
					{
						moveScore++;
					}

					if (arr[j + k][i] == "O" && j + k <= 4) // South
					{
						moveScore++;
					}

					if (arr[j + k][i - k] == "O" && j + k <= 4 && i + k >= 0) // South West
					{
						moveScore++;
					}

					if (arr[j][i - k] == "O" && i - k >= 0) // West
					{
						moveScore++;
					}

					if (arr[j - k][i - k] == "O" && j - k >= 0 && i + k >= 0) // North West
					{
						moveScore++;
					}

					if (moveScore > bestMoveScore)
					{
						bestMoveScore = moveScore;
						bestCol = i;
					}
				}
				break;
			}
		}
	}

	//place peice after looking at all possible moves
	//place peice in selected column
	//find the lowest . in row colSelect
	for (int i = 4; i >= 0; i--)
	{
		if (arr[i][bestCol] == ".")
		{
			//place peice in position checked before
			arr[i][bestCol] = "O";
			break;
		}
	}

	printBoard();
}

bool checkWin()
{
	//check row wins
	for (int i = 4; i >= 0; i--)
	{
		if (arr[i][0] == "X" && arr[i][1] == "X" && arr[i][2] == "X" && arr[i][3] == "X") { cout << "you win!" << endl; return true; }
		if (arr[i][1] == "X" && arr[i][2] == "X" && arr[i][3] == "X" && arr[i][4] == "X") { cout << "you win!" << endl; return true; }
		if (arr[i][2] == "X" && arr[i][3] == "X" && arr[i][4] == "X" && arr[i][5] == "X") { cout << "you win!" << endl; return true; }

		if (arr[i][0] == "O" && arr[i][1] == "O" && arr[i][2] == "O" && arr[i][3] == "O") { cout << "you lose!" << endl; return true; }
		if (arr[i][1] == "O" && arr[i][2] == "O" && arr[i][3] == "O" && arr[i][4] == "O") { cout << "you lose!" << endl; return true; }
		if (arr[i][2] == "O" && arr[i][3] == "O" && arr[i][4] == "O" && arr[i][5] == "O") { cout << "you lose!" << endl; return true; }
	}

	//check col wins
	for (int i = 0; i <= 5; i++)
	{
		if (arr[4][i] == "X" && arr[3][i] == "X" && arr[2][i] == "X" && arr[1][i] == "X") { cout << "you win!" << endl; return true; }
		if (arr[3][i] == "X" && arr[2][i] == "X" && arr[1][i] == "X" && arr[0][i] == "X") { cout << "you win!" << endl; return true; }

		if (arr[4][i] == "O" && arr[3][i] == "O" && arr[2][i] == "O" && arr[1][i] == "O") { cout << "you lose!" << endl; return true; }
		if (arr[3][i] == "O" && arr[2][i] == "O" && arr[1][i] == "O" && arr[0][i] == "O") { cout << "you lose!" << endl; return true; }
	}

	//check diag wins
	for (int i = 0; i <= 2; i++)
	{
		if (arr[4][i] == "X" && arr[3][i + 1] == "X" && arr[2][i + 2] == "X" && arr[1][i + 3] == "X") { cout << "you win!" << endl; return true; }
		if (arr[3][i] == "X" && arr[2][i + 1] == "X" && arr[1][i + 2] == "X" && arr[0][i + 3] == "X") { cout << "you win!" << endl; return true; }

		if (arr[0][i] == "X" && arr[1][i + 1] == "X" && arr[2][i + 2] == "X" && arr[3][i + 3] == "X") { cout << "you win!" << endl; return true; }
		if (arr[1][i] == "X" && arr[2][i + 1] == "X" && arr[3][i + 2] == "X" && arr[4][i + 3] == "X") { cout << "you win!" << endl; return true; }

		if (arr[4][i] == "O" && arr[3][i + 1] == "O" && arr[2][i + 2] == "O" && arr[1][i + 3] == "O") { cout << "you lose!" << endl; return true; }
		if (arr[3][i] == "O" && arr[2][i + 1] == "O" && arr[1][i + 2] == "O" && arr[0][i + 3] == "O") { cout << "you lose!" << endl; return true; }

		if (arr[0][i] == "O" && arr[1][i + 1] == "O" && arr[2][i + 2] == "O" && arr[3][i + 3] == "O") { cout << "you lose!" << endl; return true; }
		if (arr[1][i] == "O" && arr[2][i + 1] == "O" && arr[3][i + 2] == "O" && arr[4][i + 3] == "O") { cout << "you lose!" << endl; return true; }
	}

	if (turnCount >= 30)
	{
		cout << "Tie!" << endl;
		return true;
	}

	return false;
}

int main()
{
	//fill board with .
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			arr[i][j] = ".";
		}
	}

	printBoard();

	while (checkWin() == false)
	{
		myTurn();
		if (checkWin())
		{
			break;
		}
		aiTurn();
		cout << "Checked " << checkedStates << " game states on node " << turnCount << "." << endl;
	}
}