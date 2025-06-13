#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

enum class NodeKind {
  Class,
  Struct,
  Function,
};

struct Node {
  std::string id;             // full "name" of function, including class relations
  NodeKind kind;
  std::string sourceFile;

  // Functions
  Node(std::string _id, NodeKind _kind, std::string _file) : id(std::move(_id)), kind{_kind}, sourceFile(std::move(_file)) {} 
                                                                                
  // For implementation later:
  std::vector<Node*> outgoing;          // What functions use this 
  std::vector<Node*> incoming;          // What functions this goes into (inverse of above)
};

enum class EdgeKind {
  Calls,
  Inherits,
  Uses,
};

struct Edge {
  Node* from;
  Node* to;
  EdgeKind kind;

  // We make calls to this constructor with specific kinds in mind
  Edge(Node* _from, Node* _to, EdgeKind _kind) : from{_from}, to{_to}, kind(_kind) {} 
};

class Graph {
public:
  Graph() = default;

  // -> We only create a node object when inside graph
  Node* insertNode(std::string id, NodeKind kind, std::string file);
  void addEdge(Node* from, Node* to, EdgeKind kind);
  
  void printNodes();
private:
  std::unordered_map<std::string, std::unique_ptr<Node>> nodes_;
  std::vector<Edge> edges_;
};
