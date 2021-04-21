#include "Simulation.hpp"
#include "Game.hpp"

#include <iostream>
#include <stdexcept>

/**
 * Simulation implementation
 * @author Borislav Sabotinov
 * 
 * 
 */

Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

/**
* Runs all games runs as delineated in Simulation.hpp
* 
* p1_alg: 1 p1_eval: 1 p2_alg: 1 p2_eval: 1
* p1_alg: 1 p1_eval: 1 p2_alg: 1 p2_eval: 2
* p1_alg: 1 p1_eval: 1 p2_alg: 1 p2_eval: 3
* p1_alg: 1 p1_eval: 2 p2_alg: 1 p2_eval: 1
* p1_alg: 1 p1_eval: 2 p2_alg: 1 p2_eval: 2
* p1_alg: 1 p1_eval: 2 p2_alg: 1 p2_eval: 3
* p1_alg: 1 p1_eval: 3 p2_alg: 1 p2_eval: 1
* p1_alg: 1 p1_eval: 3 p2_alg: 1 p2_eval: 2
* p1_alg: 1 p1_eval: 3 p2_alg: 1 p2_eval: 3
* p1_alg: 1 p1_eval: 1 p2_alg: 2 p2_eval: 1
* p1_alg: 1 p1_eval: 1 p2_alg: 2 p2_eval: 2
* p1_alg: 1 p1_eval: 1 p2_alg: 2 p2_eval: 3
* p1_alg: 1 p1_eval: 2 p2_alg: 2 p2_eval: 1
* p1_alg: 1 p1_eval: 2 p2_alg: 2 p2_eval: 2
* p1_alg: 1 p1_eval: 2 p2_alg: 2 p2_eval: 3
* p1_alg: 1 p1_eval: 3 p2_alg: 2 p2_eval: 1
* p1_alg: 1 p1_eval: 3 p2_alg: 2 p2_eval: 2
* p1_alg: 1 p1_eval: 3 p2_alg: 2 p2_eval: 3
* p1_alg: 2 p1_eval: 1 p2_alg: 2 p2_eval: 1
* p1_alg: 2 p1_eval: 1 p2_alg: 2 p2_eval: 2
* p1_alg: 2 p1_eval: 1 p2_alg: 2 p2_eval: 3
* p1_alg: 2 p1_eval: 2 p2_alg: 2 p2_eval: 1
* p1_alg: 2 p1_eval: 2 p2_alg: 2 p2_eval: 2
* p1_alg: 2 p1_eval: 2 p2_alg: 2 p2_eval: 3
* p1_alg: 2 p1_eval: 3 p2_alg: 2 p2_eval: 1
* p1_alg: 2 p1_eval: 3 p2_alg: 2 p2_eval: 2
* p1_alg: 2 p1_eval: 3 p2_alg: 2 p2_eval: 3
* 
*/
void Simulation::runFullSimulation()
{
    std::cout << "\033[0;32mRunning a FULL simulation!\033[0m" << std::endl;

    for (int depth = 2; depth <= 4; depth += 2)
    {
        std::cout << "Depth: " << depth << std::endl;

        for (int p1_alg = 0; p1_alg < 2; p1_alg++)
        {
            for (int p2_alg = 0; p2_alg < 2; p2_alg++)
            {
                for (int p1_eval = 1; p1_eval < 4; p1_eval++)
                {
                    for (int p2_eval = 1; p2_eval < 4; p2_eval++)
                    {
                        // omit duplicates to save time - we only care about unique runs
                        // player 1 need not use alg 2. It's already covered by Player 2
                        if (p1_alg == 2 && p2_alg == 1)
                            continue;

                        std::cout << "p1_alg: " << p1_alg << " p1_eval: " << p1_eval << " p2_alg: "
                                  << p2_alg << " p2_eval: " << p2_eval << std::endl;

                        Game *game = new Game(p1_alg, p1_eval, p2_alg, p2_eval, 4);
                        Game::GameOver endGameStatus = game->startGame();

                        // TODO: print game status, num nodes generated, time it took, etc. 

                        delete game; 

                    } // p2_eval
                }     // p1_eval
            }         // p2_alg
        }             // p1_alg
    }                 // depth
}

/**
* @param int algorithm - If 1, minimax; if 2, AB Prune
* @param int evalFunction - 1,2, or 3
*/
void Simulation::runSpecificSimulation(int playerOneAlg, int playerOneEvalFunct, int playerTwoAlg, int playerTwoEvalFunct, int depth)
{
    std::cout << Pieces::ANSII_GREEN_START << "Running a SINGLE game, specific simulation!" << Pieces::ANSII_END << std::endl;

    // Validate algorithm selections
    if ((playerOneAlg < 0 || playerOneAlg > 3) && (playerTwoAlg < 0 || playerTwoAlg > 3))
        throw std::runtime_error("Error: algorithm may only be 1 (minimax-a-b) or 2 (ab-prune)!");

    // Validate evaluation function selections
    if ((playerOneEvalFunct < 0 || playerOneEvalFunct > 4) && (playerTwoEvalFunct < 0 || playerTwoEvalFunct > 4))
        throw std::runtime_error("Error: evalFunction may only be 1, 2, 3, or 4!");
    
    // Validate depth
    if (depth <= 0 || depth > 15)
        throw std::runtime_error("Error: depth must be > 0 and <= 15. ");

    Game *game = new Game(playerOneAlg, playerOneEvalFunct, playerTwoAlg, playerTwoEvalFunct, depth);
    Game::GameOver endGameStatus = game->startGame();

    if (endGameStatus == Game::GameOver::BLACK_WINS)
    {
        std::cout << "\nBLACK WINS!!!" << std::endl; 
        std::cout << "BLACK Player: ᕙ(-_-')ᕗ" << std::endl;
        std::cout << "But most importantly, RED looooses (boooo!)" << std::endl;
        std::cout << "RED Player: (╯°□°）╯︵ ┻━┻" << std::endl;
    }
    else if (endGameStatus == Game::GameOver::RED_WINS)
    {
        std::cout << "\nRED WINS!!!" << std::endl; 
        std::cout << "RED Player: ᕙ(-_-')ᕗ" << std::endl;
        std::cout << "But most importantly, BLACK looooses (boooo!)" << std::endl;
        std::cout << "BLACK Player: (╯°□°）╯ ︵ ┻━┻" << std::endl; 
    }
    else if (endGameStatus == Game::GameOver::DRAW)
    {
        std::cout << "DRAW!!!" << std::endl;
        std::cout << "Red - (ง •̀_•́)ง   ლ( `Д’ ლ) - Black" << std::endl;
        std::cout << "Mission FAILED...We'll get em next time!" << std::endl; 
    }
    else 
        std::cout << "Oops, something went wrong!" << std::endl;

    delete game; 
}

/**
 * runPlayerVsAISimulation - play a game with a human against a computer player
 * 
 */ 
void Simulation::runPlayerVsAISimulation(int playerAlg, int playerEvalFunct, int depth) 
{
    
    Player computerPlayer = Player(playerAlg, Color::RED, depth, playerEvalFunct); 
    
    while (true)
    {

    }
}

/** 
 * getNumGamesPlayed - returns a count of the number of games played in a simulation
 *
 */
int Simulation::getNumGamesPlayed()
{
    return 0;
}

/**
 * generateAnalsysisResults creates a table with results for analysis how many nodes were created, etc.
 */ 
void Simulation::generateAnalysisResults()
{
}