/*
* Copyright 2019 Dustin Ward <dustin.ward@uleth.ca>
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include <gtest/gtest.h>
#include "../include/mathProblem.h"


TEST(testMathProblem, addProblemTest) {
  MathProblem* p1 = new MathProblem(0, '+', 0);
  MathProblem* p2 = new MathProblem(5, '+', 35);
  MathProblem* p3 = new MathProblem(99, '+', 99);

  EXPECT_TRUE(p1->solve(0));
  EXPECT_TRUE(p2->solve(40));
  EXPECT_TRUE(p3->solve(198));
  EXPECT_FALSE(p3->solve(0));

  delete p1;
  delete p2;
  delete p3;
}

TEST(testMathProblem, subProblemTest) {
  MathProblem* p1 = new MathProblem(0, '-', 0);
  MathProblem* p2 = new MathProblem(5, '-', 35);
  MathProblem* p3 = new MathProblem(99, '-', 90);

  EXPECT_TRUE(p1->solve(0));
  EXPECT_TRUE(p2->solve(-30));
  EXPECT_TRUE(p3->solve(9));

  delete p1;
  delete p2;
  delete p3;
}

TEST(testMathProblem, multProblemTest) {
  MathProblem* p1 = new MathProblem(0, '*', 0);
  MathProblem* p2 = new MathProblem(5, '*', 35);
  MathProblem* p3 = new MathProblem(99, '*', 99);

  EXPECT_TRUE(p1->solve(0));
  EXPECT_TRUE(p2->solve(175));
  EXPECT_TRUE(p3->solve(9801));

  delete p1;
  delete p2;
  delete p3;
}

TEST(testMathProblem, randProblemTest) {
  MathProblem* p1 = new MathProblem();

  p1->generate();

  char op = p1->getOperator();

  switch (op) {
  case '+':
    EXPECT_TRUE(p1->solve(p1->getLeft() + p1->getRight()));
    break;
  case '-':
    EXPECT_TRUE(p1->solve(p1->getLeft() - p1->getRight()));
    break;
  case '*':
    EXPECT_TRUE(p1->solve(p1->getLeft() * p1->getRight()));
    break;
  }

  delete p1;
}

TEST(testMathProblem, outputTest) {
  MathProblem* p1 = new MathProblem(2, '+', 2);

  EXPECT_EQ("What is 2+2?", p1->output_Str());

  delete p1;
}
