#include <fstream>

#include "render.hpp"

std::vector<rEdge> renderEdges;            // {callername, calleename};
std::vector<NodeName> renderNodes;        // all unique functions/classes/etc

void writeDot(const std::string& file) {
  std::ofstream out(file);
  out << "digraph CallGraph {\n";
  out << "  rankdir=LR;             // left -> right layout (subject to change)\n";
  out << "  node [shape=box];       // Can change shape to ellipse, box, etc \n\n";

  // 1. Declare all nodees (option if every node appreas in an edge)
  for (auto& n : renderNodes) {
    out << "  \"" << n << "\";\n";
  }
  out << "\n";

  // emit all edges
  for (auto& e : renderEdges) {
    out << "  \"" << e.first << "\""
        << " -> "
        << "\"" << e.second << "\""
        << ";\n";
  }

  out << "}\n";
}
