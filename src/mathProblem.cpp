/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#include "../include/mathProblem.h"
#include <cstdlib>
#include <random>
#include <string>

MathProblem::MathProblem(int l, char o, int r) : left{l}, op{o}, right{r} {
  switch (o) {
  case '+':
    correctAns = l + r;
    break;
  case '-':
    correctAns = l - r;
    break;
  case '*':
    correctAns = l * r;
    break;
  }
}

void MathProblem::generate() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist99(0, 99);
  std::uniform_int_distribution<std::mt19937::result_type> dist20(0, 20);
  std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 2);
  int tempOp = dist3(rng);

  switch (tempOp) {
  case 0:
    op = '+';
    left = dist99(rng);
    right = dist99(rng);
    correctAns = left + right;
    break;
  case 1:
    op = '-';
    left = dist99(rng);
    right = dist99(rng);
    correctAns = left - right;
    break;
  case 2:
    op = '*';
    left = dist20(rng);
    right = dist20(rng);
    correctAns = left * right;
    break;
  }
}

int MathProblem::getLeft() const {
  return left;
}

int MathProblem::getRight() const {
  return right;
}

char MathProblem::getOperator() const {
  return op;
}

bool MathProblem::solve(int ans) {
  if (ans == correctAns)
    return true;
  return false;
}

std::string MathProblem::output_Str() {
  return ("What is " + std::to_string(getLeft()) + getOperator()
          + std::to_string(getRight()) + "?");
}
