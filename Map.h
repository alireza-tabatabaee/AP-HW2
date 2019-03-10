#ifndef MAP_H
#define MAP_H


class Map
{
    public:
        Map(int);
        virtual ~Map();
        void showMap();
        void findRoute();
        void findRoute_B();
        void showRoute();
        void shortestRoute();

    private:
        int n{};
        int** a{};
        bool** b{};
};

#endif
