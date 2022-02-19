https://www.hackerrank.com/contests/sda-hw-10-2021/challenges/cinema-2021

#include <vector>
#include <iostream>

void infect(std::vector<std::vector<short>> &FMI, int j, int h, int i) {
    if (j < 0 || h < 0 || j >= FMI.size() || h >= FMI[j].size()) {
        return;
    }
    if (FMI[j][h] != -1) {
        return;
    }
    FMI[j][h] = (short) i + 1;
}

int main() {
    int n, m, t, k;
    std::cin >> n >> m >> t >> k;
    int temp1, temp2;
    std::vector<std::vector<short>> FMI(n, std::vector<short>(m, -1));
    for (int i = 0; i < k; i++) {
        std::cin >> temp1 >> temp2;
        FMI[temp1 - 1][temp2 - 1] = 1;
    }
    for (int i = 1; i <= t; i++) {
        for (int j = 0; j < n; j++) {
            for (int h = 0; h < m; h++) {
                if (FMI[j][h] == i) {
                    infect(FMI, j - 1, h, i);
                    infect(FMI, j, h - 1, i);
                    infect(FMI, j + 1, h, i);
                    infect(FMI, j, h + 1, i);
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (FMI[i][j] == -1) {
                sum++;
            }
        }
    }
    std::cout << sum;
}
