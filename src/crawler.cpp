#include "../includes/crawler.h"

using namespace std;


// Global queues
queue<string> dir_queue;
vector<string> file_queue;

class Crawler {
public:
    enum State { Idle, Busy };
    State current_state = Idle;

    void set_crawl_state(State new_state) {
        current_state = new_state;
    }

    void crawl(const string& directory) {
        // Sets busy state
        set_crawl_state(Busy);
        // Update global queues
        try {
            for (const auto& entry : filesystem::directory_iterator(directory)) {
                if (entry.is_directory()) {
                    dir_queue.push(entry.path().string());
                } else if (entry.is_regular_file()) {
                    file_queue.push_back(entry.path().string());
                }
            }
        } catch (const filesystem::filesystem_error& e) {
            cerr << "Filesystem error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            cerr << "General error: " << e.what() << '\n';
        }
        // Sets idle state
        set_crawl_state(Idle);
    }
};


vector<Crawler> crawlers(10); // List of 10 crawlers (should have a way to set different sizes)


bool allCrawlersIdle() {
    for (const auto& crawler : crawlers) {
        if (crawler.current_state != Crawler::Idle) {
            return false;
        }
    }
    return true;
}


// Here should be the file crawling structure    
vector<string> crawl_files() {
    vector<string> output;
    dir_queue.push("/home"); // The entrypoint

    while (!dir_queue.empty() || !allCrawlersIdle()) {
        // Check for idle crawlers
        for (auto& crawler : crawlers) {
            if (crawler.current_state == Crawler::Idle) {
                // Assign a directory to the idle crawler
                if (!dir_queue.empty()) {
                    string directory = dir_queue.front();
                    dir_queue.pop();
                    crawler.crawl(directory);
                } else {
                    break; // No more directories to crawl
                }
            }
        }
    }

    return file_queue;
}
