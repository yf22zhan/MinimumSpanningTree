#include "Weighted_graph.h"
#include <limits>
#include <exception>

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Constructor
// The parameter is assumed to be reasonable
Weighted_graph::Weighted_graph(int n) :
	adjacency_matrix(new double*[n]),
	degree_array(new int[n]()),
	MST_node_visited(new bool[n]()),
	edge_num(0),
	vertex_num(n) {
	// Create a new 2-dimensional array
	for (int i = 0; i < vertex_num; ++i) {
		adjacency_matrix[i] = new double[n]();
	}

	// Initialize the array with 0 in the main diagonal and INF elsewhere
	for (int i = 0; i < vertex_num; ++i) {
		for (int j = 0; j < vertex_num; ++j) {
			if (i != j) {
				adjacency_matrix[i][j] = INF;
			}
		}
	}
}

// Destructor
Weighted_graph::~Weighted_graph() {
	// Free the adjacency_matrix
	for (int i = 0; i < vertex_num; ++i) {
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;

	// Free the MST_node_visited
	delete[] MST_node_visited;

	// Free the degree_array
	delete[] degree_array;
}

// Accessors
int Weighted_graph::degree(int n) const {
	// If the vertex n does not exist,
	// throw an illegal argument exception
	if ((n < 0) || (n >= vertex_num)) {
		throw std::invalid_argument("received invalid vertex");
	}

	return degree_array[n];
}

int Weighted_graph::edge_count() const {
	return edge_num;
}

double Weighted_graph::adjacent(int m, int n) const {
	// If the vertices m, n do not exist,
	// throw an illegal argument exception
	if (((m < 0) || (m >= vertex_num)) || ((n < 0) || (n >= vertex_num))) {
		throw std::invalid_argument("received invalid vertex");
	}

	return adjacency_matrix[m][n];
}

bool Weighted_graph::is_connected() const {
	// if empty graph with no vertex, return "unconnected"/false
	if (vertex_num == 0) {
		return false;
	}
	else {
		minimum_spanning_tree(0);
	}

	// Iterate through MST_node_visited
	// to see if it connects all the nodes
	// If not, return false; otherwise, return true
	for (int i = 0; i < vertex_num; ++i) {
		if (!MST_node_visited[i]) {
			return false;
		}
	}
	return true;
}

double Weighted_graph::minimum_spanning_tree(int m) const {
	// If the vertex m does not exist,
	// throw an illegal argument exception
	if ((m < 0) || (m >= vertex_num)) {
		throw std::invalid_argument("received invalid vertex");
	}

	// Reset the MST_node_visited array to all false
	// and set node m to true as a visited node/origin
	for (int i = 0; i < vertex_num; ++i) {
		MST_node_visited[i] = false;
	}
	MST_node_visited[m] = true;
	int visited_counter = 1;
	double sum = 0;

	// In each iteration, find the least_weighted_edge,
	// break the loops if all nodeds visited or every
	// other unvisited node is disconnected from the 
	// connected
	while (visited_counter != vertex_num) {
		double least_weigthed_edge = INF;
		int vertex_to_include;

		for (int i = 0; i < vertex_num; ++i) {
			if (MST_node_visited[i]) {
				for (int j = 0; j < vertex_num; ++j) {
					if (!MST_node_visited[j]) {
						if (adjacency_matrix[i][j] < least_weigthed_edge) {
							least_weigthed_edge = adjacency_matrix[i][j];
							vertex_to_include = j;
						}
					}
				}
			}
		}

		// Used for debugging
		//std::cout << "least_weigthed_edge: " << least_weigthed_edge << "\n";

		if (least_weigthed_edge == INF) {
			break;
		}
		sum = sum + least_weigthed_edge;
		visited_counter++;
		// Include the unvisited node which has the least_weighted edge
		MST_node_visited[vertex_to_include] = true;
	}

	return sum;
}

// Mutators
void Weighted_graph::insert(int m, int n, double w) {
	// If the weight w < 0 or w = INF,
	// throw an illegal argument exception
	if ((w < 0) || (w == INF)) {
		throw std::invalid_argument("received invalid weight");
	}

	// If the vertices m, n do not exist or are equal,
	// throw an illegal argument exception
	if ((m == n) ||
		((m < 0) || (m >= vertex_num)) ||
		((n < 0) || (n >= vertex_num))) {
		throw std::invalid_argument("received invalid vertex");
	}

	// If w = 0, remove edge between m and n if any,
	// else, add an edge of weight w or replace the old edge
	if (w == 0) {
		if (adjacency_matrix[m][n] != INF) {
			adjacency_matrix[m][n] = INF;
			adjacency_matrix[n][m] = INF;
			degree_array[m] -= 1;
			degree_array[n] -= 1;
			edge_num -= 1;
		}
	}
	else {
		if (adjacency_matrix[m][n] == INF) {
			degree_array[m] += 1;
			degree_array[n] += 1;
			edge_num += 1;
		}
		adjacency_matrix[m][n] = w;
		adjacency_matrix[n][m] = w;
	}
}

// << operator override
std::ostream &operator<<(std::ostream &out, Weighted_graph const &graph) {
	out << "The vertex number: " << graph.vertex_num << "\n";
	out << "The edge_count: " << graph.edge_count() << "\n";
	out << "\n";

	out << "The adjacency_matrix:\n";
	for (int i = 0; i < graph.vertex_num; ++i) {
		for (int j = 0; j < graph.vertex_num; ++j) {
			out << graph.adjacency_matrix[i][j] << " ";
		}
		out << "\n";
	}
	out << "\n";

	out << "The degree_matrix:\n";
	for (int i = 0; i < graph.vertex_num; ++i) {
		out << graph.degree_array[i] << " ";
	}
	out << "\n\n";

	out << "The MST_node_visited:\n";
	for (int i = 0; i < graph.vertex_num; ++i) {
		out << graph.MST_node_visited[i] << " ";
	}
	out << "\n";

	return out;
}