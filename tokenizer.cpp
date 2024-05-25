#include "tokenizer.h"

#include "result.h"

#include <cctype>
#include <cstdlib>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const TokenType& type) {
    switch (type) {
    case TokenType::Number: {
        os << "TokenType::Number";
        break;
    }
    case TokenType::BinaryOperator: {
        os << "TokenType::BinaryOperator";
        break;
    }
    case TokenType::Symbol: {
        os << "TokenType::Symbol";
        break;
    }
    case TokenType::SemiColon: {
        os << "TokenType::SemiColon";
        break;
    }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.type << ", value: " << token.value;
    return os;
}

Tokenizer::Tokenizer(std::string src) : src(src) {}
Result<std::vector<Token>> Tokenizer::Tokenize() {
    std::vector<Token> tokens;
    std::string::iterator curr = src.begin();
    while (curr != src.end()) {
        if (std::isspace(*curr)) {
            curr++;
            continue;
        }

        if (std::isdigit(*curr)) {
            Result<Token> number = Number(curr);
            if (number.Ok()) {
                tokens.push_back(number.GetValue());
            } else {
                return Result<std::vector<Token>>(Error(number.GetError()));
            }
        }

        if (std::isalpha(*curr)) {
            Result<Token> keyword = Symbol(curr);
            tokens.push_back(keyword.GetValue());
        }

        switch (*curr) {
        case '+': {
            tokens.push_back({.type = TokenType::BinaryOperator, .value = "+"});
            break;
        }
        case '-': {
            tokens.push_back({.type = TokenType::BinaryOperator, .value = "-"});
            break;
        }
        case ';': {
            tokens.push_back(SemiColon().GetValue());
            break;
        }
        }
        curr++;
    }
    return Result<std::vector<Token>>(tokens);
}

Result<Token> Tokenizer::Number(std::string::iterator& curr) {
    std::string buffer;
    buffer.push_back(*curr);
    curr++;
    while (std::isdigit(*curr)) {
        buffer.push_back(*curr);
        curr++;
        if (*curr == ';') {
            return Result<Token>({.type = TokenType::Number, .value = buffer});
        }
        if (!std::isspace(*curr) && !std::isdigit(*curr)) {
            return Result<Token>(Error("Invalid character in number literal"));
        }
    }
    return Result<Token>({.type = TokenType::Number, .value = buffer});
}

Result<Token> Tokenizer::Symbol(std::string::iterator& curr) {
    std::string buffer;
    buffer.push_back(*curr);
    curr++;

    while (std::isalnum(*curr)) {
        buffer.push_back(*curr);
        curr++;
        if (*curr == ';') {
            return Result<Token>({.type = TokenType::Symbol, .value = buffer});
        }
    }
    return Result<Token>({.type = TokenType::Symbol, .value = buffer});
}

Result<Token> Tokenizer::SemiColon() {
    return Result<Token>({.type = TokenType::SemiColon, .value = ";"});
}
