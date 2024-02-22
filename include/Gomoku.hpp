/*
** EPITECH PROJECT, 2021
** EpitechTools
** File description:
** main
*/

#ifndef GOMOKU_HPP_
#define GOMOKU_HPP_

/* INCLUDES */
#include <string>

#include "Game.hpp"

/* STATIC CONST */
static const int SUCCESS = 0;
static const int FAIL = 1;
static const int ERROR = 84;

#define RES "\e[0;0m"
#define RED "\e[3;1;5;31m"
#define CYAN "\e[1;36m"
#define GR "\e[1;32m"
#define BLUE "\e[1;34m"
#define YE "\e[1;33m"

/* CLASS */

namespace gomoku {
    class Gomoku {
        public:
            Gomoku();
            ~Gomoku() = default;

            void Play() noexcept;

        private:
            gomoku::Game _game;
    }; // class Gomoku
} // namespace gomoku

/* PROTOTYPE */

std::vector<std::string> Split(const std::string &line, char const &sep) noexcept;

#endif /* !GOMOKU_HPP_ */
