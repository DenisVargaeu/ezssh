
# 🚀 EzSSH

![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)
![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-4D4D4D?style=for-the-badge\&logo=windows-terminal\&logoColor=white)
![C](https://img.shields.io/badge/C_Language-00599C?style=for-the-badge\&logo=c\&logoColor=white)

> **EzSSH** is a simple tool for managing SSH connections through the command line and a basic Windows GUI.
> Written in **C**, designed to be fast and minimalistic.

---

## ✨ Features

* 🖥 **CLI mode** – quick commands for managing saved SSH connections
* 🪟 **GUI mode (beta)** – simple WinAPI interface
* 📁 Manage and organize saved configs
* 🚀 One-click fast connections
* 🛠 Edit and delete saved configs

---

## 📦 Installation

### 🔹 Option 1: Download Pre-built Executable

1. Download `ezssh.exe` from the [Releases](https://github.com/DenisVargaeu/ezssh/releases/new).
2. Move it to a folder, e.g. `C:\Tools\ezssh\`.
3. Add that folder to your **PATH**:

   * \**Start → Environment Variables → Path → Edit → New → C:\Tools\ezssh\**
4. Restart your terminal.
5. Verify installation:

   ```bash
   ezssh -v
   ```

---

### 🔹 Option 2: Build from Source

1. Clone the repo:

   ```bash
   git clone https://github.com/your-username/ezssh.git
   cd ezssh
   ```

2. Check your compiler (GCC / MSVC):

   ```bash
   gcc --version
   ```

3. Build the project:

   ```bash
   gcc ezssh.c -o ezssh -mwindows
   ```

---

## ⚡ Usage

### 🖥 CLI Commands

```bash
ezssh -n             # create a new configuration
ezssh -c <name>      # connect to a saved server
ezssh --c <name>     # connect in a new window
ezssh -in <name>     # show config details
ezssh -e <name>      # edit a configuration
ezssh -d <name>      # delete a configuration
ezssh -l             # list all configurations
ezssh -v             # show version info
ezssh -gui           # launch GUI (beta)
```

### 🪟 GUI Mode (beta)

* Click **New Connection** → create and save a connection
* Enter connection name + **Connect** → quick connect
* View info about saved connections

---

## 🛠 Requirements

* Windows OS (GUI built with WinAPI)
* C compiler (MinGW / MSVC) if building from source
* Windows SSH client (`ssh.exe`)

---

## 📄 License

MIT License – © 2025 [Denis Varga](https://denisvarga.eu)

---

## 👤 Author

* **Name:** Denis Varga
* **Website:** [denisvarga.eu](https://denisvarga.eu)
* **Studio:** DV Studio

