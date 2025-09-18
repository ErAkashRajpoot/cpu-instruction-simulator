# CPU Instruction Set Simulator (C++)


## 📌 Project Overview
A **CPU Instruction Set Simulator (ISS)** implemented in **C++** that models a **5-stage pipelined CPU**. It demonstrates instruction execution, hazards, and performance metrics like CPI.


## 🚀 Features
- 5-stage pipeline: IF, ID, EX, MEM, WB
- Instruction set: ADD, SUB, LOAD, STORE, BRANCH
- Pipeline registers & cycle-by-cycle execution
- Performance metrics: Cycles, Instructions, CPI


## 🛠️ Tech Stack
- C++
- g++ compiler (Linux/Windows)
- Makefile

## 📖 Example Output
```
Cycle 1 completed.
Cycle 2 completed.
Cycle 3 completed.
...
Execution Finished!
Total Cycles: 15
Instructions Executed: 10
CPI: 1.5
```


## 🎯 Future Work
- Add hazards & forwarding
- Branch prediction
- Expand instruction set


clean:
rm -f $(TARGET)
```
