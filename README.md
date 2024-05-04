# c_budget
c_budget is a command line app built to be compiled and run on a Windows machine.

c_budget is designed to take data from a text file as input. The output of c_budget is simply a few tables displaying some useful budget figures.

Importantly, the data file must contain data formatted precisely like the data is formatted in the budget_data_sample.txt file, included in this repository (the data does not have to be sorted by date). Also included in this repository is a picture of the output of a successful session with the c_budget program.

To use c_budget, complete the following steps:
1. Download c_budget's source files into your chosen directory.
2. Ensure you have Visual Studio installed or the Build Tools for Visual Studio and the optional Desktop development with C++ workload.
3. Open the Developer Command Prompt for VS 2022.
4. cd to the directory containing c_budget's program files. For example,
   -  cd C:\Users\User\c_budget.
5. Compile c_budget by typing the following:
   -  cl -W4 c_budget.c program_init.c validate_budget_line.c get_data.c budget_calculations.c print_budget_figures.c -link -out:c_budget.exe
7. Run c_budget by typing one of the following commands:
   -  c_budget
   -  c_budget my_budget_data.txt

If you do not include a file name after typing the program name into the command prompt, the default data file will be used, if possible. The default data file name is defined in a macro in the program code.
