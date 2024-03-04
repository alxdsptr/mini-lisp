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

ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& env);
extern const std::unordered_map<std::string, SpecialFormType*> SPECIAL_FORMS;

#endif  // MINI_LISP_FORMS_H
