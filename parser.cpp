#include "parser.hpp"

#include <clang-c/Index.h>
#include <vector>
#include <string>
#include <iostream>

ClangParser::ClangParser(const std::vector<std::string>& args) : args_{args} {
  index_ = clang_createIndex(0, 0);
  for (auto arg : args) {
    CXTranslationUnit unit = clang_parseTranslationUnit(index_, arg.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None); 

    if (unit == nullptr) {
      std::cerr << "Unable to parser translation unit.\n";
      continue;
    }

    units_.emplace_back(unit);          // Still figuring if to use emplace vs push
  }

}

ClangParser::~ClangParser() {
  // clang_disposeString(name) of remaining stuff; probably index, units, etc
    for (auto& tu : units_)
    clang_disposeTranslationUnit(tu);
  clang_disposeIndex(index_);
}

CXChildVisitResult ClangParser::visitor(CXCursor cursor, CXCursor parent, CXClientData clientData) {
  auto kind = clang_getCursorKind(cursor);

  switch (kind) {
    case CXCursor_FunctionDecl:
    case CXCursor_CXXMethod:
    case CXCursor_Constructor:
    case CXCursor_Destructor:
    case CXCursor_ConversionFunction: {
      auto name = clang_getCursorSpelling(cursor);
      std::cout << "Function: " << clang_getCString(name) << "\n";
      clang_disposeString(name);
      break;
        }

    case CXCursor_ClassDecl:
    case CXCursor_StructDecl:
    case CXCursor_ClassTemplate: {
      auto name = clang_getCursorSpelling(cursor);
      std::cout << "Class / Struct: " << clang_getCString(name) << "\n";
      clang_disposeString(name);
      break;
        }
    
    default:
      break;
    }
          return CXChildVisit_Recurse;
}

void ClangParser::traverse() {
  for (auto unit : units_) {
    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, ClangParser::visitor, nullptr);
  }
}
