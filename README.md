# 🛡️ Project Aegis: High-Frequency Trading Backtester Engine

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![Docker](https://img.shields.io/badge/Docker-Enabled-2496ED?style=flat&logo=docker)
![Status](https://img.shields.io/badge/Status-Prototype-orange)

**A high-performance financial backtesting engine built in modern C++ (C++17) designed to simulate and analyze algorithmic trading strategies with historical market data.**

This engine processes large datasets of OHLCV (Open, High, Low, Close, Volume) candles, manages multi-tiered user portfolios with dynamic commission structures, and generates detailed financial performance reports.

---
## 📖 The Story Behind the Code
I wrote an article detailing the engineering challenges and optimizations in this project:  
👉 **[Read on Medium: 4 Ways I Sabotaged My High-Performance C++ Engine](https://medium.com/@katia-osorio/881e98626225)**

---

## 🚀 Key Features

* **⚡ High Performance:** Optimized for low latency using `std::string_view` for zero-copy string parsing and efficient memory management.
* **🏗️ Architecture:** Implements **RAII** principles and **Smart Pointers** (`std::unique_ptr`) for robust resource management and leak prevention.
* **🧩 Polymorphic Wallet System:** Supports multiple user tiers (Premium, Pro, Standard) with distinct fee structures and commission logic using inheritance and polymorphism.
* **📊 Financial Analytics:** Calculates real-time ROI (Return on Investment), PnL (Profit and Loss), and transaction metrics.
* **🐳 Dockerized:** Fully containerized environment ensuring reproducibility and easy deployment across different platforms.

---

## 🛠️ Tech Stack

* **Language:** C++17
* **Build System:** CMake
* **Containerization:** Docker
* **Paradigm:** Object-Oriented Programming (OOP)
* **Data Format:** CSV (Comma-Separated Values) processing

---

## 📂 Project Structure

    AegisFinancialEngine/
    ├── src/
    │   ├── main.cpp         # Entry point of the simulation
    │   ├── Wallet.cpp       # Implementation of wallet logic and trading execution
    │   └── Functions.cpp    # Data parsing, file I/O, and report generation utilities
    ├── include/
    │   ├── Wallet.h         # Base class and derived classes (Premium, Pro, Standard)
    │   ├── Types.h          # Data structures (Candle, UserData)
    │   └── Utils.h          # Utility headers and dependencies
    ├── data/
    │   ├── Bitcoin Historical Data.csv  # Historical market data (OHLCV)
    │   └── Users.csv                    # User portfolio configurations
    ├── outputFiles/
    │   └── monthlyReport.txt            # Generated performance report
    ├── Dockerfile           # Container configuration
    └── CMakeLists.txt       # Build configuration

---

## ⚙️ How to Run
### Manual Build (CMake)

Requirements: C++ Compiler (GCC/Clang/MSVC) and CMake.

    mkdir build
    cd build
    cmake ..
    cmake --build .
    ./AegisFinancialEngine

---

## 📊 Sample Output

The engine generates a detailed report in `outputFiles/monthlyReport.txt`.

  ===================================================================================================================
                                                Performance Monthly Report
    ===================================================================================================================
     USER                                CATEGORY     INITIAL BALANCE    FINAL BALANCE      OPS      ROI       REVENUE
    ===================================================================================================================
     Larriega Velasquez Moises Roberto   Pro          $23326.62          $25029.25          10       7.30%     $592.73
     Valverde Pinto Edilberto            Standard     $4986.02           $5217.86           10       4.65%     $250.23
     Moscoso Laura Janet Valentina       Premium      $41935.70          $45905.62          10       9.47%     $215.28
     ...                                 ...          ...                ...                ...      ...       ...
    -------------------------------------------------------------------------------------------------------------------
                                                      $1532109.96        $1665997.60        770                $18297.20
    ===================================================================================================================
     METRIC ANALYSIS
           • Total Monthly Revenue: $18297.20 USD
           • Total Operations: A total of 770 buy/sell transactions were executed
           • Top Performer: The user Escalante Vergel Nestor Manuel achieved the highest margin with 9.47%
    ===================================================================================================================

---

## 🧠 Design Decisions

* **Why `std::unique_ptr`?** To handle the ownership of `Wallet` objects explicitly. Since wallets are unique to users and shouldn't be copied, unique pointers ensure safe memory deallocation without the overhead of garbage collection or manual `delete`.
* **Why `std::string_view`?** In high-frequency trading simulations, parsing millions of lines of CSV data can be a bottleneck. `string_view` allows us to read and tokenize strings without creating expensive temporary copies.

---

## 👤 Author

**Katia**
* Computer Engineering Student at PUCP
* [(https://www.linkedin.com/in/katia-osorio-dev/)]
---

**Disclaimer:** This project is for educational and simulation purposes only. It does not constitute financial advice.
