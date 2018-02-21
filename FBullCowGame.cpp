#pragma once
#include "FBullCowGame.h"

// making map syntax Unreal friendly
#define TMap std::map

FBullCowGame::FBullCowGame(FString _Isogram) {
	CurrentTry = 0;
	Isogram = _Isogram;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<std::string, int32> WordLengthToMaxTries{ {"easy", 5}, {"medium", 10}, {"hard", 15} };

	if (GetIsoLength() <= 5) {
		return WordLengthToMaxTries["easy"];
	}

	else if (GetIsoLength() > 5 && GetIsoLength() <= 10) {
		return WordLengthToMaxTries["medium"];
	}

	else {
		return WordLengthToMaxTries["hard"];
	}
}

int32 FBullCowGame::GetCurrentTry() const {
	return CurrentTry;
}

std::string FBullCowGame::GetIsogram() const {
	return Isogram;
}

int32 FBullCowGame::GetIsoLength() const
{
	return Isogram.length();
}

void FBullCowGame::Reset() {
	CurrentTry = 0;
	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> LetterTracker;

	//0 char or 1 is isogram
	if (Guess.length() <= 1) {
		return true;
	}

	//check every letter against a growing list of letters being tracked. If match is found, or not alpha, not isogram
	for (char Letter : Guess) {
		if (LetterTracker[Letter] || !isalpha(Letter)) {
			return false;
		}
		else {
			LetterTracker[Letter] = true;
		}
	}

	//if above didn't return, word is isogram
	return true;
}

void FBullCowGame::UpdateCurrentTry(int32 Num) {
	CurrentTry += Num;
	return;
}

void FBullCowGame::SetIsogram(FString S) {
	Isogram = S;
	return;
}

EGuessStatus FBullCowGame::ValidateGuess(FString Guess) const {
	
	//Check if isogram
	if (!IsIsogram(Guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	}

	//Check length
	if (Guess.length() != GetIsoLength()) {
		if (int32(Guess.length()) > GetIsoLength()) {
			return EGuessStatus::TOO_LONG;
		}
		else if (int32(Guess.length()) < GetIsoLength()) {
			return EGuessStatus::TOO_SHORT;
		}
	}

	return EGuessStatus::OK;
}

//Receives valid guess, increments try counter and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	const FString SecretWord = GetIsogram();
	const int32 LENGTH = GetIsoLength(); //Guess already validated to be same length
	FBullCowCount CountStruct;

	//Loop through each letter in Guess and compare to each letter in SecretWord
	for (int32 i = 0; i < LENGTH; i++) {
		for (int32 j = 0; j < LENGTH; j++) {
			//If letters are the same
			if (Guess[i] == SecretWord[j]) {
				if (i == j) { //If they're in the same position
					CountStruct.Bulls++;
				}
				else { //If they're in different positions
					CountStruct.Cows++;
				}
			}
		}
	}

	return CountStruct;
}
