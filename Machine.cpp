#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>  
using namespace std;

class Memory {
protected:
    map<int, string> cells;  // Memory cells
public:
    Memory() {
        for (int i = 0; i < 256; i++) {
            cells[i] = "00";
        }
    }

    void setM(int address, const string& val) {
        cells[address] = val;
    }

    string get(int address) const {
        string ir = cells.at(address) +cells.at(address+1);
        return ir;
    }

    string getM(int address) const {
        return cells.at(address);
    }

    void displayM(){
        for(int i=0 ; i < 256;i++){
            cout << cells[i] << "\n";
        }
    }

    void getInput() {
        ifstream file1;
        string filename;
        do {
            cout << "Enter the name of the first file: ";
            cin >> filename;
            file1.open(filename);
            if (!file1.is_open())
                cout << "Error opening the file \n";
        } while (!file1.is_open());

        string word;
        int index = 0;
        while (file1 >> word) {
            if (index < 256) {
                cells[index++] = word.substr(0, 2);
                if (index < 256 && word.length() > 2) {
                    cells[index++] = word.substr(2, 2);
                }
            }
        }
        file1.close();
    }
};

class Register {
private:
    string value;
public:
    Register(const string& value = "00") : value(value) {}

    void setRegister(const string& newValue) {
        value = newValue;
    }

    string getRegister() const {
        return value;
    }

    
};

class Instructions {
private:
    string instruction;
public:
    void set(const string& instruction) {
        this->instruction = instruction;
    }
    string get() const {
        return instruction;
    }
};
int convertHexToDecimal(const string& hex) {
    return stoi(hex, nullptr, 16);
}
string convertDecimalToHex(int x) {
    ostringstream con;
    con << hex << uppercase << x;
    return con.str();
}

class Machine {
private:
    Instructions ir;
    int pC;
    Memory mem;
    map<int, Register> registers;

public:
    Machine() : pC(0) {
        for (int i = 0; i < 16; i++) {
            registers[i] = Register();  // Initialize registers
        }
    }

    void readFile() {
        mem.getInput();
    }

    void setRegisterValue(int num, const string& value) {
        if (registers.find(num) == registers.end()) {
            throw invalid_argument("Register not found");
        }
        registers[num].setRegister(value);
    }

    string getRegisterValue(int num) const {
        if (registers.find(num) == registers.end()) {
            throw invalid_argument("Register not found");
        }
        return registers.at(num).getRegister();
    }

    void display() {
        cout << "Memory :\n";
        mem.displayM();  
        cout << "=======================================================================\n";
        cout << "Registers:\n";
        for (const auto& reg : registers) {
            cout << "Register " << reg.first << ": " << reg.second.getRegister() << "\n";  // Adjust as needed
        }
    }

    void fetch() {
        string instruction = mem.get(pC);  
        ir.set(instruction);
        pC += 2;  // Increment PC after fetching
    }

    void decode() {
    string instruction = ir.get();
    switch (instruction[0]) {
        case '1': {  // LOAD from memory to register
            int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
            int memoryAddress = convertHexToDecimal(instruction.substr(2, 2));
            string memValue = mem.getM(memoryAddress);
            setRegisterValue(registerNumber, memValue);
            break;
        }
        case '2': {  // LOAD immediate value to register
            int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
            string immediateValue = instruction.substr(2, 2);
            setRegisterValue(registerNumber, immediateValue);
            break;
        }
        case '3': {  // STORE from register to memory
            int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
            int memoryAddress = convertHexToDecimal(instruction.substr(2, 2));
            string regValue = getRegisterValue(registerNumber);
            mem.setM(memoryAddress, regValue);
            break;
        }
        case '4': {  // MOVE from one register to another
            int sourceRegister = convertHexToDecimal(instruction.substr(2, 1));
            int destRegister = convertHexToDecimal(instruction.substr(3, 1));
            string valueToMove = getRegisterValue(sourceRegister);
            setRegisterValue(destRegister, valueToMove);
            break;
        }
        case '5':  // ADD two's complement values
        case '6': {  // ADD floating-point values
            int destRegister = convertHexToDecimal(instruction.substr(1, 1));
            int srcRegister1 = convertHexToDecimal(instruction.substr(2, 1));
            int srcRegister2 = convertHexToDecimal(instruction.substr(3, 1));
            string value1 = getRegisterValue(srcRegister1);
            string value2 = getRegisterValue(srcRegister2);

            // Ensure the values are not empty before conversion
            if (value1.empty() || value2.empty()) {
                return;
            }

            int result = (instruction[0] == '5') 
                ? (convertHexToDecimal(value1) + convertHexToDecimal(value2)) 
                : (stof(value1) + stof(value2));

            setRegisterValue(destRegister, convertDecimalToHex(result));
            break;
        }
        case 'B': {  // JUMP if register R is zero
            int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
            int memoryAddress = convertHexToDecimal(instruction.substr(2, 2));
            if (getRegisterValue(registerNumber) == "00"){
                pC = memoryAddress;
            }
            break;
        }
        case 'C': {  // HALT
            cout << "Program halted.\n";
            exit(0);
        }
        default:
            break;
    }
}


    
};


int main() {
    Machine mc;
    mc.readFile();

    for (int i = 0; i < 256; i += 2) {
        mc.fetch();
        mc.decode();
    }

    mc.display();
    return 0;
}