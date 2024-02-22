/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Cmd
*/

#include "Gomoku.hpp"


static bool CheckDone(const std::string &input)
{
    std::vector<std::string> cmd = Split(input, ' ');

    if (cmd.size() == 1 && cmd[0].compare("DONE") == 0)
        return true;
    return false;
}

namespace gomoku {
    void Game::Start(std::vector<std::string> cmd) noexcept
    {
        if (cmd.size() != 2)
            std::cout << "ERROR invalid argument" << std::endl;
        else if (_isStarted)
            std::cout << "ERROR the game has already started" << std::endl;
        else if (std::atoi(cmd[1].c_str()) <= SIZE)
            std::cout << "ERROR unsupported size" << std::endl;
        else {
            for (auto i = 0; i != std::atoi(cmd[1].c_str()); ++i) {
                std::vector<int> tmp;
                for (auto j = 0; j != std::atoi(cmd[1].c_str()); ++j)
                    tmp.push_back(0);
                _map.push_back(tmp);
            }
            _isStarted = true;
            std::cout << "OK - everything is good" << std::endl;
        }
    }

    void Game::Restart(std::vector<std::string> cmd) noexcept
    {
        std::size_t size = 0;

        if (cmd.size() != 1) {
            std::cout << "ERROR this command doesn't take arguments" << std::endl;
            return;
        }
        else if (_map.empty()) {
            std::cout << "ERROR cannot restart a game that hasn't started" << std::endl;
            return;
        }
        size = _map.size();
        _map.clear();
        for (std::size_t i = 0; i != size; ++i) {
            std::vector<int> tmp;
            for (std::size_t j = 0; j != size; ++j)
                tmp.push_back(0);
            _map.push_back(tmp);
        }
        std::cout << "OK" << std::endl;
    }

    void Game::End(std::vector<std::string> cmd) noexcept
    {
        if (cmd.size() != 1)
            std::cout << "ERROR command don't take argument" << std::endl;
        else if (!_isStarted)
            std::cout << "ERROR the game hasn't started yet" << std::endl;
        else {
            _map.clear();
            _isStarted = false;
            _hasEnded = true;
        }
    }

    void Game::Begin(std::vector<std::string> cmd) noexcept
    {
        if (cmd.size() != 1)
            std::cout << "ERROR this command doesn't take arguments" << std::endl;
        else if (_map.empty())
            std::cout << "ERROR no map specified" << std::endl;
        else {
            std::string pos;
            auto xy = _map.size() / 2 - 1;
            pos.append(std::to_string(xy));
            pos.append(",");
            pos.append(std::to_string(xy));
            PutStone(pos, 1);

            std::cout << "  ";
            for (std::size_t i = 0; i != _map.size(); ++i)
                std::cout << i % 10 << " ";
            std::cout << std::endl;
            for (std::size_t i = 0; i != _map.size(); ++i) {
                std::cout << i % 10 << " ";
                for (std::size_t j = 0; j != _map[i].size(); ++j)
                    if (_map[i][j] == 1)
                        std::cout << RED << _map[i][j] << RES << " ";
                    else if (_map[i][j] == 2)
                        std::cout << GR << _map[i][j] << RES << " ";
                    else
                        std::cout << _map[i][j] << " ";
                std::cout << std::endl;
            }
            
            std::cout << xy << "," << xy << std::endl;
        }
    }

    void Game::Turn(std::vector<std::string> cmd) noexcept
    {
        std::string bestMove = "";

        if (cmd.size() != 2)
            std::cout << "ERROR this command takes a position '[x],[y]' as argument" << std::endl;
        else if (!_isStarted)
            std::cout << "ERROR the game has not started yet" << std::endl;
        else if (!CheckPositions(cmd[1], false))
            return;
        else {
            PutStone(cmd[1], 2); // put the stone of the adversary
            // temp display the map
            bestMove = _glados.PlayBestMove(_map);
            PutStone(bestMove, 1); // puts own stone
            // temp display the map
            std::cout << "  ";
            for (std::size_t i = 0; i != _map.size(); ++i)
                std::cout << i % 10 << " ";
            std::cout << std::endl;
            for (std::size_t i = 0; i != _map.size(); ++i) {
                std::cout << i % 10 << " ";
                for (std::size_t j = 0; j != _map[i].size(); ++j)
                    if (_map[i][j] == 1)
                        std::cout << RED << _map[i][j] << RES << " ";
                    else if (_map[i][j] == 2)
                        std::cout << GR << _map[i][j] << RES << " ";
                    else
                        std::cout << _map[i][j] << " ";
                std::cout << std::endl;
            }
            std::cout << bestMove << std::endl;
        }
    }

    void Game::BoardCommand(std::vector<std::string> cmd) noexcept
    {
        std::string input;
        std::string bestMove = "";

        if (cmd.size() != 1)
            std::cout << "ERROR this command doesn't take arguments" << std::endl;
        else if (_map.empty())
            std::cout << "ERROR the board is not defined" << std::endl;
        else {
            while (1) {
                if (!std::getline(std::cin, input) || CheckDone(input))
                    break;
                else if (!CheckPositions(input, true))
                    continue;
                else
                    PutStone(input, 0);
            }
            if (!_isStarted)
                _isStarted = true;
            bestMove = _glados.PlayBestMove(_map);
            PutStone(bestMove, 1);
            std::cout << bestMove << std::endl;
        }
    }
}