#include "tokenizer.h"
#include "types.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string ReadWholeFile(char* name);
void Usage();

i32 main(i32 argc, char* argv[]) {
    if (argc < 2) {
        Usage();
    }
    Tokenizer tokenizer(ReadWholeFile(argv[1]));
    auto tokens = tokenizer.Tokenize();

    if (!tokens.Ok()) {
        std::cerr << tokens.GetError() << std::endl;
        return -1;
    }

    for (const auto& token : tokens.GetValue()) {
        std::cerr << token << std::endl;
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
