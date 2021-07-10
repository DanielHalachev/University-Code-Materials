

#ifndef HW4_DEVELOPER_HPP
#define HW4_DEVELOPER_HPP

#include <string>

class TeamLead;

class Developer {
protected:
    std::string name;
    TeamLead *teamLead;
    double salary;
public:
    Developer(const std::string &name);

    // forbid copy constructor and operator= to prevent segmentation fault
    Developer(const Developer &other) = delete;

    Developer &operator=(const Developer &other) = delete;

    //make destructor default in order to prevent segmentation fault
    virtual ~Developer() = default;

    std::string getName() const;

    double getSalary() const;

    TeamLead *getTeamLead() const;

    void setTeamLead(TeamLead *newTeamLead);

    void setInitialSalary(const double &amount);

    void setSalary(const double &amount);

    void sendLeavingRequest();

    void sendPromotionRequest(const double &amount);
};


#endif //HW4_DEVELOPER_HPP
