//
// Created by alxdsptr on 3/4/2024.
//

#include "eval_env.h"

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
            if(v[0]->isSymbol()){
                using namespace std::literals;
                std::string symbol = v[0]->toString();
                if(symbol == "define"s){
                    if(v.size() != 3){
                        throw LispError("define: wrong number of arguments");
                    }
                    if(!v[1]->isSymbol()){
                        throw LispError("define: first argument must be a symbol");
                    }
                    //v[2]不合法的时候怎么办？
                    auto value = eval(v[2]);
                    vars[v[1]->toString()] = value;
                    return std::make_shared<NilValue>();
                }else{
                    if(!vars.contains(symbol)){
                        throw LispError("procedure not found: " + symbol);
                    }
                    auto proc = vars[symbol];
                    if(!proc->isProc()){
                        throw LispError("procedure not found: " + symbol);
                    }
                    std::vector<ValuePtr> args;
                    for(int i = 1; i < v.size(); i++){
                        args.push_back(std::move(eval(v[i])));
                    }
                    auto val = static_cast<BuiltinProcValue*>(proc.get())->apply(args);
                    return val;
                }
            }
        }
    }else if(expr->isSymbol()){
        auto symbol = expr->toString();
        if(vars.contains(symbol)){
            return vars[symbol];
        }else{
            throw LispError("Variable: " + symbol + " not defined.");
        }
    }
    else {
        throw LispError("Unimplemented");
    }
}