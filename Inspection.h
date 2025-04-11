#ifndef INSPECTION_H
#define INSPECTION_H

#include <iostream>
#include <string>
using std::string;
using std::ostream;
using std::istream;

class Inspection {
public:
    Inspection();
    Inspection(int id, int agentId, int propertyId, const string &dateTime, const string &notes);

    // Getters
    int getId() const;
    int getAgentId() const;
    int getPropertyId() const;
    string getDateTime() const;
    string getNotes() const;

    // Setters
    void setId(int id);
    void setAgentId(int agentId);
    void setPropertyId(int propertyId);
    void setDateTime(const string &dateTime);
    void setNotes(const string &notes);

    // Validation
    bool isValid() const;

    // Overloaded stream operators
    friend ostream& operator<<(ostream &os, const Inspection &inspection);
    friend istream& operator>>(istream &is, Inspection &inspection);

private:
    int m_id;           // Use -1 if unsaved.
    int m_agentId;
    int m_propertyId;
    string m_dateTime;  // Expected format "YYYY-MM-DD HH:MM:SS" (as string)
    string m_notes;
};

#endif // INSPECTION_H
