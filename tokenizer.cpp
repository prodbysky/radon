#include "tokenizer.h"

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
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.type << ", value: " << token.value;
    return os;
}

Tokenizer::Tokenizer(std::string src) : src(src) {}
std::vector<Token> Tokenizer::Tokenize() {
    std::vector<Token> tokens;
    std::string::iterator curr = src.begin();
    while (curr != src.end()) {
        if (std::isspace(*curr)) {
            curr++;
            continue;
        }

        if (std::isdigit(*curr)) {
            tokens.push_back(Number(curr));
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
        }
        curr++;
    }

    return tokens;
}

Token Tokenizer::Number(std::string::iterator& curr) {
    std::string buffer;
    buffer.push_back(*curr);
    curr++;
    while (std::isdigit(*curr)) {
        buffer.push_back(*curr);
        curr++;
    }
    return {.type = TokenType::Number, .value = buffer};
}
