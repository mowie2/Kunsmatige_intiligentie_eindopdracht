#pragma once

#pragma once
#include "kmint/graph/basic_edge.hpp"
#include "kmint/graph/basic_graph.hpp"
#include "kmint/graph/basic_node.hpp"
#include "kmint/map/map.hpp"
#include "kmint/math/size.hpp"

class Astar
{
public:
	Astar() = default;
	~Astar() = default;
	std::vector<const kmint::map::map_node*> FindShortestPath(const kmint::map::map_node &firstNode, const kmint::map::map_node &lastNode);
private:
	float calculateDistance(const kmint::map::map_node &firstNode, const kmint::map::map_node &secondNode);
};