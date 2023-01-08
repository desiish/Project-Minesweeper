/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Desislava Shunina
* @idnumber 6MI0600163
* @compiler GCC
*
* <file with game>
*
*/


#include <iostream>
#include <ctime>
#include <cstdlib>
const unsigned N = 10;//max size of field
bool isValidInputOfSize(size_t size) {
	return size <= 10 && size >= 3;
}
bool isValidInputOfMines(size_t size, unsigned numOfMines) {
	return numOfMines >= 1 && numOfMines <= 3 * size;
}
void GiveAllTheSameValue(char field[N][N], char value) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			field[i][j] = value;
		}
	}
}
bool isMarked(char fieldCell) {
	return fieldCell == '*';
}
void GetValidCoordinatesOfMine(int& Xcoordinate, int& Ycoordinate, size_t sizeOfField) {
	while (Xcoordinate >= sizeOfField) {
		Xcoordinate = rand() % 10;
	}
	while (Ycoordinate >= sizeOfField) {
		Ycoordinate = rand() % 10;
	}
}
void CreateMines(char field[N][N], size_t size, unsigned numOfMines) {
	srand(time(0));
	for (int i = 1; i <= numOfMines; i++) {
		int Xcoordinate = rand() % 10;
		int Ycoordinate = rand() % 10;
		GetValidCoordinatesOfMine(Xcoordinate, Ycoordinate, size);
		if (isMarked(field[Xcoordinate][Ycoordinate])) {
			i--;
		}
		else {
			field[Xcoordinate][Ycoordinate] = '*';
		}
	}
}
void GetCountOfMinesInCurrentCell(char field[N][N], size_t size, int x, int y) {
	char count = '0';
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && j >= 0 && i < size && j < size) {
				if (i == x && j == y)
					continue;
				if (field[i][j] == '*')
					count++;
			}
		}
	}
	field[x][y] = count;
}
void GetCountOfMinesInEveryCell(char field[N][N], size_t size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (field[i][j] != '*') {
				GetCountOfMinesInCurrentCell(field, size, i, j);
			}
		}
	}
}
void printField(const char field[N][N], size_t size) {
	std::cout << std::endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << "[" << field[i][j] << "]";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void OpenAllNeighboursWhenZero(const char field[N][N], char RevealedField[N][N], int x, int y, size_t size, unsigned& forRevealing) {
	if (RevealedField[x][y] == ' ') {
		RevealedField[x][y] = field[x][y];
		forRevealing--;
	}
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if (i >= 0 && j >= 0 && i < size && j < size) {
				if (i == x && j == y)
					continue;
				if (RevealedField[i][j] == ' ' && field[i][j] != '*') {
					RevealedField[i][j] = field[i][j];
					forRevealing--;
					if (RevealedField[i][j] == '0') {
						OpenAllNeighboursWhenZero(field, RevealedField, i, j, size, forRevealing);
					}
				}
			}
		}
	}
}
int myStrcmp(const char* first, const char* second)
{
	if (first == nullptr || second == nullptr)
		return -2;
	while (*first != '\0' && *second != '\0')
	{
		if (*first < *second)
			return -1;
		if (*first > *second)
			return 1;
		first++;
		second++;
	}
	if (*first == '\0' && *second == '\0')
		return 0;
	return *first == '\0' ? -1 : 1;
}
bool isValidUserInput(int x, int y, char* operation, size_t size) {
	return (myStrcmp(operation, "open") == 0 || myStrcmp(operation, "mark") == 0 || myStrcmp(operation, "unmark") == 0)
		&& x >= 0 && x < size&& y >= 0 && y < size;
}
void OpenCellCommand(char RevealedField[N][N], const char field[N][N], size_t size, unsigned& forRevealing, int x, int y, bool& GameOver) {
	if (RevealedField[x][y] == '!') {
		std::cout << "Cell has been marked! Unmark first! " << std::endl;
	}
	else if (RevealedField[x][y] != ' ') {
		std::cout << "Cell has already been opened! " << std::endl;
	}
	else {
		if (field[x][y] == '*') {
			RevealedField[x][y] = field[x][y];
			printField(RevealedField, size);
			std::cout << "You stepped on a mine! Game Over :(" << std::endl;
			printField(field, size);
			GameOver = true;
		}
		else if (field[x][y] != '0') {
			RevealedField[x][y] = field[x][y];
			forRevealing--;
		}
		else {
			OpenAllNeighboursWhenZero(field, RevealedField, x, y, size, forRevealing);
		}
	}
}
void MarkCellCommand(char RevealedField[N][N], const char field[N][N], int& countOfMarks, unsigned& numOfMines, int x, int y) {
	if (countOfMarks != 0) {
		if (RevealedField[x][y] == '!')
			std::cout << "Cell has already been marked!" << std::endl;
		else if (RevealedField[x][y] != ' ')
			std::cout << "Invalid input - cell has already been opened!" << std::endl;
		else {
			RevealedField[x][y] = '!';
			if (RevealedField[x][y] == '!') {
				countOfMarks--;
				if (field[x][y] == '*')
					numOfMines--;
			}
		}
	}
	else {
		std::cout << "All available marks have been placed! " << std::endl;
	}
}
void UnmarkCellCommand(char RevealedField[N][N], const char field[N][N], unsigned& numOfMines, int& countOfMarks, int x, int y) {
	if (RevealedField[x][y] != ' ' && RevealedField[x][y] != '!')
		std::cout << "Invalid input - cell has already been opened!" << std::endl;
	else {
		if (RevealedField[x][y] != '!')
			std::cout << "Cell has not been marked yet! Mark first!" << std::endl;
		else {
			RevealedField[x][y] = ' ';
			countOfMarks++;
			if (RevealedField[x][y] == ' ' && field[x][y] == '*')
				numOfMines++;
		}
	}
}
bool WinnerCheck(unsigned numOfMines, unsigned forRevealing) {
	return numOfMines == 0 && forRevealing == 0;
}
void PlayGame(char RevealedField[N][N], const char field[N][N], size_t size, unsigned numOfMines, unsigned forRevealing) {
	char operation[7];//longest is unmark
	int x, y;
	int countOfMarks = numOfMines;
	printField(RevealedField, size);
	bool GameOver = false;
	do {
		std::cout << "Please enter operation (open, mark or unmark) and valid coordinates of field cell: " << std::endl;
		std::cin >> operation >> x >> y;
		if (isValidUserInput(x, y, operation, size)) {
			if (myStrcmp(operation, "open") == 0) {
				OpenCellCommand(RevealedField, field, size, forRevealing, x, y, GameOver);
				if (GameOver)
					break;
			}
			else if (myStrcmp(operation, "mark") == 0) {
				MarkCellCommand(RevealedField, field, countOfMarks, numOfMines, x, y);
			}
			else if (myStrcmp(operation, "unmark") == 0) {
				UnmarkCellCommand(RevealedField, field, numOfMines, countOfMarks, x, y);
			}
			printField(RevealedField, size);
			if (WinnerCheck(numOfMines, forRevealing)) {
				std::cout << "Congratulations! You won! " << (char)1 << std::endl;
				break;
			}
		}
		else {
			std::cout << "Invalid input!" << std::endl;
		}
	} while (true);
}
void PrintRules() {
	std::cout << "~~~~~~~Mineweeper~~~~~~~" << std::endl;
	std::cout << "RULES OF THE GAME:" << std::endl;
	std::cout << "1. Choose valid size of the field (from 3 to 10) and valid\nnumber of mines (from 1 to 3*size of the field) to start playing;" << std::endl;
	std::cout << "2. Choose valid command and coordinates of a cell form the field." << std::endl;
	std::cout << "*Note: Valid commands are:\n - open;\n - mark;\n - unmark." << std::endl;
	std::cout << "3. If you step on a mine, you lose." << std::endl;
	std::cout << "4. If you mark all mines and open all of the other cells, you win." << std::endl;
	std::cout << "Have fun and enjoy!" << (char)1 << std::endl;
	std::cout << std::endl;
}
void ValidateUserInput(size_t& size, unsigned& numOfMines) {
	std::cout << "Choose size of field (from 3 to 10): ";
	std::cin >> size;
	while (!isValidInputOfSize(size)) {
		std::cout << "Invalid input! Please enter valid data to play!" << std::endl;
		std::cout << "Choose size of field (from 3 to 10): ";
		std::cin >> size;
	}
	std::cout << "Choose number of mines (from 1 to " << 3 * size << "): ";
	std::cin >> numOfMines;
	while (!isValidInputOfMines(size, numOfMines)) {
		std::cout << "Invalid input! Please enter valid data to play!" << std::endl;
		std::cout << "Choose number of mines (from 1 to " << 3 * size << "): ";
		std::cin >> numOfMines;
	}
}
int main() {
	PrintRules();
	size_t size;
	unsigned numOfMines;
	ValidateUserInput(size, numOfMines);
	unsigned forRevealing = size * size - numOfMines;
	char field[N][N];
	char RevealedField[N][N];
	GiveAllTheSameValue(field, ' ');
	GiveAllTheSameValue(RevealedField, ' ');
	CreateMines(field, size, numOfMines);
	GetCountOfMinesInEveryCell(field, size);
	PlayGame(RevealedField, field, size, numOfMines, forRevealing);
	return 0;
}