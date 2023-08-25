//
// Created by Oznak Banshee on 8/21/23.
//

#include "Controller.h"

namespace s21 {
void Controller::Calculate(const std::string &math_expr, double x) {
  model_->UpdateExpression(math_expr, x);
}

double Controller::GetResult() { return model_->GetResult(); }
}  // namespace s21