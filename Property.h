#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
#include <string>
#include "Exceptions.h"

class Property {
public:
    Property();
    Property(int id, double sizeSqm, double price, const std::string &propertyType,
             int bedrooms, int bathrooms, const std::string &place,
             bool available, const std::string &listingType);

    // Getters
    int getId() const;
    double getSizeSqm() const;
    double getPrice() const;
    std::string getPropertyType() const;
    int getBedrooms() const;
    int getBathrooms() const;
    std::string getPlace() const;
    bool getAvailability() const;
    std::string getListingType() const;

    // Setters
    void setId(int id);
    void setSizeSqm(double sizeSqm);
    void setPrice(double price);
    void setPropertyType(const std::string &propertyType); // "land", "house", or "apartment"
    void setBedrooms(int bedrooms);
    void setBathrooms(int bathrooms);
    void setPlace(const std::string &place);
    void setAvailability(bool available);
    void setListingType(const std::string &listingType); // "sale" or "rent"

    // Validation
    bool isValid() const;

    // Overloaded stream operators
    friend std::ostream& operator<<(std::ostream &os, const Property &property);
    friend std::istream& operator>>(std::istream &is, Property &property);

private:
    int m_id;
    double m_sizeSqm;
    double m_price;
    std::string m_propertyType;
    int m_bedrooms;
    int m_bathrooms;
    std::string m_place;
    bool m_available;
    std::string m_listingType;
};

#endif // PROPERTY_H
