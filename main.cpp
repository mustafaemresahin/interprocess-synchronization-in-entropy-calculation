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

