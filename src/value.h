//
// Created by alxdsptr on 3/4/2024.
//
#include <memory>
#include <string>
#include <vector>

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
    using ValuePtr = std::shared_ptr<Value>;
private:
    ValueType type;
protected:
    Value(ValueType type) : type{type} {}
public:
    virtual ~Value() = default;
    ValueType getType() const {
        return type;
    }

    virtual std::string toString() const;

};
class BooleanValue : public Value{
private:
    bool value;
public:
    BooleanValue(bool value) : Value(ValueType::BooleanValue), value{value} {}
    bool getValue() const {
        return value;
    }
    std::string toString() const override;

};
class NumericValue : public Value{
private:
    double value;
public:
    NumericValue(double value) : Value(ValueType::NumericValue), value{value} {}
    double getValue() const {
        return value;
    }
    std::string toString() const override;
};
class StringValue : public Value{
private:
    std::string value;
public:
    StringValue(std::string value) : Value(ValueType::StringValue), value{value} {}
    std::string getValue() const {
        return value;
    }
    std::string toString() const override;

};
class NilValue : public Value{
public:
    NilValue() : Value(ValueType::NilValue) {}
    std::string toString() const override;

};
class SymbolValue : public Value{
private:
    std::string value;
public:
    SymbolValue(std::string value) : Value(ValueType::SymbolValue), value{value} {}
    std::string getValue() const {
        return value;
    }
    std::string toString() const override;

};
class PairValue : public Value{
private:
    std::shared_ptr<Value> car, cdr;
public:
    PairValue() : Value(ValueType::PairValue) {};
    PairValue(std::shared_ptr<Value> car, std::shared_ptr<Value> cdr) : Value(ValueType::PairValue), car{std::move(car)}, cdr{std::move(cdr)} {}
    PairValue(std::vector<std::shared_ptr<Value>>);
    std::shared_ptr<Value> getCar() const {
        return car;
    }
    std::shared_ptr<Value> getCdr() const {
        return cdr;
    }
    std::string toString() const override;

};

std::ostream& operator<<(std::ostream& os, const Value& value);
using ValuePtr = std::shared_ptr<Value>;

#endif  // MINI_LISP_VALUE_H
