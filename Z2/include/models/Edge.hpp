#pragma once
struct Edge {
        int to;
        int from;
        int weight;
        Edge (int from, int to, int weight) : from (from), to (to), weight (weight) {}

        bool operator< (const Edge& other) const {
            return weight < other.weight;
        }
};