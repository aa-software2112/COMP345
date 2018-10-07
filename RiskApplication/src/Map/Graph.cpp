
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

	/** For each vertex u */
	for(i = 0; i<this->vertices.size(); i++)
	{
		/** Current country checking over */
		cout << "Connections for: " << (*(this->vertices[i])).vertex_GetElement();

		/** For each vertex and edge v, e connected to u */
		map<Vertex *, Edge *> * adjacencyMap = (*this->vertices[i]).vertex_GetOutgoing();

		for (typename std::map< typename Graph<V, E>::Vertex *, typename Graph<V, E>::Edge *>::iterator it=(*adjacencyMap).begin(); it!=(*adjacencyMap).end(); ++it)
		{
			/** Display the Country name connected to */
			cout << (*(it->first)).vertex_GetElement() << endl;
		}



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

template <class V, class E>
vector<typename Graph<V, E>::Vertex *> * Graph<V, E>::graph_GetVertices(void)
{

	return &(this->vertices);

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
V * Graph<V, E>::Vertex::vertex_GetElementPtr(void)
{
	return this->element;

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

template <class V, class E>
map< typename Graph<V, E>::Vertex *, typename Graph<V, E>::Edge *> * Graph<V, E>::Vertex::vertex_GetOutgoing(void)
{

	return &(this->vertexToEdge);

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
