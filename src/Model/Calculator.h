//
// Created by Oznak Banshee on 8/20/23.
//

#ifndef CPP3_SMARTCALC_V2_MODEL_CALCULATOR_H
#define CPP3_SMARTCALC_V2_MODEL_CALCULATOR_H
#include "Converter.h"

namespace s21 {
class Calculator {
 public:
  Calculator(const std::vector<Token> &polish_notation);
  double get_result();

 private:
  double result_;
  double GenerateResult(const std::vector<Token> &polish_notation);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_CALCULATOR_H
