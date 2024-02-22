/*
** EPITECH PROJECT, 2022
** B-AIA_Gomoku
** File description:
** Evaluate
*/

#include <fstream>
#include <sstream>
#include <string>

#include "IA.hpp"

namespace gomoku {

    double IA::ComputeShapeScore(const int &consecutive, const int &openEnds, const Turn team) noexcept
    {
        switch (consecutive) {
            case 1:
                return (1 * openEnds);
            case 2:
                return (30 * openEnds);
            case 3:
                return (500 * openEnds);
            case 4:
                return (1000 * openEnds);
            case 5:
                return WINSCORE;
        }
        return WINSCORE;
    }

    double IA::EvaluateHorizontal(const Board &map, const Turn team) noexcept
    {
        double score = 0;
        int consecutive = 0;
        int openEnds = 0;
        int player = 1;

        if (team == Turn::ENEMY)
            player = 2;

        for (std::size_t i = 0; i != map.size(); ++i) {
            for (std::size_t j = 0; j != map[i].size(); ++j) {
                if (map[i][j] == player) {
                    consecutive += 1;
                    if (consecutive == 1 && j > 0) {
                        if (map[i][j - 1] == 0)
                            openEnds = 1;
                    }
                    if (j == map.size() - 1) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
                else if (map[i][j] == 0 && consecutive > 0) {
                    openEnds++;
                    score += ComputeShapeScore(consecutive, openEnds, team);
                    consecutive = 0;
                } else {
                    if (consecutive > 0) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
            }
            consecutive = 0;
            openEnds = 0;
        }
        return score;
    }

    double IA::EvaluateVertical(const Board &map, const Turn team) noexcept
    {
        double score = 0;
        int consecutive = 0;
        int openEnds = 0;
        int player = 1;

        if (team == Turn::ENEMY)
            player = 2;

        for (std::size_t i = 0; i != map[0].size(); ++i) {
            for (std::size_t j = 0; j != map.size(); ++j) {
                if (map[j][i] == player) {
                    consecutive += 1;
                    if (consecutive == 1 && j > 0) {
                        if (map[j - 1][i] == 0)
                            openEnds = 1;
                    }
                    if (j == map.size() - 1) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
                else if (map[j][i] == 0 && consecutive > 0) {
                    openEnds++;
                    score += ComputeShapeScore(consecutive, openEnds, team);
                    consecutive = 0;
                } else {
                    if (consecutive > 0) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
            }
            consecutive = 0;
            openEnds = 0;
        }

        return score;
    }

    double IA::EvaluateDiagonalRight(const Board &map, const Turn team) noexcept
    {
        int size = static_cast<int>(map.size());
        double score = 0;
        int consecutive = 0;
        int openEnds = 0;
        int start = 0;
        int end = 0;
        int player = 1;

        if (team == Turn::ENEMY)
            player = 2;

        for (int k = 1 - size; k < size; ++k) {
            start = std::max(0, k);
            end = std::min(size + k - 1, size - 1);
            for (int i = start, j = 0; i <= end; ++i) {
                j = i - k;
                if (map[i][j] == player) {
                    consecutive += 1;
                    if (consecutive == 1 && (i > 0 && j > 0)) {
                        if (map[i - 1][j - 1] == 0)
                            openEnds = 1;
                    }
                    if (j == size - 1 || i == size - 1) {
                        openEnds = 1;
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
                else if (map[i][j] == 0 && consecutive > 0) {
                    openEnds++;
                    score += ComputeShapeScore(consecutive, openEnds, team);
                    consecutive = 0;
                    openEnds = 0;
                } else {
                    if (consecutive > 0) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
            }
            consecutive = 0;
            openEnds = 0;
        }
        return score;
    }

    double IA::EvaluateDiagonalLeft(const Board &map, const Turn team) noexcept
    {
        int size = static_cast<int>(map.size());
        double score = 0;
        int consecutive = 0;
        int openEnds = 0;
        int start = 0;
        int end = 0;
        int player = 1;

        if (team == Turn::ENEMY)
            player = 2;

        for (int k = 0; k != size * 2; ++k) {
            start = std::max(0, k - size);
            end = std::min(size, k);
            for (int i = start, j = 0; i != end; ++i) {
                j = k - i - 1;
                if (map[i][j] == player) {
                    consecutive += 1;
                    if (consecutive == 1 && (i > 0 && j < size - 1)) {
                        if (map[i - 1][j + 1] == 0)
                            openEnds = 1;
                    }
                    if (i == map.size() - 1 || j == 0) {
                        openEnds = 1;
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
                else if (map[i][j] == 0 && consecutive > 0) {
                    openEnds++;
                    score += ComputeShapeScore(consecutive, openEnds, team);
                    consecutive = 0;
                } 
                else {
                    if (consecutive > 0) {
                        score += ComputeShapeScore(consecutive, openEnds, team);
                        consecutive = 0;
                        openEnds = 0;
                    }
                }
            }
            consecutive = 0;
            openEnds = 0;
        }

        return score;
    }

    double IA::ComputeScore(Board map, Turn team) noexcept
    {
        double score = 0;

        score += EvaluateHorizontal(map, team) + EvaluateVertical(map, team);
        score += EvaluateDiagonalLeft(map, team) + EvaluateDiagonalRight(map, team);
        return score;
    }

    double IA::EvaluateBoard(const Board &map, const Turn team) noexcept
    {
        double ownScore = ComputeScore(map, Turn::OWN);
        double enemyScore = ComputeScore(map, Turn::ENEMY);
        if (ownScore == 0)
            ownScore = 1;
        if (enemyScore == 0)
            enemyScore = 1;
        
        return (ownScore/enemyScore);
    }
}