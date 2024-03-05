//
// Created by alxdsptr on 3/4/2024.
//

#include "eval_env.h"
#include "forms.h"
ValuePtr EvalEnv::lookupBinding(std::string &symbol) const{
    if(vars.contains(symbol)){
        return vars.find(symbol)->second;
    }else if(parent){
        return parent->lookupBinding(symbol);
    }else{
        throw LispError("Variable: " + symbol + " not defined.");
    }
}

ValuePtr EvalEnv::eval(ValuePtr expr) {
    if(expr->isSelfEvaluating()) {
        return expr;
    }else if(expr->isNil()) {
        throw LispError("Evaluating nil is prohibited.");
    }else if(expr->isList()){
        auto v = static_cast<PairValue*>(expr.get())->toVector();
        if(v.empty()){
            throw LispError("Empty list is prohibited.");
        }else{
            if(v[0]->isSymbol() or v[0]->isList()){
                ValuePtr proc;
                if(v[0]->isSymbol()){
                    std::string symbol = v[0]->toString();
                    if(SPECIAL_FORMS.contains(symbol)){
                        return SPECIAL_FORMS.find(symbol)->second(v, *this);
                    }
                    proc = lookupBinding(symbol);
                }else{
                    proc = eval(v[0]);
                }
                if(!proc->isProc() and !proc->isLambda()){
                    throw LispError(v[0]->toString() + ": not a procedure");
                }
                std::vector<ValuePtr> args;
                for(int i = 1; i < v.size(); i++){
                    args.push_back(std::move(eval(v[i])));
                }
                ValuePtr val;
                if(proc->isProc()){
                    val = static_cast<BuiltinProcValue*>(proc.get())->apply(args);
                }else{
                    val = static_cast<LambdaValue*>(proc.get())->apply(args);
                }
                return val;
            }else{
               throw LispError(v[0]->toString() + ": not a procedure");
            }
        }
    }else if(expr->isSymbol()){
        auto symbol = expr->toString();
        auto val = lookupBinding(symbol);
        return val;
    }
    else {
        throw LispError("Unimplemented");
    }
}