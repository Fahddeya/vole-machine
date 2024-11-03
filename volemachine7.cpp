#include <bits/stdc++.h>
#include <bitset>
using namespace std;

class ALU{
public:
    int converthexatodecimal(string hex){
        return stoi(hex,nullptr,16);
    }

    string convertdecimaltohexa(int x){
        ostringstream con;
        con<<hex<<uppercase<<x;
        return con.str();
    }


    string convertDecimalToBinary(int decimal, int bits = 6) {
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


    string first_complement(int x, int bits) {
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


    string addOneToBinary(const string &binary) {
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


    string second_complement(int x, int bits = 6) {
        if (x >= 0) {
            return convertDecimalToBinary(x, bits);
        }
        else{
            string firstComplement = first_complement(x, bits);
            string twoComplement = addOneToBinary(firstComplement);
            return twoComplement;
        }
    }


    int convertBinaryToDecimal( string &binary) {
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

    bool isHexadecimal(const string& input){
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

};




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
    ALU alu;
public:
    Memory(){
        for(int i=0 ; i < 256;i++){
            mem[i] = "00";
        }
    }

    bool readfile(int pc){
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



    void displayM(){
        for(int i = 0; i < 256; i++){
            cout << mem[i] << "  ";
            if((i + 1) % 16 == 0){
                cout << "\n";
            }
        }
    }

    string getIR(int pc){
        string instruction = mem[pc] +mem[pc+1];
        return instruction;
    }

    string getR(int pc){
        string instruction = mem[pc];
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
    ALU alu;
    virtual void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) = 0;
};

// first instruction : loading register R with the bit pattern in memory cell with address XY

class Instruction1  : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
        int memory_address=alu.converthexatodecimal(XY);
        string loaded_value_in_register=memo.getR(memory_address);
        regist.set(loaded_value_in_register,register_index);
    }
};

// Second instruction : loading the register R with the bit pattern XY

class Instruction2 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
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
        int register_index=alu.converthexatodecimal(giveninstructions.substr(1,1));
        string XY=giveninstructions.substr(2,2);
         int memory_address=alu.converthexatodecimal(XY);
         string value_stored=regist.get(register_index);
         memo.set(memory_address , value_stored);
    }
};

//fourth instruction : 0RS Moving bit pattern found in register R to register S
class Instruction4 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
    {
        int R = alu.converthexatodecimal(giveninstructions.substr(2,1));
        int S = alu.converthexatodecimal(giveninstructions.substr(3,1));
        string copied_value=regist.get(R);
        regist.set(copied_value,S);
    }
};

// fifth instruction : adding the values as two complement representation in register S and T and loading it in register R

class Instruction5 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
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
};

//Sixth instruction: Adding patterns found in registers S and T and leaving the floating
//point result in register R

class Instruction6 : public Instruction{
public:
    void execute(Register &regist,Memory &memo , int &programcounter , string giveninstructions) override
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
};

//Seventh instruction: BRXY jump to memory address XY if value of register R not equal register 0

class InstructionBB : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {
        int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        string XY = giveninstructions.substr(2, 2);
        int memory_address = alu.converthexatodecimal(XY);
        if (regist.get(R) == regist.get(0)) {
            programcounter = memory_address;
        }
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

//Bonus instructions

//AND the bit patterns found in registers s and t and load the result in register R

class InstructionAND : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {
        int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS & decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
    }
};

//OR the bit patterns found in registers s and t and load the result in register R


class InstructionOR : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {

        int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS | decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
    }
};

//XOR the bit patterns found in registers s and t and load the result in register R


class InstructionXOR : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {

        int R = alu.converthexatodecimal(giveninstructions.substr(1, 1));
        int S = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int T = alu.converthexatodecimal(giveninstructions.substr(3, 1));


        int decimalS = alu.converthexatodecimal(regist.get(S));
        int decimalT = alu.converthexatodecimal(regist.get(T));


        int result = decimalS ^ decimalT;


        regist.set(alu.convertdecimaltohexa(result), R);
    }
};

//rotate the bit pattern found in regiser R x bits to the right

class InstructionROTATE : public Instruction {
public:
    void execute(Register &regist, Memory &memo, int &programcounter, string giveninstructions) override {

        int R = alu.converthexatodecimal(giveninstructions.substr(2, 1));
        int X = alu.converthexatodecimal(giveninstructions.substr(3, 1));

        int decimalR = alu.converthexatodecimal(regist.get(R));

        int rotatedResult = (decimalR >> X) | (decimalR << (16 - X));

        regist.set(alu.convertdecimaltohexa(rotatedResult), R);
    }
};




class Machine{
    InstructionRegister ir;
    int programcounter;
    Memory memory;
    Register registers;
    int commands_counter;

public:
    Machine(int pc) : programcounter(pc) , commands_counter(0){
        cout << "Machine initialized with 16 Registers and 256 Memory blocks.\n";
    }

    bool Readfile(int pc){
        if(memory.readfile(pc)){
            return true;
        }
        else{
            return false;
        }
    }

    //void tryregister()
    //{
      //   int x=200;
      // int y=10;
      //   ALU calc;
       //  string store1 = calc.convertdecimaltohexa(x);
        // string store2 = calc.convertdecimaltohexa(y);
         //registers.set(store1,10);
         //registers.set(store2,11);

   // } did some trials

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
        cout << "pc: " << programcounter << "->" << instruction << "\n";
        programcounter += 2;
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

     int number_of_commands_till_HALT(){return commands_counter;}
};


int main() {
    cout << "Welcome to the vole machine.\n";
    int choice;
    int pc;
    Machine mc(0);
    do{
        cout << "\nPlease choose from the following menu:\n";
        cout << "1) Read file and load program.\n";
        cout << "2) Execute program.\n";
        cout << "3) Display data.\n";
        cout << "4) Exit.\n";
        cin >> choice;
        while (true) {
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (choice < 1 || choice > 4) {
                cout << "Invalid choice, please try again.\n";
            } else {
                break;
            }
        }
        switch(choice){
            case 1:
                cout << "Enter the starting location for storing data in memory (0 < location < 256):\n";
                while (true) {
                    cin >> pc;
                    if (cin.fail()){
                        cout << "Invalid input! Please enter a number between 1 and 256.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else if(pc < 1 || pc > 256){
                        cout << "Invalid choice, please try again.\n";
                    }
                    else{
                        break;
                    }
                }
                mc = Machine(pc);
                while(!mc.Readfile(pc)){
                    cout << "Please try loading file with less number of instructions.\n";
                }
                break;

            case 2:
                try{
                    for(int i = 0; i < 256; i += 2){
                        mc.fetch();
                        mc.decode();
                    }
                }catch(const HaltException& e){
                    cout << e.what() << endl;
                    cout << "Exiting after executing " << mc.number_of_commands_till_HALT() << " commands\n";
                }
                break;
            case 3:
                mc.display();
                break;
            case 4:
                cout << "see you soon..\n";
                break;
        }
    }while(choice != 4);
}
