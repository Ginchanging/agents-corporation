#include <iomanip>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

namespace fs = std::filesystem;

std::string read_file(std::string path) {
    std::ifstream in(path);
    if(!in) {
        throw std::runtime_error("ifstream: " + path);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void mk_dir() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream id;
    id << std::put_time(std::localtime(&t), "%Y%m%d-%H%M%S");
    fs::path run_dir = fs::path(".agent-dev") / "runs" / id.str();
    fs::create_directory(run_dir);
}

int main(int argc, const char * argv[]) {
    if(argc < 2) {
        std::cerr << "Usage: agent-dev <task.yaml>\n";
        return 1;
    }
    std::string task_content = read_file(argv[1]);
    std::cout << "Read task file, " << task_content.size() << " bytes\n";
    return EXIT_SUCCESS;
}
