#ifndef REPLAYBUFFER_H
#define REPLAYBUFFER_H

#include <vector>
#include <deque>
#include <algorithm>
#include <random>
#include "Environment.h"
using namespace std;

struct Experience {
    State state;//紀錄當下在哪個格子的狀態
    int action;//做的動作0,1,2,3
    double reward;//獎勵
    State nextState;
    bool done;//是否踩到陷阱或終點
};

class ReplayBuffer {
    deque<Experience> buffer;//新的進來舊的丟掉，刪除舊資料最方便
    size_t capacity;

public://記憶回放機制
    ReplayBuffer(size_t size) : capacity(size) {}

    void push(Experience ex) {
        if (buffer.size() >= capacity) {
            buffer.pop_front(); //移除最舊的
        }
        buffer.push_back(ex);//寫入最新的經驗
    }

    //隨機抽取 batchSize 個樣本
    vector<Experience> sample(int batchSize) {
        vector<Experience> batch;

        vector<Experience> tempBuffer(buffer.begin(), buffer.end());//複製目前的記憶

        // 簡單的隨機洗牌
        random_device rd;
        minstd_rand g(rd());//一般的rand()機率不夠公平範圍也太小
        shuffle(tempBuffer.begin(), tempBuffer.end(), g);//洗牌把所有順序打亂，否則容易overfitting，也能學到新的規則


        for (size_t i = 0; i < (size_t)batchSize && i < tempBuffer.size(); ++i) {
            batch.push_back(tempBuffer[i]);
        }
        return batch;
    }

    int size() { return buffer.size(); }
};
#endif
