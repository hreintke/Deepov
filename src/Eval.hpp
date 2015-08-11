#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Board.hpp"
#include "Utils.hpp"
#include "EvalTables.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"

class Eval
{
public:
    const static int TOTAL_MATERIAL = 7940;

    Eval(std::shared_ptr<Board> boardPtr);
    int evaluate();

    /* These functions are called just before execute/undoMove, to keep the current colorToPlay*/
    void updateEvalAttributes(const Move &move);
    void rewindEvalAttributes(const Move &move);

    /* Functions that calculate eval parameters */
    int calcMobilityScore(const int64_t alpha) const; // alpha is TOTAL_MATERIAL-myGameStage

    /* These functions are mainly for tests */
    inline int getOpeningPSQValue() const {return myOpeningPSQValue;};
    inline int getEndgamePSQValue()const {return myEndgamePSQValue;};
    inline int64_t getGameStage() const {return myGameStage;};
	inline int getMaterialScore() const {return myMaterialScore;};

    /* Move ordering */
	static void sortMoveList(std::vector<Move>& moveList);

private:

    std::shared_ptr<Board> myBoard;
    int64_t myGameStage; // Total material for both sides
    int myOpeningPSQValue; // Updated after each move in evaluate
    int myEndgamePSQValue;
    int myMaterialScore;

    void init(); // Here i permute the tables to get the indexes in the right order and i fill black values

    int getWhitePiecesValue() const;
    int getBlackPiecesValue() const;
    static int pieceTypeToValue(int type);

};

#endif // EVAL_H_INCLUDED
