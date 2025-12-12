#pragma once
#include <string>
struct Sensor {
        int id;
        std::string sensor_type;
        int criticality;
        int data_output;

        Sensor () : id (-1), sensor_type (""), criticality (0), data_output (0) {}

        Sensor (int id, const std::string& sensor_type, int criticality, int data_output)
            : id (id), sensor_type (sensor_type), criticality (criticality), data_output (data_output) {}
};