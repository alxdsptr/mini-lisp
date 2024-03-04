//
// Created by alxdsptr on 3/4/2024.
//

#ifndef MINI_LISP_FORMS_H
#define MINI_LISP_FORMS_H

#include "value.h"
//#include "eval_env.h"
#include <unordered_map>
class EvalEnv;

using SpecialFormType = ValuePtr (const std::vector<ValuePtr>&, EvalEnv&);

extern const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS;
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr quoteForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr ifForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr andForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr orForm(const std::vector<ValuePtr>& args, EvalEnv& env);
ValuePtr lambdaForm(const std::vector<ValuePtr>& args, EvalEnv& env);


#endif  // MINI_LISP_FORMS_H
