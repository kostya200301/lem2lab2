#ifndef SEN2LAB2_ALFPOINTER_H
#define SEN2LAB2_ALFPOINTER_H

#include <string>
#include <string.h>
#include <malloc.h>
#include "Sequence.h"
#include "DynamicArray.h"

using namespace std;

int CMPCharStrings(const char * s1, const char * s2) {
    if (strcmp(s1, s2) == 0) {
        return 1;
    }
    return 0;
}

int CMPINTStrings(int s1, int s2) {
    if (s1 == s2) {
        return 1;
    }
    return 0;
}

class AlfPointer {
private:
    int type;
    int k;
    string str;
    Sequence<const char *>* sec;
    Sequence<Sequence<const char *>*>* sequence;
    IMap<const char *, int>* map;
private:
    void Split(string s) {
        sec = new ArraySequence<const char *>();
        std::string delimiter = " ";
        while (memcmp(s.c_str(), delimiter.c_str(), delimiter.size()) == 0) {
            s.erase(0, delimiter.length());
        }
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            char* cstr = (char*) malloc(sizeof(char) * token.size());
            memcpy(cstr, token.c_str(), sizeof(char) * token.size() + 1);
            sec->Append(cstr);
            s.erase(0, pos + delimiter.length());
            while (memcmp(s.c_str(), delimiter.c_str(), delimiter.size()) == 0) {
                s.erase(0, delimiter.length());
            }
        }
        char* cstr = (char*) malloc(sizeof(char) * s.size());
        memcpy(cstr, s.c_str(), sizeof(char) * s.size() + 1);
        sec->Append(cstr);
    }

    void Divide() {
        sequence = new ArraySequence<Sequence<const char *>*>();
        if (type == 1){
            auto s = new ArraySequence<const char *>();
            for (int i = 0; i < sec->GetLength(); i++) {
                if (i == k / 2 or (sequence->GetLength() % 10 == 0 and s->GetLength() == k * 3 / 4) or s->GetLength() % k == 0 && i != 0) {
                    sequence->Append(s);
//                    s->~ArraySequence();
                    s = new ArraySequence<const char *>();
                    cout << "\n";
                }
                const char * cpstr = (char *)malloc(sizeof(sec->Get(i)));
                memcpy(&cpstr, &sec->Get(i), sizeof(sec->Get(i)));
                s->Append(cpstr);
                cout << cpstr << " ";
            }
            if (s->GetLength() != 0) {
                sequence->Append(s);
//                s->~ArraySequence();
            }
            cout << endl;
        }
        else {
            auto s = new ArraySequence<const char *>();
            int dubleK = k / 2;
            for (int i = 0; i < sec->GetLength(); i++) {
                if (dubleK - (int)strlen(sec->Get(i)) >= 0) {
                    dubleK -= (int)strlen(sec->Get(i));
                    s->Append(sec->Get(i));
//                    cout << sec->Get(i) << endl;
                    dubleK--;

                } else {
                    if (sequence->GetLength() % 10 == 0){
                        dubleK = k * 3 / 4;
                    }
                    else {
                        dubleK = k;
                    }
                    sequence->Append(s);
//                    s->~ArraySequence();
                    s = new ArraySequence<const char *>();
                }
            }
            if (s->GetLength() != 0) {
                sequence->Append(s);
//                s->~ArraySequence();
            }

        }
    }

    void MakeMap() {
        map = new IMap<const char *, int>();
        for (int i = 0; i < sequence->GetLength(); i++) {
            for (int j = 0; j < sequence->Get(i)->GetLength(); j++) {
                if (sequence->Get(i)->Get(j)[0] != '\0') {
                    map->SetValueByKey(sequence->Get(i)->Get(j), i + 1, CMPCharStrings, 0, 0, CMPINTStrings);
                }
            }
        }
    }


public:

    AlfPointer(string str, int type, int k) {
        this->type = type;
        this->k = k;
        this->str = str;
        this->Split(str);
        this->Divide();
        this->MakeMap();
    }

    ~AlfPointer() {
        this->str.clear();
        this->sec->~Sequence();
        this->sequence->~Sequence();
        this->map->~IMap();
    }

    AlfPointer (const AlfPointer & alfP)
    {
        this->k = alfP.k;
        this->str = alfP.str;
        this->sequence = alfP.sequence;
        this->sec = alfP.sec;
        this->map = alfP.map;
        this->type = alfP.type;
    }


    void Print() {
        map->Print();
    }

    IMap<const char *, int>* GetMap() {
        return this->map;
    }


};

ostream& operator << (ostream &os, Sequence<const char *>* d) {
    for (int i = 0; i < d->GetLength(); i++) {
        os << d->Get(i) << " ";
    }
    os << endl;
    return os;
}

#endif //SEN2LAB2_ALFPOINTER_H
