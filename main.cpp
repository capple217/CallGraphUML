#include <iostream>
#include <clang-c/Index.h>

auto visit(CXCursor current_cursor, CXCursor parent, CXClientData client_data) {

          auto kind = clang_getCursorKind(current_cursor);

          switch (kind) {
            case CXCursor_FunctionDecl:
            case CXCursor_CXXMethod:
            case CXCursor_Constructor:
            case CXCursor_Destructor:
            case CXCursor_ConversionFunction: {
              auto name = clang_getCursorSpelling(current_cursor);
              std::cout << "Function: " << clang_getCString(name) << "\n";
              clang_disposeString(name);
              break;
              }

            case CXCursor_ClassDecl:
            case CXCursor_StructDecl:
            case CXCursor_ClassTemplate: {
              auto name = clang_getCursorSpelling(current_cursor);
              std::cout << "Class / Struct: " << clang_getCString(name) << "\n";
              clang_disposeString(name);
              break;
              }
            default:
              break;
          }

          return CXChildVisit_Recurse;
}

int main() {

  CXIndex clIndex = clang_createIndex(0, 0);    // Create Index
  CXTranslationUnit unit = clang_parseTranslationUnit(clIndex, "file.cpp", nullptr, 0, nullptr, 0, CXTranslationUnit_None);     // Parse "file.cpp"

  if (unit == nullptr) {
    std::cerr << "Unable to parse translation unit. Quitting.\n";
    return 0;
  }
  
  CXCursor cursor = clang_getTranslationUnitCursor(unit);   // Get a cursor at the root of the tranlation unit 
  clang_visitChildren(cursor, visit, nullptr);
  
}
