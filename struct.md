
- core
  - Director
    - 用于解释执行脚本逻辑
  - Environment
    - 用于存放游戏状态。**所有**和存档有关的代码都要放到这
  - Parser
    - 用于解析脚本，**Parser应该被设计成无状态的**（因为游戏的状态都应该由Environment管理）
