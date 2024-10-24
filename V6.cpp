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
    void set(string input,int index){
        reg[index] = input;
    }
    string get(int index){
        return reg[index];
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
            mem[index++] = first.substr(2,1) +second.substr(2,1);
            mem[index++] = third.substr(2,2);
        }
        input.close();
    }


    void displayM(){
        for(int i=0 ; i < 256;i++){
            cout << mem[i] << "\n";
        }
    }

    string getIR(int pc){
        string instruction = mem[pc] +mem[pc+1];
        return instruction;
    }
    
    string getR(int pc){
        string instruction = mem[pc+1];
        return instruction;
    }

    void set(int address , string &value)
    {
        if(address==0){
            cout<<"This is the memory address 00\n";
            cout<<"Now writing to the screen the current value "<<value<<endl;
        }
        else if(address>=0 && address<256){
            mem[address]=value;
        }
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

int converthexatodecimal(string hex)
{
    return stoi(hex,nullptr,16);
}

class Instruction{
public:
    virtual void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) = 0;
};

// first instruction : loading register R with the bit pattern in memory cell with address XY

class Instruction1  : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int register_index=converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        int memory_address=converthexatodecimal(XY);
        string loaded_value_in_register=memo.getR(memory_address);
        regist.set(loaded_value_in_register,register_index);
    }
};

// Second instruction : loading the register R with the bit pattern XY

class Instruction2 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int register_index=converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        regist.set(XY,register_index);
    }
};

//Third instruction 1 : storing the bit pattern found in register R in the memory cell whose address XY
//Third instruction 2 : Store to location 00 , which is memory mapping for the screen

class Instruction3 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int register_index=converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
         int memory_address=converthexatodecimal(XY);
         string value_stored=regist.get(register_index);
         memo.set(memory_address , value_stored);
    }
};

//fourth instruction : 0RS Moving bit pattern found in register R to register S
class Instruction4 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R = converthexatodecimal(giveninstructions.substr(2,1));
        int S = converthexatodecimal(giveninstructions.substr(3,1));
        string copied_value=regist.get(R);
        regist.set(copied_value,S);
    }
};
// fifth instruction : adding the values in register S and T and loading it in register R
class Instruction5 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R=converthexatodecimal(giveninstructions.substr(1,1));
        int S=converthexatodecimal(giveninstructions.substr(2,1));
        int T=converthexatodecimal(giveninstructions.substr(3,1));
        int summation = converthexatodecimal(regist.get(S))+ converthexatodecimal(regist.get(R));
        if(summation<0)
            regist.set("00",R);
        else if(summation>255)
            regist.set("ff",R);
        else
            regist.set(to_string(summation),R);

    }
};

class Instruction6 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {

    }
};

class InstructionBB : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {

    }
};

class InstructionCC : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {

    }
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
    
    void Readfile(string input){
        memory.readfile(input);
    }

    void display(){
        memory.displayM();
        registers.displayR();
    }

    void fetch(){
        string instruction = memory.getIR(programcounter);
        ir.set(instruction);
        programcounter += 2;  // Increment PC after fetching
    }

    void decode(){
        string instruction = ir.get();
        unique_ptr<Instruction> instructionss;

        // Decode the first character and select the appropriate instruction
        switch(instruction[0]){
        case '1':
            instructionss = make_unique<Instruction1>();
            break;
        case '2':
            instructionss = make_unique<Instruction2>();
            break;
        case '3':
            instructionss = make_unique<Instruction3>();
            break;
        case '4':
            instructionss = make_unique<Instruction4>();
            break;
        case '5':
            instructionss = make_unique<Instruction5>();
            break;
        case '6':
            instructionss = make_unique<Instruction6>();
            break;
        case 'B':
            instructionss = make_unique<InstructionBB>();
            break;
        case 'C':
            instructionss = make_unique<InstructionCC>();
            break;
        default:
            return;
        }

        // Execute the decoded instruction
        instructionss->execute(registers, memory, programcounter, instruction);
    }

};


int main(){
    Machine mc;
    mc.Readfile("test.txt");
    
    for(int i = 0; i < 256; i+=2){
        mc.fetch();
        mc.decode();
    }

    mc.display();
    
    cout<<"Hello\n";

}
