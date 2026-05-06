# 🏥 Smart Hospital Management System (C++)

A high-performance system designed to manage patient flow using **Data Structures (DSA)**. It ensures that critical patients are treated first while maintaining records permanently.

## 🚀 Key Technical Features
- **$O(1)$ Complexity:** Uses an `unordered_map` (Hash Map) for instant patient lookup and cancellation.
- **Triage Logic:** Implements an Array of Queues to prioritize patients (Critical > Serious > Normal).
- **Data Persistence:** Automatically saves and loads data from a `hospital_records.csv` file.
- **Robustness:** Handles invalid inputs using C++ Exception Handling concepts.

## 🛠️ Data Structures Used
- **Hash Map (`std::unordered_map`):** For constant time indexing.
- **Queues (`std::queue`):** For FCFS (First-Come-First-Served) scheduling within priority levels.
- **File I/O (`fstream`):** For permanent database management.

## 💻 How to Run
1. Download `hospital_system.cpp`.
2. Compile using any C++ compiler (e.g., `g++ hospital_system.cpp -o hospital`).
3. Run the executable.
