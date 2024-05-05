# c_budget
c_budget is a simple command-line or terminal budget app.

c_budget is designed to take data from a text file as input. The output of c_budget is simply a few tables displaying some useful budget summary figures.

Importantly, the input file must contain data formatted precisely like the data is formatted in the budget_data_sample.txt file included in this repository (the data does not have to be sorted by date). Also included in this repository is a picture of the output of a successful session with the c_budget program.

To build and use c_budget on Windows, complete the following steps:
1. Download c_budget's source files into your chosen directory.
2. Ensure you have Visual Studio installed or the Build Tools for Visual Studio and the optional Desktop development with C++ workload.
3. Open the Developer Command Prompt for VS 2022.
4. cd to the directory containing c_budget's program files. For example,
   -  cd C:\Users\User\c_budget
5. Compile c_budget by typing the following:
   -  cl -W4 c_budget.c program_init.c validate_budget_line.c get_data.c budget_calculations.c print_budget_figures.c -link -out:c_budget.exe
7. Run c_budget by typing one of the following commands (note, if you do not include a file name after typing the program name into the command prompt, the default data file will be used, if possible. The default data file name is defined in a macro in the program code):
   -  c_budget
   -  c_budget my_budget_data.txt

To build and use c_budget on Linux, complete the following steps:
1. Download c_budget's source files into your chosen directory.
2. Ensure you have gcc installed.
3. cd to the directory containing c_budget's program files. For example,
   -   cd /home/user/c_budget
4. Compile c_budget by typing the following:
   -   gcc -g -Wall -Wextra -O -W -pedantic -ansi -std=c89 c_budget.c program_init.c validate_budget_line.c get_data.c print_budget_figures.c budget_calculations.c -o c_budget
5. Run c_budget by typing one of the following commands (note, if you do not include a file name after typing the program name into the command prompt, the default data file will be used, if possible. The default data file name is defined in a macro in the program code):
   -   ./c_budget
   -   ./c_budget my_budget_data.txt
