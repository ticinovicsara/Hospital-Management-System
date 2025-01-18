# Hospital Management System

This project is a simple **Hospital Management System** developed in **C**, created as part of a seminar project at the Faculty of Electrical Engineering, Mechanical Engineering, and Naval Architecture (FESB) in Split. The system simulates essential hospital operations such as managing patients, doctors, and emergency cases using **Abstract Data Types (ADT)** and **Data Structures**.

---

## Features

### 1. Patient Management
- **Add Patient**: Allows users to add new patient records to the system.
- **Search Patient**: Search for patients by their **ID** or **surname** to access detailed patient information.
- **Delete Patient**: Removes patient records from the system.

### 2. Doctor Management
- **Add Doctor**: Allows users to add doctors to the system along with their details (name, surname, specialization, available appointment slots).
- **Search Doctor by Name**: Search for doctors by **name** and **surname**.
- **Search Doctor by Specialization**: List doctors based on their **specialization**.
- **Delete Doctor**: Remove doctors from the system.

### 3. Emergency Case Management
- **Add Emergency Case**: Users can add new emergency cases with a **description** and **priority** (where lower numbers represent higher priority). Each emergency case is linked to an existing patient.
- **View Emergency Cases**: View active emergency cases sorted by priority.

---

## Data Structures Used
- **Linked Lists**: Used for managing lists of doctors and patients.
- **Binary Search Tree (BST)**: Used to organize doctors based on their specialization, allowing for efficient searching and insertion.
- **Hash Table**: A hash table is used to store and retrieve patient records efficiently.
- **Priority Queue**: A priority queue is used to manage emergency cases, ensuring that the most critical cases are prioritized.

---

## Functional Overview
- The system provides an interactive **menu-based interface** that allows users to:
  - Add, delete, and search for patients and doctors.
  - Manage emergency cases by viewing and adding them with priority levels.
  
- **Efficient Searching**: Utilizes various data structures to provide fast searching and management of data (e.g., doctors are organized in a binary search tree by specialization, and patients are stored in a hash table for quick lookups).

- **Emergency Case Management**: Emergency cases are handled through a priority queue, ensuring that more urgent cases are dealt with first.

---

## Getting Started

### Prerequisites
- A C compiler (e.g., GCC) is required to compile and run this project.

### Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/hospital-management-system.git

2. Navigate to the repository and compile using:
   ```bash
   make

3. To run the project, type command:
   ```bash
   ./hospital




