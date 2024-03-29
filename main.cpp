#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <pthread.h>
#include <sstream>
#include <string>
#include <vector>

// Define a struct to hold thread data
struct ThreadData {
  std::vector<std::string> input;    // Vector to store input strings for each thread
  int id;                            // ID to identify the thread
  int *counter;                      // Pointer to a counter used for synchronization
  pthread_mutex_t *first_mutex;      // Pointer to the first mutex for synchronization
  pthread_mutex_t *second_mutex;     // Pointer to the second mutex for synchronization
  pthread_cond_t *turn_cond;         // Pointer to the condition variable for turn-based synchronization
};

// Function to calculate incremental entropy
double calc_incremental_entropy(std::map<char, int> &freq, int &currFreq, double &currH, char selectedTask, int extraFreq, int &NFreq) {
  double H, newTerm, currentTerm;

  // Update the total frequency
  NFreq = currFreq + extraFreq;

  // Calculate the entropy
  if (NFreq == extraFreq) {
    H = 0;
  } else {
    currentTerm = freq[selectedTask] == 0 ? 0 : freq[selectedTask]*log2(freq[selectedTask]);
    newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq);
    NFreq = static_cast<double>(NFreq);
    H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq)-currentTerm + newTerm) / NFreq;
  }

  // Update the current frequency and entropy
  currFreq = NFreq;
  currH = H;

  return H;
};

// Thread function to calculate entropy
void *entropy(void *arg) {
    std::vector<double> entropies;  // Vector to store calculated entropies
    ThreadData *data = (ThreadData *)arg;  // Cast argument to ThreadData pointer

    // Extract local input and ID for this thread
    std::string localInput = data->input[data->id];
    int localID = data->id;

    // Unlock the first mutex signaling this thread is ready
    pthread_mutex_unlock(data->first_mutex);

    // Stream to parse input string
    std::istringstream iss(localInput);
    char selectedTask;
    int extraFreq;
    std::map<char, int> freq;  // Map to store frequency of tasks
    int currFreq = 0;
    double currH = 0.0;
    int NFreq = 0;

    // Parse input and calculate entropy for each task
    while (iss >> selectedTask >> extraFreq) {
        if (freq.find(selectedTask) == freq.end()) {
        freq[selectedTask] = 0;
        }
        double ent = calc_incremental_entropy(freq, currFreq, currH, selectedTask, extraFreq, NFreq);
        freq[selectedTask] += extraFreq;
        entropies.push_back(ent);
    }

    // Synchronize output by waiting for turn
    pthread_mutex_lock(data->second_mutex);
    while (*data->counter != localID) {
        pthread_cond_wait(data->turn_cond, data->second_mutex);
    }
    pthread_mutex_unlock(data->second_mutex);

    // Output results for this thread
    std::cout << "CPU " << localID + 1 << std::endl;
    std::cout << "Task scheduling information: ";
    std::istringstream iss2(localInput);
    char task;
    int time;
    bool first = true;

    // Display task scheduling information
    while (iss2 >> task >> time) {
        if (!first)
        std::cout << ", ";
        std::cout << task << "(" << time << ")";
        first = false;
    }

    std::cout << std::endl << "Entropy for CPU " << localID + 1 << std::endl;
    // Display calculated entropy values
    for (double e : entropies) {
        std::cout << std::fixed << std::setprecision(2) << e << ' ';
    }
    std::cout << std::endl << std::endl;

    // Signal this thread's completion and wake up other threads
    pthread_mutex_lock(data->second_mutex);
    (*data->counter)++;
    pthread_cond_broadcast(data->turn_cond);
    pthread_mutex_unlock(data->second_mutex);

    return NULL;
}

int main() {
  std::string line;
  int length = 0;

  // Initialize mutexes and condition variable
  pthread_mutex_t first_mutex;
  pthread_mutex_init(&first_mutex, nullptr);
  pthread_mutex_t second_mutex;
  pthread_mutex_init(&second_mutex, nullptr);
  pthread_cond_t turn_cond = PTHREAD_COND_INITIALIZER;
  static int counter = 0;

  // Initialize ThreadData struct
  ThreadData data;
  data.first_mutex = &first_mutex;
  data.second_mutex = &second_mutex;
  data.turn_cond = &turn_cond;
  data.counter = &counter;

  // Read input lines for task scheduling
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    data.input.push_back(line);
    length++;
  }
  std::vector<pthread_t> tid(length);  // Vector to store thread IDs
  
  // Create threads for entropy calculation
  for (int i = 0; i < length; i++) {
    pthread_mutex_lock(&first_mutex);
    data.id = i;
    pthread_create(&tid[i], NULL, entropy, &data);
  }

  // Wait for all threads to complete
  for (int i = 0; i < length; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
