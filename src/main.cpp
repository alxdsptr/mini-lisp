#include <iostream>
#include <string>

#include "./tokenizer.h"
#include "./value.h"

int main() {
//    auto* pair = new PairValue(std::make_shared<NumericValue>(1.0), std::make_shared<PairValue>(std::make_shared<NumericValue>(2.0), std::make_shared<PairValue>(std::make_shared<SymbolValue>("a"), std::make_shared<StringValue>("hello"))));
//    std::cout << pair->toString() << std::endl;
    while (true) {
        try {
            std::cout << ">>> " ;
            std::string line;
            std::getline(std::cin, line);
            if (std::cin.eof()) {
                std::exit(0);
            }
            auto tokens = Tokenizer::tokenize(line);
            for (auto& token : tokens) {
                std::cout << *token << std::endl;
            }
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
