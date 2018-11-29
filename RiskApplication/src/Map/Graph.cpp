
#define GRAPH_LOCAL
#include "Graph.h"


template <class V, class E>
Graph<V, E>::~Graph(void)
{

	cout << "In Graph Destructor" << endl;

	/** Delete all vertices */
	for (typename vector<typename Graph<V, E>::Vertex *>::iterator it=vertices.begin(); it!=vertices.end(); ++it)
	{
		delete *it;
	}


	/** Delete all edges */
	for (typename vector<typename Graph<V, E>::Edge *>::iterator it=edges.begin(); it!=edges.end(); ++it)
	{
		delete *it;
	}


}


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

	/** For each vertex u */
	for(unsigned i = 0; i<this->vertices.size(); i++)
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

template <class V, class E>
bool Graph<V, E>::graph_isConnected(void)
{

	if (this->vertices.size() > 0)
	{
		set<Vertex *> visitedVertices;
		Vertex * startVertex = this->vertices[0];

		this->graph_DepthFirstSearch(startVertex, visitedVertices);


		cout << "The Depth-First-Search reached " << visitedVertices.size() << " vertices" << endl;
		cout << "There are " << this->vertices.size() << " vertices in the graph" << endl;

		/** Same size means graph is fully connected */
		return (visitedVertices.size() == this->vertices.size());
	}

	return false;

}

template <class V, class E>
bool Graph<V, E>::graph_IsConnectedSubgraph(set<Vertex *>& subGraphOfVertices)
{
	/** Checks if the passed parameter is a connected subgraph */
	if (subGraphOfVertices.size() > 0){

		/** Get first vertex in set */
		typename std::set<typename Graph<V, E>::Vertex *>::iterator it = subGraphOfVertices.begin();

		Vertex * firstVertex = *it;
		set<Vertex *> visitedVertices;

		this->graph_DepthFirstSearch(firstVertex, visitedVertices, subGraphOfVertices);

		cout << "The Subgraph Depth-First-Search reached " << visitedVertices.size() << " vertices" << endl;
		cout << "There are " << subGraphOfVertices.size() << " vertices in the subgraph" << endl << endl;

		/** Same size means graph is fully connected */
		return (visitedVertices.size() == subGraphOfVertices.size());

	}

	return false;

}

template <class V, class E>
void Graph<V, E>::graph_DepthFirstSearch(Vertex * startVertex, set<Vertex *>& knownVertices, set<Vertex *>& subGraph)
{

	/** Add start vertex into the known set */
	knownVertices.insert(startVertex);

	/** Get (Vertex, Edge) map for start Vertex */
	map<Vertex *, Edge *> * adjacentVerticesAndEdges = startVertex->vertex_GetOutgoing();

	/** it->first is a Vertex connected to startVertex through it->second, the edge connected to startVertex */
	for (typename std::map< typename Graph<V, E>::Vertex *, typename Graph<V, E>::Edge *>::iterator it=(*adjacentVerticesAndEdges).begin(); it!=(*adjacentVerticesAndEdges).end(); ++it)
	{
		/** Store current edge */
		Edge * edge = (it->second);

		Vertex * opposite = this->graph_GetOppositeVertex(startVertex, edge);

		/** No opposite vertex is disconnected, immediately disqualifies connection definition */
		if (opposite == NULL)
		{
			return;
		}

		/** Vertex has not been visited yet AND
		 * vertex is part of the subgraph */
		if ((knownVertices.count(opposite) == 0) && (subGraph.count(opposite) != 0))
		{
			this->graph_DepthFirstSearch(opposite, knownVertices, subGraph);

		}

	}

}


template <class V, class E>
void Graph<V, E>::graph_DepthFirstSearch(Vertex * startVertex, set<Vertex *>& knownVertices)
{

	/** Add start vertex into the known set */
	knownVertices.insert(startVertex);

	/** Get (Vertex, Edge) map for start Vertex */
	map<Vertex *, Edge *> * adjacentVerticesAndEdges = startVertex->vertex_GetOutgoing();

	/** it->first is a Vertex connected to startVertex through it->second, the edge connected to startVertex */
	for (typename std::map< typename Graph<V, E>::Vertex *, typename Graph<V, E>::Edge *>::iterator it=(*adjacentVerticesAndEdges).begin(); it!=(*adjacentVerticesAndEdges).end(); ++it)
	{
		/** Store current edge */
		Edge * edge = (it->second);

		Vertex * opposite = this->graph_GetOppositeVertex(startVertex, edge);

		/** No opposite vertex is disconnected, immediately disqualifies connection definition */
		if (opposite == NULL)
		{
			return;
		}

		/** Vertex has not been visited yet */
		if (knownVertices.count(opposite) == 0)
		{
			this->graph_DepthFirstSearch(opposite, knownVertices);

		}

	}

}

template <class V, class E>
typename Graph<V, E>::Vertex * Graph<V, E>::graph_GetOppositeVertex(Vertex * u, Edge * e)
{
	vector<Vertex *> * vertices = e->edge_GetEndpoints();

	if((*vertices)[0] == u)
	{
		return (*vertices)[1];
	}
	else if ((*vertices)[1] == u)
	{
		return (*vertices)[0];
	}
	else
	{
		/** TODO, throw error */
		print("Could not find opposite vertex!");
		return NULL;
	}


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
Graph<V, E>::Vertex::~Vertex(void)
{
	cout << "In Vertex destructor" << endl;

	delete this->element;


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
	this->endpoints.push_back(u);
	this->endpoints.push_back(v);
	this->element = NULL;
}

template <class V, class E>
Graph<V, E>::Edge::~Edge(void)
{
	cout << "In Edge destructor" << endl;

	delete this->element;

}

template <class V, class E>
vector<typename Graph<V, E>::Vertex *> * Graph<V, E>::Edge::edge_GetEndpoints(void)
{
	return &(this->endpoints);
}

template class Graph<Country, string>;
