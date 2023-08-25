//
// Created by Oznak Banshee on 8/21/23.
//

#ifndef CPP3_SMARTCALC_V2_CONTROLLER_CONTROLLER_H
#define CPP3_SMARTCALC_V2_CONTROLLER_CONTROLLER_H

#include "../Model/Model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model *model) : model_(model){};
  void Calculate(const std::string &math_expr, double x);
  double GetResult();

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_CONTROLLER_CONTROLLER_H
