#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include<bits/stdc++.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct State {
    int x, y; //包裝座標
    bool operator==(const State& other) const { return x == other.x && y == other.y; }
    //用State比較x,y
};

class Environment {
public:
    int width = 5;
    int height = 5; //5*5的二維陣列
    State agentP;
    //'P': Player
    vector<string> map = {
        ".....",
        ".X.X.",
        "...X.",
        ".XX..",
        "....G" //(4,4) is Goal, 'G': Goal, 'X': Trap, '.': Empty
    };

    Environment() { reset(); }
    State reset() {
        agentP = {0, 0}; //左上角為起點
        return agentP;
    }

    // 0:Up, 1:Right, 2:Down, 3:Left
    struct StepResult { State nextState; double reward; bool done; };

    StepResult step(int action) {
        int nx = agentP.x;
        int ny = agentP.y;

        if (action == 0 && ny > 0) ny--;
        else if (action == 1 && nx < width - 1) nx++;
        else if (action == 2 && ny < height - 1) ny++;
        else if (action == 3 && nx > 0) nx--;

        agentP = {nx, ny};//更新位置
        char cell = map[ny][nx];
        //reward獎勵機制
        if (cell == 'G') return {agentP, 15.0, true};  //到終點+15分
        if (cell == 'X') return {agentP, -10.0, true}; //踩到陷阱-10分
        return {agentP, -1.0, false}; //走1步扣1分
    }

    void display() {//掃描並繪圖
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (x == agentP.x && y == agentP.y) cout << "A ";//找A的位置
                else cout << map[y][x] << " ";//不是A就照原始印
            }
            cout << "\n";
        }
    }
};
#endif
