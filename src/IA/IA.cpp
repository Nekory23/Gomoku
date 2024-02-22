/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** IA
*/

#include "Gomoku.hpp"

namespace gomoku {

    Board IA::CopyMap(const Board &map) noexcept
    {
        Board newMap;

        for (std::size_t i = 0; i != map.size(); ++i)
            newMap.push_back(map[i]);
        return newMap;
    }

    std::vector<Coords> IA::GeneratePossibleMoves(const Board &map) noexcept
    {
        std::size_t size = map.size();
        Board dummy = CopyMap(map);
        std::vector<Coords> possibleMoves;

       for (std::size_t i = 0; i != dummy.size(); ++i)
            for (std::size_t j = 0; j != dummy[i].size(); ++j)
                if (dummy[i][j] == 1 || dummy[i][j] == 2) {
                    if (i > 0 && dummy[i - 1][j] == 0) { // north
                        possibleMoves.push_back(std::make_pair<int, int>(i - 1, j));
                        dummy[i - 1][j] = 3;
                    }
                    if (i < size - 1 && dummy[i + 1][j] == 0) { // south
                        possibleMoves.push_back(std::make_pair<int, int>(i + 1, j));
                        dummy[i + 1][j] = 3;
                    }
                    if (j > 0 && dummy[i][j - 1] == 0) { // west
                        possibleMoves.push_back(std::make_pair<int, int>(i, j - 1));
                        dummy[i][j - 1] = 3;
                    }
                    if (j < size - 1 && dummy[i][j + 1] == 0) { // east
                        possibleMoves.push_back(std::make_pair<int, int>(i, j + 1));
                        dummy[i][j + 1] = 3;
                    }
                    if (i > 0 && j > 0 && dummy[i - 1][j - 1] == 0) { // north west
                        possibleMoves.push_back(std::make_pair<int, int>(i - 1, j - 1));
                        dummy[i - 1][j - 1] = 3;
                    }
                    if (i < size - 1 && j < size - 1 && dummy[i + 1][j + 1] == 0) { // south east
                        possibleMoves.push_back(std::make_pair<int, int>(i + 1, j + 1));
                        dummy[i + 1][j + 1] = 3;
                    }
                    if (i < size - 1 && j > 0 && dummy[i + 1][j - 1] == 0) { // south west
                        possibleMoves.push_back(std::make_pair<int, int>(i + 1, j - 1));
                        dummy[i + 1][j - 1] = 3;
                    }
                    if (i > 0 && j < size - 1 && dummy[i - 1][j + 1] == 0) { // north west
                        possibleMoves.push_back(std::make_pair<int, int>(i - 1, j + 1));
                        dummy[i - 1][j + 1] = 3;
                    }
                }
        return possibleMoves;
    }

    Move_t IA::Minimax(int depth, const Board &map, const Turn &team, double a, double b) noexcept
    {    
        if (depth == 0) {
            Move_t results;
            results.score = EvaluateBoard(map, team);
            return results;
        }

        Move_t best;
        std::vector<Coords> possibleMoves = GeneratePossibleMoves(map);

        if (depth == DEPTH) {
            best.coords = SearchWinningMove(map, possibleMoves);
            if (best.coords.first != -1) {
                //std::cout << "FOUND ONE WINNING MOVE \\o/" << std::endl;
                return best;
            }
        }

        if (team == Turn::OWN) {
            best.score = -999999.0;
            for (std::size_t i = 0; i != possibleMoves.size(); ++i) {
                Board dummy = CopyMap(map);
                dummy[possibleMoves[i].first][possibleMoves[i].second] = 1;
                Move_t temp = Minimax(depth - 1, dummy, Turn::ENEMY, a, b);

                a = std::max(a, temp.score);
                if (temp.score >= b)
                    return temp;
                if (temp.score >= best.score) {
                    best = temp;
                    best.coords = possibleMoves[i];
                }
            }
        } else {
            best.score = 999999.0;
            for (std::size_t i = 0; i != possibleMoves.size(); ++i) {
                Board dummy = CopyMap(map);
                dummy[possibleMoves[i].first][possibleMoves[i].second] = 2;
                Move_t temp = Minimax(depth - 1, dummy, Turn::OWN, a, b);

                b = std::min(b, temp.score);
                if (temp.score <= a)
                    return temp;
                if (temp.score < best.score) {
                    best = temp;
                    best.coords = possibleMoves[i];
                }
            }
        }
        return best;
    }

    Coords IA::SearchWinningMove(const Board &map, const std::vector<Coords> &possibleMoves) noexcept
    {
        Board dummy = CopyMap(map);
        Coords win(-1, -1);

        for (std::size_t i = 0; i != possibleMoves.size(); ++i) {
            dummy[possibleMoves[i].first][possibleMoves[i].second] = 1;
            if (ComputeScore(dummy, Turn::OWN) >= WINSCORE) {
                win = possibleMoves[i];
                dummy.clear();
                return win;
            }
            dummy[possibleMoves[i].first][possibleMoves[i].second] = 0;
        }
        dummy.clear();
        return win;
    }

    std::string IA::PlayBestMove(const Board &map) noexcept
    {
        Move_t bestMoveCoords;
        std::string bestMoveStr = "";
        
        bestMoveCoords.coords.first = -1;
        bestMoveCoords.coords.second = -1;
        bestMoveCoords.score = -1;

        bestMoveCoords = Minimax(DEPTH, map, Turn::OWN, -WINSCORE, WINSCORE);
        bestMoveStr.append(std::to_string(bestMoveCoords.coords.first));
        bestMoveStr.append(",");
        bestMoveStr.append(std::to_string(bestMoveCoords.coords.second));
        return bestMoveStr;
    }
}