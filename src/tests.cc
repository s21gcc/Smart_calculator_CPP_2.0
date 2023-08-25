#include <gtest/gtest.h>

#include "Model/Model.h"

class ModelCalcTest : public ::testing::Test {
 protected:
  s21::Model calculator_test;
};

TEST_F(ModelCalcTest, SimpleCalc1) {
  calculator_test.UpdateExpression("5+3+2+5+5+1+2+3+4+5+6+7+8+9", 0);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), 65);
}

TEST_F(ModelCalcTest, SimpleCalc2) {
  calculator_test.UpdateExpression("5-3-2-5-5-1-2-3-4-5-6-7-8-9", 0);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), -55);
}

TEST_F(ModelCalcTest, SimpleCalc3) {
  calculator_test.UpdateExpression("5143*1213*24532/1213/1445", 0);
  ASSERT_NEAR(calculator_test.GetResult(), 87313.5474048, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc4) {
  calculator_test.UpdateExpression(
      "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123", 0);
  ASSERT_NEAR(calculator_test.GetResult(), 0.79973842646, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc5) {
  calculator_test.UpdateExpression("5", 0);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), 5);
}

TEST_F(ModelCalcTest, SimpleCalc6) {
  calculator_test.UpdateExpression("2^3^2", 0);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), 512);
}

TEST_F(ModelCalcTest, SimpleCalc7) {
  calculator_test.UpdateExpression("5*x", 6);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), 30);
}

TEST_F(ModelCalcTest, SimpleCalc8) {
  calculator_test.UpdateExpression("2+x/x-x*(xmodx)", 3);
  ASSERT_DOUBLE_EQ(calculator_test.GetResult(), 3);
}

TEST_F(ModelCalcTest, HardCalc1) {
  calculator_test.UpdateExpression(
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
      3);
  ASSERT_NEAR(calculator_test.GetResult(), -30.0721649, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc2) {
  calculator_test.UpdateExpression("cos(2-sin(3+0.26*7+1))", 3);
  ASSERT_NEAR(calculator_test.GetResult(), -0.7681865, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc3) {
  calculator_test.UpdateExpression("10*(-5+log(2+(9/3)))", 3);
  ASSERT_NEAR(calculator_test.GetResult(), -43.0102999, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc4) {
  calculator_test.UpdateExpression("-ln(tan(sqrt(50-1)))", 3);
  ASSERT_NEAR(calculator_test.GetResult(), 0.1375991, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc5) {
  calculator_test.UpdateExpression(
      "acos(-(0+1))+asin(sqrt(81)-8.321)-atan(123mod(5-2)+0.123)", 3);
  ASSERT_NEAR(calculator_test.GetResult(), 3.76560701, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc6) {
  calculator_test.UpdateExpression("sin(sin(sin(sin(sin(90)))))", 3);
  ASSERT_NEAR(calculator_test.GetResult(), 0.6023926, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc7) {
  calculator_test.UpdateExpression("-(3)*(-3.141592-(7*(-(-(-(-7))))))", 3);
  ASSERT_NEAR(calculator_test.GetResult(), 156.424776, 1e-7);
}

TEST_F(ModelCalcTest, ErrorCalc1) {
  EXPECT_THROW(calculator_test.UpdateExpression("", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc2) {
  EXPECT_THROW(calculator_test.UpdateExpression("5+(3", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc3) {
  EXPECT_THROW(calculator_test.UpdateExpression("5)+3", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc4) {
  EXPECT_THROW(calculator_test.UpdateExpression("00", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc5) {
  EXPECT_THROW(calculator_test.UpdateExpression("1+()2", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc6) {
  EXPECT_THROW(calculator_test.UpdateExpression("1+(+-2)", 3),
               std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc7) {
  EXPECT_THROW(calculator_test.UpdateExpression("*", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc8) {
  EXPECT_THROW(calculator_test.UpdateExpression("(^)", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc9) {
  EXPECT_THROW(calculator_test.UpdateExpression(")2+3(", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc10) {
  EXPECT_THROW(calculator_test.UpdateExpression("2..3", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc11) {
  EXPECT_THROW(calculator_test.UpdateExpression("7.1*2.3.2", 3),
               std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc12) {
  EXPECT_THROW(calculator_test.UpdateExpression("5+.2", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc13) {
  EXPECT_THROW(calculator_test.UpdateExpression("asin()", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc14) {
  EXPECT_THROW(calculator_test.UpdateExpression("mod3", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc15) {
  EXPECT_THROW(calculator_test.UpdateExpression("000.2", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc16) {
  EXPECT_THROW(calculator_test.UpdateExpression("cos(*tan(2))", 3),
               std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc17) {
  EXPECT_THROW(calculator_test.UpdateExpression("5x", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc18) {
  EXPECT_THROW(calculator_test.UpdateExpression("xxxx", 3), std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc19) {
  EXPECT_THROW(calculator_test.UpdateExpression("xsin(3)", 3),
               std::logic_error);
}

TEST_F(ModelCalcTest, ErrorCalc20) {
  EXPECT_THROW(calculator_test.UpdateExpression("x.", 3), std::logic_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
