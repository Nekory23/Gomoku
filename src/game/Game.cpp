/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Game
*/

#include "Gomoku.hpp"

namespace gomoku {

    const Game::cmd_t Game::_all_cmd[] = { 
        {"END", &gomoku::Game::End},
        {"START", &gomoku::Game::Start},
        {"BEGIN", &gomoku::Game::Begin},
        {"TURN", &gomoku::Game::Turn},
        {"BOARD", &gomoku::Game::BoardCommand},
        {"RESTART", &gomoku::Game::Restart},
        {nullptr, nullptr}
    };

    Game::Game()
    {
        gomoku::IA ia;
        
        _glados = ia;
        _isStarted = false;
        _hasEnded = false;
    }

    void Game::Start() noexcept
    {
        std::string input;
        std::vector<std::string> cmd;

        if (!std::getline(std::cin, input))
            return ;
        if (input.empty())
            std::cout << "UNKNOWN command not found" << std::endl;
        cmd = Split(input, ' ');
        HandleCmd(cmd);
    }

    void Game::HandleCmd(std::vector<std::string> &cmd) noexcept
    {
        auto i = 0;

        for (; _all_cmd[i].cmd != nullptr; ++i)
            if (cmd[0].compare(_all_cmd[i].cmd) == 0) {
                (*this.*_all_cmd[i].func_ptr)(cmd);
                break;
            }
        if (_all_cmd[i].cmd == nullptr)
            std::cout << "UNKNOWN command not found" << std::endl;
    }

    bool Game::CheckPositions(const std::string &positions, const bool &isBoard) noexcept
    {
        std::vector<std::string> pos = Split(positions, ',');

        if (pos.size() != 2 && !isBoard)
            std::cout << "ERROR the position must be in the '[x],[y]' format" << std::endl;
        if (pos.size() != 3 && isBoard)
            std::cout << "ERROR the position must be in the '[x],[y],[field]' format" << std::endl;
        for (std::size_t i = 0; i != pos.size(); ++i)
            for (std::size_t j = 0; j != pos[i].size(); ++j) {
                if (pos[i][j] < '0' || pos[i][j] > '9') {
                    std::cout << "ERROR the position must be in the '[x],[y]' format" << std::endl;
                    return false;
                }
            }
        if (static_cast<std::size_t>(std::atoi(pos[0].c_str())) >= _map.size() || static_cast<std::size_t>(std::atoi(pos[1].c_str())) >= _map.size()) {
            std::cout << "ERROR this position is not valid" << std::endl;
            return false;
        }
        if (isBoard) {
            int player = std::atoi(pos[2].c_str());
            if (player < 1 || player > 2) {
                std::cout << "ERROR the player specified is invalid" << std::endl;
                return false;
            }
        }
        return true;
    }

    void Game::PutStone(const std::string &input, const int &player) noexcept
    {
        std::vector<std::string> data = Split(input, ',');
        int x = std::atoi(data[0].c_str());
        int y = std::atoi(data[1].c_str());
        if (player == 0 && _map[x][y] == 0) {
            _map[x][y] = std::atoi(data[2].c_str());
        }
        else if (player != 0 && _map[x][y] == 0) {
            _map[x][y] = player;
        } else
            std::cout << "ERROR this position is already occupied" << std::endl;
    }

    bool Game::getHasEnded() const noexcept
    {
        return _hasEnded;
    }
}