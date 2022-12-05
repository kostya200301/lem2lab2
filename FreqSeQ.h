#ifndef SEN2LAB2_FREQSEQ_H
#define SEN2LAB2_FREQSEQ_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Sequence.h"

using namespace std;


class FreqSequence{
private:
    string str;
    int m;
    int M;
    Sequence<string*>* sec;
    Sequence<string*>* prefSeq;
    IMap<string*, int>* map;
private:
    int countFreq(string& pat, string& txt)
    {
        int M = pat.length();
        int N = txt.length();
        int res = 0;


        for (int i = 0; i <= N - M; i++) {

            int j;
            for (j = 0; j < M; j++)
                if (txt[i + j] != pat[j])
                    break;

            if (j == M) {
                res++;
            }
        }
        return res;
    }

    static int strCMP(string* s1, string* s2) {
        if (s1->length() != s2->length()) {
            return 0;
        }
        for (int i = 0; i < s1->length(); i++) {
            if ((*s1)[i] != (*s2)[i]) {
                return 0;
            }
        }
        return 1;
    }

    static int intCMP(int a, int b) {
        return a == b;
    }

    void CreateMap(int m, int M) {
        for (int i = 0; i < this->str.length(); i++) {
            for (int j = m; j < M; j++) {
                if (i + j < this->str.length()){
                    auto ss = (char*)malloc(j + 1); ss[j] = '\0';
                    string tStr = this->str.substr(i, j);
                    memcpy(ss, tStr.c_str(), j);
                    string* subStr = new string(ss, j); //Get Substr

                    if (!subStr->empty()){
                        this->map->SetValueByKey(subStr, countFreq(*subStr, this->str), strCMP, 1);
                    }
                }
            }
        }
    }



public:
    FreqSequence(string str_, int m, int M) {
        this->str = str_;
        this->m = m;
        this->M = M;
        map = new IMap<string*, int>();
        CreateMap(m, M);
    }

    ~FreqSequence() {
        this->sec->~Sequence();
        this->prefSeq->~Sequence();
        this->map->~IMap();
        this->str.clear();
    }

    FreqSequence(const FreqSequence& map_) {
        this->sec = map_.sec;
        this->prefSeq = map_.prefSeq;
        this->map = map_.map;
        this->str = map_.str;
        this->m = map_.m;
        this->M = map_.M;
    }

    void Print(int m=-1, int M=-1){
        if (map != NULL) {
            map->~IMap();
            map = new IMap<string*, int>();
        }
        if (m == -1 and M == -1) {
            CreateMap(this->m, this->M);
        }
        else {
            CreateMap(m, M);
        }
        map->Print();
    }

    void PrintTop(int n) {

        auto vec = this->map->GetVectorKeyElements();

        if (n >= vec.size()){
            return;
        }
        std::sort(vec.begin(), vec.end(), cmp);
        for (auto el : vec) {
            n--;
            cout << '(' << *(el.first) << ", " << el.second->Get(0) << ')' << endl;
            if (n <= 0) {
                return;
            }
        }
    }

    vector<pair<string*, Sequence<int>*>> GetData() {
        auto vec = this->map->GetVectorKeyElements();
        std::sort(vec.begin(), vec.end(), cmp);
        return vec;
    }




private:
    static bool cmp(pair<string*, Sequence<int>*>& p1, pair<string*, Sequence<int>*>& p2){
        return p1.second->Get(0) > p2.second->Get(0);
    }

};



ostream& operator<<(ostream &os, string*& d) {
    return os << *d;
}


#endif //SEN2LAB2_FREQSEQ_H
