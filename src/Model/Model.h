//
// Created by Oznak Banshee on 8/21/23.
//

#ifndef CPP3_SMARTCALC_V2_MODEL_MODEL_H
#define CPP3_SMARTCALC_V2_MODEL_MODEL_H
#include "Calculator.h"

namespace s21 {
class Model {
 public:
  Model() : parser_(nullptr), converter_(nullptr), calculator_(nullptr){};
  void UpdateExpression(const std::string &math_expr, double x);
  double GetResult();

 private:
  std::unique_ptr<Parser> parser_;
  std::unique_ptr<Converter> converter_;
  std::unique_ptr<Calculator> calculator_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_MODEL_H
