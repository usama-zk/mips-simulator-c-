#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

const int t_reg = 32;

class MIPS {
public:
    int Register[t_reg];
    unordered_map<int, int> memory;

    MIPS() {
        for (int i = 0; i < t_reg; i++) {
            Register[i] = i * 10; // Assign Values to register 0,10,20,30
        }

        for (int i = 0; i < 100; i++) {
            memory[i] = i * 2;
        }
    }

    void simulate(vector<string> program) {
        for (const string& line : program) {
            vector<string> instruction = split(line);
            try {
                execuation(instruction);
            }
            catch (const runtime_error& e) {
                throw; // Rethrow the exception to be caught by the caller
            }
        }
    }

    int getRegister(const string& reg) {
        if (reg[0] != '$') {
            throw runtime_error("Invalid register");
        }
        else {
            int regNum = stoi(reg.substr(1));
            if (regNum >= t_reg || regNum < 0) {
                throw runtime_error("Register out of range");
            }
            else {
                return regNum;
            }
        }
    }

    void execuation(vector<string>& instruction) {
        if (instruction.empty()) {
            throw runtime_error("Empty Instruction");
        }
        const string& opcode = instruction[0];
        if (opcode == "add") {
            if (instruction.size() != 4) {
                throw runtime_error("Invalid add instruction format");
            }
            int rd = getRegister(instruction[1]);
            int rs = getRegister(instruction[2]);
            int rt = getRegister(instruction[3]);
            Register[rd] = Register[rs] + Register[rt];
        }
        else if (opcode == "sub") {
            if (instruction.size() != 4) {
                throw runtime_error("Invalid sub instruction format");
            }
            int rd = getRegister(instruction[1]);
            int rs = getRegister(instruction[2]);
            int rt = getRegister(instruction[3]);
            Register[rd] = Register[rs] - Register[rt];
        }
        else if (opcode == "lw") {
            if (instruction.size() != 3) {
                throw runtime_error("Invalid lw instruction format");
            }
            int rt = getRegister(instruction[1]);
            string offset_base = instruction[2];

            regex rgx(R"((\d+)\(\$(\d+)\))");
            smatch match;
            if (regex_search(offset_base, match, rgx)) {
                int offset = stoi(match[1]);
                int rs = stoi(match[2]);
                int address = Register[rs] + offset;
                if (memory.count(address)) {
                    Register[rt] = memory[address];
                }
                else {
                    Register[rt] = 9999; // a default value for memory if address is out of range
                }
            }
            else {
                throw runtime_error("Invalid lw instruction format");
            }
        }
        else if (opcode == "sw") {
            if (instruction.size() != 3) {
                throw runtime_error("Invalid sw instruction format");
            }
            int rt = getRegister(instruction[1]);
            string offset_base = instruction[2];

            regex rgx(R"((\d+)\(\$(\d+)\))");
            smatch match;
            if (regex_search(offset_base, match, rgx)) {
                int offset = stoi(match[1]);
                int rs = stoi(match[2]);
                int address = Register[rs] + offset;
                memory[address] = Register[rt];
            }
            else {
                throw runtime_error("Invalid sw instruction format");
            }
        }
        else {
            throw runtime_error("Unknown instruction: " + opcode);
        }
    }

    vector<string> split(const string& str) {
        vector<string> result;
        istringstream iss(str);
        for (string s; iss >> s;)
            result.push_back(s);
        return result;
    }
};