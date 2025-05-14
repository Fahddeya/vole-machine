# Vole Machine Simulation

This project is a C++ simulation of a Vole Machine, a simple computer architecture.
It features a 256-byte memory, 16 general-purpose registers, and an Arithmetic Logic Unit (ALU) capable of various operations including integer arithmetic (2's complement), logical operations (AND, OR, XOR), and bit rotation.

The machine loads its program from a user-specified file containing hexadecimal machine code. Each instruction is 4 hex digits long.

## Getting Started

These instructions will help you compile and run the Vole Machine simulation on your local machine.

### Prerequisites

You will need a C++ compiler that supports C++11 or later (due to features like `stoi`, `to_string`, and standard library headers like `<bits/stdc++.h>` which is a common GNU extension).

- **GCC (GNU Compiler Collection):** A popular open-source compiler.
  ```bash
  # Example for Debian/Ubuntu
  sudo apt-get update
  sudo apt-get install build-essential g++
  ```
- **Clang:** Another widely used C++ compiler.
- **MSVC (Microsoft Visual C++):** If you are on Windows and using Visual Studio.

### Installing & Running

1.  **Clone the repository (if applicable) or download the source files.**

    ```bash
    # git clone <repository-url>
    # cd <project-directory>
    ```

2.  **Compile the source code.**
    The primary files for the simulation appear to be `MyMachine.h`, `MyMachine.cpp`, and a `main.cpp` file that instantiates and runs the `Machine` from `MyMachine.h`. You'll need to create a `main.cpp` that uses the `Machine` class from `MyMachine.h` or adapt the existing one.

    A general compilation command using g++ would look like this (assuming your main file is `main.cpp` and it uses `MyMachine.cpp`):

    ```bash
    g++ main.cpp MyMachine.cpp -o vole_simulation -std=c++11
    ```

    _(You might need to adjust this command based on your project structure and chosen main file.)_

3.  **Prepare an input file.**
    The simulation expects an input file containing hexadecimal machine code. Each instruction should be on a new line or separated by spaces, represented as 4 hexadecimal characters. For example:

    ```
    201A  // Load register 0 with immediate value 1A
    2105  // Load register 1 with immediate value 05
    5201  // Add R0 and R1, store in R2 (R2 = R0 + R1)
    3200  // Store R2 to memory address 00 (and print to screen)
    C000  // Halt
    ```

4.  **Run the simulation.**
    Execute the compiled program. It will prompt you for the name of the input file.
    ```bash
    ./vole_simulation
    ```
    Then, when prompted, enter the name of your machine code file.

## Running the tests

Explain how to run the automated tests for this system.

### Break down into end-to-end tests

Explain what these tests test and why.

```
Give an example
```

### And coding style tests

Explain what these tests test and why.

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system.

## Built With

_(This section can be used to list major libraries or tools if any are central to your project, otherwise, it can be removed if not applicable for a C++ simulation.)_

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

- **[Your Name/Handle]** - _Initial work_ - [Link to your profile if desired]

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

- Hat tip to anyone whose code was used
- Inspiration
- etc
