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

        while (true) {
          browser.printPath();
          std::cout << "[A]dd this item [U]p [D]own [R]eset [C]ancel: ";
          char cmd;
          std::cin >> cmd;
          switch(tolower(cmd)) {
            case 'a': {
              auto p = browser.current();
              if (fs::is_regular_file(p) && 
                  (p.extension() == ".cpp" || p.extension() == ".hpp" || 
                  p.extension() == ".c" || p.extension() == ".h")) {
                files.push_back(p.string());
                std::cout << "Added " << p << "\n";
              }
              else {
                std::cout << "Not a valid .cpp/.hpp/.c/.h file\n";
              }
              goto done_adding;       // May change control flow to allow only one add per command
            }

            case 'u': browser.goUp(); break;
            case 'd': browser.selectChild(); break;
            case 'r': browser.reset(); break;
            case 'c': goto done_adding;
            default: std::cout << "Unkown cmd\n"; break;
          }
        }
        done_adding:
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
