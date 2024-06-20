#include <vector>
#include <iostream>
#include <dirent.h>
#include <string>

using namespace std;

// Here should be the file processing logic
void process_file(const string& line) {
    // In case databse files are found, there could be a special kind of detection
    if (line.ends_with(".db")) {
        cout << "Found a database file: " << line << endl;
    }

    // Basic regex is going to be applied for env files
    if (line.ends_with(".env")) {
        cout << "Found an env file: " << line << endl;
    }
}


// Here should be the file crawling structure    
vector<string> crawl_files() {
    vector<string> output;
    // Temporary popen file detection using bash
    // It must be replaced with a proper C++ function
    FILE* pipe = popen("find / 2>/dev/null", "r");
    if (!pipe) {
        cerr << "popen failed!";
        return {};
    }

    char buffer[1024]; // Buffer to hold each line of output
    while (fgets(buffer, sizeof(buffer), pipe)!= nullptr) {
        // Remove trailing newline character
        string line = buffer;
        line.erase(line.find_last_not_of("\n") + 1);
        // Append the new line
        output.push_back(line);
    }

    pclose(pipe);
    return output;
}


int main()
{
    // The quote could be chosen from a quote list
    cout << "The snow fox starts its hunt!" << endl << endl;
    // The ascii art would be printed here along with the quote

    // This should be an iterator
    vector<string> files = crawl_files();
    for (const auto& file_path : files) {
        process_file(file_path);
    }
}