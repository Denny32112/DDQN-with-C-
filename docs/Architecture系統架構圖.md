# 🏗️ System Architecture

本專案採用模組化設計，將 AI 的大腦 (Agent)、記憶 (Buffer) 與環境 (Environment) 分離。

## Class Diagram (類別關係圖)

## 1.Interaction: Agent 觀察 Environment 的 State。

## 2.Decision: Agent 透過 policyNet 決定 Action。

## 3.Storage: 結果存入 ReplayBuffer。

## 4.Learning: Agent 從 Buffer 取樣，更新 policyNet，並定期同步給 targetNet。

```mermaid
classDiagram
    class DDQNAgent {
        +SimpleNet policyNet
        +SimpleNet targetNet
        +ReplayBuffer memory
        +train()
        +act()
    }
    
    class ReplayBuffer {
        -deque<Experience> buffer
        +push()
        +sample()
    }

    class SimpleNet {
        -vector weights
        +forward()
        +update()
        +copyFrom()
    }

    class Environment {
        -vector map
        +step()
        +reset()
    }

    DDQNAgent *-- SimpleNet : contains (2)
    DDQNAgent *-- ReplayBuffer : contains
    DDQNAgent ..> Environment : interacts with