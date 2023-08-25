//
// Created by Oznak Banshee on 8/17/23.
//

#ifndef CPP3_SMARTCALC_V2_MODEL_PARSER_H
#define CPP3_SMARTCALC_V2_MODEL_PARSER_H

#include <cmath>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
struct Token {
  double data_;
  int priority_;
  std::string type_;
};

class Parser {
 public:
  Parser(const std::string &expression, double x);
  const std::vector<Token> &get_vector_of_tokens();

 private:
  std::string expression_;
  double x_value_;
  std::vector<Token> vector_of_tokens_;
  const std::map<std::string, int> map_of_valid_operations_ = {
      {"(", 0},   {")", 0},    {"+", 1},    {"-", 1},    {"*", 2},
      {"/", 2},   {"mod", 2},  {"^", 3},    {"sin", 4},  {"cos", 4},
      {"tan", 4}, {"asin", 4}, {"acos", 4}, {"atan", 4}, {"sqrt", 4},
      {"ln", 4},  {"log", 4},
  };
  void FormateExpression();
  void Tokenize();
  void ProcessingNum(std::string &current_token, const std::regex &pattern);
  void ProcessingOperation(std::string &current_token,
                           const std::regex &pattern, const char &s_char,
                           int &i);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_PARSER_H
