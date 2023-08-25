//
// Created by Oznak Banshee on 8/20/23.
//

#include "Calculator.h"

namespace s21 {
Calculator::Calculator(const std::vector<Token> &polish_notation) {
  result_ = GenerateResult(polish_notation);
}

double Calculator::GenerateResult(const std::vector<Token> &polish_notation) {
  std::vector<Token> input_vector = polish_notation;
  std::stack<Token> calculating_stack;
  double result = 0;
  while (!input_vector.empty()) {
    if (input_vector.front().type_ == "s21_num") {
      calculating_stack.push(input_vector.front());
      input_vector.erase(input_vector.begin());
    } else if (input_vector.front().type_ != "s21_num") {
      double value = 0;
      if (calculating_stack.empty())
        throw std::logic_error("INCORRECT MATH EXPRESSION");
      if (input_vector.front().priority_ == 4) {
        if (input_vector.front().type_ == "cos")
          value = std::cos(calculating_stack.top().data_);
        if (input_vector.front().type_ == "sin")
          value = std::sin(calculating_stack.top().data_);
        if (input_vector.front().type_ == "tan")
          value = std::tan(calculating_stack.top().data_);
        if (input_vector.front().type_ == "acos")
          value = std::acos(calculating_stack.top().data_);
        if (input_vector.front().type_ == "asin")
          value = std::asin(calculating_stack.top().data_);
        if (input_vector.front().type_ == "atan")
          value = std::atan(calculating_stack.top().data_);
        if (input_vector.front().type_ == "sqrt")
          value = std::sqrt(calculating_stack.top().data_);
        if (input_vector.front().type_ == "log")
          value = std::log10(calculating_stack.top().data_);
        if (input_vector.front().type_ == "ln")
          value = std::log(calculating_stack.top().data_);
        calculating_stack.pop();
        input_vector.erase(input_vector.begin());
        calculating_stack.push({value, 0, "s21_num"});
      } else {
        if (calculating_stack.size() < 2)
          throw std::logic_error("INCORRECT MATH EXPRESSION");
        double first = calculating_stack.top().data_;
        calculating_stack.pop();
        double second = calculating_stack.top().data_;
        calculating_stack.pop();

        if (input_vector.front().type_ == "+") value = second + first;
        if (input_vector.front().type_ == "-") value = second - first;
        if (input_vector.front().type_ == "*") value = second * first;
        if (input_vector.front().type_ == "/") value = second / first;
        if (input_vector.front().type_ == "mod") value = fmod(second, first);
        if (input_vector.front().type_ == "^") value = pow(second, first);
        input_vector.erase(input_vector.begin());
        calculating_stack.push({value, 0, "s21_num"});
      }
    }
  }
  if (calculating_stack.empty())
    throw std::logic_error("INCORRECT MATH EXPRESSION");
  if (calculating_stack.size() != 1)
    throw std::logic_error("INCORRECT MATH EXPRESSION");
  result = calculating_stack.top().data_;
  return result;
}

double Calculator::get_result() { return result_; }
}  // namespace s21