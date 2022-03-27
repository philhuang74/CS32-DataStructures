//
//  CarMap.cpp
//  CS32_HW1
//
//  Created by Philip Huang on 1/16/22.
//

#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap(){
}

bool CarMap::addCar(std::string license){
    if(m_Map.insert(license,0)){
        return true;
    }
    else{
        return false;
    }
}
  // If a car with the given license plate is not currently in the map,
  // and there is room in the map, add an entry for that car recording
  // that it has been driven 0 miles, and return true.  Otherwise,
  // make no change to the map and return false.

double CarMap::miles(std::string license) const{
    if (m_Map.contains(license)){
        double value;
        m_Map.get(license, value);
        return value;
    }
    else{
        return -1;
    }
}
  // If a car with the given license plate is in the map, return how
  // many miles it has been driven; otherwise, return -1.

bool CarMap::drive(std::string license, double distance){
    if(!m_Map.contains(license) || distance < 0){
        return false;
    }
    else{ //m_Map contains license and distance > 0
        m_Map.update(license, distance);
        return true;
    }
}
  // If no car with the given license plate is in the map or if
  // distance is negative, make no change to the map and return
  // false.  Otherwise, increase by the distance parameter the number
  // of miles the indicated car has been driven and return true.

int CarMap::fleetSize() const{
    return m_Map.size();
}
// Return the number of cars in the CarMap.

void CarMap::print() const{
    for (int i=0; i < m_Map.size(); i++){
        std::string license;
        double miles;
        m_Map.get(i,license,miles);
        cout << license << " " << miles << "\n";
    }
}
  // Write to cout one line for every car in the map.  Each line
  // consists of the car's license plate, followed by one space,
  // followed by the number of miles that car has been driven.  Write
  // no other text.  The lines need not be in any particular order.
