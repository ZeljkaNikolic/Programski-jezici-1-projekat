#include "vehicle.h"




    // Konstruktor
    Vehicle::Vehicle(const std::string& _id, double _avg_speed, double _real_speed,const std::string &_start, const std::string &_end)
    {
        id=_id;
        average_speed=_avg_speed;
        real_speed=_real_speed;
        start_location=_start;
        end_location=_end;
    }

    // Getteri i setteri
    std::string Vehicle::getId() const { return id; }
    double Vehicle::getAverageSpeed() const { return average_speed; }
    double Vehicle::getMaxSpeed() const { return max_speed; }
    double Vehicle:: getCurrentSpeed() const { return real_speed; }
    std::string Vehicle::getStartLocation() const { return start_location; }
    std::string Vehicle::getEndLocation() const { return end_location; }

    void Vehicle::setId(const std::string& _id) { id = _id; }
    void Vehicle::setAverageSpeed(double _avg_speed) { average_speed = _avg_speed; }
    void Vehicle::setMaxSpeed(double _max_speed) { max_speed = _max_speed; }
    void Vehicle::setCurrentSpeed(double _current_speed) { real_speed = _current_speed; }
    void Vehicle::setStartLocation(const std::string& _start) { start_location = _start; }
    void Vehicle::setEndLocation(const std::string& _end) { end_location = _end; }


    void Vehicle::provozajSe(int i, int j, TrafficGraph g, int t[][6])
    {
        putanja(i,j,g,t,j);
    }
