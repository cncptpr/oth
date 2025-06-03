#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

void build(const std::string& file) {
    std::string command;
    if (file.ends_with(".cpp")) {
        command = "g++ -std=c++20 -o " + file.substr(0, file.find_last_of('.')) + " " + file;
    } else if (file.ends_with(".c")) {
        command = "gcc -std=c11 -o " + file.substr(0, file.find_last_of('.')) + " " + file; // Use C11 for C files
    } else {
        std::cerr << "Unsupported file type: " << file << std::endl;
        return;
    }

    if (system(command.c_str()) != 0) {
        std::cerr << "Build failed for " << file << std::endl;
    } else {
        std::cout << "Built " << file << " successfully." << std::endl;
    }
}

void run(const std::string& file) {
    build(file);
    std::string executable = file.substr(0, file.find_last_of('.'));
    if (system((executable + " < /dev/stdin").c_str()) != 0) {
        std::cerr << "Execution failed for " << executable << std::endl;
    }
}

void test(const std::string& file) {
    std::string baseName = file.substr(0, file.find_last_of('.'));
    std::vector<std::string> testFiles;

    // Find all test files with .1.test, .2.test, etc.
    for (const auto& entry : fs::directory_iterator(fs::path(baseName).parent_path())) {
        if (entry.path().string().starts_with(baseName) && entry.path().extension() == ".test") {
            testFiles.push_back(entry.path().string());
        }
    }

    if (testFiles.empty()) {
        std::cerr << "No test files found for " << file << std::endl;
        return;
    }

    for (const auto& testFile : testFiles) {
        std::ifstream input(testFile);
        if (!input) {
            std::cerr << "Failed to open test file: " << testFile << std::endl;
            continue;
        }

        // Read the entire content of the test file
        std::string inputContent((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
        input.close();

        // Build the executable
        std::string executable = file.substr(0, file.find_last_of('.'));
        build(file);

        // Execute the program and pipe the entire content of the test file
        FILE* pipe = popen((executable + " <<< \"" + inputContent + "\"").c_str(), "r");
        if (!pipe) {
            std::cerr << "Failed to run " << executable << std::endl;
            continue;
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::cout << buffer; // Output the result
        }
        pclose(pipe);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: program [command] [file]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string file = argv[2];

    if (command == "build") {
        build(file);
    } else if (command == "run") {
        run(file);
    } else if (command == "test") {
        test(file);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}

