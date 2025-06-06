#include "MyMachine.h"
#include<bits/stdc++.h>


using namespace std;

int ALU::converthexatodecimal(string hex)
{
    return stoi(hex,nullptr,16);
}

string ALU::convertdecimaltohexa(int x)
{
     ostringstream con;
     con<<hex<<uppercase<<x;
     return con.str();
}

string ALU::convertDecimalToBinary(int decimal , int bits=6)
{
    string binary = "";
        while(decimal > 0) {
            binary = to_string(decimal % 2) + binary;
            decimal /= 2;
        }
        while(binary.size() < bits) {
            binary = "0" + binary;
        }
        return binary;
}

string ALU::first_complement(int x, int bits) {
        string convert = convertDecimalToBinary(-x, bits);
        string inverted = "";
        for(char i : convert) {
        if(i == '0') {
            inverted += '1';
        }
        else{
            inverted += '0';
        }
    }
        return inverted;
    }

string ALU::addOneToBinary(const string &binary) {
        string result = binary;
        int n = result.size();
        for(int i = n - 1; i >= 0; i--){
            if(result[i] == '0') {
                result[i] = '1';
                return result;
            }
            else{
                result[i] = '0';
            }
        }
        return "1" + result;
    }

string ALU::second_complement(int x, int bits = 6) {
        if (x >= 0) {
            return convertDecimalToBinary(x, bits);
        }
        else{
            string firstComplement = first_complement(x, bits);
            string twoComplement = addOneToBinary(firstComplement);
            return twoComplement;
        }
    }

int ALU::convertBinaryToDecimal( string &binary) {
        int decimal = 0;
        int power = 0;
        for(int i = binary.size() - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimal += pow(2, power);
            }
            power++;
        }
        return decimal;
    }

bool ALU::isHexadecimal(const string& input){
        if(input.length() != 4){
            return false;
        }

        for(char c : input){
            if (!isxdigit(c)){
                return false;
            }
        }
        return true;
    }

Register::Register()
{
    for(int i=0 ; i < 16;i++){
            reg[i] = "00";
        }
}

void Register::displayR(){
        for(int i=0 ; i < 16;i++){
            cout << reg[i] << "\n";
        }
    }

void Register::set(string input,int index){
        reg[index] = input;
    }

string Register::get(int index){
        return reg[index];
    }

Memory::Memory()
{
    for(int i=0 ; i < 256;i++){
            mem[i] = "00";
        }
}

bool Memory::readfile(int pc){
        string filename;
        ifstream input;
        do{
            cout << "Enter the filename please: ";
            cin >> filename;
            input.open(filename);
            if(!input.is_open()){
                cout << "Error opening the file, please enter it again :\n";
            }
        }while(!input.is_open());
            string word;
            int availableSpace = 256 - pc;
            int instructionCount = 0;
        while(input >> word){
            if(alu.isHexadecimal(word)){
                if(instructionCount >= availableSpace){
                    cout << "Error: Not enough memory to load all instructions.\n";
                    input.close();
                    return false;
                }
                mem[pc++] = word.substr(0, 2);
                mem[pc++] = word.substr(2, 2);
                instructionCount += 2;
            }
        }
            if(mem[pc-2] + mem[pc-1] != "C000"){
                mem[pc++] = "C0";
            }
            input.close();
            return true;
        }

void Memory::displayM(){
        for(int i = 0; i < 256; i++){
            cout << mem[i] << "  ";
            if((i + 1) % 16 == 0){
                cout << "\n";
            }
        }
    }

string Memory::getIR(int pc){
        string instruction = mem[pc] +mem[pc+1];
        return instruction;
    }

string Memory::getR(int pc){
        string instruction = mem[pc];
        return instruction;
    }

void Memory::set(int address , string &value)
    {
        if(address==0){
            cout<<"This is the memory address 00\n";
            cout<<"Now writing to the screen the current value "<<value<<endl;
        }
        else if(address>=0 && address<256){
            mem[address]=value;
        }
    }

InstructionRegister::InstructionRegister()
{
    IR="0000";
}

void InstructionRegister::set(string instruction){
        IR = instruction;
    }

string InstructionRegister::get(){
        return IR;
    }


void Instruction1::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        int memory_address=alu.converthexatodecimal(XY);
        string loaded_value_in_register=memo.getR(memory_address);
        regist.set(loaded_value_in_register,register_index);
}

void Instruction2::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        regist.set(XY,register_index);
}

void Instruction3::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
         int memory_address=alu.converthexatodecimal(XY);
         string value_stored=regist.get(register_index);
         memo.set(memory_address , value_stored);
}

void Instruction4::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(2,1));
        int S = alu.converthexatodecimal(giveninstructions.substr(3,1));
        string copied_value=regist.get(R);
        regist.set(copied_value,S);
}

void Instruction5::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R=alu.converthexatodecimal(giveninstructions.substr(1,1));
        int S=alu.converthexatodecimal(giveninstructions.substr(2,1));
        int T=alu.converthexatodecimal(giveninstructions.substr(3,1));

        int valueS = alu.converthexatodecimal(regist.get(S));
        int valueT = alu.converthexatodecimal(regist.get(T));

        string twocomplementsum=alu.second_complement(valueS+valueT);

        string tempsum= to_string(alu.convertBinaryToDecimal(twocomplementsum));

        int sum=stoi(tempsum);

        string hexasum=alu.convertdecimaltohexa(sum);

        if(hexasum.size()==1)
            hexasum="0"+hexasum;

         regist.set(hexasum,R);
}

void Instruction6::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(1,1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2,1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3,1));

        int operandS=alu.converthexatodecimal(regist.get(S));
        int operandT=alu.converthexatodecimal(regist.get(T));


        int sum=operandS+operandT;

        if(sum<0)
            regist.set("00",R);
        else if(sum>255)
            regist.set("FF",R);
        else
            regist.set(alu.convertdecimaltohexa(sum),R);
}

void InstructionBB::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        string XY = giveninstructions.substr(2, 2);
        int memory_address = alu.converthexatodecimal(XY);
        if (regist.get(R) == regist.get(0)) {
            programcounter = memory_address;
        }

}

const char *HaltException::what() const noexcept
{
     return "HALT instruction was executed\n";
}

void InstructionCC::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
     throw HaltException();
}

//Bonus instructions

void InstructionOR::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS | decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
}

void InstructionAND::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
     int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS & decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
}

void InstructionXOR::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS ^ decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
}

void InstructionROTATE::execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions)
{
    int R = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int X = alu.converthexatodecimal(giveninstructions.substr(3, 1));

        int decimalR = alu.converthexatodecimal(regist.get(R));

        int rotatedResult = (decimalR >> X) | (decimalR << (16 - X));

        regist.set(alu.convertdecimaltohexa(rotatedResult), R);
}

Machine::Machine(int pc)
{
    programcounter=pc;
    commands_counter=0;
}

bool Machine::Readfile(int pc){
        if(memory.readfile(pc)){
            return true;
        }
        else{
            return false;
        }
    }

void Machine::display(){
        cout<<"Memory cells:\n";
        memory.displayM();
        cout<<"======================================\n";
        cout<<"Registers:\n";
        registers.displayR();
    }

void Machine::fetch(){
        string instruction = memory.getIR(programcounter);
        ir.set(instruction);
        cout<<"pc: "<<programcounter<<"->"<<instruction<<"\n";
        programcounter += 2;  // Increment PC after fetching
    }

void Machine::decode(){
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
        case '7':
            instructionss = make_unique<InstructionOR>();
            break;
        case '8':
            instructionss = make_unique<InstructionAND>();
            break;
        case '9':
            instructionss=make_unique<InstructionXOR>();
            break;
        case 'A':
            instructionss=make_unique<InstructionROTATE>();
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

     int Machine::number_of_commands_till_HALT(){return commands_counter;}

