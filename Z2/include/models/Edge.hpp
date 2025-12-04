#pragma once
struct Edge {
        int to_;
        int from_;
        int weight_;
        Edge (int from, int to, int weight) : from_ (from), to_ (to), weight_ (weight) {}

        bool operator< (const Edge& other) const {
            return weight_ < other.weight_;
        }
};