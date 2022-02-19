https://www.hackerrank.com/contests/sda-hw-9-2021/challenges/weighing-animals

#include <iostream>
#include <map>

struct DefaultInt {
    long long value = 0;
};

int main() {
    long long n, k;
    std::cin >> n >> k;
    std::map<long long, DefaultInt> second;
    std::map<long long, DefaultInt> third;
    long long counter = 0;
    long long temp;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        counter += third[temp].value;
        third[temp * k].value += second[temp].value;
        second[temp * k].value++;
    }
    std::cout << counter;
    return 0;
}
