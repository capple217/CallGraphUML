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
  auto* parser = static_cast<ClangParser*>(clientData); // Our instantiation
                                                        
  // Fill node name
  CXString name = clang_getCursorSpelling(cursor);
  std::string id(clang_getCString(name));
  clang_disposeString(name);

  // Get file name
  CXFile fileHandle;
  unsigned line, col, offset;
  clang_getSpellingLocation(
    clang_getCursorLocation(cursor),
    &fileHandle, &line, &col, &offset);
    CXString fileCX = clang_getFileName(fileHandle);
  std::string file = clang_getCString(fileCX);
  clang_disposeString(fileCX);

  // Might move all insert renderNodes and edges calls here instead of inside switch

  switch (kind) {
    case CXCursor_FunctionDecl:
    case CXCursor_CXXMethod:
    case CXCursor_Constructor:
    case CXCursor_Destructor: {

      Node* fnNode = parser->graph.insertNode(id, NodeKind::Function, file);
      renderNodes.push_back(id);

      parser->callStack.push_back(fnNode);

      clang_visitChildren(cursor, ClangParser::visitor, clientData);    // Manually traverse our function's internals

      parser->callStack.pop_back();

      // Skip Clang's default recursion since we did ours manually
      return CXChildVisit_Continue;
        }

    case CXCursor_ClassDecl:
    case CXCursor_StructDecl:               // Have to eventually seperate this from classes
    case CXCursor_ClassTemplate: {

      parser->graph.insertNode(id, NodeKind::Class, file);
      renderNodes.push_back(id);

      break;
        }
    
    case CXCursor_CallExpr: {
      if (parser->callStack.empty()) break;
      Node* caller = parser->callStack.back();

      CXCursor calleeCursor = clang_getCursorReferenced(cursor);
      CXString calleeName = clang_getCursorSpelling(calleeCursor);
      std::string calleeId(clang_getCString(calleeName));
      clang_disposeString(calleeName);

      // insert callee node and add the edge
      Node* callee = parser->graph.insertNode(calleeId, NodeKind::Function, file);
      parser->graph.addEdge(caller, callee, EdgeKind::Calls);
      renderEdges.emplace_back(caller->id, callee->id);

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
