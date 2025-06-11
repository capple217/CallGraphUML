#include <iostream>
#include <clang-c/Index.h>

#include "parser.hpp"

int main() {

  std::vector<std::string> args;
  args.push_back("file.cpp");
  args.push_back("file2.cpp");

  ClangParser parser(args);
  parser.traverse();
  parser.print();

  return 0;
}
