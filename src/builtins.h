//
// Created by alxdsptr on 3/4/2024.
//

#ifndef MINI_LISP_BUILTINS_H
#define MINI_LISP_BUILTINS_H

#include "./value.h"
#include "error.h"

ValuePtr add(const std::vector<ValuePtr>& args);
ValuePtr minus(const std::vector<ValuePtr>& args);
ValuePtr divide(const std::vector<ValuePtr>& args);
ValuePtr mul(const std::vector<ValuePtr>& args);
ValuePtr print(const std::vector<ValuePtr>& args);
ValuePtr equal_num(const std::vector<ValuePtr>& args);
ValuePtr smaller(const std::vector<ValuePtr>& args);
ValuePtr bigger(const std::vector<ValuePtr>& args);

extern const std::vector<std::pair<std::string, BuiltinFuncType*>> BUILTINS;


#endif  // MINI_LISP_BUILTINS_H
