#include "../includes/crawler.h"

using namespace std;


// Global queues
queue<string> dir_queue;
vector<string> file_queue;

// Global protectors
mutex dir_queue_mutex;
mutex file_queue_mutex;
mutex crawler_mutex;

// Globals used for metrics
int crawlers_amount = 100;
int working_crawlers = 0;


class Crawler {
public:
    enum State { Idle, Busy };
    State current_state = Idle;

    void set_busy() {
        lock_guard<mutex> lock(crawler_mutex);
        working_crawlers++;
        current_state = Busy;
    }

    void set_idle() {
        lock_guard<mutex> lock(crawler_mutex);
        working_crawlers--;
        current_state = Idle;
    }

    void async_crawl(const string& directory) {
        // Sets busy state
        set_busy();
        thread([this, directory]() {
            try {
                crawl(directory);
            } catch (const exception& e) {
                cerr << "Exception in async crawl: " << e.what() << '\n';
            }
        }).detach(); // Detach the thread to let it run independently
    }

    void crawl(const string& directory) {
        // Update global queues
        try {
            for (const auto& entry : filesystem::directory_iterator(directory)) {
                if (entry.is_directory()) {
                    lock_guard<mutex> lock(dir_queue_mutex);
                    dir_queue.push(entry.path().string());
                } else if (entry.is_regular_file()) {
                    lock_guard<mutex> lock(file_queue_mutex);
                    file_queue.push_back(entry.path().string());
                }
            }
        } catch (const filesystem::filesystem_error& e) {
            // Ignores permission denied errors
            // cerr << "Filesystem error: " << e.what() << '\n';
        } catch (const std::exception& e) {
            cerr << "General error: " << e.what() << '\n';
        }
        // Sets idle state
        set_idle();
    }
};

vector<Crawler> crawlers(crawlers_amount); // List of crawlers (should have a way to set different sizes)

// Here should be the file crawling structure    
vector<string> crawl_files() {
    vector<string> output;

    // Base directories to look
    dir_queue.push("/home");
    dir_queue.push("/var");
    dir_queue.push("/etc");

    int i = 0;
    while (!dir_queue.empty() || working_crawlers > 0) {
        // Debug
        // cout << working_crawlers << "/" << crawlers_amount << " active crawlers" << endl;

        // Check for idle crawlers
        if (crawlers[i].current_state == Crawler::Idle) {
            // Assign a directory to the idle crawler
            if (!dir_queue.empty()) {
                lock_guard<mutex> lock(dir_queue_mutex);
                string directory = dir_queue.front();
                dir_queue.pop();
                // cout << directory << endl;
                crawlers[i].async_crawl(directory);
            } else if (working_crawlers == 0) {
                break; // No more directories to crawl
            }
        }
        i++;
        // Goes back to the start of the list
        if (i > crawlers_amount) {
            i = 0;
        }
    }

    return file_queue;
}
