/*
 * Piece.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef Piece_HPP_
#define Piece_HPP_

#include <ostream>
#include <vector>

#include "Position.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Board;

class Piece
{
public:

	Piece();
	Piece(Position position);
	Piece(Position position, int color);
	Piece(Position position, int color, bool isPinned);

	Position getPosition() const;
	char getValue() const;
	int getColor() const;
	bool isEmpty() const;
	bool areColorDifferent(Piece &piece);
	std::vector<Move> getPseudoLegalMoves(Board &board);

protected:

	Position myPosition;

private:

	bool myIsEmpty;
	int myColor;
	bool myIsPinned;
};

inline std::ostream& operator<<(std::ostream &strm, const Piece &piece)
{
    std::string color = piece.getColor() == 0 ? " WHITE" : " BLACK";

   	strm << piece.getPosition() << color <<std::endl;
	return strm;
}

#endif /* Piece_HPP_ */
