#include "rock.hpp"

// ---------------- HELPERS ----------------

/**
 * @brief Helper function, responsible for receiving a two float values and
 * returning the one with greater value.
 * 
 * @param a The first float value to be compared.
 * @param b The second float value to be compared.
 * @returns The greatest float value between the two.
 */
float max(float a, float b) {
  return a > b ? a : b;
}

// ---------------- ALGORITHM HELPERS ----------------

/**
 * @brief Algorithm helper function, responsible for dealing with the greatest 
 * subvector algorithm base case, receiving a unique element value and its idx
 * and then returning a base case answer.
 * 
 * @param elementVal The value of the vector element on the idx index.
 * @param idx The element index on the initial vector.
 * @returns A base case answer struct containing convenient values according to
 * the elementVal.
 */
struct Answ handleBaseCase(float elementVal, int idx) {
  struct Answ thisAnsw;
  thisAnsw.sum = elementVal;

  float maxBetweenZeroAndElementVal = max(0, elementVal);
  int answerIdx = maxBetweenZeroAndElementVal > 0 ? idx : -1;

  thisAnsw.mss.value = maxBetweenZeroAndElementVal;
  thisAnsw.mss.begin = answerIdx;
  thisAnsw.mss.end = answerIdx;

  thisAnsw.suf.value = maxBetweenZeroAndElementVal;
  thisAnsw.suf.begin = answerIdx;
  thisAnsw.suf.end = answerIdx;

  thisAnsw.pref.value = maxBetweenZeroAndElementVal;
  thisAnsw.pref.begin = answerIdx;
  thisAnsw.pref.end = answerIdx;

  return thisAnsw;
}

/**
 * @brief Algorithm helper function, responsible for dealing with the Mss(Maximum Sum SubVector)
 * calculation, i.e., asserting values on the both vector halfs and attributing
 * the best to the MSS value, as well as it handles the calculation of the MSS begin
 * and end indexes.
 * 
 * @param left The answer struct form the left vector being united.
 * @param right The answer struct form the right vector being united.
 * @returns A VecSpan struct containing the new MSS value as well as it's begin
 * and end indexes.
 */
struct VecSpan handleCalcMss(struct Answ left, struct Answ right) {
  float leftMss = left.mss.value;
  float rightMss = right.mss.value;
  float middleSum = left.suf.value + right.pref.value;

  if(middleSum > leftMss && middleSum > rightMss) {
    struct VecSpan thisMss;
    thisMss.value = middleSum;
    thisMss.begin = left.suf.begin;
    thisMss.end = right.pref.end;
  
    return thisMss;
  }

  if(leftMss > rightMss)
    return left.mss;
  else
    return right.mss;
}

/**
 * @brief Algorithm helper function, responsible for dealing with the Suffix calculation, 
 * i.e., asserting values on the both vector halfs and attributing the best to the 
 * Suffix value, as well as it handles the calculation of the Suffix begin and end 
 * indexes.
 * 
 * @param left The answer struct form the left vector being united.
 * @param right The answer struct form the right vector being united.
 * @returns A VecSpan struct containing the new Suffix value as well as it's begin
 * and end indexes.
 */
struct VecSpan handleCalcSuf(struct Answ left, struct Answ right) {
  float rightSuf = right.suf.value;
  float rightPlusLeftSuf = right.sum + left.suf.value;

  if(rightPlusLeftSuf > rightSuf) {
    struct VecSpan thisSuf;
    thisSuf.value = rightPlusLeftSuf;
    thisSuf.begin = left.suf.begin;
    thisSuf.end = right.suf.end;

    return thisSuf;
  } else
    return right.suf;
}

/**
 * @brief Algorithm helper function, responsible for dealing with the Prefix calculation, 
 * i.e., asserting values on the both vector halfs and attributing the best to the 
 * Prefix value, as well as it handles the calculation of the Prefix begin and end 
 * indexes.
 * 
 * @param left The answer struct form the left vector being united.
 * @param right The answer struct form the right vector being united.
 * @returns A VecSpan struct containing the new Prefix value as well as it's begin
 * and end indexes.
 */
struct VecSpan handleCalcPref(struct Answ left, struct Answ right) {
  float leftPref = left.pref.value;
  float leftPlusRightPref = left.sum + right.pref.value;

  if(leftPlusRightPref > leftPref) {
    struct VecSpan thisPref;
    thisPref.value = leftPlusRightPref;
    thisPref.begin = left.pref.begin;
    thisPref.end = right.pref.end;

    return thisPref;
  } else
    return left.pref;
}

// ---------------- ALGORITHM ----------------

/**
 * @brief Maximum Sum SubArray Algorithm implementation in it's recursive and 
 * divide and conquer approach. Retrieves an answer struct with the Mss(Maximum 
 * Sum SubVector) and its begin and end indexes.
 * 
 * @param V A float vector where wants to find the problem answer
 * @param begin The begin index of the current analyzed subvector.
 * @param end The end index of the current analyzed subvector.
 * @returns A Answ struct containing answer for the current analyzed subvector.
 */
struct Answ MaximumSubArrayRecursive(std::vector<float> V, int begin, int end) {
  if(begin == end) return handleBaseCase(V[begin], begin);

  struct Answ thisAnsw;

  struct Answ leftAnsw = MaximumSubArrayRecursive(V, begin, (begin + end)/2);
  struct Answ rightAnsw = MaximumSubArrayRecursive(V, ((begin + end)/2) + 1, end);

  thisAnsw.sum = leftAnsw.sum + rightAnsw.sum;
  thisAnsw.mss = handleCalcMss(leftAnsw, rightAnsw);
  thisAnsw.suf = handleCalcSuf(leftAnsw, rightAnsw);
  thisAnsw.pref = handleCalcPref(leftAnsw, rightAnsw);

  return thisAnsw;
}

struct Answ MaximumSumSubArray(std::vector<float> V) {
  return MaximumSubArrayRecursive(V, 0, V.size());
}