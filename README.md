# Project-Banking-System
Author : Utsojet Paticor
Roll : 22 CSE 017

Documentation for the Banking System Project:

1. Introduction:
The Banking System Project is a simple console-based application written in C, designed to simulate a basic banking system. It allows users to create accounts, log in, perform various banking transactions, and keep track of their account history. This documentation provides an overview of the project's features, functionality, and code structure.

3. Project Structure:
- The project consists of a single C source file.
- It includes standard C libraries like `<stdio.h>`, `<string.h>`, and `<stdlib.h>` for various functionalities.
- 
3. Key Components:
The project comprises several key components:

  File Handling:
  - It uses file handling to store account data and transaction history.
  - Account data is stored in a file called `acountDatabase.txt`, and each account's transaction history is stored in separate files named after their account numbers (e.g., `12345.txt`).
  - The project provides functions to read and update these files.

  User Accounts:
  - Users can create accounts by specifying their account number, name, and password.
  - Account information is stored in the `acountDatabase.txt` file.

  Login System:
  - Users can log in using their account number and password.
  - The project verifies user credentials from the `acountDatabase.txt` file.

  Bank Capital Management:
  - The project maintains a bank capital balance stored in the `bankCapital.txt` file.
  - Users can deposit, withdraw, or take loans, and the bank's capital is adjusted accordingly.

  Transactions:
   - Users can perform the following types of transactions:
     - Deposit money.
     - Withdraw money.
     - Transfer money to other accounts.
     - Receive transfers from other accounts.
     - Take loans.

  Transaction History:
  - The project keeps a record of each account's transaction history in separate text files.

4. Functions:

The project contains several functions, each responsible for specific tasks:

- setGetBankCapital: Manages the bank's capital and returns the updated balance.

- searchDB: Searches for a specific account in the account database.

- getDetailsDB: Retrieves account details, including name, balance, and password, from the account database.

- editAcountDatabase: Updates account balances in the account database after deposits or withdrawals.

- updateStatement: Updates the transaction history for an account.

5. Main Menu:

The main menu allows users to perform various actions, including creating accounts, logging in, depositing, withdrawing, transferring funds, taking loans, viewing transaction history, checking account balances, and logging out.

6. Usage:

- To create an account, choose option 1 from the menu and provide account details.
- To log in, select option 2 and enter the account number and password.
- Once logged in, you can use options 3 to 8 to perform different transactions.
- Option 7 allows you to view your transaction history.
- Option 8 displays your account balance.
- To log out, select option 9.

7. Error Handling:
The project includes error handling for various scenarios, such as file I/O errors and insufficient funds during withdrawals.

8. Future Improvements:
This project is a simplified representation of a banking system and can be further enhanced with the following improvements:

- Improved error handling and user feedback.
- Enhanced security measures.
- More detailed transaction history.
- Support for multiple users and concurrent transactions.
- User-friendly interfaces.

9. Conclusion:
The Banking System Project is a basic yet functional simulation of a banking system. It demonstrates the use of file handling, user authentication, and transaction management in a simple console-based application. Further development and improvements can be made to enhance its functionality and usability.
