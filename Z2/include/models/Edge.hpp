#pragma once
struct Edge {
        int to;
        int from;
        int weight;
        Edge (int from, int to, int weight) : to (to), from (from), weight (weight) {}

        bool operator< (const Edge& other) const {
            return weight < other.weight;
        }
};