#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "graph.hpp"

Node* Graph::insertNode(std::string id, NodeKind kind, std::string file) {
    // Check if already in map
  auto it = nodes_.find(id);  
  if (it != nodes_.end()) return it->second.get();

  auto node = std::make_unique<Node>(std::move(id), kind, std::move(file));
  Node* ptr = node.get();
  nodes_.emplace(ptr->id, std::move(node));
  return ptr;
}

void Graph::addEdge(Node* to, Node* from, EdgeKind kind) {
  edges_.emplace_back(from, to, kind);
  from->outgoing.push_back(to);
  to->incoming.push_back(from);
}

void Graph::printNodes() {
  for (const auto& [key, val] : nodes_) {
    std::cout << "The name of the node is " << key << " (from file: " << val->sourceFile << ")\n";  
  }
}
