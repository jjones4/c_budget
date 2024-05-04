# c_budget
c_budget is a command line app built to be compiled and run on a Windows machine.

c_budget is designed to take data from a text file as input. The output of c_budget is simply a few tables displaying some useful budget figures.

Importantly, the data file must contain data formatted precisely like the data is formatted in the budget_data_sample.txt file, included in this repository (the data does not have to be sorted by date). Also included in this repository is a picture of the output of a successful session with the c_budget program.

To use c_budget, first cd to the directory containing c_budget's executable file. For example,

- cd C:\Users\User\c_budget

Next, run c_budget by typing one of the following commands:

1. c_budget
2. c_budget my_budget_data.txt

If you do not include a file name after typing the program name into the command prompt, the default data file will be used, if possible. The default data file name is defined in a macro in the program code.
