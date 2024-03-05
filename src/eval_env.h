//
// Created by alxdsptr on 3/4/2024.
//

#ifndef MINI_LISP_EVAL_ENV_H
#define MINI_LISP_EVAL_ENV_H
#include "./value.h"
#include "./error.h"
#include "builtins.h"
#include <unordered_map>

class EvalEnv : public std::enable_shared_from_this<EvalEnv>{
private:
    std::unordered_map<std::string, ValuePtr> vars;
    std::shared_ptr<const EvalEnv> parent;
public:
    EvalEnv(std::shared_ptr<const EvalEnv> parent = nullptr) : parent{std::move(parent)}{
        if(parent == nullptr){
            for(auto const &i : BUILTINS){
                vars[i.first] = std::make_shared<BuiltinProcValue>(i.second);
            }
        }
    }
    void addVar(const std::string& name, ValuePtr value){
        vars[name] = std::move(value);
    }
    ValuePtr lookupBinding(std::string &symbol) const;
    ValuePtr eval(ValuePtr expr);
    void setParent(std::shared_ptr<const EvalEnv> p){
        parent = std::move(p);
    }
};

#endif  // MINI_LISP_EVAL_ENV_H
