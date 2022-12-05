#ifndef SEN2LAB2_SPARSEMATRIX_H
#define SEN2LAB2_SPARSEMATRIX_H

#include "IMap.h"

int cmpIntPair(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first and a.second == b.second) {
        return 1;
    }
    return 0;
}

template <typename V>
class SparseMatrix {
private:
    IMap<pair<int, int>, V>* imap;
    int n;
    int m;
public:
    SparseMatrix(Sequence<Sequence<V>*>* sec, int (*isNULL)(V)) {
        this->n = sec->GetLength();
        this->m = sec->Get(0)->GetLength();
        imap = new IMap<pair<int, int>, V>();
        for (int i = 0; i < sec->GetLength(); i++) {
            for (int j = 0; j < sec->Get(i)->GetLength(); j++) {
                if (!isNULL(sec->Get(i)->Get(j))){
                    imap->SetValueByKey(make_pair(i, j), sec->Get(i)->Get(j), cmpIntPair);
                }
            }

        }
    }

    ~SparseMatrix() {
        this->imap->~IMap();
    }

    SparseMatrix(const SparseMatrix& sparseMatrix) {
        this->imap = sparseMatrix.imap;
        this->m = sparseMatrix.m;
        this->n = sparseMatrix.n;
    }

    V Get(int i, int j) {
        if (imap->GetElementsByKey(make_pair(i, j))->GetLength() != 0){
            return imap->GetElementsByKey(make_pair(i, j))->Get(0);
        }
        return 0;
    }

    void Set(int i, int j, V object) {
        imap->ReplaceValueByKey(make_pair(i, j), object);
    }

    void Print() {

        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                cout << Get(i, j) << " ";
            }
            cout << "\n";
        }

        this->imap->Print();
    }
};

#endif //SEN2LAB2_SPARSEMATRIX_H
