#pragma once

#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileBrowser {
public:
  FileBrowser(fs::path rootDir);
  void goUp();
  void printPath();
  void reset();

  void selectChild();

private:
  std::vector<fs::path> _selected;     // All the current saved files
  fs::path _current;                   // current point in our iteration
  fs::path _root;                      // our starting position. If we encounter issues, we can always return here
  std::vector<fs::path> _children;     // Children of the current pathway. Visited iteratively
}

// Current implementation
// 1. Display current pathway we're on:
//      - Vector gets filled with all the pathways that are led from this one
//      - They get indexed and are shown
// 2. Go into child pathway
//      - Must run (1), aka display pathway and consequently fill vector with indexed paths
//      - we choose what path to choose and set that as the new current
// ONLY when we decide to go into a child pathway OR display current pathway do we fill our vector with the current paths
// Otherwise it stays on to what is was whenever it was last checked
