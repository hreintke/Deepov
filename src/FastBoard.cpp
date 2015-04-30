#include "FastBoard.hpp"




FastBoard::FastBoard() : myWhitePawns(0 | 0xFF << 8 ), myWhiteKnights(0 | (1 << 1) | (1 << 6)), myWhiteBishops(0x0 | (1 << 1) | (1 << 6))
{
	myWhitePieces = myWhitePawns | myWhiteKnights;
	myAllPieces = myBlackPieces | myWhitePieces;
}

	/* Get the bitboards */

U64 FastBoard::getWhitePawns() const{return myWhitePawns;}
U64 FastBoard::getWhiteKnights() const{return myWhiteKnights ;}
U64 FastBoard::getWhiteBishops() const{return myWhiteBishops;}
U64 FastBoard::getWhiteRooks() const{return myWhiteRooks;}
U64 FastBoard::getWhiteQueens() const{return myWhiteQueens;}
U64 FastBoard::getWhiteKing() const{return myWhiteKing;}

U64 FastBoard::getBlackPawns() const{return myBlackPawns;}
U64 FastBoard::getBlackKnights() const{return myBlackKnights;}
U64 FastBoard::getBlackBishops() const{return myBlackBishops;}
U64 FastBoard::getBlackRooks() const{return myBlackRooks;}
U64 FastBoard::getBlackQueens() const{return myBlackQueens;}
U64 FastBoard::getBlackKing() const{return myBlackKing;}

U64 FastBoard::getWhitePieces() const{return myWhitePieces;}
U64 FastBoard::getBlackPieces() const{return myBlackPieces;}
U64 FastBoard::getAllPieces() const{return myAllPieces;}

	/*  **********  */

    /* Moves methods */

U64 FastBoard::kingPseudoLegalMoves(const int& color, const U64& kingPos) const
{
    /* Copied from http://pages.cs.wisc.edu/~psilord/blog/data/chess-pages/nonsliding.html */
	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */

    U64	king_clip_file_h(kingPos & LookUpTables::CLEAR_FILE[7]);
	U64 king_clip_file_a(kingPos & LookUpTables::CLEAR_FILE[0]);

	/* remember the representation of the board in relation to the bitindex
		when looking at these shifts.... There is an error in the source link
		the code is copied from !! */
	U64 NW(king_clip_file_a << 7);
	U64 N(kingPos << 8);
	U64 NE(king_clip_file_h << 9);
	U64 E(king_clip_file_h << 1);

	U64 SE(king_clip_file_h >> 7);
	U64 S(kingPos >> 8);
	U64 SW(king_clip_file_a >> 9);
	U64 W(king_clip_file_a >> 1);

	/* N = north, NW = North West, from King location, etc */
	U64 kingMoves = NW | N | NE | E | SE | S | SW | W;

	U64 kingValid = kingMoves & ~getPieces(color);

	/* compute only the places where the king can move and attack. The caller
		will interpret this as a white or black king. */
	return kingValid;
}

U64 FastBoard::queenPseudoLegalMoves(const int& color, const U64& kingPos) const
{
    return 0;
}

U64 FastBoard::bishopPseudoLegalMoves(const int& color, const U64& kingPos) const
{
    return 0;
}

U64 FastBoard::rookPseudoLegalMoves(const int& color, const U64& kingPos) const
{
    return 0;
}

U64 FastBoard::knightPseudoLegalMoves(const int& color, const U64& kingPos) const
{
	/* we can ignore the rank clipping since the overflow/underflow with
		respect to rank simply vanishes. We only care about the file
		overflow/underflow. */

    U64	knight_clip_file_h(knightPos & LookUpTables::CLEAR_FILE[7]);
	U64 knight_clip_file_a(knightPos & LookUpTables::CLEAR_FILE[0]);

    U64	knight_clip_file_gh(knightPos & LookUpTables::CLEAR_FILE[7] & LookUpTables::CLEAR_FILE[6]);
	U64 knight_clip_file_ab(knightPos & LookUpTables::CLEAR_FILE[0] & LookUpTables::CLEAR_FILE[1]);

	/* remember the representation of the board in relation to the bitindex
		when looknight at these shifts.... */
    U64 WNW(knight_clip_file_ab << 6);
	U64 NNW(U64 knight_clip_file_a << 15);
	U64 NNE(U64	knight_clip_file_h << 17);
	U64 ENE(U64	knight_clip_file_gh << 10);

	U64 ESE(U64	knight_clip_file_gh >> 6);
    U64 SSE(U64	knight_clip_file_h >> 15);
	U64 SSW(U64 knight_clip_file_a >> 17);
	U64 WSW(knight_clip_file_ab >> 10);


	/* N = north, NW = North West, from knight location, etc */
	U64 knightMoves = WNW | NNW | NNE | ENE | ESE | SSE | SSW | WSW;

	U64 knightValid = knightMoves & ~getPieces(color);

	/* compute only the places where the knight can move and attack. The caller
		will interpret this as a white or black knight. */
	return knightValid;
}

U64 FastBoard::pawnPseudoLegalMoves(const int& color, const U64& kingPos) const
{
    return 0;
}

std::vector<FastMove> FastBoard::getMoves() const
{
    return myMoves;
}
