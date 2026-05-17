# 📚 Quiz Game - Data Structures Implementation

<div align="center">

![C](https://img.shields.io/badge/language-C-555555?style=flat-square&logo=c)
![Data Structures](https://img.shields.io/badge/cs-Data%20Structures-2ecc71?style=flat-square)
![Academic](https://img.shields.io/badge/type-Academic%20Project-3498db?style=flat-square)
![Status](https://img.shields.io/badge/status-Completed-9b59b6?style=flat-square)

</div>

---

## 📖 Project Overview

A comprehensive quiz game application built in **C** that demonstrates practical implementation of core data structures concepts. This project was developed as a final assignment for the **Data Structures** course, showcasing fundamental operations like linked list traversal, stack manipulation, and dynamic memory management in a real-world interactive application.

The application features an interactive quiz system with multiple difficulty levels, timed questions, dynamic scoring, and student performance tracking.

---

## 🧠 Data Structures Showcase

This section demonstrates how theoretical data structure concepts are applied in real-world programming:

### 1. Linked List - Question Storage

```
┌─────────────┐      ┌─────────────┐      ┌─────────────┐
│   HEAD      │      │   Node 1    │      │   Node 2    │
│  (pointer)  │─────▶│  Question 1 │─────▶│  Question 2 │
└─────────────┘      └─────────────┘      └─────────────┘
                           │
                           ▼
                    ┌─────────────┐
                    │   Node 3    │
                    │  Question 3 │
                    └─────────────┘
```

**Implementation Details:**
- **Structure**: `QuestionList` with `head` pointer
- **Node Data**: Question text, difficulty level (EASY/MEDIUM/HARD), correct answer, question number
- **Operations Used**:
  - `insert_at_end()` - Adding questions to the list
  - `insert_at_end_ALL()` - Moving nodes between lists
  - Traversal with `temp->next` for sequential access
- **Memory**: Dynamic allocation using `calloc()`

### 2. Stack - Answer Tracking

```
    PUSH Operation                  POP Operation
    ┌─────────────┐                 ┌─────────────┐
    │  New Answer │                 │             │
    └──────┬──────┘                 └──────┬──────┘
           │                                   │
           ▼                                   ▼
┌───┬───┬───┬───┐                   ┌───┬───┬───┬───┐
│ A │ B │ C │ D │   ───────────►    │ A │ B │ C │   │
└───┴───┴───┴───┘                   └───┴───┴───┴───┘
 TOP: D                              TOP: C
```

**Implementation Details:**
- **Structure**: `AnswerNode` with `next` pointer (LIFO - Last In First Out)
- **Node Data**: Question index, student's answer, score achieved
- **Operations Used**:
  - `push_answer()` - Push student's answer onto stack
  - `pop_answer()` - Pop answers to calculate final score
- **Application**: Score calculation and answer history tracking

### 3. Array - Student Records

```
┌──────────────────────────────────────────────────────────┐
│  Student Database (Fixed Array - 10 students)           │
├──────────────┬──────────────┬─────────────┬──────────────┤
│    Name      │    Score    │ Rate Score  │   Status     │
├──────────────┼──────────────┼─────────────┼──────────────┤
│  Student 1   │     180     │      3      │   PASSED     │
│  Student 2   │     120     │      2      │   FAILED     │
│  Student 3   │     165     │      3      │   PASSED     │
│     ...      │     ...     │     ...     │     ...      │
└──────────────┴──────────────┴─────────────┴──────────────┘
```

**Implementation Details:**
- **Structure**: `Student` array with fixed size (10 students)
- **Data**: Name (max 25 chars), score, rate_score multiplier
- **Operations**:
  - Array indexing for direct access
  - Element removal with array shifting

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| 🎯 **Three Difficulty Levels** | Easy, Medium, and Hard questions stored in separate linked lists |
| ⏱️ **Timed Questions** | 15-second countdown per question using `gettimeofday()` |
| 📊 **Dynamic Scoring** | Score multiplier increases with correct answers (1x → 3x) |
| 🎲 **Randomized Questions** | Questions are randomly selected from each difficulty pool |
| 📈 **Student Dashboard** | Track all students' scores and pass/fail status |
| 🧮 **Stack-Based Calculation** | Final score computed via stack pop operations |
| 📖 **Built-in Guidebook** | Help documentation loaded from external text file |
| 🎨 **ASCII Art UI** | Visual feedback for correct/incorrect answers |

---

## 🛠️ Technical Implementation

### Architecture
```
┌─────────────────────────────────────────────────────────────┐
│                        main.c                               │
│                  (Entry Point & Logic)                      │
└───────────────────────┬─────────────────────────────────────┘
                        │
        ┌───────────────┼───────────────┐
        ▼               ▼               ▼
┌──────────────┐ ┌──────────────┐ ┌──────────────┐
│    menu/     │ │ quiz_related/│ │   usecase/   │
│   (UI/UX)    │ │   (Timer)    │ │  (Business   │
│              │ │              │ │    Logic)    │
└──────────────┘ └──────────────┘ └──────────────┘
```

### Key Technical Highlights
- **Modular Design**: Separate header/source files for menu, timer, and quiz operations
- **File I/O**: Reading questions and answers from external `.txt` files
- **Memory Management**: Proper allocation (`calloc`) and deallocation (`free`)
- **Makefile Build System**: Automated compilation with `gcc`
- **Cross-platform Considerations**: Uses conditional compilation for Windows (`windows.h`)

### Data Flow
```
External Files ──► Linked List ──► Question Display ──► Stack (Answers)
                      │                                     │
                      ▼                                     ▼
                Random Selection                    Score Calculation
                      │                                     │
                      ▼                                     ▼
                User Input ◄────────────────────── Final Result
```

---

## 📁 Project Structure

```
QUIZ_GAME/
├── README.md                 # This file
├── Makefile                  # Build configuration
├── LICENSE                   # Project license
├── src/
│   ├── main.c               # Entry point & core logic
│   └── usecase/             # Business logic modules
│       ├── menu/            # Menu operations
│       ├── questions/       # Question handling
│       ├── answers/        # Answer stack operations
│       ├── score/          # Score calculations
│       └── students/       # Student management
├── utils/
│   ├── menu/               # UI utilities
│   │   ├── print_collections.c/h
│   │   └── color.c/h
│   └── quiz_related/       # Quiz utilities
│       ├── timer.c/h
│       └── result_display.c/h
├── docs/                   # Data files
│   ├── quiz_related/
│   │   ├── questions/
│   │   │   ├── 1_beginner.txt
│   │   │   ├── 2_intermediate.txt
│   │   │   └── 3_advanced.txt
│   │   └── answers/
│   │       ├── 1_beginner.txt
│   │       ├── 2_intermediate.txt
│   │       └── 3_advanced.txt
│   └── guidebook/
│       └── help.txt
└── tasks/
    └── tasks.md           # Project task tracking
```

---

## 🚀 Getting Started

### Prerequisites
- **Compiler**: GCC (GNU Compiler Collection)
- **Operating System**: Windows (for full compatibility) or Linux/Unix
- **Build Tools**: Make (for Makefile usage)

### Build Instructions

**Using Makefile:**
```bash
# Compile the project
make

# Run the executable
./bin/main.exe

# Clean build artifacts
make clean
```

**Manual Compilation:**
```bash
# Compile all source files
gcc -Wall -Wextra -c src/main.c -o obj/main.o
gcc -Wall -Wextra -c utils/menu/print_collections.c -o obj/print_collections.o
gcc -Wall -Wextra -c utils/quiz_related/timer.c -o obj/timer.o

# Link object files
gcc -Wall -Wextra obj/main.o obj/print_collections.o obj/timer.o -o bin/main.exe
```

### Running the Program
After successful compilation, run `bin/main.exe` and follow the on-screen menu:
1. **Option A**: Start Quiz → Enter your name → Answer questions
2. **Option B**: View Guide Book
3. **Option C**: View Student Report
4. **Option Q**: Quit

---

## 🎓 Skills Demonstrated

### Technical Skills
| Skill | Application |
|-------|-------------|
| **Linked List** | Question storage and traversal |
| **Stack** | Answer tracking and score calculation |
| **Dynamic Memory** | Runtime allocation with `calloc()`/`free()` |
| **File I/O** | Reading questions from external files |
| **Modular Programming** | Separate header/source files |
| **Makefile** | Automated build system |
| **Time Handling** | Timer implementation with `gettimeofday()` |
| **Debugging** | ASCII art and error handling |

### Soft Skills
- **Problem Solving**: Designing data structures for real-world application
- **Code Organization**: Maintaining clean, modular architecture
- **Documentation**: Comprehensive README and inline comments
- **Self-Learning**: Implementing features from scratch using C standard library

---

## 👤 Author Information

| Field | Details |
|-------|---------|
| **Name** | Daniel Adi Pratama |
| **NIM** | 4.33.23.0.07 |
| **Class** | TI-1A |
| **Course** | Struktur Data (Data Structures) |
| **Lecturer** | Eri Eli Lavindi, M.Kom. |
| **Institution** | Politeknik Negeri Semarang |

---

## 📄 License

This project is for educational purposes and is open for learning and modification.

---

<div align="center">

*Built with ❤️ using C and Data Structures*

</div>
