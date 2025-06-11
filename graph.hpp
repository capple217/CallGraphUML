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
  Node createNode(std::string id, NodeKind kind, std::string file);             // Want the return to move from function to caller, not create copy
                                                                                
  // For implementation later:
  std::vector<Node*> outgoing;          // What functions use this 
  std::vector<Node*> incoming;          // What functions this goes into (inverse of above)
};

enum class EdgeKind {
  Calls,
  Inherits,
  Uses,
}

struct Edge {
  Node* from;
  Node* to;
  EdgeKind kind;

  // Functions
  Edge createEdge(Node& from, Node& to);
};

class Graph {
public:
  Graph() = default;

  // Might want to change return to bool to get status on if insertion was good
  void insertNode(Node& node);
  void insertEdge(Edge& edge);
  
private:
  std::unordered_map<std::string, std::unique_pointer<Node>> nodes_;
  std::vector<Edge> edges_;
};
