//
// Created by alxdsptr on 3/4/2024.
//

#include "value.h"
#include <iomanip>

using namespace std::literals;

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

std::string PairValue::toString() const {
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
std::string Value::toString() const {
    return std::string();
}
