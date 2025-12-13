#include <cassert>
#include <iostream>

#include "../include/models/Sensor.hpp"
#include "../include/simulation/LoadCalculator.hpp"
#include "../include/tree/TreeBuilder.hpp"

void test_simple_tree_load()
{
    std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 1}};

    TreeBuilder builder;
    builder.SetRoot(0);
    builder.AddEdges(edges);
    auto tree = builder.Build();

    std::vector<Sensor> sensors = {{1, "temp", 50, 10}, {2, "humidity", 60, 20}};

    LoadCalculator calc;
    calc.Calculate(*tree, sensors);

    auto loads = calc.GetEdgeLoads();
    auto bottleneck = calc.GetBottleneck();

    // Test loads
    assert(loads.size() == 2);

    // Test bottleneck - grana 2->0 prenosi  20KB (najveće opterećenje)
    assert(bottleneck.valid == true);
    assert(bottleneck.child == 2);
    assert(bottleneck.parent == 0);
    assert(bottleneck.load == 20);
    assert(bottleneck.sensor_count == 1);
    (void)bottleneck; /// CMmake iz nekog razloga vidi bottlenneck kao neiskorišćenu varijablu pa ga moram ovako "utušiti"
    std::cout << "[PASS] test_simple_tree_load\n";
}

void test_nested_tree_load()
{
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 1}, {1, 3, 1}};

    TreeBuilder builder;
    builder.SetRoot(0);
    builder.AddEdges(edges);
    auto tree = builder.Build();

    std::vector<Sensor> sensors = {{1, "a", 50, 5}, {2, "b", 50, 10}, {3, "c", 50, 15}};

    LoadCalculator calc;
    calc.Calculate(*tree, sensors);

    auto loads = calc.GetEdgeLoads();
    auto bottleneck = calc.GetBottleneck();

    assert(loads.size() == 3);

    // Grana 1->0: 5 + 10 + 15 = 30KB (svi senzori  su ispod čvora 1)
    assert(bottleneck.valid == true);
    assert(bottleneck.child == 1);
    assert(bottleneck.parent == 0);
    assert(bottleneck.load == 30);
    assert(bottleneck.sensor_count == 3);
    (void)bottleneck;
    std::cout << "[PASS] test_nested_tree_load\n";
}

void test_no_sensors()
{
    std::vector<Edge> edges = {{0, 1, 1}};

    TreeBuilder builder;
    builder.SetRoot(0);
    builder.AddEdges(edges);
    auto tree = builder.Build();

    std::vector<Sensor> sensors; // Prazan vektor

    LoadCalculator calc;
    calc.Calculate(*tree, sensors);

    auto loads = calc.GetEdgeLoads();
    auto bottleneck = calc.GetBottleneck();

    assert(loads.size() == 1);

    assert(bottleneck.valid == true);
    assert(bottleneck.load == 0);
    assert(bottleneck.sensor_count == 0);
    assert(bottleneck.child == 1);
    assert(bottleneck.parent == 0);
    (void)bottleneck;
    std::cout << "[PASS] test_no_sensors\n";
}

void test_deep_tree()
{
    std::vector<Edge> edges = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}};

    TreeBuilder builder;
    builder.SetRoot(0);
    builder.AddEdges(edges);
    auto tree = builder.Build();

    std::vector<Sensor> sensors = {{4, "deep", 100, 100}};

    LoadCalculator calc;
    calc.Calculate(*tree, sensors);

    auto loads = calc.GetEdgeLoads();
    auto bottleneck = calc.GetBottleneck();

    // Sve 4 grane nose isti load (100KB) jer je samo jedan senzor na kraju
    assert(loads.size() == 4);
    assert(bottleneck.valid == true);
    assert(bottleneck.load == 100);
    assert(bottleneck.sensor_count == 1);
    (void)bottleneck;
    std::cout << "[PASS] test_deep_tree\n";
}

void test_multiple_bottlenecks()
{
    std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 1}};

    TreeBuilder builder;
    builder.SetRoot(0);
    builder.AddEdges(edges);
    auto tree = builder.Build();

    std::vector<Sensor> sensors = {{1, "a", 50, 50}, {2, "b", 50, 50}};

    LoadCalculator calc;
    calc.Calculate(*tree, sensors);

    auto loads = calc.GetEdgeLoads();
    auto bottleneck = calc.GetBottleneck();

    // Obje grane imaju isti load
    assert(loads.size() == 2);
    assert(bottleneck.valid == true);
    assert(bottleneck.load == 50);
    assert(bottleneck.sensor_count == 1);
    // Bottleneck može biti bilo koja od dvije grane (1 ili 2)
    assert(bottleneck.child == 1 || bottleneck.child == 2);
    assert(bottleneck.parent == 0);
    (void)bottleneck;
    std::cout << "[PASS] test_multiple_bottlenecks\n";
}

int main()
{
    std::cout << "=== LoadCalculator Tests ===\n";

    test_simple_tree_load();
    test_nested_tree_load();
    test_no_sensors();
    test_deep_tree();
    test_multiple_bottlenecks();

    std::cout << "All LoadCalculator tests passed!\n";
    return 0;
}