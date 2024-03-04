//
// Created by alxdsptr on 3/4/2024.
//

#include "forms.h"
#include "eval_env.h"

const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
        {"define", defineForm}
};
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    if(args.size() != 3){
        throw LispError("define: wrong number of arguments");
    }
    if(!args[1]->isSymbol()){
        throw LispError("define: first argument must be a symbol");
    }
    //v[2]不合法的时候怎么办？
    auto value = env.eval(args[2]);
    env.addVar(args[1]->toString(), value);
    return std::make_shared<NilValue>();
}