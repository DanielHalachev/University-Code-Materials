
#ifndef HW4_TEAMLEAD_HPP
#define HW4_TEAMLEAD_HPP


#include "Developer.hpp"
#include "PromotionRequest.hpp"
#include "LeavingRequest.hpp"
#include <vector>

class TeamLead : public Developer {
private:
    std::vector<Developer *> team;
    std::vector<LeavingRequest> leavingRequests;
    std::vector<PromotionRequest> promotionRequests;
public:
    TeamLead(const std::string &name, double salary);

    // forbid copy constructor and operator= because the team
    // developers are pointers and can't have more than one team leader
    TeamLead(const TeamLead &other) = delete;

    TeamLead &operator=(const TeamLead &other) = delete;

    // set the destructor to default in order to prevent double freeing
    ~TeamLead() override = default;

    std::vector<Developer *> &getTeam();

    void addDeveloperToTeam(Developer *developer, double salary);

    void removeDeveloperFromTeam(const std::string &name);

    void increaseTeamSalariesBy(const double &amount);

    void decreaseTeamSalariesBy(const double &amount);

    void fulfillLeavingRequests();

    void fulfillPromotionRequests();

    void addPromotionRequest(const PromotionRequest &promotionRequest);

    void addLeavingRequest(const LeavingRequest &leavingRequest);
};


#endif //HW4_TEAMLEAD_HPP
