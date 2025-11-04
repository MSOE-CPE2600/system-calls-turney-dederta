# Lab 9 - System Calls
**Course:** CPE 2600 111
**Author:** Ashlyn Dedert
**Date:** 10/29/2025

---

## Overview

This program explores Linux system calls for both processes and files.

### Programs

- **info.c** - Displays general system information using standard libraries.
- **pinfo.c** - Shows a process's PID, scheduling policy, and priority. Optional PID argument, but defaults to the current process.
- **pmod.c** - Reduces its own priority by 10, then sleeps using 'nanosleep', then prints a goodbye message.
- **finfo.c** - Displays file type, permissions, owner UID, size, and last modified time. Requires a file path argument.

---

## Compilation

Use the Makfile

'''bash
make all    # Build all programs
make clean  # Remove executables and object files

## Usage
./info          # Displays system information
./pinfo [PID]   # Show process info
./pmod          # Change priority, sleep, print goodbye
./finfo <file>  # Show file info