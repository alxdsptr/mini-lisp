#include <iostream>
#include <string>

#include "./tokenizer.h"
#include "./value.h"
#include "./parser.h"

int main() {
    /*
    auto* pair = new PairValue(std::make_shared<NumericValue>(1.0), std::make_shared<PairValue>(std::make_shared<NumericValue>(2.0), std::make_shared<PairValue>(std::make_shared<SymbolValue>("a"), std::make_shared<StringValue>("hello"))));
    std::cout << pair->toString() << std::endl;
    ValuePtr a = std::make_shared<NumericValue>(42);
    ValuePtr b = std::make_shared<BooleanValue>(false);
    ValuePtr c = std::make_shared<SymbolValue>("eq?");
    ValuePtr d = std::make_shared<StringValue>("Hello");
    ValuePtr e = std::make_shared<NilValue>();
    ValuePtr f = std::make_shared<PairValue>(
        c,
        std::make_shared<PairValue>(
            a,
            std::make_shared<PairValue>(d, e)
                )
    );
std::cout << a->toString() << '\n'
          << b->toString() << '\n'
          << c->toString() << '\n'
          << d->toString() << '\n'
          << e->toString() << '\n'
          << f->toString() << std::endl;
          */
    while (true) {
        try {
            std::cout << ">>> " ;
            std::string line;
            std::getline(std::cin, line);
            if (std::cin.eof()) {
                std::exit(0);
            }
            auto tokens = Tokenizer::tokenize(line);
            auto parser = Parser(tokens);
            auto value = parser.parse();
            std::cout << *value << std::endl;
//            for (auto& token : tokens) {
//                std::cout << *token << std::endl;
//            }
        } catch (std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
