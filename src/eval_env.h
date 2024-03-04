//
// Created by alxdsptr on 3/4/2024.
//

#ifndef MINI_LISP_EVAL_ENV_H
#define MINI_LISP_EVAL_ENV_H
#include "./value.h"
#include "./error.h"
#include <unordered_map>

class EvalEnv {
private:
    std::unordered_map<std::string, Value::ValuePtr> vars;
public:
    ValuePtr eval(ValuePtr expr);
};

#endif  // MINI_LISP_EVAL_ENV_H
