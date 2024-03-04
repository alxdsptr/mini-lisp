//
// Created by alxdsptr on 3/4/2024.
//

#ifndef MINI_LISP_EVAL_ENV_H
#define MINI_LISP_EVAL_ENV_H
#include "./value.h"
#include "./error.h"
#include "builtins.h"
#include <unordered_map>

class EvalEnv {
private:
    std::unordered_map<std::string, ValuePtr> vars;
public:
    EvalEnv(){
        vars["+"] = std::make_shared<BuiltinProcValue>(add);
        vars["print"] = std::make_shared<BuiltinProcValue>(print);
        vars["-"] = std::make_shared<BuiltinProcValue>(minus);
        vars["*"] = std::make_shared<BuiltinProcValue>(mul);
        vars["/"] = std::make_shared<BuiltinProcValue>(divide);
        vars["="] = std::make_shared<BuiltinProcValue>(equal_num);
        vars["<"] = std::make_shared<BuiltinProcValue>(smaller);
        vars[">"] = std::make_shared<BuiltinProcValue>(bigger);
    }
    ValuePtr eval(ValuePtr expr);
};

#endif  // MINI_LISP_EVAL_ENV_H
