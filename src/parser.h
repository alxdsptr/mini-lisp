//
// Created by alxdsptr on 3/4/2024.
//
#include <deque>

#include "./value.h"
#include "./token.h"

#ifndef MINI_LISP_PARSER_H
#define MINI_LISP_PARSER_H

class Parser {
private:
    std::deque<TokenPtr> tokens;
public:
    Parser(std::deque<TokenPtr> tokens) : tokens{std::move(tokens)} {}
    ValuePtr parse();
    ValuePtr parseTails();
};

#endif  // MINI_LISP_PARSER_H
