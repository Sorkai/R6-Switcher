# R6-Switcher: Rainbow Six Siege Game Version Switching and Launching Tool

[中文版本](README.md)

## Project Introduction
This project is a small tool written in C++ for switching between the Steam and Uplay versions of Rainbow Six Siege by replacing the `defaultargs.dll` file. The tool also provides the ability to directly launch the game. It achieves version switching by reading and modifying a configuration file and supports updating the `defaultargs.dll` file to the corresponding program directory.

[Releases, other downloads and feedback](https://www.sorkai.com/?p=228)

Inspiration: [how to convert rainbow six between uplay and steam versions](https://www.bilibili.com/opus/230015736591751068)

---

## Features

1. **Switch Versions**
   - Users can select the target version (Steam or Uplay).
   - The corresponding `defaultargs.dll` file is copied to the game directory to complete the version switch.

2. **Update DLL File**
   - Extracts the `defaultargs.dll` file from the current game version directory and updates it to the corresponding program directory.

3. **Launch Game**
   - Users can directly launch the Steam or Uplay version of the game through the tool.

4. **Exit Program**
   - Exit the main menu of the program.

---

## Project Structure

### File Directory
```
Project Directory
├── steam/
│   └── defaultargs.dll
├── uplay/
│   └── defaultargs.dll
├── config.cfg
├── main.cpp
```

### `config.cfg` File Example
```cfg
game_path="D:\SteamLibrary\steamapps\common\Tom Clancy's Rainbow Six Siege"
edition=uplay
```
- **`game_path`**: The game installation path, supporting spaces, must be enclosed in double quotes.
- **`edition`**: The current version, with possible values `steam` or `uplay`.

---

## Usage Instructions

### Run the Program

​	https://github.com/Sorkai/R6-Switcher/releases/latest

1. Download the latest version and extract it👆.
2. Open the `config.cfg` file.
3. Change `game_path="D:\SteamLibrary\steamapps\common\Tom Clancy's Rainbow Six Siege"` to your current game installation directory.
4. Change `edition=uplay` to your current game version.
5. Run `R6Switcher.exe`.
6. Use the features provided in the program.

### Main Menu Features
After running the program, users will see the following main menu:

```
Current game version: uplay
1. Switch Versions
2. Update defaultargs.dll
3. Launch Game
4. Exit
Choose an option:
```

#### Feature Details
1. **Switch Versions**
   - Enter option `1`, and the program will prompt you to select the target version:
     ```
     Select version:
     1. steam
     2. uplay
     ```
   - After selecting the version, the program will copy the corresponding `defaultargs.dll` file to the game directory.
   - The configuration file will be updated to the selected version.

2. **Update DLL File**
   - Enter option `2`, and the program will prompt you to select the currently running version:
     ```
     Select version:
     1. steam
     2. uplay
     ```
   - The program will extract the `defaultargs.dll` file from the game directory and update it to the corresponding version's program directory.

3. **Launch Game**
   - Enter option `3`, and the program will directly launch the game based on the current version.
     - Launch Steam version: `steam://rungameid/359550`
     - Launch Uplay version: `uplay://launch/635/0`

4. **Exit Program**
   - Enter option `4`, and the program will exit.

---

## Compilation and Execution

### Compilation
Use a compiler that supports C++17 or later (e.g., `g++` or `MSVC`).

#### Windows Example (g++)
```bash
g++ -std=c++17 -o R6Switcher.exe main.cpp
```

### Execution
Run the compiled executable in the terminal:
```bash
./R6Switcher.exe
```

---

## Notes
1. Ensure that the program has sufficient permissions to access and modify the `defaultargs.dll` file in the game directory.
2. If the path configuration is incorrect, the program may fail to read or write the configuration file.
3. Do not delete the `steam` and `uplay` folders in the program directory while using the tool.

---

## Example Outputs
### Switch Versions
```
Current game version: steam
1. Switch Versions
2. Update defaultargs.dll
3. Launch Game
4. Exit
Choose an option: 1
Select version:
1. steam
2. uplay
Enter option (1 or 2): 2
Successfully switched to the uplay version.
Press any key to return to the main menu...
```

### Update DLL File
```
Current game version: uplay
1. Switch Versions
2. Update defaultargs.dll
3. Launch Game
4. Exit
Choose an option: 2
Select version:
1. steam
2. uplay
Enter option (1 or 2): 1
Successfully updated the steam version's defaultargs.dll.
Press any key to return to the main menu...
```

### Launch Game
```
Current game version: uplay
1. Switch Versions
2. Update defaultargs.dll
3. Launch Game
4. Exit
Choose an option: 3
Launching the uplay version of the game...
```

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contributions
Issues and pull requests are welcome!

