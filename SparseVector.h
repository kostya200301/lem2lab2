#ifndef SEN2LAB2_SPARSEVECTOR_H
#define SEN2LAB2_SPARSEVECTOR_H

#include "IMap.h"

int cmpINT(int a, int b) {
    return a == b;
}

template <typename V>
class SparseVector {
private:
    IMap<int, V>* imap;
    size_t size;
public:
    SparseVector(Sequence<V>* sec, int (*isNULL)(V)) {
        this->size = sec->GetLength();
        imap = new IMap<int, V>();
        for (int i = 0; i < sec->GetLength(); i++) {
            if (!isNULL(sec->Get(i))){
                imap->SetValueByKey(i, sec->Get(i), cmpINT);
            }
        }
    }

    ~SparseVector() {
        this->imap->~IMap();
    }

    SparseVector(const SparseVector& sparseVector) {
        this->imap = sparseVector.imap;
        this->size = sparseVector.size;
    }

    V Get(int index) {
        if (imap->GetElementsByKey(index)->GetLength() != 0){
            return imap->GetElementsByKey(index)->Get(0);
        }
        return 0;
    }

    void Set(int index, V object) {
        imap->ReplaceValueByKey(index, object);
    }

    void Print() {
        for (int i = 0; i < this->size; i++) {
            cout << this->Get(i) << " ";
        }
        cout << endl;
        this->imap->Print();
    }


};



#endif //SEN2LAB2_SPARSEVECTOR_H
