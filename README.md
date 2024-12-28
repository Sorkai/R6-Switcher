# R6-Switcher 游戏版本切换与启动工具

[English version](README.en-US.md)

## 项目简介
该项目是一个用 C++ 编写的小工具，用于在 Steam 和 Uplay 版本的彩虹六号围攻（Rainbow Six Siege）之间切换 `defaultargs.dll` 文件，并提供直接启动游戏的功能。工具通过读取和修改配置文件实现版本切换，同时支持更新 `defaultargs.dll` 文件到相应的程序目录。

---

## 功能说明

1. **切换版本**
   - 用户可以选择目标版本（Steam 或 Uplay）。
   - 将对应版本的 `defaultargs.dll` 文件复制到游戏目录以完成版本切换。

2. **更新 DLL 文件**
   - 从当前游戏版本目录中提取 `defaultargs.dll` 文件，更新到程序目录下的相应版本文件夹。

3. **启动游戏**
   - 用户可以通过程序直接启动 Steam 或 Uplay 版本的游戏。

4. **退出程序**
   - 退出程序的主菜单。

---

## 项目结构

### 文件目录
```
项目目录
├── steam/
│   └── defaultargs.dll
├── uplay/
│   └── defaultargs.dll
├── config.cfg
├── main.cpp
```

### `config.cfg` 文件内容示例
```cfg
game_path="D:\SteamLibrary\steamapps\common\Tom Clancy's Rainbow Six Siege"
edition=uplay
```
- **`game_path`**：游戏安装路径，支持路径中包含空格，需用双引号括起来。
- **`edition`**：当前版本，可选值为 `steam` 或 `uplay`。

---

## 使用方法

### 运行程序

​	https://github.com/Sorkai/R6-Switcher/releases/latest

1. 点击上方下载最新版本并解压
2. 打开`config.cfg`文件
3. 修改`game_path="D:\SteamLibrary\steamapps\common\Tom Clancy's Rainbow Six Siege"`为你当前的游戏安装目录
4. 修改`edition=uplay`为你当前的游戏版本
5. 运行R6Switcher.exe
6. 使用其中的功能

### 主菜单功能
运行程序后，用户会看到以下主菜单：

```
当前游戏版本: uplay
1. 切换版本
2. 更新 defaultargs.dll
3. 启动游戏
4. 退出
请选择一个选项:
```

#### 功能说明
1. **切换版本**
   - 输入选项 `1`，程序会提示选择目标版本：
     ```
     请选择版本:
     1. steam
     2. uplay
     ```
   - 选择版本后，程序会将对应目录下的 `defaultargs.dll` 文件复制到游戏目录。
   - 配置文件会更新为当前选择的版本。

2. **更新 DLL 文件**
   - 输入选项 `2`，程序会提示选择当前实际运行的版本：
     ```
     请选择版本:
     1. steam
     2. uplay
     ```
   - 程序会从游戏目录提取 `defaultargs.dll` 文件，更新到对应版本的程序目录中。

3. **启动游戏**
   - 输入选项 `3`，程序会根据当前版本直接启动游戏。
     - 启动 Steam 版本：`steam://rungameid/359550`
     - 启动 Uplay 版本：`uplay://launch/635/0`

4. **退出程序**
   - 输入选项 `4`，程序将退出。

---

## 编译与运行

### 编译
使用支持 C++17 或更高标准的编译器（如 `g++` 或 `MSVC`）。

#### Windows 示例（g++）
```bash
g++ -std=c++17 -o R6Switcher.exe main.cpp
```

### 运行
在终端中运行编译后的可执行文件：
```bash
./R6Switcher.exe
```

---

## 注意事项
1. 请确保程序具有足够的权限访问和修改游戏目录下的 `defaultargs.dll` 文件。
2. 如果路径配置错误，程序可能无法正确读取或写入配置文件。
3. 使用时请勿删除程序目录中的 `steam` 和 `uplay` 文件夹。

---

## 示例效果
### 切换版本
```
当前游戏版本: steam
1. 切换版本
2. 更新 defaultargs.dll
3. 启动游戏
4. 退出
请选择一个选项: 1
请选择版本:
1. steam
2. uplay
请输入选项 (1 或 2): 2
成功切换到 uplay 版本。
按任意键返回主菜单...
```

### 更新 DLL 文件
```
当前游戏版本: uplay
1. 切换版本
2. 更新 defaultargs.dll
3. 启动游戏
4. 退出
请选择一个选项: 2
请选择版本:
1. steam
2. uplay
请输入选项 (1 或 2): 1
成功更新 steam 的 defaultargs.dll。
按任意键返回主菜单...
```

### 启动游戏
```
当前游戏版本: uplay
1. 切换版本
2. 更新 defaultargs.dll
3. 启动游戏
4. 退出
请选择一个选项: 3
正在启动 uplay 版游戏...
```

---

## 许可证
该项目采用 MIT 许可证。详情请参阅 [LICENSE](LICENSE) 文件。

---

## 贡献
欢迎提交 issue 和 pull request！

