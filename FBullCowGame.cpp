 //
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Adarsh Prakash on 25/07/17.
//  Copyright © 2017 Adarsh Prakash. All rights reserved.
//

#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map //to make syntax unreal friendly

using int32 = int;

//Getter Functions

FBullCowGame :: FBullCowGame() //default constructor
{
    Reset();
}


int32 FBullCowGame :: GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame :: GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame :: GetMaxTries() const
{
    TMap<int32, int32>WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
    {
        
    }return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame :: IsGameWon() const { return bGameIsWon; }
 
void FBullCowGame :: Reset()
{
    
    const FString HIDDEN_WORD = "flight"; //this MUST be an isogram
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry =1;
    bGameIsWon = false; 
    return;
}


EGuessStatus FBullCowGame :: CheckGuessValidity(FString Guess) const
{
    if(!IsIsogram(Guess))  // if the guess isnt an isogram
    {
        return EGuessStatus::Not_Isogram; 
    }
    else if(!IsLowercase(Guess))  // if the guess isnt all lowercase
    {
        return EGuessStatus::Not_Lowercase; //
    }
    else if(Guess.length() != GetHiddenWordLength())// if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else// otherwise
    {
        return EGuessStatus::Ok;
    }
}

//recieves a valid guess,increments turn and returns count

FBullCowCount FBullCowGame:: SubmitValidGuess(FString Guess)
{
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess

    //loop through all the letters in hidden word
    for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        //comapare letters against the guess
        for(int32 GChar = 0; GChar < WordLength; GChar++)
        {
            //if they match then
            if(Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if(MHWChar == GChar) //if they are in the same place

                {
                    BullCowCount.Bulls++;  //increment bulls
                }
                else
                {
                    BullCowCount.Cows++;  // increment cows if not
                }
            }
        }
        
    }
    if(BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else{
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    //treat 0 and 1 as isograms
    if (Word.length() <= 1)
    {
        return true;
    }
    
    TMap<char,bool> LetterSeen; //setup our map
    for(auto Letter : Word) //for all letters of the word
    {
        Letter = tolower(Letter); //handle mixed case
    
        if (LetterSeen[Letter])//if letter is in the map
        {
            return false; //we do not have an isogram
        }
        else{
            LetterSeen[Letter] = true; //add letter to the map as seen
        }
    
            
}
    return true; //for cases where /0 is entered
}
bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
        return false;
        }
    }
    return true;
}
