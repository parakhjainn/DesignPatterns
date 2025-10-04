#pragma once
#include <string>
#include <vector>
#include "team.h"
#include "innings.h"
using namespace std;

class Match {
private:
    string matchId;
    Team team1;
    Team team2;
    string venue;
    string date;
    string time;
    string status;
    Innings innings1;
    Innings innings2;
    vector<string> commentary;
    bool isFirstInnings;

public:
    Match(const string& matchId,
          const Team& team1,
          const Team& team2,
          const string& venue,
          const string& date,
          const string& time,
          const string& status,
          const Innings& innings1,
          const Innings& innings2,
          const vector<string>& commentary)
        : matchId(matchId),
          team1(team1),
          team2(team2),
          venue(venue),
          date(date),
          time(time),
          status(status),
          innings1(innings1),
          innings2(innings2),
          commentary(), // initialize as empty vector
          isFirstInnings(true)
    {}

    bool getIsFirstInnings() const {
        return isFirstInnings;
    }

    void setIsFirstInnings(bool value) {
        isFirstInnings = value;
    }

    vector<string> getCommentary() const {
        return commentary;
    }

    void setCommentary(const vector<string>& comm) {
        commentary = comm;
    }

    string getMatchId() const {
        return matchId;
    }

    void setMatchId(const string& id) {
        matchId = id;
    }

    Team getTeam1() const {
        return team1;
    }

    void setTeam1(const Team& t1) {
        team1 = t1;
    }

    Team getTeam2() const {
        return team2;
    }

    void setTeam2(const Team& t2) {
        team2 = t2;
    }

    string getVenue() const {
        return venue;
    }

    void setVenue(const string& v) {
        venue = v;
    }

    string getDate() const {
        return date;
    }

    void setDate(const string& d) {
        date = d;
    }

    string getTime() const {
        return time;
    }

    void setTime(const string& t) {
        time = t;
    }

    string getStatus() const {
        return status;
    }

    void setStatus(const string& s) {
        status = s;
    }

    Innings getInnings1() const {
        return innings1;
    }

    void setInnings1(const Innings& i1) {
        innings1 = i1;
    }

    Innings getInnings2() const {
        return innings2;
    }

    void setInnings2(const Innings& i2) {
        innings2 = i2;
    }
};