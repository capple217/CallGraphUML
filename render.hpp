#pragma once

#include <string>
#include <vector>
#include <utility>

using NodeName = std::string;
using rEdge = std::pair<NodeName, NodeName>;

extern std::vector<NodeName> renderNodes;
extern std::vector<rEdge> renderEdges;

void writeDot(const std::string& file);

