# Archger (v0.1b)

Archger is a lightweight C++ CLI management utility designed specifically for Arch Linux. It automates essential system maintenance tasks, starting with safe orphan package removal.

## Features

- Orphan Detection: Scans the system using pacman -Qtdq to identify unneeded dependency packages.
- Whitelist Protection: Allows users to exclude specific packages (e.g., rust, development tools) from being removed.
- Automated Cleanup: Safely executes package deletion via pacman -Rns.
- Status Verification: Re-checks the system post-cleanup to verify successful package removal.

## Installation & Build

### Prerequisites
- Arch Linux
- g++ compiler
- sudo privileges for package management

### Compilation
Clone the repository and build using g++:
```bash
git clone https://github.com/danrau/arch-manager.git
cd archger
g++ main.cpp -o archger
```
## Usage

Run the compiled executable
```bash
./archger
```
Follow the on-screen interactive menu:
1. Select 1 to scan for orphan packages.
2. Enter any package names you wish to preserve (or press Enter to skip).
3. Confirm the deletion prompt (Y/n).

## License

MIT License. Free to use and modify.