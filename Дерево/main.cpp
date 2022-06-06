#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <thread>
#include <list>
#include "TreeMap.h"
#include "BalancedTreeMap.h"
#include "Tree.h"
#include "BalancedTree.h"


using namespace std;
using namespace sf;

vector<int> mas = { rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100,rand() % 200 - 100 };

bool flag = true;
Tree tree(mas);
BalancedTree balancedtree;


void SetDisplay() {
    RenderWindow window(sf::VideoMode(1200, 700), "");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(Color(216, 164, 94));
        if (flag) {
            TreeMap a(tree);
            a.Draw(window);
        }
        else {
            BalancedTreeMap a(balancedtree);
            a.Draw(window);
        }

        window.display();
    }
}

void SetConsole() {
    balancedtree = BalancedTree(tree);
    flag = false;
    string str = "";
    int a;
    char c;
    cout << endl << "��� ������ � ���������� �������� ��������, ������� ������ ���������: " << endl;
    while (true) {
        cout << "1. �������� ������� � ������ ������" << endl;
        cout << "2. ������� ������� �� ������ ������" << endl;
        cout << "3. ����� ������������� ��������" << endl;
        cout << "4. ����� �� ���������" << endl;
        cout << "�������: ";
        cin >> str;

        switch (str[0])
        {
        case '1':
            while (true) {
                cout << "������� ����� ������� : ";
                cin >> str;
                try {
                    a = atoi(str.c_str());
                    balancedtree.Add(atoi(str.c_str()));
                    break;
                }
                catch (...) {

                }
            }
            break;
        case '2':
            while (true) {
                cout << "������� ������� ������� ����� ������� : ";
                cin >> str;
                try {
                    a = atoi(str.c_str());
                    balancedtree.Del(atoi(str.c_str()));
                    break;
                }
                catch (...) {

                }
            }
            break;
        case '3': 
            while (true) {
                cout << "������� ������� ��� ������: ";
                cin >> str;
                try {
                    a = atoi(str.c_str());
                    cout << "������� " << a << " ����������� � ������: " << balancedtree.Search(atoi(str.c_str())) << endl;
                    break;
                }
                catch (...) {
                    cout << "������� �� ����������� � ������" << endl;
                }
            }
            break;
        case '4':
            exit(0);
        default:
            cout << endl << "������� �������� ��� � ������" << endl;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    system("chcp1251");
    system("cls");

    thread a(SetDisplay); 
    thread c(SetConsole);
    a.join(); 
    c.join();

    return 0;
}