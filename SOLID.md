# Architecture

This project was designed following Clean Architecture and SOLID principles to ensure scalability, strict type safety, and memory integrity.

## 1. Single Responsibility Principle (SRP)
**Principle:** A module should have one, and only one, reason to change.
**Implementation:**
- `Functions.cpp`: Handles Data Ingestion exclusively (raw CSV parsing, string tokenization, and stream I/O).
- `Wallet.cpp`: Handles Financial Domain Logic exclusively (state management, order execution, and ROI calculation).
- Data parsing logic is strictly decoupled from the trading algorithms, ensuring that changes in file formats do not break business rules.

## 2. Open/Closed Principle (OCP)
**Principle:** Software entities should be open for extension, but closed for modification.
**Implementation:**
- The `Wallet` hierarchy is designed for extension. New user tiers (e.g., `Institutional` or `VIP`) can be added simply by inheriting from the base class.
- The core trading engine (`makeExchanges` function) operates on the abstract interface. It remains closed to modification, requiring zero refactoring to support future account types.

## 3. Liskov Substitution Principle (LSP)
**Principle:** Objects of a superclass shall be replaceable with objects of its subclasses without breaking the application.
**Implementation:**
- The system leverages runtime polymorphism via `std::vector<std::unique_ptr<Wallet>>`.
- Derived classes (`Premium`, `Pro`) can be substituted for the base `Wallet` type anywhere in the execution pipeline without altering the correctness of the program, guaranteeing robust type safety and behavior consistency.
