#pragma once

#include "FBullCowGame.h"
#include <algorithm>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	MyCurrentTry = 1;
	Difficulty = 1;
	MaxDifficulty = 5;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return HiddenWord.length();
}

int32 FBullCowGame::GetDifficulty() const
{
	return Difficulty;
}

bool FBullCowGame::IsGameWon(FString Guess) const
{
	if (Guess == HiddenWord)
		return true;

	return false;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	for (int i = 0; i < Guess.length(); i++)
	{
		if (Guess[i] == HiddenWord[i])
			BullCowCount.Bulls++;
		else if (Guess.find(HiddenWord[i]) != std::string::npos)
			BullCowCount.Cows++;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// declare and initialize a map that holds alphabet characters with associated
	// boolean value based on whether or not the character has been identified already
	TMap<char, bool> charMap;

	// for each character in guess string compare with the map and check the value of the boolean
	// if boolean is true for that character, the guess is not an isogram
	for (int i = 0; i < Guess.length(); i++)
	{
		char val = Guess[i];

		if (charMap[val])
			return false;
		else charMap[val] = true;
	}

	return true;
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	return;
}

void FBullCowGame::IncrementDifficulty()
{
	if (Difficulty >= MaxDifficulty)
		Difficulty = 1;
	else
		Difficulty++;

	return;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto i : Guess)
	{
		if (isupper(i))
		{
			break;
			return false;
		}
	}

	return true;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	EWordStatus IsValid = OK;
	int32 MyWordLength = HiddenWord.length();

	if (guess.length() > MyWordLength || guess.length() < MyWordLength)
		IsValid = Wrong_Length;
	else if (guess.find_first_of("0123456789!@#$%^&*()-_=':<>/\\?\"[]{}~`,.;|+") != std::string::npos)
		IsValid = Invalid_Chars;
	else if (guess.find(' ') != std::string::npos)
		IsValid = Contains_Whitespace;
	else if (!IsLowerCase(guess))
		IsValid = Not_Lowercase;
	else if (!IsIsogram(guess))
		IsValid = Not_Isogram;
	
	return IsValid;
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

void FBullCowGame::SetMaxTries(int32 Difficulty)
{
	TMap<int32, int32> tryMap;

	tryMap[1] = 5;
	tryMap[2] = 7;
	tryMap[3] = 10;
	tryMap[4] = 12;
	tryMap[5] = 15;

	if (Difficulty == 0)
		Difficulty = 1;

	if (Difficulty > tryMap.size())
		Difficulty = 5;

	MyMaxTries = tryMap[Difficulty];
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::SetHiddenWord(int32 Difficulty)
{
	TMap<int32, FString> wordMap;

	wordMap[1] = "car";
	wordMap[2] = "plant";
	wordMap[3] = "costume";
	wordMap[4] = "parhelions";
	wordMap[5] = "importunable";

	if (Difficulty == 0)
		HiddenWord = wordMap[1];

	if (Difficulty > wordMap.size())
		HiddenWord = wordMap[3];

	HiddenWord = wordMap[Difficulty];

	return;
}