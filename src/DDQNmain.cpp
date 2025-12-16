#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "Environment.h"
#include "Agent.h"
using namespace std;

int main() {
    srand(time(0));
    Environment env;
    DDQNAgent agent;
    ofstream logFile("training_log.csv");
    // 欄位：回合, 該回合總步數, 該回合總分, 目前的探索率
    logFile << "Episode,Steps,TotalReward,Epsilon\n";

    int episodes = 500;
    int maxSteps = 50;
    int step = 0;
    for (int e = 0; e < episodes; ++e) {
        State state = env.reset();
        int totalReward = 0;

        // ★ 關鍵修改：判斷是否為「展示回合」(前20次 或 後20次)
        bool isDemoEpisode = (e < 20 || e >= episodes - 20);

        for (step = 0; step < maxSteps; ++step) {
            // 1. 選擇動作
            int action = agent.act(state);

            // 2. 執行動作
            auto result = env.step(action);

            // 3. 存入記憶體
            agent.memory.push({state, action, result.reward, result.nextState, result.done});

            // 4. 訓練 Agent
            agent.train(32);

            state = result.nextState;
            totalReward += result.reward;

            // ★ 畫面顯示邏輯：只有「展示回合」才畫圖，節省時間
            if (isDemoEpisode) {
                system("cls"); // Windows 用 cls, Linux/Mac 用 clear

                cout << "=== " << (e < 20 ? "Training Start (Dumb)" : "Training End (Smart)") << " ===\n";
                cout << "Episode: " << e << " | Step: " << step << " | Reward: " << totalReward << "\n";

                env.display(); // 畫出迷宮

                // 暫停一下才看得到動畫 (Windows: Sleep(100), Mac/Linux: this_thread::sleep_for...)
                // 這裡使用 C++ 標準寫法
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            if (result.done) break;
        }

        // 定期更新 Target Network
        if (e % 10 == 0) agent.updateTargetNetwork();

        // ★ CSV 紀錄邏輯：
        // 建議紀錄「每一回合」的結果，這樣 Excel 畫出來的線才是連續的
        logFile << e << "," << step << "," << totalReward << "," << agent.epsilon << "\n";

        // 在終端機印出簡短進度 (非展示回合時顯示)
        if (!isDemoEpisode) {
            // 使用 \r 讓文字在同一行刷新，不會洗版
            cout << "Training... Episode: " << e << " | Reward: " << totalReward << " | Epsilon: " << agent.epsilon << "      \r";
        }
    }

    logFile.close();
    cout << "\n\nDone! Check training_log.csv for details.\n";

    return 0;
}
