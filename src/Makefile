# Makefile

# 編譯器設定
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# 目標檔案名稱
TARGET = ddqn_demo

# 原始碼
SRC = DDQNmain.cpp

# 編譯規則
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# 清除規則 (make clean)
clean:
	rm -f $(TARGET)
	rm -f *.o