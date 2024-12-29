#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <limits>

using namespace std;
namespace fs = std::filesystem;

// 读取配置文件的函数
bool readConfig(const string &configPath, string &gamePath, string &edition)
{
    ifstream configFile(configPath);
    if (!configFile.is_open())
    {
        cerr << "无法打开配置文件: " << configPath << endl;
        return false;
    }

    string line;
    while (getline(configFile, line))
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
bool writeEdition(const string &configPath, const string &gamePath, const string &edition)
{
    try
    {
        ofstream configFile(configPath, ios::trunc);
        if (!configFile.is_open())
        {
            throw ios_base::failure("无法打开文件");
        }
        configFile << "game_path=\"" << gamePath << "\"\n";
        configFile << "edition=" << edition << endl;
        configFile.close();
        return true;
    }
    catch (const exception &e)
    {
        cerr << "写入配置文件时出错: " << e.what() << endl;
        return false;
    }
}

// 复制 DLL 文件的函数
bool copyDLL(const string &source, const string &destination)
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
    catch (const exception &e)
    {
        cerr << "复制文件时出错: " << e.what() << endl;
        return false;
    }
}

// 获取用户选择的版本
string getEditionFromUser()
{
    int editionChoice;
    while (true)
    {
        cout << "请选择版本:\n1. steam\n2. uplay\n请输入选项 (1 或 2): ";
        if (cin >> editionChoice)
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
                cerr << "无效的选择，请重新输入。" << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "无效输入，请输入数字 1 或 2。" << endl;
        }
    }
}

// 启动游戏函数
void launchGame(const string &edition)
{
    string launchCommand;
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
        cerr << "未知的版本，无法启动游戏。" << endl;
        return;
    }

    cout << "正在启动 " << edition << " 版游戏..." << endl;
    system(launchCommand.c_str());
}

int main()
{
    const string configPath = "config.cfg";
    string gamePath;
    string edition;

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
        cout << "当前游戏版本: " << edition << endl;
        cout << "1. 切换版本\n2. 更新 defaultargs.dll\n3. 启动游戏\n4. 退出\n请选择一个选项: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "无效输入，请输入数字。" << endl;
            continue;
        }

        if (choice == 1)
        {
            // 切换版本
            string newEdition = getEditionFromUser();
            string sourceDLL = newEdition + "/defaultargs.dll";
            string destinationDLL = gamePath + "/defaultargs.dll";

            if (copyDLL(sourceDLL, destinationDLL))
            {
                cout << "成功切换到 " << newEdition << " 版本。" << endl;
                edition = newEdition;
                writeEdition(configPath, gamePath, edition);
            }
            else
            {
                cerr << "切换版本失败。" << endl;
            }
        }
        else if (choice == 2)
        {
            // 更新 defaultargs.dll
            string currentEdition = getEditionFromUser();
            string sourceDLL = gamePath + "/defaultargs.dll";
            string destinationDLL = currentEdition + "/defaultargs.dll";

            if (copyDLL(sourceDLL, destinationDLL))
            {
                cout << "成功更新 " << currentEdition << " 的 defaultargs.dll。" << endl;
            }
            else
            {
                cerr << "更新 defaultargs.dll 失败。" << endl;
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
            cerr << "无效的选择，请重新输入。" << endl;
        }

        cout << "按任意键返回主菜单...";
        cin.ignore();
        cin.get();
    }

    return 0;
}