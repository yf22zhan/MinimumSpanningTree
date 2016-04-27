#pragma once
#include <iostream>

class Weighted_graph {
private:
	static const double INF;
	double** adjacency_matrix;
	int* degree_array;
	bool* MST_node_visited;
	int edge_num;
	int vertex_num;


public:
	Weighted_graph(int = 50);
	~Weighted_graph();

	int degree(int) const;
	int edge_count() const;
	double adjacent(int, int) const;
	double minimum_spanning_tree(int) const;
	bool is_connected() const;

	void insert(int, int, double);

	// Friends

	friend std::ostream &operator<<(std::ostream &, Weighted_graph const &);
};