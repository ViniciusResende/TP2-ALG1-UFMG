#include <vector>

// ---------------- DATA STRUCTURES ----------------
struct VecSpan {
  float value;
  int begin;
  int end;
};

struct Answ {
  struct VecSpan sum;
  struct VecSpan mss; // maximum sum subvector answer
  struct VecSpan suf;
  struct VecSpan pref;
};

// ---------------- ALGORITHM ----------------

/**
 * @brief Maximum Sum SubArray Algorithm interface, that allows the user to just
 * provide the vector and expect the answer without worrying about implementation
 * parameters needs.
 * 
 * @param V A float vector where wants to find the problem answer
 * @returns A Answ struct containing answer for the provided vector.
 */
struct Answ MaximumSumSubArray(std::vector<float> V);