#pragma once

#include <clang-c/Index.h>
#include <vector>
#include <string>

class ClangParser {
public:
  ClangParser(const std::vector<std::string>& args);
  ~ClangParser();

  void traverse();
private:
  CXIndex index_;
  std::vector<CXTranslationUnit> units_;    // Each file we input will have its own unit
  std::vector<std::string> args_;           // Name of all the files we read

  static CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData clientData);
};
