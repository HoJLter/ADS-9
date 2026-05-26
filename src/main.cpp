// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "tree.h"

int main() {
  std::cout << "n,getAll,getPerm1,getPerm2\n";

  std::srand(std::time(NULL));

  for (int n = 2; n <= 10; n++) {
    std::vector<char> a;
    for (int i = 0; i < n; i++) {
      a.push_back('A' + i);
    }

    PMTree tree(a);

    int maxPerm = factor(n);

    unsigned int seed = std::time(NULL);
    int r = rand_r(&seed) % maxPerm + 1;

    auto start = std::chrono::high_resolution_clock::now();
    getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    double tAll =
        std::chrono::duration<double, std::micro>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm1(tree, r);
    end = std::chrono::high_resolution_clock::now();
    double t1 = std::chrono::duration<double, std::micro>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    getPerm2(tree, r);
    end = std::chrono::high_resolution_clock::now();
    double t2 = std::chrono::duration<double, std::micro>(end - start).count();

    std::cout << n << "," << tAll << "," << t1 << "," << t2 << "\n";
  }

  return 0;
}

