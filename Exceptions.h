#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base exception class for the CRM system
class CRMException : public std::runtime_error {
public:
    CRMException(const std::string& message) : std::runtime_error(message) {}
};

// Entity not found exceptions
class EntityNotFoundException : public CRMException {
public:
    EntityNotFoundException(const std::string& entity, int id) 
        : CRMException(entity + " with ID " + std::to_string(id) + " not found"), entityType(entity), entityId(id) {}
    
    std::string getEntityType() const { return entityType; }
    int getEntityId() const { return entityId; }

private:
    std::string entityType;
    int entityId;
};

class AgentNotFoundException : public EntityNotFoundException {
public:
    AgentNotFoundException(int id) : EntityNotFoundException("Agent", id) {}
};

class ClientNotFoundException : public EntityNotFoundException {
public:
    ClientNotFoundException(int id) : EntityNotFoundException("Client", id) {}
};

class PropertyNotFoundException : public EntityNotFoundException {
public:
    PropertyNotFoundException(int id) : EntityNotFoundException("Property", id) {}
};

class ContractNotFoundException : public EntityNotFoundException {
public:
    ContractNotFoundException(int id) : EntityNotFoundException("Contract", id) {}
};

// Validation exceptions
class ValidationException : public CRMException {
public:
    ValidationException(const std::string& message) : CRMException("Validation error: " + message) {}
};

class InvalidEmailException : public ValidationException {
public:
    InvalidEmailException(const std::string& email) 
        : ValidationException("Invalid email format: " + email), email(email) {}
    
    std::string getEmail() const { return email; }

private:
    std::string email;
};

class InvalidPhoneException : public ValidationException {
public:
    InvalidPhoneException(const std::string& phone) 
        : ValidationException("Phone must be exactly 8 numeric digits: " + phone), phone(phone) {}
    
    std::string getPhone() const { return phone; }

private:
    std::string phone;
};

class InvalidDateException : public ValidationException {
public:
    InvalidDateException(const std::string& date) 
        : ValidationException("Invalid date format or value: " + date), date(date) {}
    
    std::string getDate() const { return date; }

private:
    std::string date;
};

class InvalidDateRangeException : public ValidationException {
public:
    InvalidDateRangeException(const std::string& startDate, const std::string& endDate) 
        : ValidationException("End date " + endDate + " must be after start date " + startDate),
          startDate(startDate), endDate(endDate) {}
    
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }

private:
    std::string startDate;
    std::string endDate;
};

class FileOperationException : public CRMException {
public:
    FileOperationException(const std::string& filename, const std::string& operation) 
        : CRMException("File operation failed: " + operation + " on file " + filename),
          filename(filename), operation(operation) {}
    
    std::string getFilename() const { return filename; }
    std::string getOperation() const { return operation; }

private:
    std::string filename;
    std::string operation;
};

class AuthenticationException : public CRMException {
public:
    AuthenticationException(const std::string& username) 
        : CRMException("Authentication failed for user: " + username), username(username) {}
    
    std::string getUsername() const { return username; }

private:
    std::string username;
};

#endif 