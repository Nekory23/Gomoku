/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Gomoku
*/

#include "Gomoku.hpp"

namespace gomoku {
    Gomoku::Gomoku()
    {
        gomoku::Game game;

        _game = game;
    }

    void Gomoku::Play() noexcept
    {
        while (1) {
        _game.Start();
        if (_game.getHasEnded())
            break;
        }
    }
}