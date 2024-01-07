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

    
    
    

    

    

    

    
}

