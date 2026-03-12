
#ifndef TICTACTOE10_PARTICIPATION_H
#define TICTACTOE10_PARTICIPATION_H
#include <string>

class Participation {
private:
    std::string user;
    std::string meetingIdentifier;

public:
    // CONSTRUCTOR
    Participation(std::string u, std::string m) : user(u), meetingIdentifier(m) {}

    // GETTERS
    std::string getUser() const { return user; }
    
    std::string getMeetingIdentifier() const { return meetingIdentifier; }

    // SETTERS
    void setUser(std::string u) { this->user = u; }
    void setMeeting(std::string m) { this->meetingIdentifier = m; }
};

#endif //TICTACTOE10_PARTICIPATION_H
