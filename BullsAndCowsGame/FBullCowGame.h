#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct FGameStats
{
	int32 TotalGuesses = 0;
	int32 TotalGamesPlayed = 1;
	FString LastGuess = "";
	bool WonLastGame = false;
};

enum EWordStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Invalid_Chars,
	Contains_Whitespace,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	void Reset(); // TODO Make a more rich return value
	int32 GetMaxTries() const; // Returns the max tries
	int32 GetCurrentTry() const; // Returns the current try value
	EWordStatus CheckGuessValidity(FString) const; // TODO Make a more rich return value
	void IncrementDifficulty();
	int32 GetDifficulty() const;
	FBullCowCount SubmitGuess(FString);
	int32 GetHiddenWordLength() const;
	bool IsGameWon(FString) const;
	void SetHiddenWord(int32 Difficulty);
	void SetMaxTries(int32 Difficulty);

// Ignore private members - focus on public members
private:
	// initialized via constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString HiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	int32 Difficulty;
	int32 MaxDifficulty;
};