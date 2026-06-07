// Copyright 2026 NNTU-CS
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

void displaySequence(const std::vector<char>& seq) {
  for (char symbol : seq) std::cout << symbol;
}
int main() {
  std::vector<char> digits = { '1', '2', '3' };
  PMTree permutationTree(digits);
  std::cout << "=== All variants ===\n";
  auto allVariants = getAllPerms(permutationTree);
  int counter = 0;
  for (auto& variant : allVariants) {
    std::cout << ++counter << ": ";
    displaySequence(variant);
    std::cout << '\n';
  }
  std::cout << "\n=== Perm ===\n";
  std::cout << "Perm 1 (meth 1): ";
  auto variant1 = getPerm1(permutationTree, 1);
  displaySequence(variant1);
  std::cout << "\nPerm 2 (meth 2): ";
  auto variant2 = getPerm2(permutationTree, 2);
  displaySequence(variant2);
  std::cout << "\nPerm 3 (meth 1): ";
  auto variant3 = getPerm1(permutationTree, 3);
  displaySequence(variant3);
  std::cout << "\nPerm 4 (meth 2): ";
  auto variant4 = getPerm2(permutationTree, 4);
  displaySequence(variant4);
  std::cout << "\n\n";
  std::cout << "=== Time measure ===\n";
  const std::vector<int> testSizes = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  std::random_device randomDevice;
  std::mt19937 rng(randomDevice());
  std::cout << std::left
    << std::setw(6) << "Size."
    << std::setw(16) << "All"
    << std::setw(16) << "Perm1"
    << std::setw(16) << "Perm2"
    << "\n";
  std::cout << std::string(54, '-') << "\n";

  for (int alphabetSize : testSizes) {
    std::vector<char> alphabet(alphabetSize);
    for (int idx = 0; idx < alphabetSize; ++idx) {
            alphabet[idx] = static_cast<char>('a' + idx);
    }
    PMTree tree(alphabet);
    int maxPermutations = tree.head()->totalPaths;
    std::uniform_int_distribution<> indexDist(1, maxPermutations);
    int randomPermIndex = indexDist(rng);

    auto timePoint1 = std::chrono::high_resolution_clock::now();
    volatile auto completeSet = getAllPerms(tree);
    auto timePoint2 = std::chrono::high_resolution_clock::now();
    double elapsedAll = std::chrono::duration<double, std::micro>(timePoint2 - timePoint1).count();

    timePoint1 = std::chrono::high_resolution_clock::now();
    volatile auto OneResult = getPerm1(tree, randomPermIndex);
    timePoint2 = std::chrono::high_resolution_clock::now();
    double elapsedOne = std::chrono::duration<double, std::micro>(timePoint2 - timePoint1).count();

    timePoint1 = std::chrono::high_resolution_clock::now();
    volatile auto TwoResult = getPerm2(tree, randomPermIndex);
    timePoint2 = std::chrono::high_resolution_clock::now();
    double elapsedTwo = std::chrono::duration<double, std::micro>(timePoint2 - timePoint1).count();
    std::cout << std::left
      << std::setw(6) << alphabetSize
      << std::setw(16) << std::fixed << std::setprecision(2) << elapsedAll
      << std::setw(16) << elapsedOne
      << std::setw(16) << elapsedTwo
      << "\n";
  }
  return 0;
}
