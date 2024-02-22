/*
** EPITECH PROJECT, 2022
** gomoku
** File description:
** Tools
*/

#include <sstream>

#include "Gomoku.hpp"

std::vector<std::string> Split(const std::string &line, char const &sep) noexcept
{
    std::vector<std::string> res;
    std::stringstream strStr(line);
    std::string str;

    while (std::getline(strStr, str, sep))
        res.push_back(str);
    return res;
}