/*
* Copyright 2019 Team Electra
* @author Dustin Ward, <dustin.ward@uleth.ca>
* @date 2019-11
*/

#ifndef INCLUDE_MATHPROBLEM_H_
#define INCLUDE_MATHPROBLEM_H_

#include <string>
/**
* A class used to implement random math problems to provide to the user
*/

class MathProblem {
 public:
  /**
  * Default constructor
  */
  MathProblem() {}

  /**
  * Constructor for manual problem creation
  * @param l The value of the left operand
  * @param o The operator to use ('+', '-', '*')
  * @param r The value of the right operand
  */
  MathProblem(int l, char o, int r);

  /**
  * Default destructor
  */
  virtual ~MathProblem() {}

  /**
  * Generate a math problem
  */
  void generate();

  /**
  * Access the value of the left operand
  * @return Value of the left operand as an int
  */
  int getLeft() const;

  /**
  * Access the value of the right operand
  * @return Value of the right operand as an int
  */
  int getRight() const;

  /**
  * Access the operator
  * @return The operator as a char
  */
  char getOperator() const;

  /**
  * @return Question as a string
  */
  std::string output_Str();

  /**
  * Attempt to solve the problem given an answer
  * Returns true on a correct answer, and false on an incorrect answer
  * @param ans The answer given by the user
  * @return A bool value based on if the answer was correct
  */
  bool solve(int ans);

 private:
  int correctAns;

  int left;

  int right;

  char op;
};

#endif  // INCLUDE_MATHPROBLEM_H_
