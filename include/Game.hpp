/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

/* STATIC CONST */
static const int SIZE = 5;

/* INCLUDES */
#include <vector>
#include <iostream>

#include "IA.hpp"

/* CLASS */

namespace gomoku {
    class Game {
        public:
            Game();
            ~Game() = default;

            void Start() noexcept;

            /* GETTER */

            bool getHasEnded() const noexcept;

        protected:
            /* FUNCTION */
            void HandleCmd(std::vector<std::string> &cmd) noexcept;


                /* CMD */
            void Start(std::vector<std::string> cmd) noexcept;
            void End(std::vector<std::string> cmd) noexcept;
            void Begin(std::vector<std::string> cmd) noexcept;
            void Turn(std::vector<std::string> cmd) noexcept;
            void BoardCommand(std::vector<std::string> cmd) noexcept;
            void Restart(std::vector<std::string> cmd) noexcept;

            bool CheckPositions(const std::string &pos, const bool &isBoard) noexcept;
            void PutStone(const std::string &input, const int &player) noexcept;

            /* VARIABLE */
            gomoku::IA _glados;
            Board _map;
            bool _isStarted;
            bool _hasEnded;

            typedef struct cmd_s {
                const char *cmd;
                void (Game::*func_ptr)(std::vector<std::string> cmd);
            } cmd_t;

            static const cmd_t _all_cmd[];

    }; // class Game
} // namespace gomoku

#endif /* !GAME_HPP_ */
