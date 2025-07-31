#include "nodes.h"
#include "vehicle.h"
#include "najkrace_r.h"
#include <algorithm>
#include <iomanip>

int indexFromId(const std::string &id)
{
    if (id == "A")
        return 0;
    else if (id == "B")
        return 1;
    else if (id == "C")
        return 2;
    else if (id == "D")
        return 3;
    else if (id == "I1")
        return 4;
    else if (id == "I2")
        return 5;
    else
    {
        std::cout << "Lokacija sa tim id-jem ne postoji" << std::endl;
        return -1;
    }
}

int main()
{

    int t[6][6];
    double d[6][6];

    LocationNode A("A");
    LocationNode B("B");
    LocationNode C("C");
    LocationNode D("D");
    RoadNode road1("road1", 300, 60, 12);
    RoadNode road2("road2", 200, 60, 5);
    RoadNode road3("road3", 500, 60, 17);
    RoadNode road4("road4", 600, 60, 19);
    RoadNode road5("road5", 150, 60, 5);
    RoadNode road6("road6", 310, 60, 6);
    RoadNode road7("road7", 680, 60, 15);
    RoadNode road8("road8", 130, 60, 10);
    RoadNode road9("road9", 120, 60, 5);
    IntersectionNode i1("I1", 4);
    i1.addIncomingRoad(&road2);
    i1.addIncomingRoad(&road7);
    i1.addIncomingRoad(&road4);
    i1.addOutgoingRoad(&road1);
    i1.addOutgoingRoad(&road5);
    i1.addOutgoingRoad(&road9);
    i1.addOutgoingRoad(&road3);

    i1.addEdge("road2", "road9", true, road2.getLength() + road9.getLength(), 60);
    i1.addEdge("road2", "road3", true, road2.getLength() + road3.getLength(), 60);
    i1.addEdge("road2", "road5", true, road2.getLength() + road5.getLength(), 60);
    i1.addEdge("road7", "road1", true, road7.getLength() + road1.getLength(), 60);
    i1.addEdge("road7", "road5", true, road7.getLength() + road5.getLength(), 60);
    i1.addEdge("road7", "road9", true, road7.getLength() + road9.getLength(), 60);
    i1.addEdge("road7", "road3", true, road7.getLength() + road3.getLength(), 60);
    i1.addEdge("road4", "road9", true, road4.getLength() + road9.getLength(), 60);
    i1.addEdge("road4", "road5", true, road4.getLength() + road5.getLength(), 60);
    i1.addEdge("road4", "road1", true, road4.getLength() + road1.getLength(), 60);
    i1.addEdge("road2", "road1", false, 0, 0);
    i1.addEdge("road4", "road3", true, road4.getLength() + road3.getLength(), 60);

    //i1.printEdges();


    IntersectionNode i2("I2", 5);
    i2.addIncomingRoad(&road8);
    i2.addIncomingRoad(&road6);
    i2.addOutgoingRoad(&road7);
    i2.addEdge("road8", "road7", true, road8.getLength() + road7.getLength(), 60);
    i2.addEdge("road6", "road7", true, road6.getLength() + road7.getLength(), 60);

    std::cout << std::endl;

    //i2.printEdges();

    std::cout << std::endl;

    //  Kreiranje grafa
    TrafficGraph graph;
    graph.n = 6;

    // Dodavanje lokacija, puteva i raskrsnica u graf
    graph.nodes.push_back(&A);
    graph.nodes.push_back(&B);
    graph.nodes.push_back(&C);
    graph.nodes.push_back(&D);
    graph.nodes.push_back(&i1);
    graph.nodes.push_back(&i2);
    graph.roadNodes.push_back(&road9);
    graph.roadNodes.push_back(&road8);
    graph.roadNodes.push_back(&road7);
    graph.roadNodes.push_back(&road6);
    graph.roadNodes.push_back(&road5);
    graph.roadNodes.push_back(&road4);
    graph.roadNodes.push_back(&road3);
    graph.roadNodes.push_back(&road2);
    graph.roadNodes.push_back(&road1);

    for (int m = 0; m < 6; m++)
    {
        graph.nodesInMatrix.push_back(m);
    }


    graph.matrix[0][0] = "0";
    graph.matrix[0][1] = "0";
    graph.matrix[0][2] = "0";
    graph.matrix[0][3] = "0";
    graph.matrix[0][4] = road2.getId();
    graph.matrix[0][5] = "0";
    graph.matrix[1][0] = "0";
    graph.matrix[1][1] = "0";
    graph.matrix[1][2] = "0";
    graph.matrix[1][3] = "0";
    graph.matrix[1][4] = "0";
    graph.matrix[1][5] = road8.getId();
    graph.matrix[2][0] = "0";
    graph.matrix[2][1] = "0";
    graph.matrix[2][2] = "0";
    graph.matrix[2][3] = "0";
    graph.matrix[2][4] = road4.getId();
    graph.matrix[2][5] = "0";
    graph.matrix[3][0] = "0";
    graph.matrix[3][1] = "0";
    graph.matrix[3][2] = "0";
    graph.matrix[3][3] = "0";
    graph.matrix[3][4] = "0";
    graph.matrix[3][5] = road6.getId();
    graph.matrix[4][0] = road1.getId();
    graph.matrix[4][1] = road9.getId();
    graph.matrix[4][2] = road3.getId();
    graph.matrix[4][3] = road5.getId();
    graph.matrix[4][4] = "0";
    graph.matrix[4][5] = "0";
    graph.matrix[5][0] = "0";
    graph.matrix[5][1] = "0";
    graph.matrix[5][2] = "0";
    graph.matrix[5][3] = "0";
    graph.matrix[5][4] = road7.getId();
    graph.matrix[5][5] = "0";

    initT(graph, t);
    initD(graph, d);

    floyd(graph, d, t);

    //ISPIS MATRICE NAJKRACIH RAASTOJANJA I MATRICE PRETHODNIKA NAKON POZIVANJA FLOJDOVOG ALGORITMA
    std::cout<<"Matrica najkracih rastojanja:"<<std::endl;
    std::cout<<std::endl;


    for (int i = 0; i < graph.n; i++)
    {
        for (int j = 0; j < graph.n; j++)
        {
            std::cout <<std::setw(4)<< d[i][j];
            std::cout<<" ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Matrica prethodnika:"<<std::endl;
    std::cout<<std::endl;
    for (int i = 0; i < graph.n; i++)
    {
        for (int j = 0; j < graph.n; j++)
        {
            std::cout <<std::setw(4)<<t[i][j];
            std::cout<<" ";
        }
        std::cout << std::endl;
    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    graph.serialize("graf.txt");

    //DESERIJALIZACIJA GRAFA

    std::cout<<"DESERIJALIZOVAN GRAF:"<<std::endl;
    std::cout<<std::endl;

    TrafficGraph graph1;
    graph1.deserialize("graf.txt", graph1);
    std::cout << "n= " << graph1.n << std::endl;
    // Ispis grafa radi testiranja
    for (Node *node : graph1.nodes)
    {
        if (node->getType() == "intersection")
        {
            IntersectionNode *intersection = static_cast<IntersectionNode *>(node);
            std::cout << "Intersection Node: " << intersection->getId() << ", Max Vehicles: " << intersection->getMax_vehicless() << std::endl;
            std::cout << "  Incoming Roads:" << std::endl;
            for (RoadNode *road : intersection->incoming_roads)
            {
                std::cout << "    Road: " << road->getId() << ", Length: " << road->getLength() << ", Max Speed: " << road->getMax_speed() << ", Max Vehicles: " << road->getMax_vehicles() << std::endl;
            }
            std::cout << "  Outgoing Roads:" << std::endl;
            for (RoadNode *road : intersection->outgoing_roads)
            {
                std::cout << "    Road: " << road->getId() << ", Length: " << road->getLength() << ", Max Speed: " << road->getMax_speed() << ", Max Vehicles: " << road->getMax_vehicles() << std::endl;
            }
            intersection->printEdges();
        }
        else if (node->getType() == "location")
        {
            LocationNode *location = static_cast<LocationNode *>(node);
            std::cout << "Location Node: " << location->getId() << std::endl;
        }
    }
    std::cout << "ROADS: " << std::endl;
    graph1.eliminateDuplicate();
    for (RoadNode *node : graph1.roadNodes)
    {
        std::cout << "    Road: " << node->getId() << ", Length: " << node->getLength() << ", Max Speed: " << node->getMax_speed() << ", Max Vehicles: " << node->getMax_vehicles() << std::endl;
    }
    std::cout<<std::endl;

    std::cout << "Matrix:" << std::endl;
    std::cout<<std::endl;
    graph1.printMatrix();
    
    std::cout<<std::endl;
    // INICIJALIZACIJA VOZILA, ZADAVANJE POCETNE I KRAJNJE LOKACIJE
    std::string _id="Volvo";
    std::string _start_location = "B";
    std::string _end_location = "A";
    double _average_speed = 70;
    int pocetni, krajnji;


    pocetni = indexFromId(_start_location);

    krajnji = indexFromId(_end_location);
 
    Vehicle v1(_id, _average_speed, 0, _start_location, _end_location);
    std::cout << "Putanja vozila "<<v1.getId()<<" od " << _start_location << " do " << _end_location << ": " << std::endl;
    v1.provozajSe(pocetni, krajnji, graph, t);
    std::cout << std::endl;
    double duzina = d[pocetni][krajnji];


    double real_speed = std::min(v1.getAverageSpeed(), 60.0);

    // Postavljamo realnu brzinu vozila
    v1.setCurrentSpeed(real_speed);

    std::cout << "Duzina puta i realna prosjecna brzina vozila: " << duzina <<", "<<v1.getCurrentSpeed()<< std::endl;
    std::cout<<std::endl;

    std::string _id2="Fiat";
    std::string _start_location2 = "C";
    std::string _end_location2 = "D";
    double _average_speed2 = 75;
    int pocetni2, krajnji2;


    pocetni2 = indexFromId(_start_location2);

    krajnji2 = indexFromId(_end_location2);
 
    Vehicle v2(_id2, _average_speed2, 0, _start_location2, _end_location2);
    std::cout << "Putanja vozila "<<v2.getId()<<" od " << _start_location2 << " do " << _end_location2 << ": " << std::endl;
    v2.provozajSe(pocetni2, krajnji2, graph, t);
    std::cout << std::endl;
    double duzina2 = d[pocetni2][krajnji2];


    double real_speed2 = std::min(v2.getAverageSpeed(), 60.0);

    // Postavljamo realnu brzinu vozila
    v2.setCurrentSpeed(real_speed2);

    std::cout << "Duzina puta i realna prosjecna brzina vozila: " << duzina2 <<", "<<v2.getCurrentSpeed()<< std::endl;
    std::cout<<std::endl;
    return 0;
}