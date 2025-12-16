import pandas as pd
import matplotlib.pyplot as plt

# 1. 讀取 CSV
df = pd.read_csv('training_log.csv')

# 2. 設定畫布大小
plt.figure(figsize=(10, 6))

# 3. 畫出原始數據 (比較淡的顏色，顯示波動)
plt.plot(df['Episode'], df['TotalReward'], label='Raw Reward', color='lightblue', alpha=0.5)

# 4. 畫出移動平均線 (趨勢線，最重要的部分)
# window=50 代表計算前 50 回合的平均，讓線變平滑
df['Rolling_Reward'] = df['TotalReward'].rolling(window=50).mean()
plt.plot(df['Episode'], df['Rolling_Reward'], label='Average Reward (Trend)', color='red', linewidth=2)

# 5. 加上標題與標籤
plt.title('DDQN Training Performance', fontsize=16)
plt.xlabel('Episodes', fontsize=12)
plt.ylabel('Total Reward', fontsize=12)
plt.legend() # 顯示圖例
plt.grid(True, linestyle='--', alpha=0.7) # 加上網格

# 6. 存檔與顯示
plt.savefig('images/training_result.png') # 自動存到 images 資料夾
print("圖表已儲存為 images/training_result.png")
plt.show() # 跳出視窗給你看