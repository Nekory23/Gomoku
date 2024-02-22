/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

/* INCLUDES */
#include <vector>
#include <iostream>
#include <algorithm>

typedef std::vector<std::vector<int>> Board;
typedef std::pair<int, int> Coords;

static const int DEPTH = 3;
static const double WINSCORE = 100000000;

/* CLASS */
namespace gomoku
{
    typedef struct Move_st {
        Coords coords;
        double score;
    } Move_t;

    enum class Turn {
        OWN = 1,
        ENEMY,
    };

    class IA {
        public:
            IA() = default;
            ~IA() = default;

            std::string PlayBestMove(const Board &map) noexcept;
            Coords SearchWinningMove(const Board &map, const std::vector<Coords> &possibleMoves) noexcept;
            Move_t Minimax(int depth, const Board &map, const Turn &team, double a, double b) noexcept;

            double ComputeScore(Board map, Turn team) noexcept;
            double EvaluateBoard(const Board &map, const Turn team) noexcept;
        
        private:
            std::vector<Coords> GeneratePossibleMoves(const Board &map) noexcept;
            Board CopyMap(const Board &map) noexcept;

            double EvaluateHorizontal(const Board &map, const Turn team) noexcept;
            double EvaluateVertical(const Board &map, const Turn team) noexcept;
            double EvaluateDiagonalRight(const Board &map, const Turn team) noexcept;
            double EvaluateDiagonalLeft(const Board &map, const Turn team) noexcept;
            double ComputeShapeScore(const int &consecutive, const int &openEnds, const Turn team) noexcept;

    }; // class IA
} // namespace gomoku


#endif /* !IA_HPP_ */
