# ATM System Using Verilog

This repository hosts a project focusing on the development and testing of an Automated Teller Machine (ATM) system using Verilog. It showcases the application of digital design and simulation techniques to model an ATM system, reflecting both functional and non-functional requirements.

## Project Overview

The ATM system implemented in Verilog simulates real-world ATM operations and incorporates various features to ensure a comprehensive understanding of electronic design principles. This project includes both the reference model in C++ and the fully implemented Verilog model with extensive test coverage.

### Features

- **Authentication**: The system validates user credentials against a stored database to grant access.
- **Transaction Processing**: Supports basic transactions such as deposits, withdrawals, and balance inquiries.
- **Session Handling**: Manages user sessions to ensure security between transactions.
- **Data Management**: Utilizes a database file (`atm_database.txt` for Verilog and `atm_database.csv` for C++) to manage user data.
- **Testing and Coverage**: Includes a detailed testbench (`atm_test_new.sv`) that simulates various operational scenarios to ensure the robustness of the ATM system.

## Project Structure

- **Project (1) Report.pdf**
  - A comprehensive report detailing the design process, implementation, and testing outcomes.

### Reference Model

- **atm_database.csv**
  - Database file used by the reference model in C++.
- **main.cpp**
  - Implements the ATM logic in C++.
- **outputs_cpp.txt**
  - Outputs from the C++ program execution.

### Verilog Code

- **atm.v**
  - Verilog implementation of the ATM system.
- **atm_database.txt**
  - Database file for the Verilog model.
- **atm_test_new.sv**
  - SystemVerilog testbench for the ATM design.
- **Coverage Report.txt**
  - Details on test coverage.
- **Output File.txt**
  - Simulation results.

## Setup and Running Instructions

### C++ Reference Model
Compile and run the C++ reference model by using the following commands in the `Reference Model` directory:
```bash
g++ -o atm main.cpp
./atm
```
Results are stored in `outputs_cpp.txt`.

### Verilog Model
To execute the Verilog model, use a Verilog simulator such as ModelSim or Icarus Verilog. Navigate to the `Verilog Code` directory and execute:
```bash
iverilog -o atm_simulation atm.v atm_test_new.sv
vvp atm_simulation
```
Check `Output File.txt` and `Coverage Report.txt` for simulation results and coverage details, respectively.
