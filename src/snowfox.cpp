#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;


// Password finder for env files based on regex
vector<string> env_regex_finder(const string& file_path) {
    vector<string> passwords;
    // File reader
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {};
    }

    // Regex pattern to match "PASS..=" and capture the rest of the line
    regex pattern("(PASS.*=)(.*)");

    // For every line in the document
    string line;
    while (getline(file, line)) {
        smatch matches;
        if (regex_search(line, matches, pattern)) {
            // matches[2] because matches[0] is the whole match, matches[1] is the "PASS..="
            passwords.push_back(matches[2]);
        }
    }

    // Close the file to avoid memory leaks
    file.close();

    // Return the password vector
    return passwords;
}


// Here should be the file processing logic
vector<string> process_file(const string& line) {
    // In case databse files are found, there could be a special kind of detection
    if (line.ends_with(".db")) {
        // Still needs a proper logic here
        //cout << "Found a database file: " << line << endl;
    }

    // Basic regex is going to be applied for env files
    if (line.ends_with(".env")) {
        // This is still just a basic regex, there could be more
        //cout << "Found an env file: " << line << endl;
        return env_regex_finder(line);
    }

    // In case the file is ignored
    return {};
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
        srand(static_cast<unsigned int>(time(nullptr)));

        cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠙⠻⢶⣄⡀⠀⠀⠀⢀⣤⠶⠛⠛⡇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣇⠀⠀⣙⣿⣦⣤⣴⣿⣁⠀⠀⣸⠇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣡⣾⣿⣿⣿⣿⣿⣿⣿⣷⣌⠋⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⣷⣄⡈⢻⣿⡟⢁⣠⣾⣿⣦⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⠘⣿⠃⣿⣿⣿⣿⡏⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠈⠛⣰⠿⣆⠛⠁⠀⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣦⠀⠘⠛⠋⠀⣴⣿⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣾⣿⣿⣿⣿⡇⠀⠀⠀⢸⣿⣏⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠀⠀⠀⠾⢿⣿⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣋⣁⣤⣤⡶⠶⠶⣤⣄⠈⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢰⣿⣿⣮⣉⣉⣉⣤⣴⣶⣿⣿⣋⡥⠄⠀⠀⠀⠀⠉⢻⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠋⠉⠁⠀⠀⠀⠀⠈⠛⠃⠀⠀⠀⠀
⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀)" << endl;

    vector<string> daily_wisdom = {
        "Be clever like a fox, always finding a way around obstacles.",
        "In the forest, the clever fox finds its path where others see only thorns.",
        "A wise fox knows when to hunt and when to hide.",
        "Like a fox in the night, adaptability is key to survival.",
        "In the dance of life, be swift and sly like a fox.",
        "The quick brown fox jumps over the lazy dog!",
        "The snow fox starts its hunt!",
        "The fox who chases two rabbits catches neither.",
        "In the art of survival, the fox teaches patience and observation."
    };

    int index = rand() % daily_wisdom.size();
    cout << daily_wisdom[index] << endl << endl;

    // Initializing variables
    vector<string> files;
    vector<string> passwords;

    // This should be an iterator
    files = crawl_files();
    for (const auto& file_path : files) {
        vector<string> new_passwords = process_file(file_path);
        passwords.insert(passwords.end(), new_passwords.begin(), new_passwords.end());
    }

    if (passwords.size()) {
        cout << "Scan complete, found the following passwords:" << endl;
        for (const auto& password : passwords) {
            cout << password << endl;
        }
    }
    else {
        cout << "The scan is over, but no password was found" << endl;
    }
}