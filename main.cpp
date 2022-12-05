#include <iostream>
#include <cmath>
#include "Sequence.h"
#include "IMap.h"
#include "graphik.h"
#include "SparseVector.h"
#include "SparseMatrix.h"
#include "AlfPointer.h"
#include "Person.h"
#include "FreqSeQ.h"
#include "BarChart.h"
#include "UnitTests.h"

#include <string>
#include <iostream>
#include <sstream>







int main() {

    srand(time(NULL));


    cout << "1 - AlfPointer\n";
    cout << "2 - FreqSequence\n";
    cout << "3 - BarChart\n";
    cout << "4 - SparseVector\n";
    cout << "5 - SparseMatrix\n";
    cout << "6 - Tests\n";
    cout << "7 - Exit\n";

    int action;
    cin >> action;
    if (action == 1) {
        cout << "Enter string:\n";
        std::string s;
        std::getline(std::cin, s); // del \n
        std::getline(std::cin, s);
        cout << "Enter type (1 - size in words/ 2 - in symbols) and COUNT elements in page:\n";
        int m, M;
        cin >> m >> M;
        AlfPointer* ap = new AlfPointer(s, m, M);
        ap->Print();
        ap->~AlfPointer();
    }
    else if (action == 2) {
        cout << "Enter string:\n";
        std::string s;
        std::getline(std::cin, s); // del \n
        std::getline(std::cin, s);
        cout << "Enter min and max size of subString:\n";
        int m, M;
        cin >> m >> M;
        FreqSequence* f = new FreqSequence(s, m, M);
//        f->Print(m, M);
        f->PrintTop(5);
    }
    else if (action == 3) {
        cout << "Enter count Person to generate\n";
        int k; cin >> k;
        Sequence<Person*>* sec = new ArraySequence<Person*>();
        for (int i = 0; i < k; i++) {
            sec->Append(GenPersonLink());
        }

        cout << "enter interval\n";
        float I;
        cin >> I;

        BarChart<Person*>* b = new BarChart<Person*>(sec, 0, 100, I, GetAge);
        IMap<pair<float, float>, float>* itog = b->Build();

        itog->Print();
        b->DrawGrph();
    } else if (action == 4) {
        cout << "Enter count elements to generate\n";
        int k; cin >> k;
        Sequence<int>* sec = new ArraySequence<int>();
        for (int i = 0; i < k; i++) {
            int num = rand() % 10;
            if (num <= 2) {
                sec->Append(rand() % 1000);
            }
            else {
                sec->Append(0);
            }
        }
        SparseVector<int>* spVector= new SparseVector<int>(sec, isNullInt);
        spVector->Print();

    } else if (action == 5) {
        cout << "Enter size n * m to generate matrix\n";
        int n, m; cin >> n >> m;
        Sequence<Sequence<int>*>* sec = new ArraySequence<Sequence<int>*>();
        for (int i = 0; i < n; i++) {
            auto s = new ArraySequence<int>();
            for (int j = 0; j < m; j++) {
                int num = rand() % 10;
                if (num <= 1) {
                    s->Append(rand() % 10);
                }
                else {
                    s->Append(0);
                }
            }
            sec->Append(s);
        }
        SparseMatrix<int>* spMatrix= new SparseMatrix<int>(sec, isNullInt);
        spMatrix->Print();

    } else if (action == 6) {
        UnitTests* test = new UnitTests();
        test->RUN();
    } else {
        exit(0);
    }

    return 0;
}



