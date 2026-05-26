// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "tree.h"

int main() {
  cout << "n,getAll,getPerm1,getPerm2\n";

  srand(time(NULL));

  for (int n = 2; n <= 10; n++) {
    vector<char> a;
    for (int i = 0; i < n; i++) {
      a.push_back('A' + i);
    }

    PMTree tree(a);

    int maxPerm = factor(n);
    int r = rand() % maxPerm + 1;

    auto start = high_resolution_clock::now();
    getAllPerms(tree);
    auto end = high_resolution_clock::now();
    double tAll = duration<double, micro>(end - start).count();

    start = high_resolution_clock::now();
    getPerm1(tree, r);
    end = high_resolution_clock::now();
    double t1 = duration<double, micro>(end - start).count();

    start = high_resolution_clock::now();
    getPerm2(tree, r);
    end = high_resolution_clock::now();
    double t2 = duration<double, micro>(end - start).count();

    cout << n << "," << tAll << "," << t1 << "," << t2 << "\n";
  }

  return 0;
}

