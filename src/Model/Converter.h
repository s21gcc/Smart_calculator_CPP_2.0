//
// Created by Oznak Banshee on 8/19/23.
//

#ifndef CPP3_SMARTCALC_V2_MODEL_CONVERTER_H
#define CPP3_SMARTCALC_V2_MODEL_CONVERTER_H

#include "Parser.h"

namespace s21 {
class Converter {
 public:
  Converter(const std::vector<Token> &init_tokens);
  const std::vector<Token> &get_vector_of_rpn();

 private:
  void FormingRPN(const std::vector<Token> &init_tokens);
  std::vector<Token> vector_of_rpn_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_MODEL_CONVERTER_H
