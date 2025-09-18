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


## ▶️ How to Run
```bash
git clone https://github.com/<your-username>/cpu-instruction-simulator.git
cd cpu-instruction-simulator
make
make run
```


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


## 📄 Makefile
```makefile
CXX = g++
CXXFLAGS = -Wall -O2
TARGET = cpu_sim
SRC = cpu_simulator.cpp


all: $(TARGET)


$(TARGET): $(SRC)
$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)


run: $(TARGET)
./$(TARGET)


clean:
rm -f $(TARGET)
```