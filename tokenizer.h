#include <iostream>
#include <string>
#include <vector>

enum class TokenType { Number, BinaryOperator };

std::ostream& operator<<(std::ostream& os, const TokenType& type);

struct Token {
    TokenType type;
    std::string value;

    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src);
    std::vector<Token> Tokenize();

private:
    Token Number(std::string::iterator& curr);

private:
    std::string src;
};
