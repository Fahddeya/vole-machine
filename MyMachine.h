#ifndef MyMACHINE_H
#define MyMACHINE_H

#include <bits/stdc++.h>
#include <bitset>
#include <exception>
using namespace std;

class ALU {
public:
    int converthexatodecimal(string hex);
    string convertdecimaltohexa(int x);
    string convertDecimalToBinary(int decimal, int bits );
    string first_complement(int x, int bits);
    string addOneToBinary(const string &binary);
    string second_complement(int x, int bits );
    int convertBinaryToDecimal(string &binary);
    bool isHexadecimal(const string &input);
};

class Register {
    string reg[16];
public:
    Register();
    void displayR();
    void set(string input, int index);
    string get(int index);
};

class Memory {
    string mem[256];
    ALU alu;
public:
    Memory();
    bool readfile(int pc);
    void displayM();
    string getIR(int pc);
    string getR(int pc);
    void set(int address, string &value);
};

class InstructionRegister {
    string IR;
public:
    InstructionRegister();
    void set(string instruction);
    string get();
};

class Instruction {
public:
    ALU alu;
    virtual void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) = 0;
};

class Instruction1 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Instruction2 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Instruction3 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Instruction4 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Instruction5 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Instruction6 : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class InstructionBB : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class HaltException : public exception {
public:
    const char* what() const noexcept override;
};

class InstructionCC : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class InstructionAND : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class InstructionOR : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class InstructionXOR : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class InstructionROTATE : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override;
};

class Machine {
    InstructionRegister ir;
    int programcounter;
    Memory memory;
    Register registers;
    int commands_counter;

public:
    Machine(int pc);
    bool Readfile(int pc);
    void display();
    void fetch();
    void decode();
    int number_of_commands_till_HALT();
};

#endif // MyMACHINE_H
