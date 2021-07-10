

#include <iostream>
#include "TeamLead.hpp"

TeamLead::TeamLead(const std::string &name, const double salary) : Developer(name) {
    this->teamLead = this;
    this->salary = salary;
}


std::vector<Developer *> &TeamLead::getTeam() {
    return (this->team);
}

void TeamLead::addDeveloperToTeam(Developer *developer, const double salary) {
    // check if developer exists before assignment
    if (developer != nullptr) {
        developer->setTeamLead(this);
        this->team.push_back(developer);
        this->team.back()->setSalary(salary);
    }
}

void TeamLead::removeDeveloperFromTeam(const std::string &name) {
    // check if the vector is empty before doing things
    if (this->team.empty()) {
        return;
    }
    for (unsigned int i = this->team.size() - 1; i >= 0; i--) {
        if (this->team[i]->getName() == name) {
            std::cout << "i=" << i << ": ";
            std::cout << "Erasing" << this->team[i]->getName() << std::endl;
            this->team[i]->setTeamLead(nullptr);
            this->team.erase(this->team.begin() + i);
            break;
        }
    }
}

void TeamLead::increaseTeamSalariesBy(const double &amount) {
    for (Developer *developer: this->team) {
        developer->setSalary(developer->getSalary() + amount);
    }
}

void TeamLead::decreaseTeamSalariesBy(const double &amount) {
    for (Developer *developer: this->team) {
        developer->setSalary(developer->getSalary() - amount);
    }
}

void TeamLead::addLeavingRequest(const LeavingRequest &leavingRequest) {
    this->leavingRequests.push_back(leavingRequest);
}

void TeamLead::addPromotionRequest(const PromotionRequest &promotionRequest) {
    this->promotionRequests.push_back(promotionRequest);
}

void TeamLead::fulfillLeavingRequests() {
    // remove all devs's boss
    for (LeavingRequest &leavingRequest :this->leavingRequests) {
        this->removeDeveloperFromTeam(leavingRequest.getSender());
    }
    // clear requests
    this->leavingRequests.clear();
}

void TeamLead::fulfillPromotionRequests() {
    //promote all devs
    for (PromotionRequest &promotionRequest :this->promotionRequests) {
        for (Developer *developer:this->team) {
            if (developer->getName() == promotionRequest.getSender()) {
                developer->setSalary(developer->getSalary() + promotionRequest.getAmount());
                break;
            }
        }
    }
    // clear requests
    this->promotionRequests.clear();
}

