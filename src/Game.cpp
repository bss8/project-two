#include "Game.hpp"

#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

Game::Game(bool player1MinMax, int evalVersionP1, bool player2MinMax, int evalVersionP2, int depth)
{
    state = Board();
    state.InitializeMoveTable();
    redPlayer = Player(player1MinMax, Color::RED, depth, evalVersionP1);
    blackPlayer = Player(player2MinMax, Color::BLACK, depth, evalVersionP2);
}

Game::GameOver Game::startGame()
{
    int piecesTaken;

    while (true)
    {
        std::cout << "Black's Turn..." << std::endl;

        piecesTaken = blackPlayer.takeTurn(state);
        blackPlayer.increaseNumPiecesTaken(piecesTaken);
        redPlayer.decreaseNumPieces(piecesTaken);

        if (doesBlackWin())
            return GameOver::BLACK_WINS;

        std::cout << "Red's Turn..." << std::endl;

        piecesTaken = redPlayer.takeTurn(state);
        redPlayer.increaseNumPiecesTaken(piecesTaken);
        blackPlayer.decreaseNumPieces(piecesTaken);

        if (doesRedWin())
            return GameOver::RED_WINS;

        if (isItADraw())
            return GameOver::DRAW;
    }
}

Color Game::changePlayer(Color currentPlayer)
{
    if (currentPlayer == Color::BLACK)
        return Color::RED;
    else
        return Color::BLACK;
}

bool Game::doesBlackWin()
{
    std::vector<Board::Move> redMoves = state.moveGen(Color::RED);
    return (redMoves.size() == 0);
}

bool Game::doesRedWin()
{
    std::vector<Board::Move> blackMoves = state.moveGen(Color::BLACK);
    return (blackMoves.size() == 0);
}

bool Game::isItADraw()
{
    if (redPlayer.getNumTurns() >= MAX_ALLOWED_TURNS ||
        blackPlayer.getNumTurns() >= MAX_ALLOWED_TURNS)
        return true;
    return false;
}