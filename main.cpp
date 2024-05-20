#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u64 = uint64_t;

enum class TokenType { Number, BinaryOperator };

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

struct Token {
    TokenType type;
    std::string value;

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
        os << token.type << ", value: " << token.value;
        return os;
    }
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src) : src(src) {}
    std::vector<Token> Tokenize() {
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
                tokens.push_back(
                    {.type = TokenType::BinaryOperator, .value = "+"});
                break;
            }
            case '-': {
                tokens.push_back(
                    {.type = TokenType::BinaryOperator, .value = "-"});
                break;
            }
            }
            curr++;
        }

        return tokens;
    }

private:
    Token Number(std::string::iterator& curr) {
        std::string buffer;
        buffer.push_back(*curr);
        curr++;
        while (std::isdigit(*curr)) {
            buffer.push_back(*curr);
            curr++;
        }
        return {.type = TokenType::Number, .value = buffer};
    }

private:
    std::string src;
};

std::string ReadWholeFile(char* name);
void Usage();

i32 main(i32 argc, char* argv[]) {
    if (argc < 2) {
        Usage();
    }
    Tokenizer tokenizer(ReadWholeFile(argv[1]));
    auto tokens = tokenizer.Tokenize();

    for (const auto& token : tokens) {
        std::cerr << token << '\n';
    }
}

void Usage() {
    std::cerr << "Usage: \n";
    std::cerr << "\t./radon <file-to-run>.rd\n";
    std::exit(1);
}

std::string ReadWholeFile(char* name) {
    std::stringstream ss;
    std::ifstream src(name);
    ss << src.rdbuf();
    return ss.str();
}
