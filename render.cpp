#include <set>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using NodeName = std::string;
using Edge = std::pair<NodeName, NodeName>;

std::vector<Edge> renderEdges;            // {callername, calleename};
std::vector<NodeName> renderNodes;        // all unique functions/classes/etc

void writeDot(const std::string file) {
  std::ofstream out(file);
  out << "digraph CallGraph {\n";
  out << "  rankdir=LR;             // left -> right layout (subject to change)\n";
  out << "  node [shape=box];       // Can change shape to ellipse, box, etc \n\n";

  // 1. Declare all nodees (option if every nde appreas in an edge)
  for (auto& n : nodes) {
    out << "  \"" << n << "\";\n";
  }
  out << "\n";

  // emit all edges
  for (auto& e : edges) {
    out << "  \"" << e.first << "\""
        << " -> "
        << "\"" << e.second << "\""
        << ";\n";
  }

  out << "}\n";
}
