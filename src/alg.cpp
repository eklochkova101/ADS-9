// Copyright 2026 NNTU-CS
#include <algorithm>
#include <vector>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& in) {
  std::vector<char> sorted = in;
  std::sort(sorted.begin(), sorted.end());
  root = new PermNode('\0');
  if (!sorted.empty()) {
    grow(root, sorted);
  }
  countPaths(root);
}
void PMTree::grow(PermNode* parent, const std::vector<char>& unused) {
  for (size_t i = 0; i < unused.size(); ++i) {
    PermNode* child = new PermNode(unused[i]);
    parent->branches.push_back(child);
    std::vector<char> rest;
    rest.reserve(unused.size() - 1);
    for (size_t j = 0; j < unused.size(); ++j) {
      if (j != i) {
        rest.push_back(unused[j]);
      }
    }
    grow(child, rest);
  }
}
size_t PMTree::countPaths(PermNode* nod) {
  if (nod->branches.empty()) {
    nod->totalPaths = 1;
    return 1;
  }
  size_t total = 0;
  for (PermNode* ch : nod->branches) {
    total += countPaths(ch);
  }
  nod->totalPaths = total;
  return total;
}
void PMTree::del(PermNode* nod) {
  if (!nod) return;
  for (PermNode* ch : nod->branches) {
    del(ch);
  }
  delete nod;
}
PMTree::~PMTree() {
  del(root);
}
static void traverse(const PermNode* nod, std::vector<char>& path,
  std::vector<std::vector<char>>& res) {
  if (nod->branches.empty()) {
    if (!path.empty()) {
      res.push_back(path);
    }
    return;
  }
  for (const PermNode* ch : nod->branches) {
    if (ch->symbol != '\0') {
      path.push_back(ch->symbol);
    }
    traverse(ch, path, res);
    if (ch->symbol != '\0') {
      path.pop_back();
    }
  }
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> rresult;
  std::vector<char> path;
  traverse(tree.head(), path, rresult);
  return rresult;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
  if (num < 1) return {};
  auto all = getAllPerms(tree);
  size_t pos = static_cast<size_t>(num - 1);
  if (pos >= all.size()) return {};
  return all[pos];
}
static size_t factorial(int n) {
  size_t f = 1;
  for (int i = 2; i <= n; ++i) f *= i;
  return f;
}
std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1) return {};
  const PermNode* current = tree.head();
  if (current->branches.empty()) return {};
  int depth = 0;
  const PermNode* tmp = current;
  while (!tmp->branches.empty()) {
    tmp = tmp->branches[0];
    ++depth;
  }
  size_t totalPerms = factorial(depth);
  size_t idx = static_cast<size_t>(num - 1);
  if (idx >= totalPerms) return {};
  std::vector<char> permutation;
  int level = depth;
  while (level > 0) {
    size_t blockSize = factorial(level - 1);
    size_t branchIdx = idx / blockSize;
    if (branchIdx >= current->branches.size()) return {};
    current = current->branches[branchIdx];
    permutation.push_back(current->symbol);
    idx %= blockSize;
    --level;
  }
  return permutation;
}
