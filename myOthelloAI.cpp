#include <ics46/factory/DynamicFactory.hpp>
#include "myOthelloAI.hpp"
#include "OthelloBoard.hpp"
#include "OthelloGameState.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(
    OthelloAI, csenyurt::MyOthelloAI,
    "My wonderful AI (Required)");

int evaluation(OthelloGameState& state, bool myTurn)
{
    int total = 0;

    if(state.isBlackTurn() == 1 && myTurn == 1)
    {
        total = state.blackScore() - state.whiteScore();
        if(state.board().cellAt(0, 0) == OthelloCell::black || 
    state.board().cellAt(state.board().width() - 1, state.board().width() - 1) == OthelloCell::black || 
    state.board().cellAt(0, state.board().width()-1) == OthelloCell::black ||
    state.board().cellAt(state.board().width()-1, 0) == OthelloCell::black)
    {
        total += 500;
    }

    }
    else if(state.isWhiteTurn() == 1 && myTurn == 0)
    {
        total = state.whiteScore() - state.blackScore();
        if(state.board().cellAt(0, 0) == OthelloCell::white || 
    state.board().cellAt(state.board().width() - 1, state.board().width() - 1) == OthelloCell::white ||
    state.board().cellAt(0, state.board().width()-1) == OthelloCell::white ||
    state.board().cellAt(state.board().width()-1, 0) == OthelloCell::white)
    {
        total += 500;
    }                                                            
    
    }
    return total;
}


int search(OthelloGameState& state, int depth, bool myTurn)
{
    if(depth == 0)
    {
        return evaluation(state, myTurn);
    }
    else
    {
        if(myTurn)
        {
            int bestScore = -9999;
            for(int i = 0; i < state.board().width(); ++i)
            {
                for(int j = 0; j < state.board().height(); ++j)
                {
                    if(state.board().isValidCell(i, j) && state.isValidMove(i, j))
                    {
                        std::unique_ptr<OthelloGameState> tempState = state.clone();
                        tempState->makeMove(i, j);
                        int temp = search(*tempState, depth-1, 1);

                        if(temp > bestScore)
                        {
                            bestScore = temp;
                        }
                    }
                }
            }
            return bestScore;
        }
        else
        {
            int minScore = 9999;
            for(int i = 0; i < state.board().width(); ++i)
            {
                for(int j = 0; j < state.board().height(); ++j)
                {
                    if(state.board().isValidCell(i, j) && state.isValidMove(i, j))
                    {
                        std::unique_ptr<OthelloGameState> tempState = state.clone();
                        tempState->makeMove(i, j);
                        int temp = search(*tempState, depth-1, 0);

                        if(temp < minScore)
                        {
                            minScore = temp;
                        }   
                    }
                }
            }
            return minScore;
        }
    }
}


std::pair<int, int> csenyurt::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    std::unique_ptr<OthelloGameState> newState = state.clone();
    bool myColor;
    std::vector<std::pair<int, int>> where;
    std::vector<int> bestScore;
    int depth = 4;

    if(newState->isGameOver() || depth == 0)
    {
        //game over
    }
    else
    {
        for(int i = 0; i < newState->board().width(); ++i)
        {
            for(int j = 0; j < newState->board().height(); ++j)
            {
                if(newState->board().isValidCell(i, j) && newState->isValidMove(i, j))
                {
                    where.push_back(std::make_pair(i, j));
                }
            }
        }
    
        if(newState->isBlackTurn())
        {
            myColor = 1;
        }
        else
        {
            myColor = 0;
        }

        for(int i = 0; i < where.size(); ++i)
        {
            std::unique_ptr<OthelloGameState> tempState = newState->clone();
            tempState->makeMove(where[i].first, where[i].second);
            int temp;

            temp = search(*tempState, depth, myColor);
            bestScore.push_back(temp);
        }

    }
    int location;
    location = std::distance(bestScore.begin(),std::max_element(bestScore.begin(), bestScore.end()));
    
    return where.at(location);
}

