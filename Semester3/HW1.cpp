#include <iostream>
#include <string>
#include <algorithm>

// Task 1: A number of letters is given and a word is repeated until it fills the number of symbols.
// Say how many times a specific letter has been repeated in the resulting string
unsigned int findNumberOfOccurances(const std::string &word, const unsigned int &number, const char &letter) {

    int remainder = number % word.length();
    unsigned int count = 0;
    for (char i: word) {
        if (i == letter) {
            count++;
        }
    }
    if (count == 0) {
        return 0;
    }
    if (word.length() > number) {
        return count;
    }
    count = (number / word.length()) * count;
    for (int i = 0; i < remainder; i++) {
        if (word.at(i) == letter) {
            count++;
        }
    }
    return count;
}

// Task2: A teacher gives students, ordered in a row, a specific variant of a test.
// A new student arrives late and must be seated the furthest from a student with his variant.
// Print the distance between each of the variants in the row and the late student's variant.
void printDistance(std::string word, const char variant) {
    // assigning word length a variable to avoid recalculating every time when using
    int length = word.length();
    // here we store the distances
    int *data = new int[length];
    // temporary variable to store the distance
    // theoretically it can only be the length of the word minus one at most
    int distance = length - 1;
    // find direct hits and calculate the distances on their right
    for (int i = 0; i < length; i++) {
        if (word[i] == variant) {
            data[i] = 0;
            distance = 0;
        } else {
            distance++;
            data[i] = distance;
        }
    }
    // now we calculate distances on the left of each direct hit
    // we start from the direct hit itself
    length = length - distance - 1;
    distance = 0;
    for (int i = length; i >= 0; i--) {
        if (word[i] == variant) {
            data[i] = 0;
            distance = 0;
        } else {
            distance++;
            if (data[i] > distance) {
                data[i] = distance;
            }
        }
    }
    // print data
    for (int i = 0; i < word.length(); i++) {
        std::cout << data[i] << " ";
    }
    // free memory
    delete[] data;
}

// Task3: 
// A team uses different numbers for team members(including negative and repeated). Return the smallest unused number.
int lowestUnusedTeamNumber(int *team, int teamSize) {
    // sort using std::sort - O(N*ln N)
    std::sort(team, team + teamSize);
    for (int i = 0; i < teamSize; i++) {
        if (team[i] < 0) {
            team[i] = 0;
        }
    }
    //edge case
    if (team[0] > 1) {
        return 1;
    }
    // skip numbers if they are increasing by one
    for (int i = 0; i < teamSize - 1; i++) {
        if (team[i] + 1 < team[i + 1]) {
            return team[i] + 1;
        }
    }
    // no "holes" in the progression found
    // then the lowest available number is the one after the last
    return team[teamSize - 1] + 1;
}

int main() {
    // get array size
    int n;
    std::cin >> n;
    int *team = new int[n];
    // assign array values
    for (int i = 0; i < n; i++) {
        std::cin >> team[i];
    }
    // print result
    std::cout << lowestUnusedTeamNumber(team, n);
    // free memory
    delete[] team;
    return 0;
}
