#include <iostream>
#include "2/TeamLead.hpp"

int main() {
    Developer d1("John");
    Developer d2("Eric");
    TeamLead t1("Boss", 2000);
    t1.addDeveloperToTeam(&d1, 1500);
    t1.addDeveloperToTeam(&d2, 1600);
    t1.increaseTeamSalariesBy(100);
    t1.decreaseTeamSalariesBy(200);
    for (Developer *dev:t1.getTeam()) {
        std::cout << dev->getName() << ", " << dev->getSalary() << std::endl;
    }
    d1.sendPromotionRequest(500);
    t1.fulfillPromotionRequests();
    d1.sendLeavingRequest();
    t1.fulfillLeavingRequests();
//    t1.removeDeveloperFromTeam("John");
    std::cout << "After leaving:" << std::endl;
    for (Developer *dev:t1.getTeam()) {
        std::cout << dev->getName() << ", " << dev->getSalary() << std::endl;
    }
    std::cout << "Developer:" << std::endl;
    std::cout << d1.getName() << ", " << d1.getSalary() << ", " << d1.getTeamLead();
    return 0;
}
