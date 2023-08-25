//
// Created by Oznak Banshee on 8/21/23.
//

#include "Model.h"

namespace s21 {
void Model::UpdateExpression(const std::string &math_expr, double x) {
  parser_ = std::make_unique<Parser>(math_expr, x);
  converter_ = std::make_unique<Converter>(parser_->get_vector_of_tokens());
  calculator_ = std::make_unique<Calculator>(converter_->get_vector_of_rpn());
}

double Model::GetResult() { return calculator_->get_result(); }
}  // namespace s21