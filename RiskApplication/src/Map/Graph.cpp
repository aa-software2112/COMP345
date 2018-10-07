
#define GRAPH_LOCAL
#include "Graph.h"

/** Graph code */
template <class V, class E>
Graph<V, E>::Graph(void)
{

}

template <class V, class E>
typename Graph<V, E>::Vertex * Graph<V, E>::graph_InsertVertex(V * element)
{
	/** Create new vertex */
	Vertex * newVertex = new Vertex(element);

	/** Add to list of vertices */
	this->vertices.push_back(newVertex);

	return newVertex;
}

template <class V, class E>
void Graph<V, E>::graph_DisplayGraph()
{
	int i = 0;

	for(i = 0; i<this->vertices.size(); i++)
	{
		cout << (*(this->vertices[i])).vertex_GetElement();
	}

}

template <class V, class E>
typename Graph<V, E>::Edge * Graph<V, E>::graph_InsertEdgeBetween(Vertex * v1, Vertex * v2)
{
	Edge * newEdge = NULL;

	/** Edge doesn't exist yet */
	if (v1->vertex_GetEdgeTo(v2) == NULL)
	{

		/** Create new edge */
		newEdge = new Graph<V, E>::Edge(v1, v2);

		/** Add to collection of edges */
		this->edges.push_back(newEdge);

		/** Add vertex v2 to v1, and vice versa */
		v1->vertex_AddVertexEdgePair(v2, newEdge);

		v2->vertex_AddVertexEdgePair(v1, newEdge);


	}

	return newEdge;
}

/** Vertex code */
template <class V, class E>
Graph<V, E>::Vertex::Vertex(V *element)
{
	this->element = element;
}

template <class V, class E>
V Graph<V, E>::Vertex::vertex_GetElement(void)
{
	return *(this->element);

}

template <class V, class E>
bool Graph<V, E>::Vertex::operator<(const Vertex& otherVertex)
{
	return !(this->element == otherVertex.element);

}


template <class V, class E>
typename Graph<V, E>::Edge * Graph<V, E>::Vertex::vertex_GetEdgeTo(Vertex * otherVertex)
{
	/** Could not find vertex */
	if (this->vertexToEdge.find(otherVertex) == this->vertexToEdge.end())
	{
		return NULL;
	}

	return this->vertexToEdge[otherVertex];

}

template <class V, class E>
void Graph<V, E>::Vertex::vertex_AddVertexEdgePair(Vertex *otherVertex, Edge * connectingEdge)
{

	this->vertexToEdge[otherVertex] = connectingEdge;


}


/** Edge code */
template <class V, class E>
Graph<V, E>::Edge::Edge(Vertex * u, Vertex * v)
{
	this->endpoints[0] = u;
	this->endpoints[1] = v;
	this->element = NULL;
}

template class Graph<Country, string>;
