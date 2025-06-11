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

    units_.push_back(unit);          // Still figuring if to use emplace vs push
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
  auto* parser = static_cast<ClangParser*>(clientData);
  CXString name = clang_getCursorSpelling(cursor);
  std::string id(clang_getCString(name));
  clang_disposeString(name);

  // Get file name
  CXFile fileHandle;
  unsigned line, col, offset;
  clang_getSpellingLocation(
    clang_getCursorLocation(cursor),
    &fileHandle, &line, &col, &offset);
  std::string file = clang_getCString(clang_getFileName(fileHandle));

  switch (kind) {
    case CXCursor_FunctionDecl:
    case CXCursor_CXXMethod:
    case CXCursor_Constructor:
    case CXCursor_Destructor:
    case CXCursor_ConversionFunction: {

      parser->graph.insertNode(id, NodeKind::Function, file);

      break;
        }

    case CXCursor_ClassDecl:
    case CXCursor_StructDecl:               // Have to eventually seperate this from classes
    case CXCursor_ClassTemplate: {

      parser->graph.insertNode(id, NodeKind::Class, file);

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
    clang_visitChildren(cursor, ClangParser::visitor, this);
  }
}

void ClangParser::print() {
  graph.printNodes();
}
