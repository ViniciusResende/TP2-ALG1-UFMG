#include <iostream>
#include <limits>
#include <vector>
#include "rock.hpp"

/**
 * @brief Business Rule function, responsible for being the interface between the
 * system functions and the console, reading values, passing them to the internal
 * functions and, by the end, printing the entrance result.
 * 
 * @returns Default integer value 0.
 */
int main() {
  unsigned int friendsAmount = 0;
  unsigned int showsAmount = 0;

  do {
    std::cin >> friendsAmount;
    std::cin >> showsAmount;

    if((friendsAmount == 0) && (showsAmount == 0)) return 0;

    std::vector<float> summationFriendsRatingsVec(showsAmount, 0);
    float temporaryRead = 0;
    float maximumArrayValue = -(std::numeric_limits<float>::max());
    int maximumArrayValueIdx = -1;

    for(unsigned int i = 0; i < friendsAmount; i++) {
      for(unsigned int j = 0; j < showsAmount; j++) {
        std::cin >> temporaryRead;
        summationFriendsRatingsVec[j] += temporaryRead;
        if(i == friendsAmount - 1) {
          if(maximumArrayValue < summationFriendsRatingsVec[j]) {
            maximumArrayValue = summationFriendsRatingsVec[j];
            maximumArrayValueIdx = j;
          }
        }
      }
    }

    if(maximumArrayValue < 0) {
      std::cout << maximumArrayValueIdx + 1 << " " << maximumArrayValueIdx + 1 << std::endl;
    } else {
      struct Answ sol = MaximumSumSubArray(summationFriendsRatingsVec);
      std::cout << sol.mss.begin + 1 << " " << sol.mss.end + 1 << std::endl;
    }
  } while ((friendsAmount != 0) && (showsAmount != 0));
  

  return(0);
}
