#pragma once

#include "result.h"

#include <iostream>
#include <string>
#include <vector>

enum class TokenType { Number, BinaryOperator, Word, Keyword, SemiColon };

std::ostream& operator<<(std::ostream& os, const TokenType& type);

struct Token {
    TokenType type;
    std::string value;

    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src);
    Result<std::vector<Token>> Tokenize();

private:
    Result<Token> Number(std::string::iterator& curr);
    Result<Token> Word(std::string::iterator& curr);
    Result<Token> Keyword(std::string::iterator& curr);
    Result<Token> SemiColon();

private:
    std::string src;
};
