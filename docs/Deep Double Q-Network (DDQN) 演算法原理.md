# 🧠 Deep Double Q-Network (DDQN) 演算法原理

## 1. 為什麼需要 DQN？
傳統的 Q-Learning 使用表格 (Q-Table) 來記錄每個狀態的價值。但當迷宮變大（或變成圍棋、像素畫面）時，表格會大到記憶體裝不下。
DQN 的解決方案是：**用一個函數 (神經網路) 來「估計」Q 值，而不是查表。**

## 2. 為什麼需要 "Double" DQN？
傳統 DQN 有一個致命缺點：**過度高估 (Overestimation)**。
因為公式中有 `max Q(s', a')`，神經網路容易對某些動作產生過度樂觀的誤判。

**DDQN 的解法 (Decoupling)：**
我們把「選擇動作」和「評估價值」分開給兩個網路做：
* **Policy Network (Action Selection)**：負責選出哪個動作最好。
* **Target Network (Action Evaluation)**：負責算那個動作到底值幾分。

公式如下：
$$Y_{t}^{DDQN} = R_{t+1} + \gamma Q_{target}(S_{t+1}, \underset{a}{\operatorname{argmax}} Q_{policy}(S_{t+1}, a))$$

## 3. 經驗回放 (Experience Replay)
為了打破時間相關性 (Time Correlation)，我們建立了一個 `ReplayBuffer`。
* Agent 不會學完馬上丟，而是存入 Buffer。
* 訓練時，從 Buffer 中**隨機抽樣 (Random Sample)** 一批資料來學。
* 這就像是「考前總複習」，而不是只讀最後一章。