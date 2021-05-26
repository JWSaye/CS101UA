#include <iostream>

#include "zipcode.h"

using namespace std;

// Complete the constructor (try the new format from the example)
ZipCode::ZipCode(int zip, string city, string state, int lat, int lon) : zip(zip), city(city), state(state), lat(lat), lon(lon) {
   
}

// Implement the comparison logic
bool ZipCode::compare(ZipCode &rhs, ZipCode::CompareType t) {
   ZipCode &lhs = *this;
   switch(t) {
      case CompareType::LessZip:
         return lhs.getZip() < rhs.getZip();
      case CompareType::LessCityState:
         if(lhs.getCity() < rhs.getCity()) return true;
         if(lhs.getCity() > rhs.getCity()) return false;
         return lhs.getState() < rhs.getState();
      case CompareType::LessStateCity:
         if(lhs.getState() < rhs.getState()) return true;
         if(lhs.getState() > rhs.getState()) return false;
         return lhs.getCity() < rhs.getCity();
      case CompareType::LessLatLonState:
         if(lhs.getLat() < rhs.getLat()) return true;
         if(lhs.getLat() > rhs.getLat()) return false;
         if(lhs.getLon() < rhs.getLon()) return true;
         if(lhs.getLon() > rhs.getLon()) return false;
         return lhs.getState() < rhs.getState();
      case CompareType::LessLonLatState:
         if(lhs.getLon() < rhs.getLon()) return true;
         if(lhs.getLon() > rhs.getLon()) return false;
         if(lhs.getLat() < rhs.getLat()) return true;
         if(lhs.getLat() > rhs.getLat()) return false;
         return lhs.getState() < rhs.getState();

   }  
   return false;
}

// Do not edit below this line

void ZipCode::print() {
   cout << zip << "\t" << city << "\t";
   if (city.length() < 8) cout << "\t";
   cout << state << "\t" << lat << "\t"<< lon;
}

int ZipCode::getZip() {
   return zip;
}

string ZipCode::getCity() {
   return city;
}

string ZipCode::getState() {
   return state;
}

int ZipCode::getLat() {
   return lat;
}

int ZipCode::getLon() {
   return lon;
}
