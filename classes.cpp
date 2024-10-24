#include <bits/stdc++.h>
using namespace std;

class Register{
    string reg[16];
public:
    Register(){
        for(int i=0 ; i < 16;i++){
            reg[i] = "00";
        }
    }
    void displayR(){
        for(int i=0 ; i < 16;i++){
            cout << reg[i] << "\n";
        }
    }
};

class Memory{
    string mem[256];
public:
    Memory(){
        for(int i=0 ; i < 256;i++){
            mem[i] = "00";
        }
    }

    void readfile(string filename){
        ifstream input(filename);
        while (!input.is_open()) {
            cout << "Error in list file name, please enter it again: ";
            cin >> filename;
            input.open(filename);
        }
        string first, second, third;
        int index = 0;
        while (input >> first >> second >> third) {
            mem[index++] = first.substr(2) +second.substr(2);
            mem[index++] = third.substr(2);
        }
        input.close();
    }


    void displayM(){
        for(int i=0 ; i < 256;i++){
            cout << mem[i] << "\n";
        }
    }

    string get(int pc){
        string instruction = mem[pc] +mem[pc+1];
        return instruction;
    }

};

class InstructionRegister{
    string IR;
public:
    InstructionRegister(){
        IR = "0000";
        cout << "InstructionRegister initialized with: " << IR << "\n";
    }
    void set(string instruction){
        IR = instruction;
    }
    string get(){
        return IR;
    }
};

class Instruction{
public:
    virtual void execute() = 0;
};

class Instruction1 : public Instruction{
public:
    void execute() override{}
};

class Instruction2 : public Instruction{
public:
    void execute() override{}
};

class Machine{
    InstructionRegister ir;
    int programcounter;
    Memory memory;
    Register registers;

public:
    Machine() : programcounter(0){
        cout << "Machine initialized with 16 Registers and 256 Memory blocks.\n";
    }

    void fetch(int& programcounter, Memory memory, InstructionRegister ir){
        string instruction = memory.get(programcounter);
        ir.set(instruction);
        programcounter += 2;
    }

    void decode(InstructionRegister ir){
        string instruction = ir.get();
        switch(instruction[0]){
        case '1':
            // 1st instuction fuction
            break;
        case '2':
            // 2nd instuction fuction
            break;
        case '3':
            // 3rd instuction fuction
            break;
        case '4':
            // 4th instuction fuction
            break;
        case '5':
            // 5th instuction fuction
            break;
        case '6':
            // 6th instuction fuction
            break;
        case 'B':
            // 7th instuction fuction
            break;
        case 'c':
            // 8th instuction fuction
            break;
        
        default:
            break;
        }
    }

};

int main(){
    // Machine mc;
    // Memory mem;
    // Register reg;
    // mem.readfile("test.txt");
    // reg.displayR();
    // mem.displayM();
}
