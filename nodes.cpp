#include "nodes.h"

// INTERSECTION EDGE
IntersectionEdge::IntersectionEdge(const std::string &input_id, const std::string &output_id, bool can_cross, double length, double average_speed)
    : input_node_id(input_id), output_node_id(output_id), can_cross(can_cross), length(length), average_speed(average_speed) {}

std::string IntersectionEdge::getInput() const
{
    return input_node_id;
}

std::string IntersectionEdge::getOutput() const
{
    return output_node_id;
}

void IntersectionEdge::setInput(const std::string &i)
{
    input_node_id = i;
}

void IntersectionEdge::setOutput(const std::string &o)
{
    output_node_id = o;
}

bool IntersectionEdge::getCan_cross() const
{
    return can_cross;
}

void IntersectionEdge::setCan_cross(bool info)
{
    can_cross = info;
}

double IntersectionEdge::getLength() const
{
    return length;
}

void IntersectionEdge::setLength(double l)
{
    length = l;
}

double IntersectionEdge::getAverage_speed() const
{
    return average_speed;
}

void IntersectionEdge::setAverage_speed(double a)
{
    average_speed = a;
}

// NODE

std::string Node::getType() const
{
    return type;
}
void Node::setType(const std::string &tip)
{
    type = tip;
}

std::string Node::getId() const
{
    return id;
}

void Node::setId(const std::string &id)
{
    this->id = id;
}

// LOCATION NODE

LocationNode::LocationNode(const std::string &_id)
{
    setType("location");
    setId(_id);
}

// ROAD NODE

RoadNode::RoadNode(const std::string &_id, double _length, int _max_speed, int _max_vehicles)
{
    setType("road");
    setId(_id);
    length = _length;
    max_speed = _max_speed;
    max_vehicles = _max_vehicles;
}
double RoadNode::getLength() const
{
    return length;
}

void RoadNode::setLength(double l)
{
    length = l;
}

int RoadNode::getMax_speed() const
{
    return max_speed;
}

void RoadNode::setMax_speed(int s)
{
    max_speed = s;
}

int RoadNode::getMax_vehicles() const
{
    return max_vehicles;
}
void RoadNode::setMax_vehicles(int v)
{
    max_vehicles = v;
}

// INTERSECTION NODE

IntersectionNode ::IntersectionNode(const std::string &_id, int _max_vehicles)
{
    setType("intersection");
    setId(_id);
    max_vehicless = _max_vehicles;
}

int IntersectionNode ::getMax_vehicless() const
{
    return max_vehicless;
}

void IntersectionNode ::setMax_vehicless(int ve)
{
    max_vehicless = ve;
}

// Metoda za dodavanje ulaznog puta
void IntersectionNode ::addIncomingRoad(RoadNode *road)
{
    incoming_roads.push_back(road);
}

// Metoda za dodavanje izlaznog puta
void IntersectionNode ::addOutgoingRoad(RoadNode *road)
{
    outgoing_roads.push_back(road);
}

void IntersectionNode::addEdge(const std::string &input_id, const std::string &output_id, bool can_cross, double length, double average_speed)
{
    IntersectionEdge *newEdge = new IntersectionEdge(input_id, output_id, can_cross, length, average_speed);
    edges.push_back(newEdge);
}
void IntersectionNode ::printEdges()
{
    for (IntersectionEdge *edge : edges)
        std::cout << edge->getInput() << ", " << edge->getOutput() << ", " << edge->getCan_cross() << ", " << edge->getLength() << ", " << edge->getAverage_speed() << std::endl;
}

// TRAFFIC GRAPH
void TrafficGraph::printMatrix() const
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
            std::cout << std::setw(6) << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

// Serijalizacija grafa
void TrafficGraph::serialize(const std::string &filename)
{
    std::ofstream file(filename);
    if (file.is_open())
    {
        file << nodesInMatrix.size() << std::endl;
        // Serijalizacija čvorova
        for (Node *node : nodes)
        {

            if (node->getType() == "intersection")
            {
                IntersectionNode *intersection = static_cast<IntersectionNode *>(node);
                file << "Intersection " << intersection->getId() << " " << intersection->getMax_vehicless() << std::endl;

                for (RoadNode *road : intersection->incoming_roads)
                {
                    file << "  InRoad " << road->getId() << " " << road->getLength() << " " << road->getMax_speed() << " " << road->getMax_vehicles() << std::endl;
                }

                for (RoadNode *road : intersection->outgoing_roads)
                {
                    file << "  OutRoad " << road->getId() << " " << road->getLength() << " " << road->getMax_speed() << " " << road->getMax_vehicles() << std::endl;
                }
                file << "Edges (input_node_id, output_node_id, can cross/can't cross, length, average speed):" << std::endl;
                for (IntersectionEdge *e : intersection->edges)
                {
                    file << "   " << e->getInput() << " " << e->getOutput() << " " << e->getCan_cross() << " " << e->getLength() << " " << e->getAverage_speed() << std::endl;
                }
            }
            else if (node->getType() == "location")
            {
                LocationNode *location = static_cast<LocationNode *>(node);
                file << "Location " << location->getId() << std::endl;
            }
        }

        // Serijalizacija matrice
        file << "Matrix" << std::endl;
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                file << matrix[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
    }
}

//Deserijalizacija grafa
void TrafficGraph::deserialize(const std::string &filename, TrafficGraph &graph)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            iss >> graph.n; // Učitavanje broja čvorova
        }
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "Location")
            {
                std::string id;
                iss >> id;
                LocationNode *location = new LocationNode(id);
                graph.nodes.push_back(location);
            }
            else if (type == "Intersection")
            {
                std::string id;
                int max_vehicles;
                iss >> id >> max_vehicles;
                IntersectionNode *intersection = new IntersectionNode(id, max_vehicles);
                graph.nodes.push_back(intersection);

                // Čitanje svih linija za ovu raskrsnicu
                while (std::getline(file, line))
                {
                    std::istringstream roadIss(line);
                    std::string roadType;
                    roadIss >> roadType;
                    if (roadType == "InRoad" || roadType == "OutRoad")
                    {
                        std::string roadId;
                        double length;
                        int max_speed, max_vehicles;
                        roadIss >> roadId >> length >> max_speed >> max_vehicles;
                        RoadNode *road = new RoadNode(roadId, length, max_speed, max_vehicles);
                        graph.roadNodes.push_back(road);
                        if (roadType == "InRoad")
                            intersection->addIncomingRoad(road);
                        else if (roadType == "OutRoad")
                            intersection->addOutgoingRoad(road);
                    }

                    else
                    {
                        // Ako naiđemo na novi tip čvora ili kraj datoteke za ovu raskrsnicu, prekidamo čitanje
                        break;
                    }
                }
            }
            else if (type == "Matrix")
            {
                for (int i = 0; i < 6; ++i)
                {
                    for (int j = 0; j < 6; ++j)
                    {
                        file >> graph.matrix[i][j];
                    }
                }
            }
        }
        file.close();
    }
}

RoadNode *TrafficGraph::findRoadNodeById(const std::string &id) const
{
    for (RoadNode *road : roadNodes)
    {
        if (road->getId() == id)
        {
            return road;
        }
    }
    return nullptr; // Ako čvor puta nije pronađen
}

double TrafficGraph::getDistanceFromRoadId(RoadNode *n) const
{
    return n->getLength();
}

void TrafficGraph::eliminateDuplicate()
{
    // Novi vektor za cuvanje unikatnih puteva
    std::vector<RoadNode *> uniqueRoadNodes;

    // Flag za duplikat
    bool isDuplicate;

    // Provjeravamo svaki put s ostalim putevima u vektoru
    for (RoadNode *currentRoad : roadNodes)
    {
        isDuplicate = false;
        // Provjeravamo trenutni put s ostalim putevima
        for (RoadNode *otherRoad : uniqueRoadNodes)
        {
            if (currentRoad->getId() == otherRoad->getId() &&
                currentRoad->getLength() == otherRoad->getLength() &&
                currentRoad->getMax_speed() == otherRoad->getMax_speed() &&
                currentRoad->getMax_vehicles() == otherRoad->getMax_vehicles())
            {
                // Ako su svi parametri puta isti, onda je duplikat
                isDuplicate = true;
                break;
            }
        }
        // Ako trenutni put nije duplikat, dodajemo ga u vektor unikatnih puteva
        if (!isDuplicate)
        {
            uniqueRoadNodes.push_back(currentRoad);
        }
    }

    // Zamjenjujemo originalni vektor s vektorom unikatnih puteva
    roadNodes = uniqueRoadNodes;
}
