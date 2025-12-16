#ifndef AGENT_H
#define AGENT_H

#include "SimpleNet.h"
#include "ReplayBuffer.h"
#include <cstdlib>
#include <algorithm>
using namespace std;

class DDQNAgent {
public://兩個網路是修正學習的重點
    SimpleNet policyNet; //持續更新
    SimpleNet targetNet; //久久更新一次
    ReplayBuffer memory;

    double epsilon = 1.0;//探索率
    double epsilonMin = 0.1;//最小保有0.1的探索率
    double epsilonDecay = 0.995;
    double gamma = 0.9;       //折扣因子
    double learningRate = 0.1;

    DDQNAgent() : memory(1000) {
        targetNet.copyFrom(policyNet); // 一開始先同步
    }

    int act(State s) {
        // Epsilon-Greedy 策略
        if ((double)rand() / RAND_MAX < epsilon) {
            return rand() % 4; // 隨機探索
        } else {
            vector<double> q = policyNet.forward(s);
            return distance(q.begin(), max_element(q.begin(), q.end()));
        }
    }

    void train(int batchSize) {
        if (memory.size() < batchSize) return;

        vector<Experience> batch = memory.sample(batchSize);

        for (auto& exp : batch) {
            double targetQ = exp.reward;

            if (!exp.done) {
                // === DDQN 核心演算法 ===
                // 1. 用 PolicyNet 決定下一動作 (argmax)
                vector<double> p_q = policyNet.forward(exp.nextState);
                int bestAction = distance(p_q.begin(), max_element(p_q.begin(), p_q.end()));

                // 2. 用 TargetNet 計算該動作的價值
                vector<double> t_q = targetNet.forward(exp.nextState);
                double nextQ = t_q[bestAction];

                // 3. 貝爾曼方程式
                targetQ += gamma * nextQ;
            }

            // 更新 PolicyNet
            policyNet.update(exp.state, exp.action, targetQ, learningRate);
        }

        // 降低探索率
        if (epsilon > epsilonMin) epsilon *= epsilonDecay;
    }

    void updateTargetNetwork() {
        targetNet.copyFrom(policyNet);
    }
};
#endif
