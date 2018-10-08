/*
 * GRAPH.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_GRAPH_H_
#define H_GRAPH_H_

#include <map>
#include <set>
#include <vector>
#include "Country.h"
#include "Utilities.h"
using namespace std;

/** Forward reference */

//class Vertex;


/** This implementation assumes bi-directional edges */
template <class V, class E>
class Graph {
	public:
		class Edge;
		/** Vertex (Nodes) */
		class Vertex {
			public:
				Vertex(V * element);
				V vertex_GetElement(void);
				V * vertex_GetElementPtr(void);
				bool operator< (const Vertex& otherVertex);
				Edge * vertex_GetEdgeTo(Vertex *otherVertex);
				void vertex_AddVertexEdgePair(Vertex *otherVertex, Edge * connectingEdge);
				map<Vertex *, Edge *> * vertex_GetOutgoing(void);

			private:
				/** The element stored in the vertex */
				V * element;
				map<Vertex *, Edge *> vertexToEdge;


		};

		/** Edge (Links between nodes) */
		class Edge {
			public:
				Edge(Vertex * u, Vertex * v);
				vector<Vertex *> * edge_GetEndpoints(void);
			private:
				E * element;
				vector<Vertex *> endpoints;

		};

		/** Constructor */
		Graph(void);

		/** Adds a vertex to the graph */
		Vertex * graph_InsertVertex(V * element);

		/** Inserts an edge between two vertices */
		Edge * graph_InsertEdgeBetween(Vertex * v1, Vertex * v2);

		vector<Vertex *> * graph_GetVertices(void);

		/** Displays all vertices' elements */
		void graph_DisplayGraph(void);

		/** Checks graph connectivity using recursive depth-first-search */
		bool graph_isConnected(void);

		/** Gets the vertex at opposite end of edge */
		Vertex * graph_GetOppositeVertex(Vertex *u, Edge *e);

	private:
		void graph_DepthFirstSearch(Vertex * startVertex, set<Vertex *>& knownVertices);

		vector<Vertex *> vertices;
		vector<Edge *> edges;

};

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where GRAPH_LOCAL isn't defined.
 * */
#ifdef GRAPH_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_GRAPH_H_ */
