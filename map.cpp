#include "Map.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

Map::Map(int N)
{
    n = N;
    a = new int* [n];
    b = new bool* [n];
    for(int i{}; i<n; i++){
        a[i] = new int [n];
        b[i] = new bool [n];
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);                 //creating a seed
    for(int i{}; i<n; i++)
    {
        for(int j{}; j<n; j++){
            a[i][j] = -1;
            b[i][j] = 0;
        }
    }
    for(int i{}; i<n*n; i++)
    {
        int x{static_cast<int>(mt()%n)}; 
        int y{static_cast<int>(mt()%n)};
        if(a[x][y]==-1)                    //choosing a random home
      	    a[x][y] = i;                   //and assigning random number
        else
            i--;
    }
}

void Map::showMap()
{
    for(int i{}; i<n; i++)
    {
        for(int j{}; j<n; j++)
            std::cout << std::setw(2) << a[i][j] << " ";
        std::cout << std::endl;
    }
}

void Map::findRoute()
{
    int i{}, j{};
    long int sum{};
    while(i<n-1 || j<n-1)
    {
	b[i][j] = 1;
        if(i==(n-1) || (abs(a[i+1][j] - a[i][j]) > abs(a[i][j] - a[i][j+1]))){
            sum += abs(a[i][j] - a[i][j+1]);
            j++;
        }
        else if(j==(n-1) || (abs(a[i+1][j] - a[i][j]) <= abs(a[i][j] - a[i][j+1]))){
            sum += abs(a[i+1][j] - a[i][j]);
            i++;
        }
    }
    b[i][j] = 1;
    std::cout << "\nDistance: " << sum << std::endl;
}

void Map::findRoute_B()
{
    int i{}, j{};
    long int sum{};
    for(int i{}; i<n; i++)
    {
        for(int j{}; j<n; j++)
            b[i][j] = 0;
    }
    while(i<n-1 || j<n-1)
    {
        b[i][j] = 1;
        if(i==(n-1) || (abs(a[i+1][j] - a[i][j]) > abs(a[i][j] - a[i][j+1]) && abs(a[i+1][j+1] - a[i][j]) > abs(a[i][j] - a[i][j+1]))){
            sum += abs(a[i][j] - a[i][j+1]);
            j++;
        }
        else if(j==(n-1) || (abs(a[i+1][j] - a[i][j]) <= abs(a[i][j] - a[i][j+1]) && abs(a[i+1][j] - a[i][j]) <= abs(a[i][j] - a[i+1][j+1]))){
            sum += abs(a[i+1][j] - a[i][j]);
            i++;
        }
        else if(abs(a[i+1][j+1]-a[i][j])<abs(a[i+1][j]-a[i][j]) && abs(a[i+1][j+1]-a[i][j])<abs(a[i][j+1]-a[i][j])){
            sum += abs(a[i+1][j+1] - a[i][j]);
            i++;
            j++;
        }
    }
    b[i][j] = 1;
    std::cout << "\nDistance_B: " << sum << std::endl;
}

void Map::shortestRoute()
{
    long int min{};
    bool c[2*(n-1)];
    for(int i{}; i<n-1; i++)
    {
        c[i] = 0;
        c[n+i] = 1;
    }
    while(std::next_permutation(c, c+2*(n-1)))
    {
        int x{}, y{};
        long int sum{};
        for(int i{}; i<2*(n-1); i++)
        {
            if(c[i]){
                sum += abs(a[x][y] - a[x+1][y]);
                x++;
            }
            else {
                sum += abs(a[x][y] - a[x][y+1]);
                y++;
            }
        }
        if(min==0 || sum<min)
            min = sum;
    }
    std::cout << "\nShortest distance: " << min << std::endl;
}

void Map::showRoute()
{
    std::cout << "Route:" << std::endl;
    for(int i{}; i<n; i++)
    {
        for(int j{}; j<n; j++)
        {
            if(b[i][j])
                std::cout << "+ ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
}

Map::~Map()
{
    for(int i{}; i<n; i++)
        delete[] a[i];
    delete[] a;
}
