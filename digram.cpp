http://try.umple.org/?text=class%20ALU%7B%0A%0A%20%20%20%20int%20converthexatodecimal(string%20hex)%7B%7D%0A%0A%20%20%20%20string%20convertdecimaltohexa(int%20x)%7B%7D%0A%0A%20%20%20%20string%20convertDecimalToBinary()%7B%7D%0A%0A%0A%20%20%20%20string%20first_complement(int%20x%2C%20int%20bits)%7B%7D%0A%0A%0A%20%20%20%20string%20addOneToBinary()%7B%7D%0A%0A%0A%20%20%20%20string%20second_complement()%7B%7D%0A%0A%0A%20%20%20%20int%20convertBinaryToDecimal()%7B%7D%0A%0A%20%20%20%20%0A%0Aclass%20Register%7B%0A%0A%20%20%20%20string%20reg%3B%0A%20%20%0A%20%20%20%20Register%7B%7D%0A%20%20%20%20%7D%0A%20%20%20%20void%20displayR()%7B%7D%0A%20%20%20%20void%20set(string%20input%2Cint%20index)%7B%7D%0A%20%20%20%20string%20get(int%20index)%7B%7D%0A%7D%3B%0A%0Aclass%20Memory%7B%0A%20%20%20%20string%20mem%3B%0A%20%20%20%20ALU%20alu%3B%0A%0A%20%20%20%20Memory%7B%7D%0A%0A%20%20%20%20void%20readfile()%7B%7D%0A%0A%20%20%20%20void%20displayM()%7B%7D%0A%0A%20%20%20%20string%20getIR(int%20pc)%7B%7D%0A%0A%20%20%20%20string%20getR(int%20pc)%7B%7D%0A%0A%20%20%20%20void%20set()%7B%7D%0A%7D%3B%0A%0Aclass%20InstructionRegister%7B%0A%20%20%20%20string%20ir%3B%0A%0A%20%20%20%20InstructionRegister%7B%7D%0A%20%20%20%20void%20set(string%20instruction)%7B%7D%0A%20%20%20%20string%20get()%7B%7D%0A%7D%3B%0A%0A%0A%0A%0A%0A%0Aclass%20Instruction%7B%0A%20%20%20abstract%3B%0A%20%20%20%20ALU%20alu%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0Aclass%20Instruction1%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0Aclass%20Instruction2%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0Aclass%20Instruction3%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0Aclass%20Instruction4%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0Aclass%20Instruction5%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0Aclass%20Instruction6%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0A%0Aclass%20InstructionBB%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%7B%7D%0A%7D%3B%0A%0A%0Aclass%20HaltException%7B%0A%0A%20%20%20%20noexcept()%7B%7D%0A%7D%3B%0A%0Aclass%20InstructionCC%7B%0A%20%20%20%20isA%20Instruction%3B%0A%20%20%20%20void%20execute()%20%7B%7D%0A%7D%3B%0A%0A%0Aclass%20Machine%7B%0A%20%20%20%20InstructionRegister%20ir%3B%0A%20%20%20%20int%20programcounter%3B%0A%20%20%20%20Memory%20memory%3B%0A%20%20%20%20Register%20registers%3B%0A%20%20%20%20int%20commands_counter%3B%0A%0Apublic%3A%0A%20%20%20%20Machine()%20%3A%20programcounter(0)%20%2C%20commands_counter(0)%7B%7D%0A%0A%20%20%20%20void%20Readfile()%7B%7D%0A%0A%20%20%20%20void%20display()%7B%7D%0A%0A%20%20%20%20void%20fetch()%7B%7D%0A%0A%20%20%20%20void%20decode()%7B%7D%0A%0A%7D%3B%0A%0Anamespace%20-%3B%0A%0A%0Aclass%20Register%0A%7B%0A%20%20position%20541%20226%20103.537%2078.2625%3B%0A%7D%0A%0Aclass%20Memory%0A%7B%0A%20%20position%2092%202%20154.413%20180.262%3B%0A%7D%0A%0Aclass%20Machine%0A%7B%0A%20%20position%20593%200%20183.962%20214.262%3B%0A%20%20position.association%20Machine__Memory%200%2C70%20144%2C49%3B%0A%20%20position.association%20Machine__Register%2078%2C129%20134%2C0%3B%0A%7D%0A%0Aclass%20ALU%0A%7B%0A%20%20position%20271%200%20265.1%20231.262%3B%0A%7D%0A%0Aclass%20InstructionRegister%0A%7B%0A%20%20position%204%20187%20150.7%20112.262%3B%0A%7D%0A%0Aclass%20Instruction%0A%7B%0A%20%20position%202%20304%20142.413%20111.262%3B%0A%7D%0A%0Aclass%20Instruction1%0A%7B%0A%20%20position%20134%20419%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20Instruction2%0A%7B%0A%20%20position%20205%20319%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20Instruction3%0A%7B%0A%20%20position%20286%20417%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20Instruction4%0A%7B%0A%20%20position%20359%20319%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20Instruction5%0A%7B%0A%20%20position%20435%20418%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20Instruction6%0A%7B%0A%20%20position%20507%20319%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20InstructionBB%0A%7B%0A%20%20position%20580%20420%20142.413%2078.2625%3B%0A%7D%0A%0Aclass%20HaltException%0A%7B%0A%20%20position%20655%20217%20129.012%2094.2625%3B%0A%7D%0A%0Aclass%20InstructionCC%0A%7B%0A%20%20position%20652%20317%20141.4%2087.2625%3B%0A%7D%2F%2F%24%3F%5BEnd_of_model%5D%24%3F




class ALU{

    int converthexatodecimal(string hex){}

    string convertdecimaltohexa(int x){}

    string convertDecimalToBinary(){}


    string first_complement(int x, int bits){}


    string addOneToBinary(){}


    string second_complement(){}


    int convertBinaryToDecimal(){}

    

class Register{

    string reg;
  
    Register{}
    }
    void displayR(){}
    void set(string input,int index){}
    string get(int index){}
};

class Memory{
    string mem;
    ALU alu;

    Memory{}

    void readfile(){}

    void displayM(){}

    string getIR(int pc){}

    string getR(int pc){}

    void set(){}
};

class InstructionRegister{
    string ir;

    InstructionRegister{}
    void set(string instruction){}
    string get(){}
};






class Instruction{
   abstract;
    ALU alu;
    void execute(){}
};

class Instruction1{
    isA Instruction;
    void execute(){}
};

class Instruction2{
    isA Instruction;
    void execute(){}
};
class Instruction3{
    isA Instruction;
    void execute(){}
};

class Instruction4{
    isA Instruction;
    void execute(){}
};

class Instruction5{
    isA Instruction;
    void execute(){}
};

class Instruction6{
    isA Instruction;
    void execute(){}
};


class InstructionBB{
    isA Instruction;
    void execute(){}
};


class HaltException{

    noexcept(){}
};

class InstructionCC{
    isA Instruction;
    void execute() {}
};


class Machine{
    InstructionRegister ir;
    int programcounter;
    Memory memory;
    Register registers;
    int commands_counter;

public:
    Machine() : programcounter(0) , commands_counter(0){}

    void Readfile(){}

    void display(){}

    void fetch(){}

    void decode(){}

};//$?[End_of_model]$?

namespace -;


class Register
{
  position 541 226 103.537 78.2625;
}

class Memory
{
  position 92 2 154.413 180.262;
}

class Machine
{
  position 593 0 183.962 214.262;
  position.association Machine__Memory 0,70 144,49;
  position.association Machine__Register 78,129 134,0;
}

class ALU
{
  position 271 0 265.1 231.262;
}

class InstructionRegister
{
  position 4 187 150.7 112.262;
}

class Instruction
{
  position 2 304 142.413 111.262;
}

class Instruction1
{
  position 134 419 142.413 78.2625;
}

class Instruction2
{
  position 205 319 142.413 78.2625;
}

class Instruction3
{
  position 286 417 142.413 78.2625;
}

class Instruction4
{
  position 359 319 142.413 78.2625;
}

class Instruction5
{
  position 435 418 142.413 78.2625;
}

class Instruction6
{
  position 507 319 142.413 78.2625;
}

class InstructionBB
{
  position 580 420 142.413 78.2625;
}

class HaltException
{
  position 655 217 129.012 94.2625;
}

class InstructionCC
{
  position 652 317 141.4 87.2625;
}