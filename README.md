## c_budget

c_budget is a simple command line app which stores transactions in a file called budget.txt. Take a look at the budget.txt file to see the structure of the data storage system.

With c_budget, you can create a new transaction, read all transactions, update a transaction, or delete a transaction.

To compile and link c_budget's source files, I am using GCC and Make. You can compile c_budget using the following steps:

1. Download all the source files and the makefile into your chosen directory.
2. Point your terminal to the directory.
3. Use the makefile included with c_budget to compile and link the source files.
4. If you have installed Make, run the following command: make c_budget

I plan to use various data structures to improve c_budget. I am rebuilding c_budget in the following order (please see my other repositories for various versions of c_budget):

1. c_budget (original)
2. c_budget_2d_array
3. c_budget_array_of_structures
4. c_budget_dynamic_strings
5. c_budget_linked_list
6. c_budget_ordered_list

There are some problems when the app is run in Windows. These problems have been resolved in subsequent versions of the app (see above). The problem is that the update and delete operations do not work on Windows. It has something to do with writing the new information to the temp file and removing the original budget.txt file. The program correctly writes the updated information to the temp_budget.txt file but can't remove the original file and rename the temporary file for some reason on Windows.

I compile c_budget on Windows using the followign command:

- cl -W4 c_budget c_budget.c c_budget_crud_operations.c c_budget_menus.c c_budget_read_input.c c_budget_validation.c -link -out:c_budget.exe
