//
// Created by alxdsptr on 3/4/2024.
//

#include "forms.h"
#include "eval_env.h"

const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS{
        {"define", defineForm},
        {"quote", quoteForm},
        {"if", ifForm},
        {"and", andForm},
        {"or", orForm},
        {"lambda", lambdaForm}
};
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    if(args.size() < 3){
        throw LispError("define: too few arguments");
    }
    if(args[1]->isList()){
        std::vector<ValuePtr> v = static_cast<PairValue*>(args[1].get())->toVector();
        std::vector<std::string> params;
        for(int i = 1; i < v.size(); i++){
            if(!v[i]->isSymbol()){
                throw LispError("lambda: second argument must be a list of symbols");
            }
            params.push_back(v[i]->toString());
        }
        std::vector<ValuePtr> body;
        std::copy(args.begin() + 2, args.end(), std::back_inserter(body));
        env.addVar(v[0]->toString(), std::make_shared<LambdaValue>(params, body, env.shared_from_this()));
        return std::make_shared<NilValue>();
    }
    if(!args[1]->isSymbol()){
        throw LispError("define: first argument must be a symbol or a list");
    }
    //v[2]不合法的时候怎么办？
    auto value = env.eval(args[2]);
    env.addVar(args[1]->toString(), value);
    return std::make_shared<NilValue>();
}
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    return args[1];
}
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    if(args.size() != 4){
        throw LispError("if: wrong number of arguments");
    }
    auto pred = env.eval(args[1]);
    if(pred->isBool() and !static_cast<BooleanValue*>(pred.get())->getValue()){
        return env.eval(args[3]);
    }else{
        return env.eval(args[2]);
    }
}
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    ValuePtr pred = std::make_shared<BooleanValue>(true);
    for(int i = 1; i < args.size(); i++){
        pred = env.eval(args[i]);
        if(pred->isBool() and !static_cast<BooleanValue*>(pred.get())->getValue()){
            return std::make_shared<BooleanValue>(false);
        }
    }
    return pred;
}
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    for(int i = 1; i < args.size(); i++){
        auto pred = env.eval(args[i]);
        if(!pred->isBool() or static_cast<BooleanValue*>(pred.get())->getValue()){
            return pred;
        }
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env){
    if(args.size() < 3){
        throw LispError("lambda: too few arguments");
    }else if(!args[1]->isList() and !args[1]->isNil()){
        throw LispError("lambda: second argument must be a list");
    }
    std::vector<ValuePtr> v = static_cast<PairValue*>(args[1].get())->toVector();
    std::vector<std::string> params;
    for(auto &i : v){
        if(!i->isSymbol()){
            throw LispError("lambda: second argument must be a list of symbols");
        }
        params.push_back(i->toString());
    }
    std::vector<ValuePtr> body;
//    for(int i = 2; i < args.size(); i++){
//        body.push_back(args[i]);
//    }
    std::copy(args.begin() + 2, args.end(), std::back_inserter(body));
    return std::make_shared<LambdaValue>(params, body, env.shared_from_this());
}
