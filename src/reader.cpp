#include <iostream>
#include <fstream>
#include "../includes/reader.h"

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
