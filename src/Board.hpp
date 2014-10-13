/*
 * Board.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <array>
#include <vector>
#include <memory>

#include "Piece.hpp"
#include "Position.hpp"
#include "Move.hpp"

class Board
{
public:

    static const char BOARD_SIZE = 8;

    Board();

    void addPiece(Piece &piece, Position position);
    void addPiece(Piece &piece);

    int getTurn() const;
    void executeMove(Move move); //TODO

    PiecePtr getPiecePtr(Position position) const;
    std::vector<Piece> getPieces(int color); //TODO
    std::vector<Piece> getEnnemyPieces(int color);//TODO
    Piece getKing(int color); //TODO
    Position getKingPosition(int color); //TODO

    bool isPositionFree(Position position);
    bool isPositionOnBoard(Position position);

    std::vector<Move> getLegalMoves(Piece piece); // TODO


private:

    std::array<std::array<PiecePtr, BOARD_SIZE>, BOARD_SIZE> myPieces;
    int myColorToPlay;
};

inline std::ostream& operator<<(std::ostream &strm, const Board &board)
{
		std::string boardStr;
		PiecePtr piece;

		for(int i = 7; i >= 0 ; i--)
		{
			strm << i << "|  ";

			for(int j = 0; j < 8 ; j++)
			{
				Position position(i,j);
				piece = board.getPiecePtr(position);
				
				if(piece)
				{
		            boardStr = piece->getChar();
				}
				else
				{
		            boardStr = "*";
				}
	
				strm << boardStr <<  " ";
			}

			strm << std::endl;
		}

		strm << "   ________________" << std::endl;
		strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm;
}
#endif /* BOARD_HPP_ */
