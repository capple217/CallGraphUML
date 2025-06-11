#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "graph.hpp"

Node Node::createNode(std::string id, NodeKind kind, std::string file) {

  Node node;
  node.id = id;
  node.kind = kind;
  node.file = file;

  return node;
}

Edge Edge::createEdge(Node& from, Node& to) {

  Edge edge;
  edge.from = from;
  edge.to = to;
  
  return edge;
}

void Graph::insertNode(Node& node) {
  auto ptr = std::make_unique<Node>(&node);
  nodes_

    // Check if already in map


    // insert
}
