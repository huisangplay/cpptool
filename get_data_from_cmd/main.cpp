#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include<vector>
#include <sstream>

std::string cmdProcess(const char* cmd);
std::vector<std::string> split(const std::string& s, char delimiter);
int main() {
    std::string cmdLine("ipconfig");
    // cmdSystem(cmdLine);

    //std::string tmp=cmdPopen(cmdLine);

    std::string tmp = cmdProcess(cmdLine.c_str());

//    printf("the resule of cmd is %s", tmp.c_str());
    std::vector<std::string> list= split(tmp,'\n');
    printf("the resule of cmd is %d", list.size());
    printf("the resule of cmd is %s", list.at(4).c_str());
//
//    system("pause");
    return 0;
}

std::string cmdProcess(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}