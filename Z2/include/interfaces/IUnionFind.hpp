#pragma once
class IUnionFind {
    public:
        virtual int find (int x) = 0;
        virtual bool unite (int x, int y) = 0;
        virtual bool isConnected (int x, int y) = 0;
        virtual ~IUnionFind () {}
};
