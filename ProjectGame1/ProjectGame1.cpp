#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions();
char ask_yes_no(string question);
int ask_number(string question, int high, int low = 0);
char human_piece();
char opponent(char char_piece);
void display_board(const vector <char>& board);
char winner(const vector<char>& board);
bool is_legal(const vector<char>& board, int move);
int human_move(const vector <char>& board, char human);
int computer_move(vector <char> board, char computer);
void announce_winner(char winner, char computer, char human); 

int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector <char> board(NUM_SQUARES, EMPTY);
	instructions();
	char human = human_piece();
	char computer = opponent(human);
	char turn = X;
	display_board(board);
	while (winner(board) == NO_ONE) {
		if (turn == human) {
			move = human_move(board, human);
			board[move] = human;
		}
		else {
			move = computer_move(board, computer);
			board[move] = computer;
		}
		display_board(board);
		turn = opponent(turn);
	}
	announce_winner(winner(board), computer, human);
	return 0;
}


void instructions() {
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known by entering a number, 0 - 8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << " 0 | 1 | 2\n";
	cout << " ———————--- \n";
	cout << " 3 | 4 | 5\n";
	cout << " ———————--- \n";
	cout << " 6 | 7 | 8\n\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}
char ask_yes_no(string question) {
	char response; 
	do {
		cout << "\n" << question << endl;
		cout << "answer yes or no. y/n";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}
int ask_number(string question, int high, int low) {
	int number;
	do {
		cout << "\n" << question << "(" << low <<" - " << high << ")" << endl;
		cin >> number;
		
	} while (number > high || number < low);
	return number;
}
char human_piece() {
	char first_move = ask_yes_no("do you require first move");
	if (first_move == 'y') {
		cout << "\n your first move " << endl;
		return X;
	}
	else {
		cout << "\n your second move " << endl;
		return O;
	}
	
}
char opponent(char piece) {
	if (piece == X) {
		return O;
	}
	else {
		return X;
	}
}
void display_board(const vector <char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "———————";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "———————";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\n";
}

char winner(const vector <char>& board) {
	const int WINNING_ROWS[8][3] = {
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{2,4,6},
		{0,4,8}
	};
	const int TOTAL_ROWS = 8 ;
	for (int row = 0; row < TOTAL_ROWS; ++row) {
		if ((board[WINNING_ROWS[row][0]] != EMPTY) && (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]])
			&& (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
			return board[WINNING_ROWS[row][0]];
		}
	}
	if (count(board.begin(), board.end(), EMPTY) == 0) {
		return TIE;
	}
	return NO_ONE;
}
inline bool is_legal(const vector<char>& board, int move) {
	return board[move] == EMPTY;
}
int human_move(const vector<char>& board, char human) {
	int move = ask_number("what number do you choose ", (board.size() - 1));
	while (!is_legal) {
		cout << "\n that square is occupied" << endl;
		move = ask_number("what number do you choose ", (board.size() - 1));
	}
	cout << "fine " << endl;
	return move;
}
int computer_move(vector<char> board, char computer) {
	unsigned int move = 0;
	bool found = false;
	while (!found && move < board.size()) {
		if (is_legal(board, move)) {
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found) {
			++move;
		}
	}
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (is_legal(board, move))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}
	if (!found) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		while (!found && i < board.size()) {
			move = BEST_MOVES[i];
			if (is_legal(board, move)) {
				found = true;
			}
			++i;
		}
	}
	cout << "i shall take square number " << move << endl;
	return move;
}
void announce_winner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "’s won!\n";
		cout << "As I predicted, human, I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human)
	{
		cout << winner << "’s won!\n";
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		cout << "It’s a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate... for this is the best you will ever achieve.\n";
	}
}