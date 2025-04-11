#include "Inspection.h"
#include <sstream>

Inspection::Inspection() : m_id(-1), m_agentId(-1), m_propertyId(-1) {}

Inspection::Inspection(int id, int agentId, int propertyId, const string &dateTime, const string &notes)
    : m_id(id), m_agentId(agentId), m_propertyId(propertyId), m_dateTime(dateTime), m_notes(notes)
{}

int Inspection::getId() const { return m_id; }
int Inspection::getAgentId() const { return m_agentId; }
int Inspection::getPropertyId() const { return m_propertyId; }
string Inspection::getDateTime() const { return m_dateTime; }
string Inspection::getNotes() const { return m_notes; }

void Inspection::setId(int id) { m_id = id; }
void Inspection::setAgentId(int agentId) { m_agentId = agentId; }
void Inspection::setPropertyId(int propertyId) { m_propertyId = propertyId; }
void Inspection::setDateTime(const string &dateTime) { m_dateTime = dateTime; }
void Inspection::setNotes(const string &notes) { m_notes = notes; }

bool Inspection::isValid() const {
    if(m_agentId < 0 || m_propertyId < 0) return false;
    if(m_dateTime.empty()) return false;
    return true;
}

ostream& operator<<(ostream &os, const Inspection &inspection) {
    os << "ID: " << inspection.m_id
       << "\nAgent ID: " << inspection.m_agentId
       << "\nProperty ID: " << inspection.m_propertyId
       << "\nDate/Time: " << inspection.m_dateTime
       << "\nNotes: " << inspection.m_notes;
    return os;
}

istream& operator>>(istream &is, Inspection &inspection) {
    is >> inspection.m_id >> inspection.m_agentId >> inspection.m_propertyId;
    is >> inspection.m_dateTime >> inspection.m_notes;
    return is;
}
