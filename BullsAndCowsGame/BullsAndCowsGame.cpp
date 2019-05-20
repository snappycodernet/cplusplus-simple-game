#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntroduction();
void PrintGameSummary();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void SetupGame();

FBullCowGame BCGame;
FGameStats GameStats;

int main() 
{
	do
	{
		SetupGame();
		PrintIntroduction();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());

	system("pause");
	return 0;
}

void SetupGame()
{
	BCGame.Reset();

	if (GameStats.WonLastGame)
		BCGame.IncrementDifficulty();

	auto Difficulty = BCGame.GetDifficulty();

	BCGame.SetMaxTries(Difficulty);
	BCGame.SetHiddenWord(Difficulty);
}

void PrintIntroduction() {
	std::cout << "Welcome to bulls and cows, a fun word game!\n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries to guess the correct isogram.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n\n";
	return;
}

void PrintGameSummary()
{
	bool GameWon = GameStats.WonLastGame;
	int32 Guesses = GameStats.TotalGuesses;
	int32 Games = GameStats.TotalGamesPlayed;
	double score = (1.00 / Guesses) * 100.00;
	int32 Difficulty = BCGame.GetDifficulty();

	if (GameWon)
	{
		std::cout << "**** YOU WIN!!! ****\n\n";
		GameStats.TotalGuesses = 0;
	}

	std::cout << "**** GAME SUMMARY ****\n";
	std::cout << "* Games Played: " << Games << "\n";
	std::cout << "* Total Guesses: " << Guesses << "\n";
	std::cout << "* Score: " << score << "%\n";
	std::cout << "* Difficulty: " << Difficulty << "\n";
	std::cout << "**********************\n\n";

	return;
}

FText GetGuess() {
	FText Guess = "";

	getline(std::cin, Guess);

	return Guess;
}

void PlayGame() {
	int32 MaxTries = BCGame.GetMaxTries();

	while (BCGame.GetCurrentTry() <= MaxTries) {
		std::cout << "Difficulty: " << BCGame.GetDifficulty() << " - Try " << BCGame.GetCurrentTry() << " of " << MaxTries << ": Enter Your Guess: ";
		FText Guess = GetGuess();
		EWordStatus Status = BCGame.CheckGuessValidity(Guess);

		if (Status != OK)
		{
			FText errorMsg = "Invalid Guess.. Try again.. \n";

			if (Status == EWordStatus::Contains_Whitespace)
				errorMsg = "Guess cannot contain any spaces!\n";

			if (Status == EWordStatus::Wrong_Length)
				errorMsg = "Guess character length must match isogram length of " + std::to_string(BCGame.GetHiddenWordLength()) + " characters!\n";

			if (Status == EWordStatus::Invalid_Chars)
				errorMsg = "Guess must be a proper english word and cannot contain special characters or numerals!\n";

			if (Status == EWordStatus::Not_Lowercase)
				errorMsg = "Guess word must be in all lowercase characters!\n";

			if (Status == EWordStatus::Not_Isogram)
				errorMsg = "Guess is not an isogram!\n";

			std::cout << errorMsg;
			continue;
		}

		std::cout << "You guessed: " << Guess << "\n\n";
		GameStats.TotalGuesses++;
		GameStats.LastGuess = Guess;
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		std::cout << "++ Bulls: " << BullCowCount.Bulls << "\n";
		std::cout << "++ Cows: " << BullCowCount.Cows;
		std::cout << "\n\n";

		if (BCGame.IsGameWon(Guess))
		{
			GameStats.WonLastGame = true;
			break;
		}
	}

	return;
}

bool AskToPlayAgain() {
	bool playAgain = false;
	FText input = "";

	std::cout << "Play Again? (Y/N): ";
	getline(std::cin, input);

	if (input == "Y" || input == "y")
	{
		playAgain = true;
		//BCGame.Reset();
		GameStats.TotalGamesPlayed++;
	}
		
	std::cout << std::endl;

	return playAgain;
}