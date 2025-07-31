#include "najkrace_r.h"

void floyd(TrafficGraph g, double d[6][6], int t[6][6])
{
    int i, j, k;
    for (k = 0; k < g.n; k++)
    {
        for (i = 0; i < g.n; i++)
        {
            for (j = 0; j < g.n; j++)
            {
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    t[i][j] = t[k][j];
                }
            }
        }
    }
}

void putanja(int i, int j, TrafficGraph g, int t[6][6], int dest)
{
    if (i == j)
    {
        std::cout << g.nodesInMatrix[i] << "->";
    }
    else if (t[i][j] == -1)
    {
        std::cout << "Nema putanje." << std::endl;
    }
    else
    {
        putanja(i, t[i][j], g, t, dest);
        std::cout << g.nodesInMatrix[j];
        if (dest != j) 
        {
            std::cout << "->";
        }
    }
}

void initT(TrafficGraph g, int t[6][6])
{
    int i, j;
    for (i = 0; i < g.n; i++)
        for (j = 0; j < g.n; j++)
            if (i == j || g.matrix[i][j] == "0")
                t[i][j] = -1;
            else
                t[i][j] = i;
}

void initD(TrafficGraph g, double d[6][6])
{
    int i, j;
    for (i = 0; i < g.n; ++i)
    {
        for (j = 0; j < g.n; ++j)
        {
            if (i == j)
            {
                d[i][j] = 0; // Udaljenost između istih čvorova je 0
            }
            else
            {
                if (g.matrix[i][j] == "0")
                {
                    d[i][j] = std::numeric_limits<double>::infinity(); // Ako nema puta, postavi na beskonačno
                }
                else
                {

                    d[i][j] = g.getDistanceFromRoadId(g.findRoadNodeById(g.matrix[i][j]));
 
                }
            }
        }
    }
}


