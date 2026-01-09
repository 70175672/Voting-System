Voting System

## Project Overview
This project is an **Advanced Voting System** implemented in **C++** using **object-oriented programming (OOP)** concepts. The system allows secure voting with admin controls, voter tracking, and persistent storage using file handling. It ensures confidentiality by hiding vote counts until the voting session ends.

---

## Features

### Admin Features:
- Admin login with password authentication.
- Add or remove candidates (only before voting starts).
- Start and end voting sessions.
- View voter details (voter ID and chosen candidate).

### Voter Features:
- Unique voter IDs prevent multiple votes.
- Cast votes only during active voting sessions.
- Cannot view total votes or results until voting ends.

### Voting System Features:
- Displays list of candidates during voting.
- Calculates winner automatically (supports ties).
- Shows vote counts and percentages only after voting ends.
- Persistent storage using `candidates.txt` and `voters.txt`.

---

## Files
- `AdvancedVotingSystem.cpp` – Main program file.
- `candidates.txt` – Stores candidate names and votes.
- `voters.txt` – Stores voter IDs and their chosen candidate.

---

## How to Run
1. Place `AdvancedVotingSystem.cpp` in a folder.
2. Create empty `candidates.txt` and `voters.txt` in the same folder.
3. Compile and run the program using a C++ compiler:
   ```bash
   g++ AdvancedVotingSystem.cpp -o VotingSystem
   ./VotingSystem
   ```
4. Use the admin menu to add candidates and manage voting.
5. Voters can cast their votes using unique voter IDs

## Admin Password
- Default admin password: `alishba25`

---

## Limitations
- Maximum 10 candidates and 100 voters (can be increased if needed).
- Console-based interface (no GUI).
- No online or network voting support.


