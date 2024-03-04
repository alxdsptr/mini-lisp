//
// Created by alxdsptr on 3/4/2024.
//

#include "parser.h"

#include <utility>

#include "error.h"

ValuePtr Parser::parse(){
    for(auto &token :tokens){
        if(token->getType() == TokenType::NUMERIC_LITERAL){
            auto value = static_cast<NumericLiteralToken&>(*token).getValue();
            return std::make_shared<NumericValue>(value);
        }else if(token->getType() == TokenType::BOOLEAN_LITERAL) {
            auto value = static_cast<BooleanLiteralToken &>(*token).getValue();
            return std::make_shared<BooleanValue>(value);
        }else if(token->getType() == TokenType::STRING_LITERAL) {
            auto value = static_cast<StringLiteralToken &>(*token).getValue();
            return std::make_shared<StringValue>(value);
        }else if(token->getType() == TokenType::IDENTIFIER) {
            auto value = static_cast<IdentifierToken &>(*token).getName();
            return std::make_shared<SymbolValue>(value);
        }else{
            throw SyntaxError("not implemented yet");
        }
    }
}