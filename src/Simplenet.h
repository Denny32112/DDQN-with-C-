#ifndef SIMPLENET_H
#define SIMPLENET_H

#include <vector>
#include "Environment.h"
using namespace std;

//這模擬神經網路的行為，但內部用Table存值
class SimpleNet {
    //模仿Q: Q-Table: [y][x][action]
    double q_table[5][5][4];

public:
    SimpleNet() {
        //初始化所有Q為0
        for(int y=0; y<5; y++)
            for(int x=0; x<5; x++)
                for(int a=0; a<4; a++)
                    q_table[y][x][a] = 0.0;
    }

    //Forward Pass: 輸入狀態，推出所有動作的Q值
    vector<double> forward(State s) {
        vector<double> q_values;
        for(int a=0; a<4; a++) {
            q_values.push_back(q_table[s.y][s.x][a]);
        }
        return q_values;
    }

    //Backward Pass (Simplified): 直接更新Q值(類似 Gradient Descent)
    void update(State s, int action, double targetQ, double learningRate) {
        double currentQ = q_table[s.y][s.x][action];
        //Q-Learning的更新公式，在Deep Learning裡是loss的反向傳播
        q_table[s.y][s.x][action] = currentQ + learningRate * (targetQ - currentQ);
    }

    //Target Network更新機制:把自己的權重複製給另一個網路net
    void copyFrom(const SimpleNet& other) {
        for(int y=0; y<5; y++)
            for(int x=0; x<5; x++)
                for(int a=0; a<4; a++)
                    q_table[y][x][a] = other.q_table[y][x][a];
    }
};
#endif
