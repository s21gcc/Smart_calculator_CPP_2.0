//
// Created by Oznak Banshee on 8/17/23.
//

#include "Parser.h"

namespace s21 {
Parser::Parser(const std::string &expression, double x)
    : expression_(expression), x_value_(x) {
  FormateExpression();
  Tokenize();
}

void Parser::FormateExpression() {
  if (expression_.size() > 256) throw std::logic_error("Too big expression");
  auto pos = expression_.find("x");
  while (pos != std::string::npos) {
    expression_.replace(pos, 1, " (" + std::to_string(x_value_) + ") ");
    pos = expression_.find("x", pos + 1);
  }
}

void Parser::Tokenize() {
  std::string current_token;
  std::regex pattern(R"(-?([1-9]\d*|0)(\.\d+)?)");
  for (int i = 0; i < static_cast<int>(expression_.size()); ++i) {
    char s_char = expression_[i];
    if (isspace(s_char)) {
      ProcessingNum(current_token, pattern);
    } else if (isdigit(s_char) || s_char == '.') {
      current_token += s_char;
    } else {
      ProcessingOperation(current_token, pattern, s_char, i);
    }
  }
  ProcessingNum(current_token, pattern);
}

void Parser::ProcessingNum(std::string &current_token,
                           const std::regex &pattern) {
  if (!current_token.empty()) {
    if (!std::regex_match(current_token, pattern))
      throw std::logic_error("Not valid double");
    vector_of_tokens_.push_back({std::stod(current_token), 0, "s21_num"});
    current_token.clear();
  }
}

void Parser::ProcessingOperation(std::string &current_token,
                                 const std::regex &pattern, const char &s_char,
                                 int &i) {
  ProcessingNum(current_token, pattern);
  std::string operator_str(1, s_char);
  while (i + 1 < static_cast<int>(expression_.size()) &&
         map_of_valid_operations_.find(operator_str) ==
             map_of_valid_operations_.end()) {
    ++i;
    operator_str += expression_[i];
  }
  auto it = map_of_valid_operations_.find(operator_str);
  if (it != map_of_valid_operations_.end()) {
    auto type = it->first;
    auto priority = it->second;
    if (type == "+" || type == "-") {
      if (vector_of_tokens_.empty()) {
        vector_of_tokens_.push_back({0.0, 0, "s21_num"});
      } else if (!vector_of_tokens_.empty()) {
        auto last_token = vector_of_tokens_.back();
        if (last_token.type_ == "(")
          vector_of_tokens_.push_back({0.0, 0, "s21_num"});
      }
    }
    vector_of_tokens_.push_back({0.0, priority, type});
  }
  operator_str.clear();
  current_token.clear();
}

const std::vector<Token> &Parser::get_vector_of_tokens() {
  return vector_of_tokens_;
}
}  // namespace s21