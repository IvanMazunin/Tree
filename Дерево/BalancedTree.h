#pragma once
#include <vector>
#include <iostream>
#include <list>
#include "Tree.h"

using namespace std;

template <typename T>
void Sort(vector<T>& mas) {

    for (int i = 0; i < mas.size(); i++) {
        for (int j = 0; j < mas.size() - 1 - i; j++) {
            if (mas[j] > mas[j + 1]) {
                swap(mas[j], mas[j + 1]);
            }
        }
    }
}

class BalancedTree {
private:
    int data;
    BalancedTree* Left = nullptr;
    BalancedTree* Right = nullptr;
    BalancedTree* Up = nullptr;
    int size = 0;

    void CreateBalancedTree(vector<int> mas) {
        this->data = mas[mas.size() / 2];

        if (mas.size() / 2 > 1)
            Left = new BalancedTree(CutVector(mas, 0, mas.size() / 2));
        else
            Left = new BalancedTree(mas[0]);
        Left->Up = this;
        this->size += Left->size;

        if (mas.size() - mas.size() / 2 - 1 > 1) {
            Right = new BalancedTree(CutVector(mas, mas.size() / 2 + 1, mas.size()));
            Right->Up = this;
            this->size += Right->size;
        }
        else if (mas.size() - mas.size() / 2 - 1 == 1) {
            Right = new BalancedTree(mas[mas.size() - 1]);
            Right->Up = this;
            this->size += Right->size;
        }
        this->size++;
    }

    void CreateList(const Tree& tree, list<int>& l) {
        l.push_back(tree.data);

        if (tree.Left != nullptr)
            CreateList(*tree.Left, l);
        if (tree.Right != nullptr)
            CreateList(*tree.Right, l);
    }

    void Move() {
        if (this->Left != nullptr) {
            this->data = this->Left->data;
            this->Left->Move();
        }
        else {
            if (this->Right != nullptr) {
                this->data = this->Right->data;
                this->Right->Move();
            }
            else {
                cout << this->data << endl;
                cout << this->Up << endl;
                if (this == this->Up->Right) {
                    this->Up->Right = nullptr;
                    delete this;
                }
                else if (this == this->Up->Left) {
                    this->Up->Left = nullptr;
                    delete this;
                }
            }
        }
    }
public:
    BalancedTree() {}

    BalancedTree(int data) {
        this->data = data;
    }

    BalancedTree(vector<int> mas) {
        Sort(mas);
        CreateBalancedTree(mas);
    }

    BalancedTree(const BalancedTree& tree) {
        this->data = tree.data;
        this->size = tree.size;

        if (tree.Left != nullptr) {
            this->Left = new BalancedTree(*tree.Left);
            this->Left->Up = this;
        }
        if (tree.Right != nullptr) {
            this->Right = new BalancedTree(*tree.Right);
            this->Right->Up = this;
        }
    }

    BalancedTree(const Tree& tree) {
        list <int> l;
        CreateList(tree, l);

        vector<int> mas = vector<int>(l.size());

        list<int>::iterator i = l.begin();
        for (int j = 0; j < l.size(); j++) {
            mas[j] = *i;
            i++;
        }

        Sort(mas);
        CreateBalancedTree(mas);
    }

    BalancedTree& operator = (const BalancedTree& tree) {
        this->Clear();
        this->data = tree.data;
        this->size = tree.size;

        if (tree.Left != nullptr) {
            this->Left = new BalancedTree(*tree.Left);
            this->Left->Up = this;
        }

        if (tree.Right != nullptr) {
            this->Right = new BalancedTree(*tree.Right);
            this->Right->Up = this;
        }

        return *this;
    }

    int Data() { return data; }
    int Size() { return size; }
    BalancedTree* GetLeft() { return Left; }
    BalancedTree* GetRight() { return Right; }

    void Clear() {
        if (Left != nullptr)
            delete Left;
        if (Right != nullptr)
            delete Right;
    }

    void Print() {
        cout << Up << endl;
        if (Left != nullptr)
            Left->Print();
        if (Right != nullptr)
            Right->Print();
    }

    void Add(int data) {
        if (this->data >= data)
            if (Left != nullptr)
                Left->Add(data);
            else {
                Left = new BalancedTree(data);
                Left->Up = this;
            }
        else
            if (Right != nullptr)
                Right->Add(data);
            else {
                Right = new BalancedTree(data);
                Right->Up = this;
            }
    }

    void Del(int data) {
        if (this->data == data) {
            if (Left == nullptr and Right == nullptr) {
                if (this == this->Up->Left)
                    this->Up->Left = nullptr;
                if (this == this->Up->Right)
                    this->Up->Right = nullptr;
                delete this;
            }
            else {
                Move();
            }
        }
        else {
            if (this->Left != nullptr)
                this->Left->Del(data);
            if (this->Right != nullptr)
                this->Right->Del(data);

        }
    }

    int Search(int data) {
        int repeat = 0;
        if (this->data == data)
            repeat++;

        if (this->Left != nullptr)
            repeat += this->Left->Search(data);
        if (this->Right != nullptr)
            repeat += this->Right->Search(data);
        return repeat;
    }

    ~BalancedTree() {
        this->Clear();
    }
};

