/*	This is the console executable that makes use of the BullCow class
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Using - making syntax Unreal friendly
using FText = std::string;
using int32 = int;

//Prototypes
FBullCowGame SetupGame();
void PrintIntro(FBullCowGame BCGame);
bool PlayGame(FBullCowGame BCGame);
FText GetValidGuess(FBullCowGame BCGame);
FText StringToLower(FText Text);
bool EndGame(bool Result, FBullCowGame BCGame);

//Main
int main() {
	bool Playing = true;

	while (Playing == true) {
		bool Result = false;
		//Setup Game
		FBullCowGame BCGame1 = SetupGame();

		//Intro
		PrintIntro(BCGame1);

		//Play Game
		Result = PlayGame(BCGame1);

		//Post Game
		Playing = EndGame(Result, BCGame1);
	}
	
	//End
	return 0;
}

bool PlayGame(FBullCowGame BCGame) {
	FText Guess;
	FBullCowCount BullCowCount;

	//Loop for total number of Guesses
	for (int32 i = 0; i < BCGame.GetMaxTries(); i++) {
		//Get guess from Player
		Guess = GetValidGuess(BCGame);

		//Count Bulls and Cows (letter positions) and return results
		BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print result
		std::cout << "Bulls: " << BullCowCount.Bulls << "\nCows: " << BullCowCount.Cows << "\n";
		
		//If Guess is correct
		if (Guess == BCGame.GetIsogram()) {
			return true;
		}
		//Increment current guess by one
		BCGame.UpdateCurrentTry(1);
	}
	return false;
}

//Functions
FBullCowGame SetupGame() {
	FText Isogram = "";

	//Get isogram
	std::cout << "Enter an isogram (word without repeating letters, symbols or numbers) for next Player to guess: ";
	getline(std::cin, Isogram);
	Isogram = StringToLower(Isogram);

	//Build game
	FBullCowGame Game(Isogram);

	return Game;
}

void PrintIntro(FBullCowGame BCGame) {

	//ASCII art credit to Christopher Johnson at www.chris.com/ascii

	std::cout << "\n                 WELCOME TO BULLS AND COWS!\n\n";
	std::cout << "          ,     BULL   ,                 COW\n";
	std::cout << "	 /              \\\n";
	std::cout << "	((__ -^^-,-^^-__))            (,-\"\"\"-,)\n";
	std::cout << "	  `-_---' `---_-'           '--)~   ~(--'\n";
	std::cout << "	   <__|o` 'o|__>           .-'(       );-.\n";
	std::cout << "	      \\  `  /              '~~'d\\   /b'~~'\n";
	std::cout << "	       ): :(                   |     |\n";
	std::cout << "	       :o_o:                   (6___6)\n";
	std::cout << "                \"-\"                     '---'\n";
	std::cout << "\nCan you guess the " << BCGame.GetIsoLength() << " letter isogram I'm thinking of? You get " << BCGame.GetMaxTries() << " guesses...\n";

	return;
}

FText GetValidGuess(FBullCowGame BCGame) {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INIT;

	//keep getting Guess until valid Guess (OK) is received
	do {
		std::cout << "\nEnter your guess (" << BCGame.GetMaxTries() - BCGame.GetCurrentTry() << " remaining): ";
		getline(std::cin, Guess);

		//normalize the case of string
		Guess = StringToLower(Guess);

		//validation checking
		Status = BCGame.ValidateGuess(Guess);

		//Error report based on Guess Status
		switch (Status) {
			case EGuessStatus::TOO_SHORT:
				std::cout << "Guess is too short. Please enter a " << BCGame.GetIsoLength() << " letter word.\n";
				break;
			case EGuessStatus::TOO_LONG:
				std::cout << "Guess is too long. Please enter a " << BCGame.GetIsoLength() << " letter word.\n";
				break;
			case EGuessStatus::NOT_ISOGRAM:
				std::cout << "Guess is not Isogram. Please enter a word without double letters, symbols or numbers.\n";
				break;
			default:
				continue;
		}
	} while (Status != EGuessStatus::OK);

	//once Status is 'OK', return Guess
	return Guess;
}

FText StringToLower(FText Text) {
	FText s = Text;

	std::transform(s.begin(), s.end(), s.begin(), ::tolower);

	return s;
}

bool EndGame(bool Result, FBullCowGame BCGame) {
	FText PlayAgain = "";

	//Check if game was won or lost - print summary
	if (Result == true) {
		std::cout << "\nCongratulations, you figured out the word with " << BCGame.GetMaxTries() - BCGame.GetCurrentTry() << " tries left!\n";
	}
	else {
		std::cout << "\nSorry, you're out of guesses!\n";
	}

	//Ask to play again, whether won or lost - loop until appropriate answer
	do {
		std::cout << "Would you like to play again? y/n\n";
		getline(std::cin, PlayAgain);

		//If a new game is to be started
		if (tolower(PlayAgain[0]) == 'y' && PlayAgain.length() == 1) {
			std::cout << "Here we go again!\n----------\n";
			//Reset properties to initial values
			BCGame.Reset();
			return true;
		}
		//If the session is to end
		else if (tolower(PlayAgain[0]) == 'n' && PlayAgain.length() == 1) {
			std::cout << "Thanks for playing!\n\n";
			return false;
		}
		PlayAgain = "";
	} while (PlayAgain == "");

	return false;
}