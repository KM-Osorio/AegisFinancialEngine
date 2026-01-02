# Project Aegis: High-Frequency Financial Backtesting Engine 🛡️

![C++](https://img.shields.io/badge/Language-C%2B%2B20-blue)
![Build](https://img.shields.io/badge/Build-CMake-green)
![Status](https://img.shields.io/badge/Status-MVP-orange)

A high-performance simulation engine engineered to audit **tiered investor portfolios** using **exclusive ownership semantics** and **zero-copy string parsing**.

This project solves the "Speed vs. Safety" paradox in financial simulations by enforcing manual memory management through RAII principles (Smart Pointers) instead of relying on garbage collection, preventing "double-spending" bugs and object slicing.

## 📖 The Story Behind the Code
I wrote a technical case study detailing the architectural decisions (Smart Pointers vs Raw Pointers) in this project:  
👉 **Read on Medium:** [PROJECT AEGIS: Architecting a High-Frequency Backtesting System in Modern C++](https://medium.com/@katia-osorio/optimizing-for-latency-why-i-ditched-linked-lists-for-a-hybrid-c-architecture-77e14aeb64de)

## ⚡ Key Technical Features

### 1. Exclusive Ownership Architecture (`Wallet.h`)
Standard vectors slice polymorphic objects. I implemented a strict ownership model using `std::unique_ptr`:
* **Polymorphic Integrity:** Uses a factory pattern (`loadWallet`) to instantiate `Premium` vs `Standard` users dynamically without losing vtable data (commission rates).
* **No "Double Spending":** The compiler forbids copying Wallet objects, ensuring that a user's financial state exists in exactly one memory address at any given time.

### 2. Zero-Copy Data Ingestion (`Functions.cpp`)
Parsing gigabytes of CSV logs creates massive heap allocation pressure.
* **String Views:** Utilized `std::string_view` to create lightweight "windows" over the raw text buffer instead of allocating new `std::string` objects for every field.
* **Optimized Tokenization:** Custom parsing logic that outperforms standard stream operators for structured financial data.

### 3. O(1) Sliding Window Algorithm
For the Moving Average Crossover strategy, standard vectors incur O(N) costs when shifting elements.
* **Deque Implementation:** Replaced `std::vector` with `std::deque` for the signal buffer.
* **Constant Time Complexity:** Allows **O(1)** insertion at the back and removal from the front, essential for high-frequency signal updates.

## 🛠️ Tech Stack
* **Language:** C++20 (Smart Pointers, String View, Deque, Inheritance).
* **Build System:** CMake.
* **Architecture:** Polymorphic Factory Pattern & Data-Oriented Design.

## 🚀 How to Build and Run

This project uses **CMake**. Ensure you have a C++ compiler (GCC/Clang/MSVC) installed.

```bash
# 1. Clone the repository
git clone [https://github.com/KM-Osorio/Project-Aegis.git](https://github.com/KM-Osorio/Project-Aegis.git)
cd Project-Aegis

# 2. Create build directory
mkdir build
cd build

# 3. Configure and Build
cmake ..
cmake --build .

# 4. Run the simulation
./Project_Aegis
