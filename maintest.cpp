#include "MyMachine.h"
#include<bits/stdc++.h>


using namespace std;



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