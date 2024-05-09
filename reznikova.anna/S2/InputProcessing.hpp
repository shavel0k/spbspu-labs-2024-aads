#ifndef INPUTPROCESSING_HPP
#define INPUTPROCESSING_HPP
#include <iostream>
#include <string>
#include "ElementStructs.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace reznikova
{
  void readLine(std::istream & is, Queue< Element > & infix);
  bool ifNoLessImportant(Stack< Element > & stack, Element & element);
  void makePostfix(Queue< Element > & infix, Postfix & postfix);
  long long int calculate(Postfix & postfix);
}

#endif