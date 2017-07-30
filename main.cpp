//
//  main.cpp
//  BullCowGame
//
//  Created by Adarsh Prakash on 24/07/17.
//  Copyright © 2017 Adarsh Prakash. All rights reserved.
//


/* This is the console executable, that makes use of the BullCow class.
 This acts a view in MVC pattern and is responsible for all user interaction.
 For game logic see the FBullCow class
 */
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

//to make syntax Unreal friendly
using Ftext = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AsktoPlayAgain();
void PrintGameSummary();

 FBullCowGame BCGame; // instatiate a new game ,which we re-use across plays

//the entry point for the application
int main()
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AsktoPlayAgain();
    }
    while(bPlayAgain);
}



//introduce the game
void PrintIntro()
{
    
    std::cout << "\n\nWelcome to Bulls And Cows, a fun word game\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n\n ";
    return;
}


//loop for the number of turns asking for guesses
void PlayGame()
{
   
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    //loop asking for guess while the game is NOT won
    //and there are still tries remaining
    
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        Ftext Guess = GetValidGuess();
        
        //submit vaild guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        //print number of bulls and cows
        std::cout << "Bulls " << BullCowCount.Bulls;
        std::cout << ". Cows " << BullCowCount.Cows << "\n\n";
        
        
        std::cout << std::endl;
    }
    
    PrintGameSummary();
    return;
}


//loop continually until the user gives a valid guess
Ftext GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    Ftext Guess = "";
    do
    {
        //get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your Guess: ";
        getline(std::cin, Guess);
    
        //check status and give feedback
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters\n\n";
            default:
                //assume the guess is valid
                break;
        }
    } while (Status != EGuessStatus::Ok); //keep looping until we get no errors
    return Guess;
}

bool AsktoPlayAgain()
{
    std::cout << "Do you want to play again(y/n)?";
    Ftext Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}
void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else{
        std::cout << "Better luck next time \n";
    }
}



