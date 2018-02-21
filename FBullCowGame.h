/*
The game logic - no view code or direct user interaction
The game is a simple 'guess the word' game based on Mastermind
*/

#pragma once
#include <string>
#include <algorithm>
#include <map>

//Using - making syntax Unreal friendly
using FString = std::string;
using int32 = int;

// simple class to store and return two counters
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

// specific return type with fixed range of variables for word state
enum class EGuessStatus {
	OK,
	TOO_SHORT,
	TOO_LONG,
	NOT_ISOGRAM,
	INIT,
};

class FBullCowGame {
public:
	FBullCowGame(FString _Isogram); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetIsoLength() const;
	FString GetIsogram() const;

	EGuessStatus ValidateGuess(FString Guess) const;
	FBullCowCount SubmitValidGuess(FString Guess);

	void UpdateCurrentTry(int32 Num);
	void SetIsogram(FString S);
	void Reset();
	
private:
	int32 CurrentTry;
	FString Isogram;
	bool IsIsogram(FString Guess) const;
};