// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct Node {
    char data;
    std::vector<Node*> children;
};

class PMTree {
private:
    Node* root;
    int permLen;

    Node* makeNode(char data) {
        Node* node = new Node;
        node->data = data;
        return node;
    }

    void buildTree(Node* localRoot, std::vector<char> in) {
        for (int i = 0; i < in.size(); i++) {
            Node* newChild = makeNode(in[i]);
            localRoot->children.push_back(newChild);

            std::vector<char> next = in;
            next.erase(next.begin() + i);
            buildTree(newChild, next);
        }
    }


public:
    PMTree(std::vector<char> in): permLen(in.size()) {
        root = makeNode('.');
        buildTree(root, in);
    };

    int getPermLen() {
        return permLen;
    }

    Node* getRoot() {
        return root;
    }
};

void getAllPermsI(Node* localRoot, std::vector<char>* curPerm, std::vector<std::vector<char>>* allPerms) {
    curPerm->push_back(localRoot->data);
    if (localRoot->children.empty()) {
        allPerms->push_back(*curPerm);
    }
    for (auto& child : localRoot->children) {
        getAllPermsI(child, curPerm, allPerms);
    }
    curPerm->pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree tree) {
    std::vector<char> curPerm;
    std::vector<std::vector<char>> allPerms;

    for (auto& child : tree.getRoot()->children) {
        getAllPermsI(child, &curPerm, &allPerms);
    }

    return allPerms;
}

bool getPerm1I(Node* localRoot, std::vector<char>* curPerm, int* counter, int num) {
    curPerm->push_back(localRoot->data);

    if (localRoot->children.empty()) {
        if ((*counter) == num) {
            return true;
        }

        (*counter)++;
    }

    for (auto& child : localRoot->children) {
        if (getPerm1I(child, curPerm, counter, num)) {
            return true;
        }
    }

    curPerm->pop_back();
    return false;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<char> curPerm;
    int counter = 1;

    for (auto& child : tree.getRoot()->children) {
        if (getPerm1I(child, &curPerm, &counter, num)) {
            return curPerm;
        }
    }
}

int calcDepth(Node* root) {
    int counter = 0;
    while (root && !root->children.empty()) {
        root = root->children[0];
        counter++;
    }
    return counter;
}

int factor(int x) {
    int res = 1;
    for (int i = 1; i <= x; i++) {
        res *= i;
    }
    return res;
}

void getPerm2I(Node* localRoot, int i, std::vector<char>* curPerm) {
    curPerm->push_back(localRoot->data);

    int n = localRoot->children.size();
    if (n == 0) return;

    int fact = factor(n - 1);

    int subtreeNum = i / fact;
    int newNumber = i - (fact * subtreeNum);

    getPerm2I(localRoot->children[subtreeNum], newNumber, curPerm);
}

// i-((n-1)! * (i/(n-1)!))
std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> curPerm;

    getPerm2I(tree.getRoot(), num - 1, &curPerm);

    // удалил корень
    auto it = curPerm.begin();
    curPerm.erase(it);
    return curPerm;
}
#endif  // INCLUDE_TREE_H_
