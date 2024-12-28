#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <limits>

namespace fs = std::filesystem;

// 读取配置文件的函数
bool readConfig(const std::string &configPath, std::string &gamePath, std::string &edition)
{
    std::ifstream configFile(configPath);
    if (!configFile.is_open())
    {
        std::cerr << "无法打开配置文件: " << configPath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(configFile, line))
    {
        if (line.find("game_path=") == 0)
        {
            gamePath = line.substr(10); // 提取 "game_path=" 之后的值
            if (gamePath.front() == '"' && gamePath.back() == '"')
            {
                gamePath = gamePath.substr(1, gamePath.size() - 2); // 去除前后的引号
            }
        }
        else if (line.find("edition=") == 0)
        {
            edition = line.substr(8); // 提取 "edition=" 之后的值
        }
    }

    configFile.close();
    return true;
}

// 将版本写回配置文件的函数
bool writeEdition(const std::string &configPath, const std::string &gamePath, const std::string &edition)
{
    try
    {
        std::ofstream configFile(configPath, std::ios::trunc);
        if (!configFile.is_open())
        {
            throw std::ios_base::failure("无法打开文件");
        }
        configFile << "game_path=\"" << gamePath << "\"\n";
        configFile << "edition=" << edition << std::endl;
        configFile.close();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "写入配置文件时出错: " << e.what() << std::endl;
        return false;
    }
}

// 复制 DLL 文件的函数
bool copyDLL(const std::string &source, const std::string &destination)
{
    try
    {
        if (fs::exists(destination))
        {
            fs::remove(destination); // 删除目标文件
        }
        fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "复制文件时出错: " << e.what() << std::endl;
        return false;
    }
}

// 获取用户选择的版本
std::string getEditionFromUser()
{
    int editionChoice;
    while (true)
    {
        std::cout << "请选择版本:\n1. steam\n2. uplay\n请输入选项 (1 或 2): ";
        if (std::cin >> editionChoice)
        {
            if (editionChoice == 1)
            {
                return "steam";
            }
            else if (editionChoice == 2)
            {
                return "uplay";
            }
            else
            {
                std::cerr << "无效的选择，请重新输入。" << std::endl;
            }
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "无效输入，请输入数字 1 或 2。" << std::endl;
        }
    }
}

// 启动游戏函数
void launchGame(const std::string &edition)
{
    std::string launchCommand;
    if (edition == "steam")
    {
        launchCommand = "start steam://rungameid/359550";
    }
    else if (edition == "uplay")
    {
        launchCommand = "start uplay://launch/635/0";
    }
    else
    {
        std::cerr << "未知的版本，无法启动游戏。" << std::endl;
        return;
    }

    std::cout << "正在启动 " << edition << " 版游戏..." << std::endl;
    system(launchCommand.c_str());
}

int main()
{
    const std::string configPath = "config.cfg";
    std::string gamePath;
    std::string edition;

    // 读取配置
    if (!readConfig(configPath, gamePath, edition))
    {
        return -1;
    }

    while (true)
    {
        // 清空终端
        system("cls");

        int choice;
        std::cout << "当前游戏版本: " << edition << std::endl;
        std::cout << "1. 切换版本\n2. 更新 defaultargs.dll\n3. 启动游戏\n4. 退出\n请选择一个选项: ";
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "无效输入，请输入数字。" << std::endl;
            continue;
        }

        if (choice == 1)
        {
            // 切换版本
            std::string newEdition = getEditionFromUser();
            std::string sourceDLL = newEdition + "/defaultargs.dll";
            std::string destinationDLL = gamePath + "/defaultargs.dll";

            if (copyDLL(sourceDLL, destinationDLL))
            {
                std::cout << "成功切换到 " << newEdition << " 版本。" << std::endl;
                edition = newEdition;
                writeEdition(configPath, gamePath, edition);
            }
            else
            {
                std::cerr << "切换版本失败。" << std::endl;
            }
        }
        else if (choice == 2)
        {
            // 更新 defaultargs.dll
            std::string currentEdition = getEditionFromUser();
            std::string sourceDLL = gamePath + "/defaultargs.dll";
            std::string destinationDLL = currentEdition + "/defaultargs.dll";

            if (copyDLL(sourceDLL, destinationDLL))
            {
                std::cout << "成功更新 " << currentEdition << " 的 defaultargs.dll。" << std::endl;
            }
            else
            {
                std::cerr << "更新 defaultargs.dll 失败。" << std::endl;
            }
        }
        else if (choice == 3)
        {
            // 启动游戏
            launchGame(edition);
        }
        else if (choice == 4)
        {
            // 退出程序
            break;
        }
        else
        {
            std::cerr << "无效的选择，请重新输入。" << std::endl;
        }

        std::cout << "按任意键返回主菜单...";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
