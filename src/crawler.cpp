#include "../includes/crawler.h"

using namespace std;

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
