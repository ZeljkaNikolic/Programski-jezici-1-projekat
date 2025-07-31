#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>

class IntersectionEdge
{
private:
    std::string input_node_id;  // ID ulaznog čvora
    std::string output_node_id; // ID izlaznog čvora
    bool can_cross;             // Informacija o mogućnosti prelaska s jednog na drugi čvor
    double length;              // Dužina puta
    double average_speed;       // Prosječna brzina kretanja vozila
public:
    // Konstruktor
    IntersectionEdge(const std::string &input_id, const std::string &output_id, bool can_cross, double length, double average_speed);
    std::string getInput() const;
    std::string getOutput() const;

    void setInput(const std::string &i);

    void setOutput(const std::string &o);

    bool getCan_cross() const;

    void setCan_cross(bool info);

    double getLength() const;

    void setLength(double l);

    double getAverage_speed() const;

    void setAverage_speed(double a);
};

// Klasa za čvor mreže
class Node
{
private:
    std::string type; // Tip čvora: "location", "road", "intersection"
    std::string id;   // Identifikator čvora
public:
    std::string getType() const;
    void setType(const std::string &tip);

    std::string getId() const;

    void setId(const std::string &id);
};

// Klasa za čvor lokacije
class LocationNode : public Node
{
public:
    LocationNode(const std::string &_id);
};

// Klasa za čvor puta
class RoadNode : public Node
{
private:
    double length;    // Dužina puta u metrima
    int max_speed;    // Maksimalna dozvoljena brzina kretanja na putu
    int max_vehicles; // Maksimalan broj vozila na putu
public:
    // Konstruktor
    RoadNode(const std::string &_id, double _length, int _max_speed, int _max_vehicles);
    double getLength() const;

    void setLength(double l);

    int getMax_speed() const;

    void setMax_speed(int s);

    int getMax_vehicles() const;
    void setMax_vehicles(int v);
};

// Klasa za čvor raskrsnice
class IntersectionNode : public Node
{
private:
    int max_vehicless;

public:
    std::vector<RoadNode *> incoming_roads; // Ulazni putevi sa pripadajućim dužinama
    std::vector<RoadNode *> outgoing_roads; // Izlazni putevi raskrsnice
    std::vector<IntersectionEdge *> edges;

    IntersectionNode(const std::string &_id, int _max_vehicles);

    int getMax_vehicless() const;

    void setMax_vehicless(int ve);

    // Metoda za dodavanje ulaznog puta
    void addIncomingRoad(RoadNode *road);
    // Metoda za dodavanje izlaznog puta
    void addOutgoingRoad(RoadNode *road);

    void addEdge(const std::string &input_id, const std::string &output_id, bool can_cross, double length, double average_speed);

    void printEdges();
};

class TrafficGraph
{
public:
    int n;
    std::vector<int> nodesInMatrix;
    std::vector<Node *> nodes;
    std::vector<RoadNode *> roadNodes;
    std::string matrix[6][6];

    void printMatrix() const;

    // Serijalizacija grafa
    void serialize(const std::string &filename);

    //Deserijalizacija grafa
    void deserialize(const std::string &filename, TrafficGraph &);

    //F-ja vraca pokazivac na cvor na osnovu id
    RoadNode *findRoadNodeById(const std::string &id) const;

    //F-ja vraca duzinu puta, prima pokazivac na cvor
    double getDistanceFromRoadId(RoadNode *) const;

    //F-ja pravi novi niz, izbacujuci duplikate
    void eliminateDuplicate();
};