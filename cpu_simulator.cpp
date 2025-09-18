#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

struct Instruction {
    string opcode;
    int rd, rs1, rs2, imm;
};

struct IF_ID {
    Instruction instr;
    bool valid = false;
};

struct ID_EX {
    Instruction instr;
    int rs1Val, rs2Val;
    bool valid = false;
};

struct EX_MEM {
    Instruction instr;
    int aluResult, rs2Val;
    bool valid = false;
};

struct MEM_WB {
    Instruction instr;
    int result;
    bool valid = false;
};

class CPU {
public:
    int PC = 0;
    vector<int> regs;
    vector<int> memory;
    vector<Instruction> program;

    IF_ID if_id;
    ID_EX id_ex;
    EX_MEM ex_mem;
    MEM_WB mem_wb;

    int cycle = 0;
    int executedInstr = 0;
    int stalls = 0;

    CPU(int regCount, int memSize) {
        regs.resize(regCount, 0);
        memory.resize(memSize, 0);
    }

    void loadProgram(vector<Instruction> instrs) {
        program = instrs;
    }

    void step() {
        cycle++;

        if (mem_wb.valid) {
            if (mem_wb.instr.opcode == "ADD" || mem_wb.instr.opcode == "SUB" || mem_wb.instr.opcode == "LOAD") {
                regs[mem_wb.instr.rd] = mem_wb.result;
            }
            executedInstr++;
        }

        mem_wb = {};
        if (ex_mem.valid) {
            mem_wb.instr = ex_mem.instr;
            mem_wb.valid = true;
            if (ex_mem.instr.opcode == "LOAD") {
                mem_wb.result = memory[ex_mem.aluResult];
            } else if (ex_mem.instr.opcode == "STORE") {
                memory[ex_mem.aluResult] = ex_mem.rs2Val;
                mem_wb.valid = false;
            } else {
                mem_wb.result = ex_mem.aluResult;
            }
        }

        ex_mem = {};
        if (id_ex.valid) {
            ex_mem.instr = id_ex.instr;
            ex_mem.valid = true;
            if (id_ex.instr.opcode == "ADD") {
                ex_mem.aluResult = id_ex.rs1Val + id_ex.rs2Val;
            } else if (id_ex.instr.opcode == "SUB") {
                ex_mem.aluResult = id_ex.rs1Val - id_ex.rs2Val;
            } else if (id_ex.instr.opcode == "LOAD" || id_ex.instr.opcode == "STORE") {
                ex_mem.aluResult = id_ex.rs1Val + id_ex.instr.imm;
                ex_mem.rs2Val = id_ex.rs2Val;
            } else if (id_ex.instr.opcode == "BRANCH") {
                if (id_ex.rs1Val == id_ex.rs2Val) {
                    PC += id_ex.instr.imm;
                }
            }
        }

        id_ex = {};
        if (if_id.valid) {
            id_ex.instr = if_id.instr;
            id_ex.valid = true;
            id_ex.rs1Val = regs[if_id.instr.rs1];
            id_ex.rs2Val = regs[if_id.instr.rs2];
        }

        if_id = {};
        if (PC < program.size()) {
            if_id.instr = program[PC];
            if_id.valid = true;
            PC++;
        }
    }

    bool isDone() {
        return PC >= program.size() && !if_id.valid && !id_ex.valid && !ex_mem.valid && !mem_wb.valid;
    }

void run() {
    int maxCycles = 1000; // safety cap
    while (!isDone() && cycle < maxCycles) {
        step();
        printState();
    }
    printStats();
}


    void printState() {
        cout << "Cycle " << cycle << " completed.\n";
    }

    void printStats() {
        cout << "\nExecution Finished!\n";
        cout << "Total Cycles: " << cycle << "\n";
        cout << "Instructions Executed: " << executedInstr << "\n";
        cout << "CPI: " << (double)cycle / executedInstr << "\n";
    }
};

int main() {
    CPU cpu(16, 256);

vector<Instruction> prog = {
    {"ADD", 1, 0, 0, 0},    // R1 = 0 + 0
    {"ADD", 2, 1, 0, 0},    // R2 = R1 + 0
    {"SUB", 3, 2, 1, 0},    // R3 = R2 - R1
    {"LOAD", 4, 0, 0, 10},  // R4 = MEM[10]
    {"STORE", 4, 0, 4, 20}  // MEM[20] = R4
};



    cpu.loadProgram(prog);
    cpu.run();
}
