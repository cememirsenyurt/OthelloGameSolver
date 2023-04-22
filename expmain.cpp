// expmain.cpp
//
// ICS 46 Winter 2022
// Project #3: Black and White
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the othellogame library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include <iostream>
#include <ics46/factory/DynamicFactory.hpp>
#include "myOthelloAI.hpp"
#include "OthelloGameStateFactory.hpp"

int main()
{
    
    std::unique_ptr<OthelloAI> randomAI = 
        ics46::factory::DynamicFactory<OthelloAI>::instance()
        .make("Random Move (Provided)");
    
    csenyurt::MyOthelloAI myAI;

    std::unique_ptr<OthelloGameState> state = 
        OthelloGameStateFactory{}.makeNewGameState(8, 8);
    
    int myWins  = 0;
    int oppWins = 0;
    int tie     = 0;

    for(int i = 0; i < 100; ++i)
    {
        while(!state->isGameOver())
        {
            auto[x, y] = state->isBlackTurn()
            ? randomAI->chooseMove(*state)
            : myAI.chooseMove(*state);

            state->makeMove(x, y);
        }
            std::cout << state->blackScore() << "-" << state->whiteScore() << std::endl;
            if(state->blackScore() > state->whiteScore())
            {
                oppWins++;
            }
            else if(state->blackScore() < state->whiteScore())
            {
                myWins++;
            }
            else
            {
                tie++;
            }
    }
    
    std::cout << "My AI's wins: " << myWins << std::endl;
    std::cout << "Opponent AI's wins: " << oppWins << std::endl;
    std::cout << "Tie games: " << tie << std::endl;

    return 0;
}

