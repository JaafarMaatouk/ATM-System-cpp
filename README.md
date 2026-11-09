# ATM System (C++)

A fully functional console-based ATM (Automated Teller Machine) system built in C++. The application simulates real-world banking operations, featuring a secure login system and persistent data storage using text files.

## 🎮 Features
- Secure Login: Users must enter a valid Account Number and PIN Code to access the system.
- Main Menu Options:
  - Quick Withdraw: Fast cash withdrawal (20, 50, 100, 200, 400, 600, 800, 1000).
  - Normal Withdraw: Custom withdrawal amount (must be a multiple of 5).
  - Deposit: Add funds to the account.
  - Check Balance: View current account balance.
  - Logout: Safely exit to the login screen.
- Data Persistence: Reads and saves client data (balances, PINs, etc.) to a local Client.txt file, ensuring data is not lost when the program closes.
- Input Validation: Prevents invalid withdrawals and ensures sufficient balance.

## 🛠️ Technical Details
- Uses struct to represent client data.
- Implements vector and file streams (fstream) to manage and update records dynamically.
- Uses enum for clean and readable menu navigation.
- Separates logic into modular functions for maintainability.

## 🚀 How to Run
1. Clone this repository or download it as a ZIP file.
2. Open the .sln file in Visual Studio.
3. Ensure the Client.txt file is in the same directory as the executable (or create it with sample data).
4. Press F5 or Ctrl + F5 to build and run the program.

## 📄 License
This project is open-source and available under the MIT License.
