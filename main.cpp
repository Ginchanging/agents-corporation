#include <iomanip>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

namespace fs = std::filesystem;

std::string read_file(fs::path path) {
    std::ifstream in(path);
    if(!in) {
        throw std::runtime_error("ifstream: " + path.string());
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

void write_file(const fs::path path, const std::string& content) {
    std::ofstream out(path);
    if(!out) {
        throw std::runtime_error("ofstream: " + path.string());
    }
    out << content;
}

std::string shell_quote(const std::string& raw) {
    std::string result = "'";
    for(char c : raw) {
        if(c == '\'') {
            result += "'\''";
        }
        else {
            result += c;
        }
    }
    result += '\'';
    return result;
}

fs::path mk_dir() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream id;
    id << std::put_time(std::localtime(&t), "%Y%m%d-%H%M%S");
    fs::path run_dir = fs::path(".agent-dev") / "runs" / id.str();
    fs::create_directories(run_dir);
    return run_dir;
}

int run_command_to_file(const std::string& cmd, const fs::path output) {
    std::string full_cmd = cmd + " > " + shell_quote(output.string()) + " 2>&1";
    return std::system(full_cmd.c_str());
}

int main(int argc, const char * argv[]) {
    try {
        if(argc < 3 || std::string(argv[1]) != "run") {
            std::cerr << "Usage: agent-dev <task.yaml>\n";
            return 1;
        }
        
        fs::path run_dir = mk_dir();
        std::cout << "Created run directory: " << run_dir << "\n";
        
        std::string task_content = read_file(argv[2]);
        std::cout << "Read task file, " << task_content.size() << " bytes\n";
        
        std::cout << "Generating plan with Claude...\n";
        std::string claude_headcmd = read_file("claude_headcmd");
        std::string claude_prompt = claude_headcmd + "\n\n```yaml\n" + task_content + "\n```\n";
        fs::path claude_prompt_path = run_dir / "claude_prompt.md";
        write_file(claude_prompt_path, claude_prompt);
        std::string claude_cmd = "cat " + shell_quote(claude_prompt_path.string()) + " | claude -p";
        if(run_command_to_file(claude_cmd, run_dir / "plan.md") != 0) {
            std::cerr << "Claude failed. Check: " << run_dir / "plan.md" << "\n";
            return 1;
        }
        
        std::cout << "Running OpenCode...\n";
        std::string opencode_headcmd = read_file("opencode_headcmd");
        std::string plan = read_file(run_dir / "plan.md");
        std::string opencode_prompt = opencode_headcmd + "\nTask\n\n```yaml\n" + task_content + "\n```\n\n# Plan\n\n" + plan + "\n";
        fs::path opencode_prompt_path = run_dir / "opencode_prompt.md";
        write_file(opencode_prompt_path, opencode_prompt);
        std::string opencode_cmd = "cat " + shell_quote(opencode_prompt_path.string()) + " | opencode run";
        if(run_command_to_file(opencode_cmd, run_dir / "opencode.log") != 0) {
            std::cerr << "Opencode failed. Check: " << run_dir / "opencode.log" << "\n";
            return 1;
        }
        
        std::cout << "\nDone!\n";
        std::cout << "Run directory: " << run_dir << "\n";
        std::cout << "Plan: " << run_dir / "plan.md" << "\n";
        std::cout << "OpenCode log: " << run_dir / "opencode.log" << "\n";
        std::cout << "\nReview changes with:\n";
        std::cout << "  git diff\n";
        
        
        return EXIT_SUCCESS;
    } catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
