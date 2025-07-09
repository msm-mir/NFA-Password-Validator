# 🔐 Password Validator Using NFA

This project uses a **Non-deterministic Finite Automaton (NFA)** to validate the strength of user-entered passwords. The program checks whether a password is valid based on a set of customizable rules and simulates the NFA's transitions to determine the result. Also it is implemented in **C++** as part of a Theory of Automata and Formal Language course and based on an object-oriented programming (OOP).

---

## 💡 Features

- Takes custom rules from the user to define password requirements.
- Rules include: minimum number of upercase letters, lowercase letters, digits, and special characters.
- Reads the password and checks its validity using NFA.
- Displays the NFA transition table.
- Shows the transition steps of the NFA as it reads the password.
- Outputs whether the password is valid or not.

---

## 🛠 Technical Details

- Implemented in **C++**
- The core concept of the project is based on **NFA** (Non-deterministic Finite Automaton)
- Input and output are handled through the **console**

---

## 📁 Project Structure

```
/PasswordValidatorProject
├── main.cpp
├── StateType.h
├── TransitionType.h
├── NFA.h / .cpp
├── State.h / .cpp
└── README.md
```

---

## 🚀 How to Run

- Make sure the compiler is set to support C++17 or later
- Run the program in a terminal or console window for better visibility of the output

---

## 👨‍💻 Author
- Developed as part of a C++ Theory of Automata and Formal Language course project
