#include "browser.hpp"

FileBrowser::FileBrowser(fs::path rootDir) : _root{rootDir} _current {rootDir} {}

void FileBrowser::goUp() {
  _current = _current.parent_path();
}

void FileBrowser::printPath() {
  if (_current.empty()) {
    std::cout << "This path is empty...\n";
    return;
  }

  _children.clear();
  auto idx = 0;
  for (auto& path : fs::directory_iterator{_current}) {
    _children.push_back(path);
    std::cout << idx << ": " << path << "\n";
    idx++;
  }
}

void FileBrowser::reset() {
  _current = _root;
}

void FileBrowser::selectChild() {
  printPath();

  if (_current.empty()) {
    std::cout << "This path is empty...\n";
    return;
  }
  std::cout << "Enter the number for the path you wish to follow: ";
  int idx;
  std::cin >> idx;

  if (idx < 0 || idx >= _children.size()) {
    std::cout << "This value doesn't exist within range\n";
    return;
  }

  _current = _children[idx];
}
