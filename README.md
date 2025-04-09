# CLOX - A Tree-Walk Lox Interpreter in C

This project is an implementation of the **CLOX interpreter**, a Lox language interpreter written in C. It follows the second half of the book [*Crafting Interpreters* by Robert Nystrom](https://craftinginterpreters.com/), focusing on building a high-performance bytecode virtual machine.

## 🧠 What is Lox?

Lox is a simple, dynamically typed programming language designed for learning and teaching interpreters. It features classes, closures, garbage collection, and a readable syntax inspired by languages like JavaScript and Python.

## 📘 About This Project

This repository contains only the **C implementation (CLOX)** and **not** the Java-based tree-walk interpreter (JLOX).

The project includes:

- A scanner (lexer)
- A Pratt parser
- A bytecode compiler
- A virtual machine (VM) with an evaluation loop
- A mark-and-sweep garbage collector
- Support for closures and native functions

The code is written in pure C (C99) and is organized in a modular way to keep components like the scanner, compiler, and VM isolated and testable.

### Requirements

- A C compiler (GCC or Clang recommended)
- `make`
