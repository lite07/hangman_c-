/*
Word Guessing Game (Hangman)
A small project in my past time.
It's not a fully flashed out Hangman game, but it's functioning.
Created by:
Zaky Yudha Rabbani

Contact me by:
zaky_yudha@yahoo.co.id (Email)
*/
#include <iostream>	//Input Output Stream
#include <string>	//String Class
#include <fstream>	//File Stream
#include <vector>	//Vector Class
#include <cstdlib>	//rand(),srand()
#include <time.h>	//time()
#include <cstdio>	//NULL

/*
To get letters from the target word.
To avoid reiteration of the whole string and
removing duplicates.
*/
std::string getLetters(std::string targetWord)
{
	std::string targetLetters = "";
	targetLetters += targetWord[0];
	//Checking for duplicates
	for(int i = 1; i < targetWord.size(); i++)
	{
		bool checkSim = false;
		for(int j = 0; j<targetLetters.size(); j++)
		{
			if(targetLetters[j]==targetWord[i])
			{
				checkSim = true;
				break;
			}
		} 
		//If no duplicate found, add the letter.
		if(!checkSim)
		{
			targetLetters+=targetWord[i];	
		}
	}
	return targetLetters;
}


//Get a random word from a file.
std::string getWord(int difOption)
{
	std::vector<std::string> listOfWords; 	//Vector of strings to store the words.
	std::ifstream ifile;			//Input file stream.
	std::string line;				//String variable to get from the file stream.
	//Accessing different word list according to the difficulty.
	switch(difOption)
	{
		case 1:
			ifile.open("words_easy.txt");	
			break;
		case 2:
			ifile.open("words_medi.txt");
			break;
		case 3:
			ifile.open("words_hard.txt");
			break;	
		default:
			ifile.open("words_easy.txt");	
	}
	
	while(getline(ifile,line))
	{
		listOfWords.push_back(line);
	}
	ifile.close();
	srand(time(NULL));				//Generating a random number seed.
	return listOfWords[rand()%listOfWords.size()];	//Taking a random word from the vector.
}

//A routine to check your guess.
bool checkGuess(std::string &targetLetters, std::string &guessedWord, std::string targetWord, char guessedLetter)
{
	//Scanning through the unique letter string
	for(int i = 0; i<targetLetters.size(); i++)
	{	
		char checkLetter = targetLetters[i];
		
		//If the guess is correct...
		if(guessedLetter == checkLetter){
			//Showing the guessed letter to your progress string.
			for(int j = 0; j<targetWord.size(); j++)
			{
				if(targetWord[j]==guessedLetter)
				{
					guessedWord[j]=guessedLetter;
				}
			}
			std::cout << guessedWord << std::endl;
			//Remove that letter from the unique letter string
			targetLetters.erase(targetLetters.begin()+i);
			return true;
		}
	}
	return false;
}

void hangmanGame(int difOption)
{	
	int lives = 6; 									//Number of lives. 	
	char guessedLetter = ' '; 						//Char variable to input your guess.
	std::string targetWord = getWord(difOption);	//The word you want to guess. Taking a random word from a .txt file using getWord().
	std::string guessedWord = "";		//String variable to show your progress.
	
	//Setting the guessedWord string variable to be the same length as the target.
	for(int i = 0; i<targetWord.size(); i++)
	{
		guessedWord+='_';
	}

	//Taking unique letters from the target word.
	std::string targetLetters = getLetters(targetWord);	
	
	//Core of the game.
	while(targetLetters.size()!=0&&lives>0)
	{
		std::cout << "You have " << lives << " lives left!\n";	//Displaying your remaining lives.
		std::cout << "Enter a letter: ";						//Entering your guess.
		std::cin >> guessedLetter;
		if(!checkGuess(targetLetters, guessedWord, targetWord, guessedLetter))	//Checking the guess.
		{
			std::cout << "Incorrect!\n";
			lives--;
		}
	}
	if(lives==0)
	{
		std::cout << "You lose!\nThe word is " << targetWord << std::endl;
		std::cout << "Continue playing?(y/n)\n";
	}
	else
	{
		std::cout << "You win!\nContinue playing?(y/n)\n";
	}
}

int main()
{
	bool continuePlay = true; 	//Continous option.
	char continueOpt;
	int menuOpt = 0;			//Menu option.
	int difOption = 1;			//Difficulty option.
	while(continuePlay)
	{
		std::cout <<"========================\n"
				  <<"1.Play Hangman\n"
				  <<"2.Change difficulty\n"
				  <<"3.Exit\n";
		std::cout << "Enter option: ";
		std::cin >> menuOpt;
		switch(menuOpt)
		{
			case 1: //Playing the game.
				hangmanGame(difOption);
				std::cin >> continueOpt;
				if(continueOpt=='n')
				{
					continuePlay = false;
				}
				break;
			case 2: //Changing difficulty.
				std::cout << "Difficulty level: 1.Easy || 2.Medium || 3.Hard\n";
				std::cout << "Enter option: ";
				std::cin >> difOption;
				break;
			case 3: //Exiting the game.
				continuePlay = false;
				break;
			default:
				std::cout << "Invalid option!\n";
		}
		
	}
	return 0;
}
