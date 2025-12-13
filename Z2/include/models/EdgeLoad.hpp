struct EdgeLoad {
        int child;
        int parent;
        double load;
        int sensor_count;

        EdgeLoad () : child (-1), parent (-1), load (0), sensor_count (0) {}
        EdgeLoad (int c, int p, double l, int s) : child (c), parent (p), load (l), sensor_count (s) {}
};
