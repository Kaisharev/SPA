#pragma once
#include <string>
struct Sensor {
        int id_;
        std::string sensor_type_;
        int criticality_;
        int data_output_;

        Sensor () : id_ (-1), sensor_type_ (""), criticality_ (0), data_output_ (0) {}

        Sensor (int id, const std::string& sensor_type, int criticality, int data_output)
            : id_ (id), sensor_type_ (sensor_type), criticality_ (criticality), data_output_ (data_output) {}
};