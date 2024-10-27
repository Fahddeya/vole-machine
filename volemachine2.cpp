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

    void readfile(){
        string filename;
        ifstream input;
        do{
            cout<<"Enter the filename please : ";
            cin>>filename;
            input.open(filename);
            if(!input.is_open())
                cout<<"Error opening the file , please enter it again :\n";
        }while(!input.is_open());

            string word;
            int index = 0;
            while (input >> word){
                mem[index++] = word.substr(0,2);
                mem[index++] = word.substr(2,2);
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


class ALU{
public:
    
};

int converthexatodecimal(string hex)
{
    return stoi(hex,nullptr,16);
}

string convertdecimaltohexa(int x)
{
    ostringstream con;
    con<<hex<<uppercase<<x;
    return con.str();
}


string convertDecimalToBinary(int decimal, int bits = 6) {

    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary;
        decimal /= 2;
    }


    while (binary.size() < bits) {
        binary = "0" + binary;
    }
    return binary;
}


string first_complement(int x, int bits) {

    string convert = convertDecimalToBinary(-x, bits);
    string inverted = "";


    for (char i : convert) {
    if (i == '0') {
        inverted += '1';
    } else {
        inverted += '0';
    }
}

    return inverted;
}


string addOneToBinary(const string &binary) {
    string result = binary;
    int n = result.size();


    for (int i = n - 1; i >= 0; i--) {
        if (result[i] == '0') {
            result[i] = '1';
            return result;
        } else {
            result[i] = '0';
        }
    }
    return "1" + result;
}


string second_complement(int x, int bits = 6) {
    if (x >= 0) {
        return convertDecimalToBinary(x, bits);
    } else {
        string firstComplement = first_complement(x, bits);
        string twoComplement = addOneToBinary(firstComplement);
        return twoComplement;
    }
}


int convertBinaryToDecimal( string &binary) {
    int decimal = 0;
    int power = 0;


    for (int i = binary.size() - 1; i >= 0; --i) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        power++;
    }

    return decimal;
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

// fifth instruction : adding the values as two complement representation in register S and T and loading it in register R

class Instruction5 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R=converthexatodecimal(giveninstructions.substr(1,1));
        int S=converthexatodecimal(giveninstructions.substr(2,1));
        int T=converthexatodecimal(giveninstructions.substr(3,1));

        int valueS = converthexatodecimal(regist.get(S));
        int valueT = converthexatodecimal(regist.get(T));

        string twocomplementsum=second_complement(valueS+valueT);

        string tempsum= to_string(convertBinaryToDecimal(twocomplementsum));

        int sum=stoi(tempsum);

        regist.set(convertdecimaltohexa(sum),R);


    }
};

//Sixth instruction: Adding patterns found in registers S and T and leaving the floating
//point result in register R

class Instruction6 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R = converthexatodecimal(giveninstructions.substr(1,1));
        int S = converthexatodecimal(giveninstructions.substr(2,1));
        int T = converthexatodecimal(giveninstructions.substr(3,1));
        float float_result=stof(regist.get(S))+stof(regist.get(T));
        regist.set(to_string(float_result),R);
    }
};

//Seventh instruction: BRXY jump to memory address XY if value of register R not equal register 0

class InstructionBB : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R=converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        int memory_address=converthexatodecimal(XY);
        if(regist.get(R)==regist.get(0))
            programcounter=memory_address;

    }
};

// we will need to apply exception handling to deal with the halt command

class HaltException : public exception {
public:
    const char* what() const noexcept override {
        return "HALT instruction was executed\n";
    }
};

//Eight instruction : HALT or ending the problem execution

class InstructionCC : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {
        throw HaltException();
    }
};


class Machine{
    InstructionRegister ir;
    int programcounter;
    Memory memory;
    Register registers;
    int commands_counter;

public:
    Machine() : programcounter(0) , commands_counter(0){
        cout << "Machine initialized with 16 Registers and 256 Memory blocks.\n";
    }

    void Readfile(){
        memory.readfile();
    }

    void display(){
        cout<<"Memory cells:\n";
        memory.displayM();
        cout<<"======================================\n";
        cout<<"Registers:\n";
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

        commands_counter++;
    }
     int number_of_commands_till_HALT(){return commands_counter;}
};


int main(){
    Machine mc;
    mc.Readfile();

    try {
        for (int i = 0; i < 256; i += 2) {
            mc.fetch();
            mc.decode();
        }
    } catch (const HaltException& e) {
        cout << e.what();
        cout<<"Exiting the program after executing "<<mc.number_of_commands_till_HALT()<<" commands\n";
    }

    mc.display();

}
