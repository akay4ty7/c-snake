# C Snake
## Project Goal
Snake is a classic game with simple rules: move, eat, grow, don't collide. I wanted to implement it in C as a way to work on a project with enough scope to require real organisation of multiple files, a build system, and decisions about architecture. The game runs entirely in the terminal using **termios** for input handling and cursor control. Rather than redrawing the entire screen each frame, I update only the cells that change (snake head, tail, food). This keeps the rendering lightweight and avoids the flickering that comes with full-screen clears.

**Interesting Knowledge Gained:**
- Makefile construction: Setting up a proper build system for a multi-file C project.
- Project organisation: Splitting logic across files in a way that keeps things maintainable as scope grows.
- Selective rendering: Updating only what changes rather than redrawing everything—a small optimisation that makes the output noticeably cleaner.
- Scope management: Recognising when to stop adding features and call something complete.

This project was small in concept but valuable in practice. It reinforced that strong fundamentals in memory layout, terminal control and build tooling can open up a lot of possibilities.
## Demo
![snake](https://github.com/user-attachments/assets/d6cfdd22-1b76-4b2c-940f-796fc8cd6658)
## Prerequisites
- C compiler (gcc or similar)
- make
- Linux/Unix system (termios dependency)
## Build
```bash
make
```
## Run
```bash
./game
```
