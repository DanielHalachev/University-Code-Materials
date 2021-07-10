
#include "Developer.hpp"
#include "TeamLead.hpp"

Developer::Developer(const std::string &name) {
    this->name = name;
    this->salary = 0;
    this->teamLead = nullptr;
}

double Developer::getSalary() const {
    return this->salary;
}

std::string Developer::getName() const {
    return this->name;
}

TeamLead *Developer::getTeamLead() const {
    return this->teamLead;
}

void Developer::setTeamLead(TeamLead *newTeamLead) {
    this->teamLead = newTeamLead;
}

void Developer::setInitialSalary(const double &amount) {
    if (this->salary == 0) {
        this->salary = amount;
    }
}

void Developer::setSalary(const double &amount) {
    this->salary = amount;
}

void Developer::sendLeavingRequest() {
    if (this->teamLead != nullptr) {
        this->teamLead->addLeavingRequest(LeavingRequest(this->name));
    }
}

void Developer::sendPromotionRequest(const double &amount) {
    if (this->teamLead != nullptr) {
        this->teamLead->addPromotionRequest(PromotionRequest(this->name, amount));
    }
}