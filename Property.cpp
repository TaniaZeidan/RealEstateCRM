#include "Property.h"
#include "Exceptions.h"
#include <stdexcept>
#include <algorithm>

Property::Property() : m_id(-1), m_sizeSqm(0.0), m_price(0.0), m_bedrooms(0), m_bathrooms(0), m_available(true) {}

Property::Property(int id, double sizeSqm, double price, const std::string &propertyType,
                   int bedrooms, int bathrooms, const std::string &place,
                   bool available, const std::string &listingType)
    : m_id(id), m_sizeSqm(sizeSqm), m_price(price), m_bedrooms(bedrooms), m_bathrooms(bathrooms), m_place(place), m_available(available)
{
    setPropertyType(propertyType);
    setListingType(listingType);
}

int Property::getId() const { return m_id; }
double Property::getSizeSqm() const { return m_sizeSqm; }
double Property::getPrice() const { return m_price; }
std::string Property::getPropertyType() const { return m_propertyType; }
int Property::getBedrooms() const { return m_bedrooms; }
int Property::getBathrooms() const { return m_bathrooms; }
std::string Property::getPlace() const { return m_place; }
bool Property::getAvailability() const { return m_available; }
std::string Property::getListingType() const { return m_listingType; }

void Property::setId(int id) { m_id = id; }
void Property::setSizeSqm(double sizeSqm) { m_sizeSqm = sizeSqm; }
void Property::setPrice(double price) { m_price = price; }
void Property::setPropertyType(const std::string &propertyTypeInput) {
        // Make a copy and convert to lowercase
    std::string propertyType = propertyTypeInput;
    std::transform(propertyType.begin(), propertyType.end(), propertyType.begin(), ::tolower);

    // Optionally trim leading/trailing spaces, then check
    if (propertyType != "land" && propertyType != "house" && propertyType != "apartment")
        throw ValidationException("Property type must be 'land', 'house', or 'apartment'.");
    
    m_propertyType = propertyTypeInput;
}
void Property::setBedrooms(int bedrooms) { m_bedrooms = bedrooms; }
void Property::setBathrooms(int bathrooms) { m_bathrooms = bathrooms; }
void Property::setPlace(const std::string &place) { m_place = place; }
void Property::setAvailability(bool available) { m_available = available; }
void Property::setListingType(const std::string &listingType) {
    if (listingType != "sale" && listingType != "rent")
        throw ValidationException("Listing type must be 'sale' or 'rent'.");
    m_listingType = listingType;
}

bool Property::isValid() const {
    if(m_sizeSqm <= 0) return false;
    if(m_price < 0) return false;
    if(m_propertyType != "land" && m_propertyType != "house" && m_propertyType != "apartment")return false;
    if(m_bedrooms < 0 || m_bathrooms < 0)return false;
    if(m_listingType != "sale" && m_listingType != "rent")return false;

    return true;
        
}

std::ostream& operator<<(std::ostream &os, const Property &property) {
    
    os << "ID: " << property.m_id
       << "\nSize: " << property.m_sizeSqm << " sqm"
       << "\nPrice: " << property.m_price
       << "\nType: " << property.m_propertyType
       << "\nBed: " << property.m_bedrooms
       << "\nBath: " << property.m_bathrooms
       << "\nPlace: " << property.m_place
       << "\nAvailability: " << (property.m_available ? "Yes" : "No")
       << "\nListing: " << property.m_listingType;
    return os;
}

std::istream& operator>>(std::istream &is, Property &property) {
    // Order: id, sizeSqm, price, propertyType, bedrooms, bathrooms, place, available (0/1), listingType
    int avail;
    is >> property.m_id >> property.m_sizeSqm >> property.m_price >> property.m_propertyType
       >> property.m_bedrooms >> property.m_bathrooms >> property.m_place >> avail >> property.m_listingType;
    property.m_available = (avail != 0);
    return is;
}
