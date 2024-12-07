#include <iostream>
#include <string>
#include <Windows.h> // For SetConsoleTextAttribute() and PlaySound
#include <mmsystem.h> // For sound functions
#include <conio.h> // For console input
#include <stdlib.h> // For system functions
#include <tchar.h> // For TCHAR support

#pragma comment(lib, "winmm.lib") // Link the WinMM library for sound functions

using namespace std;

// Enum class representing the symbols used in the game Tic-Tac-Toe
enum class PlayerSymbol {
	None = ' ', // Represents an empty cell
	X = 'X',    // Represents player X
	O = 'O'     // Represents player O
};

// Function prototypes for grid management and input handling
void mainMenu();
void play();
void Draw();
void Input();
void togglePlayer();
bool isWin(PlayerSymbol player); // Function to check if a player has won
bool isGameOver(); // Function to check if the game is over
void clearScreen();
void setColor(int foreground, int background);
void resetColor();
void BackgroundMusic();

// Global variables
PlayerSymbol matrix[3][3] = { PlayerSymbol::None, PlayerSymbol::None, PlayerSymbol::None,
							   PlayerSymbol::None, PlayerSymbol::None, PlayerSymbol::None,
							   PlayerSymbol::None, PlayerSymbol::None, PlayerSymbol::None };// 3x3 matrix to represent the Tic-Tac-Toe game board

PlayerSymbol currentPlayer = PlayerSymbol::X; // Start with player X
string charName1 = "Player1"; // Default name for Player 1
string charName2 = "Player 2"; // Default name for Player 2

// Function to clear the console screen
void clearScreen() {
	system("CLS"); // Clear screen in Windows
}

// Function to set text color in the console
void setColor(int foreground, int background) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
}

// Function to reset text color to default
void resetColor() {
	setColor(7, 0); // White text on black background
}

// Function to play background music
void BackgroundMusic() {
	PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\game-music-loop-6-144641.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Main function
int main()
{
	clearScreen(); //Clear the screen
	setColor(7, 0); // Set foreground color
	mainMenu(); // Call the main menu function
	return 0;
}

// Function to display the main menu and handle user choices
void mainMenu()
{
	SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8
	clearScreen();
	char userChoice = 'o'; // Variable to store user choice

	do 
	{
		setColor(4, 0); // Set color for menu title
		BackgroundMusic();
		cout << "\n Welcome to Noughts and Crosses" << endl; // Display welcome message
		resetColor(); // Reset color

		// Display menu options
		setColor(3, 0);
		cout << "\n 1. Play Game " << endl;
		cout << "\n 2. How to Play" << endl;
		cout << "\n 3. About the project" << endl;
		cout << "\n 4. Exit" << endl;
		resetColor();

		setColor(7, 0); // Set color for user input prompt
		cout << "\n Please make a choice: ";
		resetColor();

		cin >> userChoice; // Get user choice
		clearScreen(); // Clear the screen after choice

		if (userChoice == '1') // If user chooses to play the game
		{
			play(); // Start the game
			cout << "\n Game over, press Enter to return to the main menu." << endl;
			cin.ignore(); // Ignore leftover newline character
			cin.get(); // Wait for user to press Enter
		}
		else if (userChoice == '2') // If user wants to see instructions
		{
			cout << endl;
			setColor(6, 0);
			cout << " Game Instructions: " << endl;
			resetColor();
			cout << "\n 1. Get Ready for Battle! 🥳" << endl;
			cout << " Enter your player names and hit Enter to kick off the fun! Make sure to choose names that will inspire fear in your opponent!" << endl;
			cout << "\n 2. Claim Your Territory!🏴‍☠️" << endl;
			cout << " To place your marker, simply type the number of the square you want to conquer (1 - 9) and press the ENTER key. Each number corresponds to a square on the board. Choose wisely, as strategy is key!🔑" << endl;
			cout << " \n 3. The Quest for Victory! 🏆" << endl;
			cout << " Keep taking turns until one brave player manages to line up three of their markers in a row! This can be vertically, horizontally, or diagonally — whatever it takes to claim glory! 🌟" << endl;
			cout << "\n 4. Watch Out! ⚠️" << endl;
			cout << " Be careful not to pick a spot that's already taken! If you do, you’ll lose your turn and give your opponent a chance to strike! 😱" << endl;
			cout << "\n Enjoy the game, and may the best player win! Let the battle of wits begin! 🤜🤛" << endl;
			setColor(6, 0);
			cout << "\n Instructions are now complete! Are you ready to play?" << endl;
			resetColor();
		}
		else if (userChoice == '3') // If user selects "About the project"
		{
			setColor(8, 0);
			cout << "\n --------------------------------\n"
				<< "    Project Information\n"
				<< " --------------------------------\n"
				<< "  * Author: Martina Mullerova\n"
				<< "  * Programming language: C++\n"
				<< "  * Development environment: Visual Studio\n\n" << endl;
			resetColor();
		}
		else if (userChoice == '4') // If user selects "Exit"
		{
			setColor(12, 0); // Set text color to red
			cout << " Thanks for playing! Bye for now." << endl;
			resetColor();
		}
		else // If user enters an invalid choice
		{
			setColor(12, 0);
			PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_additional\\invalid_input.wav"), NULL, SND_FILENAME | SND_ASYNC);
			cout << "\n ERROR!!!" << endl;
			cout << " Please choose again" << endl;
			Sleep(3000); // Wait for 2 seconds
			cout.flush(); // Flush the output buffer
			resetColor();
		}
	} while (userChoice != '4'); // Continue the main menu loop until the user chooses to exit
}

void play() {
	setColor(3, 0); // Set text color for player name input
	// Players enter their names
	cout << "\n\n Player 1 enter your name: ";
	cin >> charName1;
	resetColor();
	setColor(2, 0);
	cout << "\n\n Player 2 enter your name: ";
	cin >> charName2;
	resetColor();
	// Play initial sound effects
	PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\fight_voice.wav"), NULL, SND_FILENAME | SND_SYNC);
	PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\tiger_fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(500); // Brief delay for sound effects

	Draw(); // Initial board display

	// Game loop: continues until the game is over
	while (!isGameOver()) {
		Input(); // Get player input
		Draw(); // Update and display the board

		// Display the name of the current player based on the value of currentPlayer.
		if (currentPlayer == PlayerSymbol::X) {
			setColor(9, 0);
			// If the current player is X, display player 1's name along with the symbol 'X'.
			cout << "\n Current player: " << charName1 << " (X)" << endl;
			resetColor();
		}
		else {
			setColor(2, 0);
			// If the current player is O, display player 2's name along with the symbol 'O'.
			cout << "\n Current player: " << charName2 << " (O)" << endl;
			resetColor();
		}
		// Call the function to toggle to the next player after a valid move.
		togglePlayer(); // Switch to the next player after a valid move
	}

	// Check for win, lose, or draw conditions after the game is over.
	if (isWin(PlayerSymbol::X)) {
		PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\victory_voice.wav"), NULL, SND_FILENAME | SND_SYNC);
		Sleep(500);
		// If player X has won, display a victory message for player 1.
		setColor(12, 0); // Set text color to red
		cout << "\n Hooray! " << charName1 << " wins! Time to celebrate!" << endl;
		resetColor();
	}
	else if (isWin(PlayerSymbol::O)) {
		PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\victory_voice.wav"), NULL, SND_FILENAME | SND_SYNC);
		Sleep(500);
		// If player O has won, display a victory message for player 2.
		setColor(12, 0); // Set text color to red
		cout << "\n Hooray! " << charName2 << " wins! Time to celebrate!" << endl;
		resetColor();
	}
	else {
		setColor(6, 0);
		// If neither player has won and the board is full, display a draw message.
		cout << "\n It's a tie! No one wins this time. Better luck next round!" << endl;
		resetColor();
	}

	BackgroundMusic(); // Restart background music after the game
	return; // Exit game after displaying the result
}

void Draw() {
	system("CLS"); // Clear the screen
	setColor(4, 0);
	cout << "\n\n Welcome to Noughts and Crosses! Ready to have some fun?\n\n"; // Print game name with a friendly message
	resetColor();
	for (int i = 0; i < 3; i++) { // i = line index
		cout << "   ";
		for (int j = 0; j < 3; j++) { // j = column index
			// Display the current symbol or the cell number if it's empty
			if (matrix[i][j] == PlayerSymbol::None) {
				cout << (i * 3 + j + 1) << "  "; // Display cell number (1-9)
			}
			else {
				cout << static_cast<char>(matrix[i][j]) << "  "; // Display 'X' or 'O'
			}
			setColor(6, 0);
			if (j < 2) {
				cout << "| "; // Vertical line, if it is not the last column
				resetColor();
			}
		}
		cout << endl;
		if (i < 2) {
			setColor(6, 0);
			cout << "   -------------\n"; // New line and horizontalline
			resetColor();
		}
	}
}

void Input() {
	int a;
	resetColor();
	do {
		// Prompt the current player to enter a move
		if (currentPlayer == PlayerSymbol::X) {
			cout << "\n It's " << charName1 << "'s turn. Enter a number: ";
		}
		else {
			cout << "\n It's " << charName2 << "'s turn. Enter a number: ";
		}
		cin.clear(); // Clean
		cin.ignore(); // Ignore all characters until the end of the line
		cin >> a; // Read the player's input

		// Validate the input
		if (a >= 1 && a <= 9) {
			// Calculate the row and column indices from the input number
			int row = (a - 1) / 3;
			int col = (a - 1) % 3;

			// Check if the selected cell is empty
			if (matrix[row][col] == PlayerSymbol::None) {
				matrix[row][col] = currentPlayer; // Set the current player's symbol
				break; // Exit the loop
			}
			else {
				// Play a sound to indicate an invalid move
				PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\fail_voice.wav"), NULL, SND_FILENAME | SND_SYNC);
				setColor(6, 0);
				cout << "\n That spot is already taken. Try again.\n\n ";
				resetColor();
			}
			// Play a sound effect after each move
			PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\tiger_fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else {
			setColor(6, 0);
			PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\invalid_input.wav"), NULL, SND_FILENAME | SND_SYNC);
			// Invalid input, display an error message
			cout << "\n Invalid input. Please enter a number between 1 and 9.\n\n ";
			resetColor();
			cin.clear(); // Clean
			cin.ignore(10000, '\n'); // Discards up to 10,000 characters from the input stream
			PlaySound(TEXT("C:\\Users\\TinaM\\OneDrive\\Desktop\\university work\\programming\\noughts_crosses_add\\tiger_fight.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}

	} while (true); // Loop until a valid move is made

}


bool isWin(PlayerSymbol player) {
	// Check rows
	for (int i = 0; i < 3; i++) {
		if (matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player) {
			return true;
		}
	}

	// Check columns
	for (int i = 0; i < 3; i++) {
		if (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player) {
			return true;
		}
	}

	// Check diagonals
	if (matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player) {
		return true;
	}
	if (matrix[0][2] == player && matrix[1][1]
		== player && matrix[2][0] == player) {
		return true;
	}

	return false; // No win condition met
}

bool isGameOver() {
	// Check for horizontal win
	for (int i = 0; i < 3; i++) {
		if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2] && matrix[i][0] != PlayerSymbol::None) {
			return true; // Win detected
		}
	}

	// Check for vertical win
	for (int i = 0; i < 3; i++) {
		if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i] && matrix[0][i] != PlayerSymbol::None) {
			return true; // Win detected
		}
	}

	// Check for diagonal wins
	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0] != PlayerSymbol::None) {
		return true; // Win detected
	}
	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2] != PlayerSymbol::None) {
		return true; // Win detected
	}

	// Check for draw
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i][j] == PlayerSymbol::None) {
				return false; // Game is still ongoing
			}
		}
	}

	// If no win or draw condition is met, the game is over
	return true; // It's a draw
}
void togglePlayer() {
	if (currentPlayer == PlayerSymbol::X) {
		currentPlayer = PlayerSymbol::O; // Switch to player O
	}
	else {
		currentPlayer = PlayerSymbol::X; // Switch to player X
	}
}