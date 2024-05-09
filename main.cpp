#include <iostream>
#include "Graph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "ui.h"
#include <string>
using namespace std;

int main(){
    int test;
    do{
        cout << "Czy przeprowadzić testy? (1-tak, 0-nie): ";
        cin >> test;
    }while(test!=0 && test!=1);
    if(test){
        //testGraph();
    }else{
        int choice = 1;
        int density = -1;
        int vertices = -1;
        int operation = 1;
        do{
            do{
                cout << "Podaj liczbę wierzchołków: ";
                cin >> vertices;
            }while (vertices <= 0);
            do {
                cout << "Podaj gęstość grafu w procentach (1-100): ";
                cin >> density;
            } while (density <= 0 || density > 100);
            generateGraphData(vertices, density, "test");
            ListGraph lG("list_test.txt");
            MatrixGraph mG("matrix_test.txt");
            do{
                cout << "Wybież operację\n";
                cout << "1 - Algorytm Dijkstry do wszystkich wierzchołków\n";
                cout << "2 - Algorytm Dijkstry do wierzchołka\n";
                cout << "3 - Wypisz graf\n";
                cout << "4 - Wczytaj graf na nowo\n";
                cout << "0 - Zakończ\n";
                cout << "Wybór: ";
                cin >> operation;
                switch (operation){
                    case 1:
                        uiDijkstraAll(mG, lG);
                        break;
                    case 2:
                        uiDijkstraToPoint(mG, lG);
                        break;
                    case 3:
                        uiprintGraph(mG, lG);
                        break;
                    case 4:
                        operation = 0;
                        break;
                    case 0:
                        choice = 0;
                        break;
                default:
                    break;
                }
            }while(operation!=0);
        }while(choice);
    }
    return 0;
}