#ifndef SEN2LAB2_UNITTESTS_H
#define SEN2LAB2_UNITTESTS_H


#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include "AlfPointer.h"
#include "Person.h"
#include "BarChart.h"


int isNullInt(int n) {
    if (n == 0) {
        return 1;
    }
    return 0;
}

class UnitTests {
private:
    template<typename T>
    bool EqVectors(Sequence<T>* v1, vector<int> v2) {
        if (v1->GetLength() != v2.size()) {
            return 0;
        }
        for (int i = 0; i < v2.size(); i++) {
            if (v1->Get(i) != v2[i]) {
                return 0;
            }
        }
        return 1;
    }



    void AlfPointerTests() {
        std::string s = " hey hey hey hey hey i am i am hello world  ";
        AlfPointer* ap = new AlfPointer(s, 1, 4);
        auto vA = ap->GetMap()->GetVectorKeyElements();
        assert(EqVectors(vA[0].second, {1, 2}));
        assert(EqVectors(vA[1].second, {2, 3}));
        assert(EqVectors(vA[2].second, {3}));
        assert(EqVectors(vA[3].second, {3}));
        assert(EqVectors(vA[4].second, {4}));
    }

    void BarChartTest() {
        Sequence<Person*>* sec = new ArraySequence<Person*>();
        sec->Append(new Person(Person_ID(), "Alex1", "Ivanov", "Petrov", 25));
        sec->Append(new Person(Person_ID(), "Alex2", "Ivanov", "Petrov", 28));
        sec->Append(new Person(Person_ID(), "Alex3", "Ivanov", "Petrov", 55));
        sec->Append(new Person(Person_ID(), "Alex4", "Ivanov", "Petrov", 77));
        sec->Append(new Person(Person_ID(), "Ale5", "Ivanov", "Petrov", 35));
        sec->Append(new Person(Person_ID(), "Alex6", "Ivanov", "Petrov", 17));
        sec->Append(new Person(Person_ID(), "Alex7", "Ivanov", "Petrov", 50));

        BarChart<Person*>* b = new BarChart<Person*>(sec, 0, 100, 20, GetAge);
        IMap<pair<float, float>, float>* itog = b->Build();
        assert(EqVectors(itog->GetElementsByKey(pair<int, int>(20, 40)), {25, 28, 35}));
        assert(EqVectors(itog->GetElementsByKey(pair<int, int>(40, 60)), {55, 50}));
        assert(EqVectors(itog->GetElementsByKey(pair<int, int>(60, 80)), {77}));
        assert(EqVectors(itog->GetElementsByKey(pair<int, int>(0, 20)), {17}));
    }

    void FreqSeqTest() {
        std::string s = "12311123331";
        FreqSequence* f = new FreqSequence(s, 1, 4);
        auto data = f->GetData();
        assert(data[0].second->Get(0) == 5); //1
        assert(data[1].second->Get(0) == 4); //3
        assert(data[2].second->Get(0) == 2); //12
        assert(data[3].second->Get(0) == 2); //123
        assert(data[4].second->Get(0) == 2); //2
    }

    void SparseVectorTest() {
        Sequence<int>* sec = new ArraySequence<int>();
        sec->Append(1);
        sec->Append(0);
        sec->Append(0);
        sec->Append(0);
        sec->Append(6);
        sec->Append(0);
        sec->Append(0);
        sec->Append(0);
        sec->Append(0);
        sec->Append(8);
        sec->Append(0);
        sec->Append(0);
        sec->Append(0);
        sec->Append(0);
        sec->Append(9);
        sec->Append(0);
        SparseVector<int>* spVector= new SparseVector<int>(sec, isNullInt);
        assert(spVector->Get(4) == 6);
        assert(spVector->Get(9) == 8);
        assert(spVector->Get(14) == 9);
        assert(spVector->Get(5) == 0);
    }

    void SparseMatrixTest() {
        Sequence<Sequence<int>*>* sec = new ArraySequence<Sequence<int>*>();
        Sequence<int>* s1 = new ArraySequence<int>();
        s1->Append(0);
        s1->Append(5);
        s1->Append(0);
        Sequence<int>* s2 = new ArraySequence<int>();
        s2->Append(0);
        s2->Append(0);
        s2->Append(0);
        Sequence<int>* s3 = new ArraySequence<int>();
        s3->Append(0);
        s3->Append(9);
        s3->Append(8);
        sec->Append(s1);
        sec->Append(s2);
        sec->Append(s3);
        SparseMatrix<int>* spMatrix= new SparseMatrix<int>(sec, isNullInt);
        assert(spMatrix->Get(0, 1) == 5);
        assert(spMatrix->Get(2, 1) == 9);
        assert(spMatrix->Get(2, 2) == 8);
        assert(spMatrix->Get(1, 1) == 0);
    }

public:
    UnitTests() {};
    void RUN(){
        AlfPointerTests();
        BarChartTest();
        FreqSeqTest();
        SparseVectorTest();
        SparseMatrixTest();
        cout << "Success!!\n";
    }

};


#endif //SEN2LAB2_UNITTESTS_H
