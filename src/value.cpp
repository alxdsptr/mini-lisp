//
// Created by alxdsptr on 3/4/2024.
//

#include "value.h"
#include <iomanip>
#include "error.h"
#include "eval_env.h"

using namespace std::literals;

const std::set<ValueType> self_evaluating_types{
        ValueType::BooleanValue,
        ValueType::NumericValue,
        ValueType::StringValue,
        ValueType::BuiltInProcValue
};

std::string Value::toString() const {
    return std::string();
}

std::string BooleanValue::toString() const {
    return "#"s + (value ? "t" : "f");
}

std::string NumericValue::toString() const {
    //if value is integer, display without decimal point
    if (value == static_cast<int>(value)) {
        return std::to_string(static_cast<int>(value));
    } else {
        return std::to_string(value);
    }
}

std::string StringValue::toString() const {
    return "\"" + value + "\"";
}

std::string NilValue::toString() const {
    return "()";
}

std::string SymbolValue::toString() const {
    return value;
}
std::string BuiltinProcValue::toString() const {
    return "#<procedure>";
}

std::string PairValue::toString() const {
    //如果pairvalue里面有null怎么办
    std::string result = "(";
    auto current = this;
    while (current) {
        result += current->car->toString();
        if (current->cdr->getType() == ValueType::PairValue) {
            result += " ";
            current = static_cast<PairValue*>(current->cdr.get());
        } else if (current->cdr->getType() == ValueType::NilValue) {
            break;
        } else {
            result += " . " + current->cdr->toString();
            break;
        }
    }
    result += ")";
    return result;
}
PairValue::PairValue(std::vector<std::shared_ptr<Value>> values) : Value(ValueType::PairValue){
    PairValue* current = this;
    for(auto &val : values){
        if(val == values[0]){
            current->car = val;
        }else{
            current->cdr = std::make_shared<PairValue>();
            current = static_cast<PairValue*>(current->cdr.get());
            current->car = val;
        }
    }
    current->cdr = std::make_shared<NilValue>();
}
std::vector<ValuePtr> PairValue::toVector() const {
    std::vector<ValuePtr> result;
    auto current = this;
    while (current) {
        result.push_back(current->car);
        if (current->cdr->getType() == ValueType::PairValue) {
            current = static_cast<PairValue*>(current->cdr.get());
        } else if (current->cdr->getType() == ValueType::NilValue) {
            break;
        } else {
            result.push_back(current->cdr);
            break;
        }
    }
    return result;
}

std::string LambdaValue::toString() const {
    return "#<procedure>";
}
ValuePtr LambdaValue::apply(const std::vector<ValuePtr>& args) {
    if(args.size() != params.size()){
        throw LispError("wrong number of arguments");
    }
    env = std::make_shared<EvalEnv>(parent);
    for(int i = 0; i < params.size(); i++){
        env->addVar(params[i], args[i]);
    }
    ValuePtr res;
    for(auto &i : body){
        res = env->eval(i);
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Value& value){
    return os << value.toString();
}
