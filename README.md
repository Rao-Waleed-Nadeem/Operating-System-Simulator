# Operating-System-Simulator

🖥️ Custom Operating System Simulation
Semester Final Project – Operating Systems Lab (Spring 2025)
Developed as part of my coursework at FAST NUCES, this project is a terminal-based simulation of a simplified operating system, implementing core OS concepts such as multitasking, resource management, process scheduling, and more.

🚀 Features
OS Boot Simulation

Displays custom OS name with loading animation

Prompts user to configure system resources (RAM, Disk, CPU cores)

Task Management

15+ standalone applications (Notepad, Calculator, Clock, Games, File ops, etc.)

Each task runs as a separate process using exec, not simple function calls

Independent terminal for each process (to simulate multitasking terminals)

Multitasking & Scheduling

Processes are managed using a Ready Queue

Multilevel Queue Scheduling with different algorithms per level

Proper resource allocation (RAM, Hard Drive, CPU cores)

No task starts if resources aren't available

Kernel Mode vs User Mode

Kernel Mode: terminate or resume tasks, access hardware-level controls

User Mode: restricted access to running and managing tasks

Interrupt Handling

Simulated manual interrupts (close/minimize tasks)

Blocked/Resumed task handling on interrupts

Task Types

Interactive (e.g., Calculator, Game)

Background (e.g., Music/Beep sound, Copying files)

Auto-running (e.g., Clock, Autosave in Notepad)

Shutdown Procedure

Graceful OS shutdown

Closes all processes, clears memory, displays exit message

🧠 Operating System Concepts Implemented
Process creation (exec, forking)

Process scheduling (multilevel queues)

Context switching

Semaphores & condition variables

Resource management (RAM, CPU cores, Disk)

User Mode & Kernel Mode

Interrupts & process signals

Multitasking & synchronization

💻 Technologies Used
Language: C / C++

Platform: Terminal (Linux preferred)

Libraries: POSIX APIs (e.g., fork(), exec(), semaphores)

🎓 Developed By
1) Amna Noor
2) Waleed Nadeem
Bachelor’s in Computer Science – FAST NUCES
Spring 2025 – Operating Systems Lab Final Term Project
