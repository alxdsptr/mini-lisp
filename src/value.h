//
// Created by alxdsptr on 3/4/2024.
//
#include <memory>
#include <string>

#ifndef MINI_LISP_VALUE_H
#define MINI_LISP_VALUE_H

enum class ValueType {
    BooleanValue,
    NumericValue,
    StringValue,
    NilValue,
    SymbolValue,
    PairValue
};

class Value{
private:
    ValueType type;
protected:
    Value(ValueType type) : type{type} {}
public:
    virtual ~Value() = default;
    ValueType getType() const {
        return type;
    }

};
class BooleanValue : public Value{
private:
    bool value;
public:
    BooleanValue(bool value) : Value(ValueType::BooleanValue), value{value} {}
    bool getValue() const {
        return value;
    }

};
class NumericValue : public Value{
private:
    double value;
public:
    NumericValue(double value) : Value(ValueType::NumericValue), value{value} {}
    double getValue() const {
        return value;
    }
};
class StringValue : public Value{
private:
    std::string value;
public:
    StringValue(std::string value) : Value(ValueType::StringValue), value{value} {}
    std::string getValue() const {
        return value;
    }

};
class NilValue : public Value{
public:
    NilValue() : Value(ValueType::NilValue) {}

};
class SymbolValue : public Value{
private:
    std::string value;
public:
    SymbolValue(std::string value) : Value(ValueType::SymbolValue), value{value} {}
    std::string getValue() const {
        return value;
    }

};
class PairValue : public Value{
private:
    std::shared_ptr<Value> car, cdr;
public:
    PairValue(std::shared_ptr<Value> car, std::shared_ptr<Value> cdr) : Value(ValueType::PairValue), car{car}, cdr{cdr} {}
    std::shared_ptr<Value> getCar() const {
        return car;
    }
    std::shared_ptr<Value> getCdr() const {
        return cdr;
    }

};


#endif  // MINI_LISP_VALUE_H
