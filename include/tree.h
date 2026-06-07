// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct PermNode {
  char symbol;
  std::vector<PermNode*> branches;
  size_t totalPaths;
  explicit PermNode(char c) : symbol(c), totalPaths(0) {}
};

class PMTree {
 public:
    explicit PMTree(const std::vector<char>& in);
    ~PMTree();
    PermNode* head() const { return root; }

 private:
    PermNode* root;
    void grow(PermNode* parent, const std::vector<char>& unused);
    void del(PermNode* node);
    size_t countPaths(PermNode* node);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
