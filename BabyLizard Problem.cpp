

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class BabyLizardGrid
{
public:
	int gridSize = 0;
	int noOfLizardsPlaced = 0;
	int currentRow = 0;
	vector<vector<int> > babyLizardVector;

public:
	BabyLizardGrid(int setGridSize, int setNoOfLizardsPlaced, int setCurrentRow)
	{
		gridSize = setGridSize;
		noOfLizardsPlaced = setNoOfLizardsPlaced;
		currentRow = setCurrentRow;
		babyLizardVector.resize(gridSize, vector<int>(gridSize));
	}
};

int CalculateNoOfConflicts(vector<vector<int> > babyLizardVector, int gridSize)
{
	int noOfConflicts = 0;

	int noOfLizards = 0;
	int row = 0;
	int column = 0;

	//Check Row for current column
	for (row = 0; row < gridSize; row++)
	{
		bool treeOnLeft = false;
		for (column = 0; column < gridSize; column++)
		{
			if (babyLizardVector[row][column] == 1)
			{
				noOfLizards++;
				treeOnLeft = false;
				if (noOfLizards == 2 && treeOnLeft == false)
				{
					break;
				}
			}
			else if (babyLizardVector[row][column] == 2)
			{
				treeOnLeft = true;
				noOfLizards = 0;
			}
		}
		if (noOfLizards >= 2)
		{
			noOfConflicts++;
		}
		noOfLizards = 0;
	}

	//Check for horizontal row
	for (column = 0; column <= gridSize; column++)
	{
		bool treeOnLeft = false;
		for (row = 0; row < gridSize; row++)
		{
			if (babyLizardVector[row][column] == 1)
			{
				noOfLizards++;
				treeOnLeft = false;
				if (noOfLizards == 2 && treeOnLeft == false)
				{
					break;
				}
			}
			else if (babyLizardVector[row][column] == 2)
			{
				treeOnLeft = true;
				noOfLizards = 0;
			}
		}
		if (noOfLizards >= 2)
		{
			noOfConflicts++;
		}
		noOfLizards = 0;
	}


	//Check Upper Diagonal
	for (int diagonal = 0; diagonal < 2 * gridSize - 1; ++diagonal)
	{
		bool treeOnLeft = false;
		int noOfElements = 0;

		if (diagonal < gridSize)
		{
			noOfElements = 0;
		}
		else
		{
			noOfElements = diagonal - gridSize + 1;
		}
		for (int j = noOfElements; j <= diagonal - noOfElements; ++j) {

			int diaognalElement = babyLizardVector[j][diagonal - j];

			if (diaognalElement == 1)
			{
				noOfLizards++;
				treeOnLeft = false;
				if (noOfLizards == 2 && treeOnLeft == false)
				{
					break;
				}

			}
			else if (diaognalElement == 2)
			{
				treeOnLeft = true;
				noOfLizards = 0;
			}
		}
		if (noOfLizards >= 2)
		{
			noOfConflicts++;
		}
		noOfLizards = 0;
	}

	//Check down side diagonal
	for (int diagonal = 0; diagonal < 2 * gridSize - 1; ++diagonal)
	{
		int noOfElements = 0;
		bool treeOnLeft = false;
		if (diagonal < gridSize)
		{
			noOfElements = 0;
		}
		else
		{
			noOfElements = diagonal - gridSize + 1;
		}
		for (int j = noOfElements; j <= diagonal - noOfElements; ++j) {

			int diaognalElement = babyLizardVector[j][(gridSize - 1) - (diagonal - j)];

			if (diaognalElement == 1)
			{
				noOfLizards++;
				treeOnLeft = false;
				if (noOfLizards == 2 && treeOnLeft == false)
				{
					break;
				}
			}
			else if (diaognalElement == 2)
			{
				treeOnLeft = true;
				noOfLizards = 0;
			}
		}
		if (noOfLizards >= 2)
		{
			noOfConflicts++;
		}
		noOfLizards = 0;
	}

	return noOfConflicts;
}

bool CheckSafePosition(vector<vector<int> > babyLizardVector, int row, int column, int gridSize)
{
	if (babyLizardVector[row][column] == 2)
		return false;

	int i, j;
	//Check for current column upward
	for (i = row; i >= 0; i--)
	{
		if (babyLizardVector[i][column] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][column] == 2)
		{
			break;
		}
	}

	//Check for current column downward
	for (i = row; i < gridSize; i++)
	{
		if (babyLizardVector[i][column] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][column] == 2)
		{
			break;
		}
	}

	//Check for horizontal row to the left
	for (i = column; i >= 0; i--)
	{
		if (babyLizardVector[row][i] == 1)
		{
			return false;
		}
		else if (babyLizardVector[row][i] == 2)
		{
			break;
		}
	}

	//Check for horizontal row to the right
	for (i = column; i < gridSize; i++)
	{
		if (babyLizardVector[row][i] == 1)
		{
			return false;
		}
		else if (babyLizardVector[row][i] == 2)
		{
			break;
		}
	}

	//Check Upper Diagonal Upside
	for (i = row, j = column; i >= 0 && j >= 0; i--, j--)
	{
		if (babyLizardVector[i][j] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][j] == 2)
		{
			break;
		}
	}

	//Check Upper Diagonal Downside
	for (i = row, j = column; i < gridSize && j < gridSize; i++, j++)
	{
		if (babyLizardVector[i][j] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][j] == 2)
		{
			break;
		}
	}

	//Check down side diagonal Upside
	for (i = row, j = column; j < gridSize && i >= 0; i--, j++)
	{
		if (babyLizardVector[i][j] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][j] == 2)
		{
			break;
		}
	}

	//Check down side diagonal downside
	for (i = row, j = column; i < gridSize && j >= 0; i++, j--)
	{
		if (babyLizardVector[i][j] == 1)
		{
			return false;
		}
		else if (babyLizardVector[i][j] == 2)
		{
			break;
		}
	}
	return true;
}

double GetRandomNumber() {
	double randomNumber = ((double)rand() / (RAND_MAX));
	return randomNumber;
}

//Check if goal is found
bool ChecGoalState(BabyLizardGrid grid, int noOfLizards)
{
	if (grid.noOfLizardsPlaced == noOfLizards)
		return true;
	else
		return false;
}

bool CheckRowForAllTrees(vector<vector<int> > vector, int row, int gridSize)
{
	int treeCount = 0;
	if ((row < gridSize))
	{
		for (int i = 0; i < gridSize; i++)
		{
			if (vector[row][i] == 2)
				treeCount++;
		}
	}

	if (gridSize == treeCount)
	{
		return true;
	}
	return false;
}

BabyLizardGrid FindDFSSolution(BabyLizardGrid babyLizardGrid, int gridSize, int noOfLizards, bool rootNode)
{
	if (ChecGoalState(babyLizardGrid, noOfLizards))
	{
		return babyLizardGrid;
	}
	else
	{
		for (int row = 0; row < gridSize; row++)
		{
			for (int column = 0; column < gridSize; column++)
			{
				if (CheckSafePosition(babyLizardGrid.babyLizardVector, row, column, gridSize))
				{
					babyLizardGrid.babyLizardVector[row][column] = 1;
					babyLizardGrid.noOfLizardsPlaced += 1;
					babyLizardGrid.currentRow = row;

					BabyLizardGrid finalBabyLizardGrid = FindDFSSolution(babyLizardGrid, gridSize, noOfLizards, rootNode);

					if (finalBabyLizardGrid.noOfLizardsPlaced != 0)
					{
						return finalBabyLizardGrid;
					}

					if (babyLizardGrid.noOfLizardsPlaced > 0)
					{
						babyLizardGrid.noOfLizardsPlaced--;
						if (babyLizardGrid.currentRow != 0)
							babyLizardGrid.currentRow--;
						babyLizardGrid.babyLizardVector[row][column] = 0;
					}
				}
			}
		}
	}
	return BabyLizardGrid(0, 0, 0);
}

vector<vector<int> > PerformSimmulatingAnnealing(vector<vector<int> > curBabyLizardGrid, int gridSize)
{
	vector<vector<int> > emptyVector;
	vector<vector<int> > nextBabyLizardVector;
	double temperature = 4000;
	double decTempFunction = 0.9;
	int deltaE;

	//Variables for time loop
	int endWhileLoop = 1;
	double elapsedTime;
	time_t startTime, endTime;
	startTime = time(NULL);

	//If there is no conflict at all return cur vector
	if (CalculateNoOfConflicts(curBabyLizardGrid, gridSize) == 0)
	{
		return curBabyLizardGrid;
	}

	while (endWhileLoop) {
		endTime = time(NULL);
		elapsedTime = difftime(endTime, startTime);
		if (elapsedTime >= 240.0)
			endWhileLoop = 0;


		nextBabyLizardVector = curBabyLizardGrid;

		int randomRow = rand() % gridSize;
		int randomColumn = rand() % gridSize;
		bool newLizardPlaced = false;

		if (nextBabyLizardVector[randomRow][randomColumn] == 1)
		{
			int nextRandomColumn = rand() % gridSize;
			int nextRandomRow = rand() % gridSize;

			if (nextBabyLizardVector[nextRandomRow][nextRandomColumn] != 2)
			{
				if (nextBabyLizardVector[nextRandomRow][nextRandomColumn] != 1)
				{
					nextBabyLizardVector[randomRow][randomColumn] = 0;
					nextBabyLizardVector[nextRandomRow][nextRandomColumn] = 1;
					newLizardPlaced = true;
				}
			}
		}

		if (newLizardPlaced)
		{
			deltaE = CalculateNoOfConflicts(nextBabyLizardVector, gridSize) - CalculateNoOfConflicts(curBabyLizardGrid, gridSize);

			if (deltaE < 0)
			{
				curBabyLizardGrid = nextBabyLizardVector;
			}
			else if (GetRandomNumber() < exp(-deltaE / temperature))
			{
				curBabyLizardGrid = nextBabyLizardVector;
			}

			if (CalculateNoOfConflicts(curBabyLizardGrid, gridSize) == 0)
			{
				return curBabyLizardGrid;
			}
		}
		temperature *= decTempFunction;
	}
	return emptyVector;
}

int main(int argc, const char * argv[]) {
	queue<BabyLizardGrid> babyLizardQueue;
	vector<vector<int> > inputGrid;

	string searchType = "";
	int gridSize = 0;
	int noOfLizards = 0;
	bool ifSolutionFound = false;

	string argumnets;
	ifstream inputFile;
	inputFile.open("input.txt");
	int lineIndex = 0;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			getline(inputFile, argumnets);
			if (argumnets != "")
			{
				if (lineIndex == 0)
				{
					searchType = argumnets;
					lineIndex += 1;
				}
				else if (lineIndex == 1)
				{
					gridSize = stoi(argumnets);
					inputGrid.resize(gridSize, vector<int>(gridSize));
					lineIndex += 1;
				}
				else if (lineIndex == 2)
				{
					noOfLizards = stoi(argumnets);
					lineIndex += 1;
				}
				else
				{
					for (int j = 0; j < gridSize; j++)
					{
						if (lineIndex - 3 < gridSize)
						{
							inputGrid[lineIndex - 3][j] = argumnets[j] - 48;
						}
					}
					lineIndex += 1;
				}
			}
		}
	}
	inputFile.close();

	//Initialize Lizard Grid for BFS Search
	vector<vector<int> > bfsBabyLizardVector;

	//Initialize Lizard Grid for DFS Search
	BabyLizardGrid dfsBabyLizardGrid = BabyLizardGrid(gridSize, noOfLizards, 0);

	//Intialize Lizard Grid for Simulated Annealing
	vector<vector<int> > saBabyLizardGrid;

	//Initialize root Baby Lizard Grid
	BabyLizardGrid rootBabyLizardGrid = BabyLizardGrid(gridSize, 0, 0);
	rootBabyLizardGrid.noOfLizardsPlaced = 0;
	rootBabyLizardGrid.babyLizardVector = inputGrid;


	if (searchType == "BFS")
	{
		bool lizardPlaced = false;
		int noOfUnsafePos = 0;

		bool rootNode = true;
		babyLizardQueue.push(rootBabyLizardGrid);
		int row = 0;

		while (!babyLizardQueue.empty())
		{
			if (bfsBabyLizardVector.size() != 0)
			{
				break;
			}

			BabyLizardGrid frontBabyLizardGrid = babyLizardQueue.front();

			if (rootNode)
			{
				if (CheckRowForAllTrees(frontBabyLizardGrid.babyLizardVector, row, gridSize))
					row = frontBabyLizardGrid.currentRow + 1;
				else
					row = frontBabyLizardGrid.currentRow;
			}
			else
			{
				//Check if next row consist of trees only
				if (CheckRowForAllTrees(frontBabyLizardGrid.babyLizardVector, row + 1, gridSize))
				{
					row = frontBabyLizardGrid.currentRow + 2;
				}
				else if (lizardPlaced == false)
				{
					row = frontBabyLizardGrid.currentRow + 2;
				}
				else
				{
					row = frontBabyLizardGrid.currentRow + 1;
				}
			}

			if (row == gridSize)
			{
				row = 0;
			}
			rootNode = false;

			// Get Tree Position
			bool ifTreeExist = false;
			for (int i = 0; i < gridSize; i++)
			{
				if (frontBabyLizardGrid.babyLizardVector[row][i] == 2)
				{
					ifTreeExist = true;
					break;
				}
			}

			if (ChecGoalState(frontBabyLizardGrid, noOfLizards))
			{
				ifSolutionFound = true;
				bfsBabyLizardVector = frontBabyLizardGrid.babyLizardVector;
				break;
			}
			else
			{
				babyLizardQueue.pop();
				queue<BabyLizardGrid> insideQueue;

				for (int column = 0; column < gridSize; column++) {
					BabyLizardGrid pushBabyLizardGrid = frontBabyLizardGrid;
					if (CheckSafePosition(pushBabyLizardGrid.babyLizardVector, row, column, gridSize))
					{
						if (noOfUnsafePos >= 0)
						{
							noOfUnsafePos--;
						}

						pushBabyLizardGrid.babyLizardVector[row][column] = 1;
						pushBabyLizardGrid.noOfLizardsPlaced += 1;
						lizardPlaced = true;
						pushBabyLizardGrid.currentRow = row;
						babyLizardQueue.push(pushBabyLizardGrid);

						if (ifTreeExist == true)
						{
							for (int i = column + 1; i < gridSize; i++)
							{
								BabyLizardGrid insideBabyLizardGrid = BabyLizardGrid(gridSize, 0, 0);
								insideBabyLizardGrid = pushBabyLizardGrid;

								if (CheckSafePosition(insideBabyLizardGrid.babyLizardVector, row, i, gridSize))
								{
									if (noOfUnsafePos >= 0)
									{
										noOfUnsafePos--;
									}

									insideBabyLizardGrid.babyLizardVector[row][i] = 1;
									insideBabyLizardGrid.noOfLizardsPlaced += 1;
									lizardPlaced = true;
									insideBabyLizardGrid.currentRow = row;
									insideQueue.push(insideBabyLizardGrid);
								}
							}
						}
					}
					else
					{
						noOfUnsafePos++;
						if (noOfUnsafePos == gridSize)
						{
							lizardPlaced = false;
						}
					}

					for (int i = 0; i < insideQueue.size(); i++)
					{
						BabyLizardGrid lizardGrid = insideQueue.front();
						insideQueue.pop();
						babyLizardQueue.push(lizardGrid);
					}

					if (ChecGoalState(pushBabyLizardGrid, noOfLizards))
					{
						ifSolutionFound = true;
						bfsBabyLizardVector = pushBabyLizardGrid.babyLizardVector;
						break;
					}
				}
			}
		}
	}
	else if (searchType == "DFS")
	{
		dfsBabyLizardGrid = FindDFSSolution(rootBabyLizardGrid, gridSize, noOfLizards, true);
		if (dfsBabyLizardGrid.noOfLizardsPlaced == noOfLizards)
		{
			ifSolutionFound = true;
		}
	}
	else if (searchType == "SA")
	{
		vector<vector<int> > curBabyLizardGrid = rootBabyLizardGrid.babyLizardVector;
		bool treePresent = false;
		int noOfLizardsPlaced = 0;

		for (int row = 0; row < gridSize; row++)
		{
			if (noOfLizardsPlaced == noOfLizards)
				break;

			for (int column = 0; column < gridSize; column++)
			{
				if (noOfLizardsPlaced < noOfLizards)
				{
					if (curBabyLizardGrid[row][column] != 2)
					{
						if (treePresent)
						{
							curBabyLizardGrid[row][column] = 1;
							noOfLizardsPlaced++;
							treePresent = false;
						}
						else if (column == 0)
						{
							curBabyLizardGrid[row][column] = 1;
							noOfLizardsPlaced++;
							treePresent = false;
						}
					}
					else
					{
						treePresent = true;;
					}
				}
				else
				{
					break;
				}
			}
		}
		if (noOfLizardsPlaced != noOfLizards)
		{
			ifSolutionFound = false;
		}
		else
		{
			saBabyLizardGrid = PerformSimmulatingAnnealing(curBabyLizardGrid, gridSize);
			if (saBabyLizardGrid.size() != 0)
			{
				ifSolutionFound = true;
			}
		}
	}

	//Print the solution
	ofstream file;
	file.open("output.txt");

	if (ifSolutionFound)
	{
		file << "OK" << endl;

		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (searchType == "BFS")
				{
					file << bfsBabyLizardVector[i][j];
				}
				else if (searchType == "DFS")
				{
					file << dfsBabyLizardGrid.babyLizardVector[i][j];
				}
				else if (searchType == "SA")
				{
					file << saBabyLizardGrid[i][j];
				}
				else
				{
					file << bfsBabyLizardVector[i][j];
				}
			}
			file << endl;
		}
		file.close();
	}
	else
	{
		file << "FAIL" << endl;
		file.close();
	}
}
