
#ifndef SEN2LAB2_BARCHART_H
#define SEN2LAB2_BARCHART_H

#include <iostream>
#include <cmath>
#include "Sequence.h"
#include "IMap.h"
#include "graphik.h"
#include "Person.h"

#include <string>
#include <iostream>
#include <sstream>


int CMPFloatPairs(pair<float, float> s1, pair<float, float> s2) {
    if (s1.first == s2.first and s1.second == s2.second) {
        return 1;
    }
    return 0;
}


template <typename T>
class BarChart {
private:
    Sequence<T>* sequence;
    IMap<pair<float, float>, float>* barchart;
    pair<float, float> valueRange;
    float partition;
    float (*GetValue)(T);

public:
    BarChart(Sequence<T>* seq, float minValue, float maxValue, float part, float (*GetValueF)(T)) {
        sequence = seq;
        valueRange = {minValue, maxValue};
        partition = part;
        GetValue = GetValueF;
    }

    ~BarChart() {
        this->barchart->~IMap();
        this->sequence->~Sequence();
    }

    BarChart (const BarChart<T>& list){
        this->sequence = list.sequence;
        this->barchart = list.barchart;
        this->valueRange = list.valueRange;
        this->partition = list.partition;
        this->GetValue = list.GetValue;
    }

    IMap<pair<float, float>, float>* Build() {
        barchart = new IMap<pair<float, float>, float>();
        for (int i = 0; i < sequence->GetLength(); i++) {
            float el = GetValue(sequence->Get(i));
            float downR = (float)floor(el / partition) * partition;
            float upR = (float)ceil(el / partition) * partition;
            if (upR == downR) {upR += partition;}
            pair<float, float> range = {downR, upR};
            barchart->SetValueByKey(range, el, CMPFloatPairs);
        }
        return barchart;
    }

    void DrawGrph() {
        vector<pair<pair<float, float>, int>> vkc = barchart->GetVectorKeyCount();
        vector<pair<float, float>> vec;
        for (int i = 0; i < vkc.size(); i++) {
            vec.push_back({(vkc[i].first.first + vkc[i].first.second) / 2.0, vkc[i].second});
        }
        Draw(vec, "gr", ceil((valueRange.second - valueRange.first) / partition), partition, valueRange);
    }
};

#endif //SEN2LAB2_BARCHART_H
