
# EzSSH

EzSSH is a simple tool for managing SSH connections via command line and a basic Windows GUI.  
It supports creating, editing, deleting, and launching saved SSH configurations.  
Written in **C** and designed for Windows.

---

## ✨ Features

- 🖥 **CLI mode** – easy commands for managing SSH saves  
- 🪟 **GUI mode** – simple Windows interface (beta)  
- 📁 Manage saved connections quickly  
- 🚀 Fast connection launch  
- 🛠 Edit and delete existing saved configs  

---

## 📦 Installation

### Option 1: Download Pre-built Executable

1. **Download the executable:**  
   Go to the [Releases page](https://github.com/your-username/ezssh/releases) and download the latest Windows version `ezssh.exe`.

2. **Add to system PATH:**  
   - Move the downloaded `ezssh.exe` to a folder where you want to keep it, e.g.,  
     `C:\Tools\ezssh\`  
   - Add this folder to your Windows PATH environment variable:  
     - Press **Start**, type **Environment Variables**, and open **Edit the system environment variables**  
     - Click **Environment Variables...**  
     - Under **System variables**, find and select **Path**, then click **Edit...**  
     - Click **New** and add the folder path, e.g., `C:\Tools\ezssh\`  
     - Confirm by clicking **OK** on all windows.

3. **Restart your command prompt** or terminal to reload PATH.

4. **Test installation:**  
   Open a new Command Prompt and type:

   ezssh -v


You should see the version info.

---

### Option 2: Build from Source

If you want to build from source:

1. **Clone the repo:**

   ```bash
   git clone https://github.com/your-username/ezssh.git
   cd ezssh
   ```

2. **Make sure you have a C compiler** (like `gcc` from MinGW or MSVC):

   ```bash
   gcc --version
   ```

3. **Build the project:**

   ```bash
   gcc ezssh.c -o ezssh -mwindows
   ```



## 🚀 Usage

### CLI mode

Run the program with commands:

```
ezssh -n             # create a new save
ezssh -c <name>      # connect to a save
ezssh --c <name>     # connect in a new window
ezssh -in <name>     # show info about a save
ezssh -e <name>      # edit a save
ezssh -d <name>      # delete a save
ezssh -l             # list all saves
ezssh -v             # show program version
ezssh -gui           # open GUI menu (beta)
```

### GUI mode (beta)

Start GUI with:

```bash
ezssh -gui
```

In the GUI you can:

* Type the connection name and click **Connect**
* Click **New Connection** to create a save
* View info about a saved connection

---

## 📷 Screenshot (GUI)

*(Add your GUI screenshot here like `screenshot.png` for extra clarity)*

---

## 🛠 Requirements

* Windows OS (GUI uses WinAPI)
* C compiler (GCC/MinGW or MSVC) if building from source
* SSH client installed (e.g., OpenSSH)

---

## 📄 License

Created by Denis Varga, released under the MIT License.

---

## 👤 Author

* **Name:** Denis Varga
* **Website:** [denisvarga.eu](https://denisvarga.eu)
* **Studio:** DV Studio

`
