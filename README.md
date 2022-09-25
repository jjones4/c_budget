## c_budget

c_budget is a simple command line budget app which stores transaction information in a file called budget.txt.

Take a look at the budget.txt file to see the structure of the data storage system.

With c_budget, you can create a new transaction, read all transactions, update a transaction, or delete a transaction.

To compile and link c_budget's source files, I am using GCC and Make.

First, download all the source files into your chosen directory.

Next, point your terminal to the directory.

Then, use the makefile included with c_budget to compile and link the source files.

If you have Make, you can compile andl ink c_budget by running the following command at the terminal:

- make c_budget

Planned improvements to c_budget include using linked lists instead of character arrays to handle the data.

I am also debugging the problems I am having when I compile c_budget on Windows. I am using the followign command:

- cl -W4 c_budget c_budget.c c_budget_crud_operations.c c_budget_menus.c c_budget_read_input.c c_budget_validation.c -link -out:c_budget.exe

However, the update and delete operations do not work on Windows. It has something to do with writing the new information to the temp file and removing the original budget.txt file. The program correctly writes the updated information to the temp_budget.txt file but can't remove the original file and rename the temporary file for some reason on Windows.

