//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Adarsh Prakash on 25/07/17.
//  Copyright © 2017 Adarsh Prakash. All rights reserved.
//

/* the game logic (no view code or direct user intercation 
 the game is a simple guess the word game based on mastermind
 
 */
#pragma once
#define FBullCowGame_hpp
#include<string>

//to make the syntax unreal friendly
using FString = std::string;
using int32 = int;

//all values initalised to zero
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    Ok,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

enum class EResetStatus
{
    No_Hidden_Word,
    Ok
};

class FBullCowGame
{
public:
    
    FBullCowGame(); //constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    
    
    //^^Pleas try and ignore this and try to focus on the interface above^^
private:
    
    //See Constructor for initialisation 
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const; 
};

