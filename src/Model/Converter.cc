//
// Created by Oznak Banshee on 8/19/23.
//
#include "Converter.h"

namespace s21 {

Converter::Converter(const std::vector<Token> &init_tokens) {
  FormingRPN(init_tokens);
}

void Converter::FormingRPN(const std::vector<Token> &init_tokens) {
  std::vector<Token> input_vector = init_tokens;
  std::vector<Token> operation_vector;
  std::string last_token_type;

  while (!input_vector.empty()) {
    if (input_vector.front().type_ == "s21_num") {
      vector_of_rpn_.push_back(input_vector.front());
    } else if (input_vector.front().priority_ == 4 ||
               input_vector.front().type_ == "(") {
      if (last_token_type == "s21_num" || last_token_type == ")")
        throw std::logic_error("INVALID MATH EXPRESSION");
      operation_vector.push_back(input_vector.front());
    } else if (input_vector.front().type_ == ")") {
      if (operation_vector.empty() || last_token_type == "(")
        throw std::logic_error("INVALID BRACKETS");
      while (operation_vector.back().type_ != "(") {
        if (operation_vector.empty())
          throw std::logic_error("INVALID BRACKETS");
        vector_of_rpn_.push_back(operation_vector.back());
        operation_vector.pop_back();
      }
      if (operation_vector.back().type_ == "(") operation_vector.pop_back();
    } else if (operation_vector.empty() ||
               (input_vector.front().priority_ >
                operation_vector.back().priority_)) {
      operation_vector.push_back(input_vector.front());
    } else if (!operation_vector.empty() &&
               (input_vector.front().priority_ <=
                operation_vector.back().priority_)) {
      if (input_vector.front().type_ == "^" &&
          operation_vector.back().type_ == "^") {
        operation_vector.push_back(input_vector.front());
      } else {
        while (!operation_vector.empty() &&
               (input_vector.front().priority_ <=
                operation_vector.back().priority_)) {
          vector_of_rpn_.push_back(operation_vector.back());
          operation_vector.pop_back();
        }
        operation_vector.push_back(input_vector.front());
      }
    }

    last_token_type = input_vector.begin()->type_;
    input_vector.erase(input_vector.begin());
  }

  if (input_vector.empty() && !operation_vector.empty()) {
    while (!operation_vector.empty()) {
      if (operation_vector.back().type_ == "(")
        throw std::logic_error("INVALID BRACKETS");
      vector_of_rpn_.push_back(operation_vector.back());
      operation_vector.pop_back();
    }
  }
}

const std::vector<Token> &Converter::get_vector_of_rpn() {
  return vector_of_rpn_;
}
}  // namespace s21