#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class HaltException : public runtime_error {
public:
    HaltException(const string& message) : runtime_error(message) {}
};

class Memory {
protected:
    map<int, string> cells;
public:
    Memory() {
        for (int i = 0; i < 256; i++) {
            cells[i] = "00";
        }
    }

    void setM(int address, const string& val) {
        if (cells.find(address) != cells.end()) {
            cells[address] = val;
        } else {
            throw out_of_range("Memory address out of range");
        }
    }

    string get(int address) const {
        if (cells.find(address) == cells.end() || cells.find(address + 1) == cells.end()) {
            throw out_of_range("Memory address out of range");
        }
        string ir = cells.at(address) + cells.at(address + 1);
        return ir;
    }

    string getM(int address) const {
        if (cells.find(address) == cells.end()) {
            throw out_of_range("Memory address out of range");
        }
        return cells.at(address);
    }

    void displayM() const {
        cout << "Memory:\n";
        for (int i = 0; i < 256; i++){
            cout <<cells.at(i) << "  ";
            if ((i + 1) % 16 == 0) {
                cout << "\n";
            }
        }
    }

    bool getInput(int initialCounter) {
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
        while (file1 >> word) {
            if (initialCounter < 256) {
                cells[initialCounter++] = word.substr(0, 2);
                if (initialCounter < 256 && word.length() > 2) {
                    cells[initialCounter++] = word.substr(2, 2);
                }
            } else {
                cout << "Warning: Exceeded memory limit while reading from file.\n";
                break;
            }
        }
        if(cells[initialCounter-2]+cells[initialCounter-1]!="C000"){
            cells[initialCounter]="C0";
        }
        file1.close();
        return initialCounter <= 256;
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
    con << hex << uppercase << setw(2) << setfill('0') << (x & 0xFF);
    return con.str();
}

class Machine {
private:
    Instructions ir;
    int pC;
    Memory mem;
    map<int, Register> registers;
    int commandCount;  // Track number of executed commands

public:
    Machine(int initialCounter) : pC(initialCounter), commandCount(0) {
        for (int i = 0; i < 16; i++) {
            registers[i] = Register();  // Initialize registers
        }
    }

    void readFile(){
        if(!mem.getInput(pC)){
            throw runtime_error("Failed to read file. Too many instructions.");
        }
    }

    void setRegisterValue(int num, const string& value){
        if (registers.find(num) == registers.end()) {
            throw invalid_argument("Register not found");
        }
        ostringstream paddedValue;
        paddedValue << setw(2) << setfill('0') << value;
        registers[num].setRegister(paddedValue.str());
    }

    string getRegisterValue(int num) const {
        if (registers.find(num) == registers.end()) {
            throw invalid_argument("Register not found");
        }
        return registers.at(num).getRegister();
    }

    void display() const {
        cout << "Memory :\n";
        mem.displayM();
        cout << "=======================================================================\n";
        cout << "Registers:\n";
        for (const auto& reg : registers) {
            cout << "Register " << reg.first << ": " << reg.second.getRegister() << "\n";
        }
    }

    void fetch(){
        cout << "Fetching instruction at PC: " << pC << endl;
        string instruction = mem.get(pC);
        cout << "Fetched instruction: " << instruction << endl;
        ir.set(instruction);
        pC += 2;
    }


    void decode(){
        string instruction = ir.get();
        commandCount++;
        switch (instruction[0]) {
            case '1': {
                int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
                int memoryAddress = convertHexToDecimal(instruction.substr(2, 2));
                if (memoryAddress < 0 || memoryAddress >= 256) {
                    throw out_of_range("Memory address out of range");
                }
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
            case '5': {  // ADD two's complement values
                int destRegister = convertHexToDecimal(instruction.substr(1, 1));
                int srcRegister1 = convertHexToDecimal(instruction.substr(2, 1));
                int srcRegister2 = convertHexToDecimal(instruction.substr(3, 1));

                int value1 = stoi(getRegisterValue(srcRegister1), nullptr, 16);
                int value2 = stoi(getRegisterValue(srcRegister2), nullptr, 16);

                if (value1 > 127) value1 -= 256;
                if (value2 > 127) value2 -= 256;

                int result = (value1 + value2) & 0xFF;

                setRegisterValue(destRegister, convertDecimalToHex(result));
                break;
            }
            case 'B': {  // JUMP if register R is zero
                int registerNumber = convertHexToDecimal(instruction.substr(1, 1));
                int memoryAddress = convertHexToDecimal(instruction.substr(2, 2));
                if(memoryAddress < 0 || memoryAddress >= 256){
                    throw out_of_range("Memory address out of range");
                }
                string registerValue = getRegisterValue(registerNumber);
                string registerZeroValue = getRegisterValue(0);
                int regValue = convertHexToDecimal(registerValue);
                int regZeroValue = convertHexToDecimal(registerZeroValue);
                if(regValue == regZeroValue){
                    pC = memoryAddress;
                }
                break;
            }
            case 'C': {  // HALT
                throw HaltException("Program has been halted.");
            }
            default: {
                break;
            }
        }
    }

    int number_of_commands_till_HALT() const {
        return commandCount;
    }
};

int main() {
    cout << "Welcome to the Vole machine.\n";
    Machine mc(0);
    int userChoice = 0;
    while(true){
        cout << "\nMenu Options:\n"
             << "1 - Load a program from a file\n"
             << "2 - Run the loaded program\n"
             << "3 - Show current memory and register values\n"
             << "4 - Exit the machine\n";

        cin >> userChoice;
        while(userChoice < 1 || userChoice > 4){
            cout << "Invalid selection. Please enter a number between 1 and 4:\n";
            cin >> userChoice;
        }

        switch(userChoice){
            case 1: {
                int startAddress;
                cout << "Specify memory location for loading (0 to 255):\n";
                cin >> startAddress;
                while(startAddress < 0 || startAddress >= 256) {
                    cout << "Invalid memory location. Try again:\n";
                    cin >> startAddress;
                }
                mc = Machine(startAddress);
                try{
                    mc.readFile();
                } catch (const runtime_error& err){
                    cout << "Error: " << err.what() << "\n";
                    cout << "Try loading a file with fewer instructions.\n";
                }
                break;

            }
            case 2: {
                try{
                    for(int i = 0; i < 256; i += 2){
                        mc.fetch();
                        mc.decode();
                    }
                } catch(const HaltException& halt){
                    cout << "Halting: " << halt.what() << "\n";
                    cout << "Executed " << mc.number_of_commands_till_HALT() << " commands before halting.\n";
                } catch(const out_of_range& oor){
                    cout << "Error: " << oor.what() << "\n";
                }
                break;
            }
            case 3:
                mc.display();
                break;
            
            case 4:
                cout << "Goodbye! Thank you for using the Vole machine.\n";
        }
    }
}
