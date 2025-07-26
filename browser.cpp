#include "browser.hpp"

FileBrowser::FileBrowser(fs::path rootDir) : _root{rootDir}, _current {rootDir} {}

void FileBrowser::goUp() {
  _current = _current.parent_path();
}

void FileBrowser::printPath() {
  if (_current.empty()) {
    std::cout << "This path is empty...\n";
    return;
  }


  if (!fs::exists(_current)) {
    std::cout << "[!] Path does not exist.\n";
    return;
  }
  if (!fs::is_directory(_current)) {
    std::cout << "[!] Not a directory, please go Up (U) or Reset (R) before going down further.\n\n";
    return;
  }

  _children.clear();
  auto idx = 0;

  std::cout << "Current: " << _current << "\n\n";
  for (const auto& entry : fs::directory_iterator{_current}) {
    const auto& path = entry.path();

    if (fs::is_directory(path)) {
      _children.push_back(path);
      std::cout << idx++ << ": [DIR] " << path.filename() << "\n";
    }

    else if (fs::is_regular_file(path)) {
      auto ext = path.extension().string();
      if (ext == ".cpp" || ext == ".hpp" || ext == ".c" || ext == "h") {
        _children.push_back(path);
        std::cout << idx++ << "      " << path.filename() << "\n";
      }
    }
  }

  if (_children.empty()) {
    std::cout << "(No valid source files or folders found in this directory)\n";
  }
}

void FileBrowser::reset() {
  _current = _root;
}

void FileBrowser::selectChild() {
  printPath();

  if (!fs::exists(_current) || !fs::is_directory(_current)) {
    std::cout << "Cannot list children-current is not a directory.\n";
    return;
  }
  std::cout << "Enter the number for the path you wish to follow: ";
  size_t idx;
  std::cin >> idx;

  if (idx < 0 || idx >= _children.size()) {
    std::cout << "This value doesn't exist within range\n";
    return;
  }

  _current = _children[idx];
}
