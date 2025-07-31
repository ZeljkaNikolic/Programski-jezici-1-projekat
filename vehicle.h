#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "nodes.h"
#include "najkrace_r.h"

class Vehicle {
private:
    std::string id;                 // Identifikator vozila
    double average_speed;           // Prosječna brzina kretanja vozila
    double max_speed;               // Maksimalna brzina kretanja vozila na segmentu puta
    double real_speed;           // Trenutna brzina kretanja vozila
    std::string start_location;   // Početna lokacija vozila(id)
    std::string end_location;     // Krajnja lokacija vozila(id)

public:
    // Konstruktor
    Vehicle(const std::string& _id, double _avg_speed, double _real_speed, const std::string& _start, const std::string&  _end);

    // Getteri i setteri
    std::string getId() const;
    double getAverageSpeed() const;
    double getMaxSpeed() const;
    double getCurrentSpeed() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;

    void setId(const std::string& _id);
    void setAverageSpeed(double _avg_speed) ;
    void setMaxSpeed(double _max_speed);
    void setCurrentSpeed(double _current_speed);
    void setStartLocation(const std::string& _start);
    void setEndLocation(const std::string& _end);


    
    void provozajSe(int, int, TrafficGraph, int t[][6]);

};