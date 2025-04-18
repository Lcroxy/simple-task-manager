# 🛠️ Simple Task Manager in C++

A simple yet functional task manager made in C++ using JSON for saving tasks. This is my personal project to practice programming, learn more about file handling, and improve my logic through something real and usable.

> ⚡ This is just the beginning. I will keep adding new features over time.

## ✨ Features

- Add new tasks with a title and description
- View all saved tasks
- Remove a specific task
- Data is saved in a JSON file (`list.json`)
- Works on both Windows and Linux (auto clear screen)

## 📁 How It Works

Tasks are stored in a local `list.json` file using the [nlohmann/json](https://github.com/nlohmann/json) library (already included in the `include/` folder).
The program reads and writes to this file every time you interact with the task manager.

## 🔧 Requirements

- C++11 or higher
- g++ or any other compatible C++ compiler
- Terminal access

## 🚀 Running the Project

Clone or download the project and compile:

```bash
g++ main.cpp -o task_manager

Then run it:

./task_manager

For Windows:

task_manager.exe

## 📌 Project Structure
makefile
.
├── include/
│   └── json.hpp         # JSON library
├── main.cpp             # Main code file
├── list.json            # Tasks are saved here
├── LICENSE              # MIT License
└── README.md            # You’re reading it :)

## 📈 Future Plans

I will continue updating this project by adding more features and improvements as I learn more. The current version is stable and works as intended, but it's only the beginning.

## 🧠 Why This Project?

Since I was a kid, I loved taking things apart — from RC cars to LEDs — just to see how they worked. I always felt curious about electronics, robotics, and later programming.
This project brings together that curiosity and my passion for building things with code. It’s simple, but it works — and it’s mine.



