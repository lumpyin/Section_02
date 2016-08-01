
#include<iostream>
#include<string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;


int main()
{
	std::cout << BCGame.GetCurrentTry();

	bool  bWants = false;
	do {

		PrintIntro();

		PlayGame();

		bWants = AskToPlayAgain();

		std::cout << std::endl;
	} while (bWants);

	return 0;
}




void PrintIntro() {
	
	std::cout << "welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		EGuessStatus status = BCGame.CheckGuessValidity(Guess);
		
		switch (status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letter. \n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letter. \n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	

	
	
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?";
	FText Respone = "";
	std::getline(std::cin, Respone);


	return (Respone[0] == 'y');
}

void PlayGame()
{
	BCGame.Reset();
	
	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries) {

		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "BUlls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		
		std::cout << std::endl;
	}
}