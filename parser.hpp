#pragma once

#include <clang-c/Index.h>
#include <vector>
#include <string>

#include "graph.hpp"
#include "render.cpp"

class ClangParser {
public:
  ClangParser(const std::vector<std::string>& args);
  ~ClangParser();     // Since we describe descructor, rule of 5

  void traverse();
  void print();
private:
  CXIndex index_;
  std::vector<CXTranslationUnit> units_;    // Each file we input will have its own unit
  std::vector<std::string> args_;           // Name of all the files we read
  
  Graph graph;

  static CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData clientData);
};
