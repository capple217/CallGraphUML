#include <iostream>
#include <clang-c/Index.h>
#include <vector>
#include <string>

#include "browser.hpp"
#include "parser.hpp"

bool renderGraph(const std::vector<std::string>& files) {
  ClangParser parser(files);
  parser.traverse();
  parser.print();

  writeDot("callgraph.dot");
  if (system("dot -Tpng callgraph.dot -o callgraph.png") != 0) {
    std::cerr << "Failed to generate PNG from DOT.\n";
    return false;
  }
#if defined(__APPLE__)
  system("open callgraph.png");
#elif defined(_WIN32)
  system("start callgraph.png");
#else
  system("xdg-open callgraph.png");
#endif
  std::cout << "callgraph.png generated and opened successfully.\n";
  return true;
}

int main() {
  std::vector<std::string> files;
  fs::path rootDir = fs::current_path();

  while (true) {
    std::cout << "\n=== CallGraphUML Menu ===\n"
              << "1) Add source file\n"
              << "2) Render graph\n"
              << "0) Exit\n"
              << "Choose an option: ";

    int choice;
    if (!(std::cin >> choice)) break;  // EOF or invalid input

    switch (choice) {
      case 1: {
        FileBrowser browser(rootDir);
        //std::cout << "Enter path to .cpp/.hpp file: ";
        
        // Need to implement browsing here

        std::string path;
        std::cin >> path;
        size_t op1 = path.find(".hpp");
        size_t op2 = path.find(".cpp");
        if (op1 == std::string::npos && op2 == std::string::npos) {
          std::cout << "File doesn't end with '.cpp' or '.hpp'\n";
          break;
        }
        
        files.push_back(path);
        std::cout << "-> Added: " << path << "\n";
        break;
      }

      case 2: {
        if (files.empty()) {
          std::cout << "No files to render—please add at least one source file.\n";
        } else {
          if (!renderGraph(files)) return 1;
        }
        break;
      }

      case 0:
        std::cout << "Goodbye!\n";
        return 0;

      default:
        std::cout << "Invalid choice, try again.\n";
        break;
    }
  }

  return 0;
}
