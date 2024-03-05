//
// Created by alxdsptr on 3/4/2024.
//

#include <iostream>
#include "builtins.h"

ValuePtr add(const std::vector<ValuePtr>& args){
    double res = 0;
    for(auto &i : args){
        if(!i->isNum()){
            throw LispError("+: arguments must be numbers");
        }
        res += static_cast<NumericValue*>(i.get())->getValue();
    }
    return std::make_shared<NumericValue>(res);
}
ValuePtr mul(const std::vector<ValuePtr>& args){
    double res = 1;
    for(auto &i : args){
        if(!i->isNum()){
            throw LispError("*: arguments must be numbers");
        }
        res *= static_cast<NumericValue*>(i.get())->getValue();
    }
    return std::make_shared<NumericValue>(res);
}
ValuePtr minus(const std::vector<ValuePtr>& args){
    double res = 0;
    if(args.size() > 2){
        throw LispError("-: wrong number of arguments");
    }else if(args.size() == 2){
        if(!args[0]->isNum() or !args[1]->isNum()){
            throw LispError("-: arguments must be numbers");
        }
        res = static_cast<NumericValue*>(args[0].get())->getValue() - static_cast<NumericValue*>(args[1].get())->getValue();
    }else if(args.size() == 1){
        if(!args[0]->isNum()){
            throw LispError("-: arguments must be numbers");
        }
        res = -static_cast<NumericValue*>(args[0].get())->getValue();
    }
    return std::make_shared<NumericValue>(res);
}
ValuePtr divide(const std::vector<ValuePtr>& args){
    double res = 1;
    if(args.size() > 2 or args.size() == 0){
        throw LispError("/: wrong number of arguments");
    }else if(args.size() == 2){
        if(!args[0]->isNum() or !args[1]->isNum()){
            throw LispError("-: arguments must be numbers");
        }else if(static_cast<NumericValue*>(args[1].get())->getValue() == 0){
            throw LispError("/: divide by zero");
        }
        res = static_cast<NumericValue*>(args[0].get())->getValue() / static_cast<NumericValue*>(args[1].get())->getValue();
    }else{
        if(!args[0]->isNum()){
            throw LispError("-: arguments must be numbers");
        }else if(static_cast<NumericValue*>(args[0].get())->getValue() == 0){
            throw LispError("/: divide by zero");
        }
        res = 1 / static_cast<NumericValue*>(args[0].get())->getValue();
    }
    return std::make_shared<NumericValue>(res);
}

ValuePtr equal_num(const std::vector<ValuePtr>& args){
    if(args.size() != 2){
        throw LispError("=: wrong number of arguments");
    }
    if(!args[0]->isNum() or !args[1]->isNum()){
        throw LispError("=: arguments must be numbers");
    }
    return std::make_shared<BooleanValue>(static_cast<NumericValue*>(args[0].get())->getValue() == static_cast<NumericValue*>(args[1].get())->getValue());
}
ValuePtr smaller(const std::vector<ValuePtr>& args){
    if(args.size() != 2){
        throw LispError("<: wrong number of arguments");
    }
    if(!args[0]->isNum() or !args[1]->isNum()){
        throw LispError("<: arguments must be numbers");
    }
    return std::make_shared<BooleanValue>(static_cast<NumericValue*>(args[0].get())->getValue() < static_cast<NumericValue*>(args[1].get())->getValue());
}
ValuePtr bigger(const std::vector<ValuePtr>& args){
    if(args.size() != 2){
        throw LispError(">: wrong number of arguments");
    }
    if(!args[0]->isNum() or !args[1]->isNum()){
        throw LispError(">: arguments must be numbers");
    }
    return std::make_shared<BooleanValue>(static_cast<NumericValue*>(args[0].get())->getValue() > static_cast<NumericValue*>(args[1].get())->getValue());
}
ValuePtr print(const std::vector<ValuePtr>& args){
    if(args.size() != 1){
        throw LispError("print: too more arguments");
    }
    std::cout << args[0]->toString() << std::endl;
    return std::make_shared<NilValue>();
}

const std::vector<std::pair<std::string, BuiltinFuncType*>> BUILTINS{
    {"+", &add},
    {"-", &minus},
    {"*", &mul},
    {"/", &divide},
    {"print", &print},
    {"=", &equal_num},
    {"<", &smaller},
    {">", &bigger}
};