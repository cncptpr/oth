/*
This programm was created to compile, run and test one-file c/c++ excercises for uni.
I got annoyed of always switching folders and changing my compile command.

Compile this with
    $ g++ --std=c++20 -o builder builder.cpp
build any c/c++ file with
    $ ./builder build path/to/file.c[pp]
use 'run' instead of 'build' to run directly
use 'test' to pipe contents of test files to the program
(one execution per file)
test files: e.g. path/to/file.1.test
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

inline std::string base_name(const std::string &file) {
    return file.substr(0, file.find_last_of('.'));
}

std::string make_command(const std::string &executable, const std::vector<std::string> &args) {
    std::string command = executable;
    for (const auto& arg : args)
        command += " " + arg;
    return command;
}

void build(const std::string& file) {
    std::string command;
    if (file.ends_with(".cpp")) {
        command = "g++ -std=c++20 -g -o " + base_name(file) + " " + file;
    } else if (file.ends_with(".c")) {
        command = "gcc -std=c11 -g -o " + base_name(file) + " " + file;
    } else {
        std::cerr << "Unsupported file type: " << file << std::endl;
        return;
    }
    
    if (system(command.c_str()) != 0) {
        // std::cerr << "Build failed for " << file << std::endl;
        // gcc prints enough, no need to print a error message
    } else {
        std::cerr << "Built " << file << " successfully." << std::endl;
    }
}

std::string find_best_match(const std::string& pattern) {
    const std::string command = "find . | grep \"\\.c$\\|\\.cpp$\" | fzf -f " + pattern;

    char buffer[128];
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to run fzf" << std::endl;
        return "";
    }
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    result.erase(result.find_last_not_of(" \n\r\t") + 1); // Trim trailing whitespace
    return result;
}

void run(const std::string& file, const std::vector<std::string>& args) {
    build(file);
    const std::string executable = base_name(file);
    auto command = make_command(executable, args);
    if (system(command.c_str()) != 0) {
        std::cerr << "Execution failed for " << executable << std::endl;
    }
}

void test(const std::string& file, const std::vector<std::string>& args) {
    // Build the executable
    build(file);

    // Find all test files with .1.test, .2.test, etc.
    const std::string baseName = base_name(file);
    std::vector<std::string> testFiles;
    for (const auto& entry : fs::directory_iterator(fs::path(baseName).parent_path())) {
        if (entry.path().string().starts_with(baseName) && entry.path().extension() == ".test") {
            testFiles.push_back(entry.path().string());
        }
    }

    if (testFiles.empty()) {
        std::cerr << "No test files found for " << file << std::endl;
        return;
    }

    const std::string command = make_command(baseName, args);
    for (const auto& testFile : testFiles) {
        // Execute the program and pipe the entire content of the test file
        FILE* pipe = popen((command + " < \"" + testFile + "\"").c_str(), "r");
        if (!pipe) {
            std::cerr << "Failed to run " << baseName << std::endl;
            continue;
        }

        const std::string testBaseName = base_name(testFile);
        const std::string outputFile = testBaseName + ".out";
        std::ofstream output(outputFile);
        if (!output) {
            std::cerr << "Failed to open output file: " << outputFile << std::endl;
            pclose(pipe);
            continue;
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output << buffer; // Write the result to the output file
        }
        pclose(pipe);
        output.close();

        const std::string expectedFile = testBaseName + ".expected";
        if (fs::exists(expectedFile)) {
            std::string diffTool;
            if (system("command -v delta > /dev/null 2>&1") == 0) {
                diffTool = "delta";
            } else {
                diffTool = "diff";
            }

            const std::string diffCommand = diffTool + " " + outputFile + " " + expectedFile;
            if (system(diffCommand.c_str()) == 0) {
                std::cout << "Test passed for " << testFile << std::endl;
            }
        } else {
            std::cout << "Test " << testFile << " was run. No 'expected' found to diff." << std::endl;
        }

    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: program [command] [file] [args...]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string file = argv[2];
    std::vector<std::string> args;
    for (int i = 3; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    if (!fs::exists(file)) {
        file = find_best_match(file);
        if (file.empty()) {
            std::cerr << "No matching file found." << std::endl;
            return 1;
        }
    }

    if (command == "build") {
        build(file);
    } else if (command == "run") {
        run(file, args);
    } else if (command == "test") {
        test(file, args);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}

