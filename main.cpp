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

  writeDot("callgraph.dot");
  int result = system("dot -Tpng callgraph.dot -o callgraph.png");

  if (result != 0) {
    std::cerr << "Failed to generate PNG from DOT.\n";
    return 1;
  }

  std::cout << "callgraph.png generated successfully.\n";
  return 0;
}
