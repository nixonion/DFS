/* Student Details:
*  Name: Nabeel Mahdi Abid Mehdi Sayed
*  GNumber: G01213257
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

//Depth First Search Algorithm
void dfs(Graph *graph, int v1);



//This function initailizes the graph
Graph *graph_initialize()
{
	//Allocate memory for graph
	Graph *new=malloc(sizeof(Graph));
	if(new == NULL)
	{
		//check for memory errors
		return NULL;
	}
	int i=0;
	int j=0;
	// Initialise the visited array and adj_matrix matrix
	for(i=0;i<MAX_VERTICES;i++)
	{
		new->visited[i]=0;
		for (j = 0; j < MAX_VERTICES; j++)
		{
			new->adj_matrix[i][j]=-1;
		}
	}
	//Initializa max vertex
	new->max_vertex=0;
	return new;
}

int graph_add_vertex(Graph *graph, int v1)
{
	//Check if vertex v1 is valid
	if(v1 < 0 || v1 >= MAX_VERTICES)
	{
		return -1;
	}
	//Check if graph is null
	if (graph == NULL)
	{
		return -1;
	}
	//check if the vertex exists or not
	if (graph->adj_matrix[v1][v1]==-1)
	{
		//If the vertex doesn't exist, increment max_vertex and assign 0 to adj_matrix location at (v1,v1)
		graph->max_vertex=(graph->max_vertex)+1;
		graph->adj_matrix[v1][v1]=0;
		return 0;
	}
	return 0;
	
}

int graph_contains_vertex(Graph *graph, int v1)
{
	//Check if v1 is valid and graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
	{
		return 0;
	}
	//Check if vertex exists
	if (graph->adj_matrix[v1][v1] != -1)
	{
		//If vertex exists, return 1
		return 1;
	}
	else
	{
		//If vertex doesn't exist, return 0
		return 0;
	}
}

int graph_remove_vertex(Graph *graph, int v1)
{
	//Check if v1 is valid and graph is NULL
	int i=0;
	if(v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
	{
		return -1;
	}

	//Check if the vertex exists 
	if (graph->adj_matrix[v1][v1] == -1)
	{
		return 0;
	}
	else
	{
		//To remove the vertex, we Initialise all the connections to and from the vertex is removed as well
		for(i=0;i<MAX_VERTICES;i++)
		{
			graph->adj_matrix[v1][i] = -1;
			graph->adj_matrix[i][v1] = -1;	
		}
		//Decrement the max_vertex
		graph->max_vertex=(graph->max_vertex)-1;
		return 0;
	}
}

int graph_add_edge(Graph *graph, int v1, int v2, int wt)
{
	//Check if v1 adn v2 are valid and graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return -1;
	}	
	//Check if vertex v1 and v2 exists in the graph
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return -1;
	}
	//Set the weight for the edge from v1 to v2
	graph->adj_matrix[v1][v2]=wt;
	return 0;
}

int graph_contains_edge(Graph *graph, int v1, int v2)
{
	//Check if v1 adn v2 are valid and graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return 0;
	}	
	//Check if vertex v1 and v2 exists in the graph
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return 0;
	}
	//Check if the edge exists
	if (graph->adj_matrix[v1][v2] > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int graph_remove_edge(Graph *graph, int v1, int v2)
{
	//Check if v1 adn v2 are valid and graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return -1;
	}	
	//Check if vertex v1 and v2 exists in the graph
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return -1;
	}
	//Check if the edge does not exist already
	if (graph->adj_matrix[v1][v2] <= 0)
	{
		return 0;
	}
	//Check if its a self edge,and initialise the edge to 0 since (v1,v1) or (v2,v2) also represents vertex
	if (v1 == v2)
	{
		graph->adj_matrix[v1][v2]=0;
		return 0;
	}
	//Set the edge value to -1
	graph->adj_matrix[v1][v2]=-1;
	return 0;
}

int graph_num_vertices(Graph *graph)
{
	int i=0;
	int count=0;
	//Check if the graph is NULL
	if (graph == NULL)
	{
		return -1;
	}
	//Iterate through each row in the graph and check if vertex is not -1, vertex always has a coordinate (i,j) where i=j 
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if (graph->adj_matrix[i][i] != -1)
		{
			count++;
		}
	}
	return count;

}

int graph_num_edges(Graph *graph)
{
	int i=0;
	int j=0;
	int count=0;
	//Check if graph is NULL
	if (graph == NULL)
	{
		return -1;
	}
	//Iterate through each element in graph
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for ( j = 0; j < MAX_VERTICES; j++)
		{
			//Check if graph element is greater than 0
			if (graph->adj_matrix[i][j] > 0)
			{
				count++;
			}
		}
	}
	return count;

}
int graph_total_weight(Graph *graph)
{
	int i=0;
	int j=0;
	int weight=0;
	if (graph == NULL)
	{
		return -1;
	}
	//Iterate through each element in graph
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for ( j = 0; j < MAX_VERTICES; j++)
		{
			//Check if an edge exists and then add teh weight
			if (graph->adj_matrix[i][j] != -1)
			{
				weight=weight+graph->adj_matrix[i][j];
			}
		}
	}

	return weight;
}
int graph_get_degree(Graph *graph, int v1)
{
	int i=0;
	int j=0;
	int degree=0;
	//Check if v1 is valid and graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
	{
		return -1;
	}
	//Check if vertex v1 exists in the graph
	if (graph->adj_matrix[v1][v1] == -1)
	{
		return -1;
	}
	//Check for all elements in vertex's row and column and increment degree
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[v1][i] > 0)
		{
			degree++;
		}
		if(graph->adj_matrix[i][v1] > 0)
		{
			degree++;
		}
	}
	return degree;
}

int graph_get_edge_weight(Graph *graph, int v1, int v2)
{
	////Check if vertex v1 and v2 exists in the graph and if graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return -1;
	}	
	//Check if vertex v1 and v2 exists
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return -1;
	}
	// Check if edge exists
	if (graph->adj_matrix[v1][v2] == -1)
	{
		return -1;
	}
	//Return edge weight
	return graph->adj_matrix[v1][v2];
}

int graph_is_neighbor(Graph *graph, int v1, int v2)
{
	//Check if vertex v1 and v2 exists in the graph and if graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return 0;
	}	
	//Check if vertex v1 and v2 exists
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return 0;
	}
	//Check if there is an edge from v1 to v2 or v2 to v1
	if (graph->adj_matrix[v1][v2] > 0  || graph->adj_matrix[v2][v1] > 0)
	{
		return 1;
	}
	return 0;
}

int *graph_get_predecessors(Graph *graph, int v1)
{
	int i=0;
	//Check if v1 is valid and if graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
	{
		return NULL;
	}
	//Check if vertex v1 exists
	if (graph->adj_matrix[v1][v1] == -1)
	{
		return NULL;
	}
	int *predecessor = malloc(sizeof(int));
	int size=1;
	//for all elements in v1's column , reallocate a new array and add the vertex with edge to v1 in array
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[i][v1] > 0)
		{
			size++;
			predecessor = realloc(predecessor, sizeof(int) * size);
			predecessor[size-2]= i;
		}		
	}
	predecessor[size-1]=-1;
	return predecessor;

}

int *graph_get_successors(Graph *graph, int v1)
{
	int i=0;
	//Check if v1 is valid and if graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || graph == NULL)
	{
		return NULL;
	}
	//Check if vertex v1 exists
	if (graph->adj_matrix[v1][v1] == -1)
	{
		return NULL;
	}
	int size=1;
	int *successor = malloc(sizeof(int));

	//for all elements in v1's row, reallocate a new array and add the vertex with edge from v1 in array
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[v1][i] > 0)
		{
			size++;
			successor = realloc(successor, sizeof(int) * size);
			successor[size-2]= i;
		}
	}
	successor[size-1]=-1;
	return successor;
}

int graph_has_path(Graph *graph, int v1, int v2)
{
	//Check if v1 and v2 are valid and if graph is NULL
	if(v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES || graph == NULL )
	{
		return 0;
	}	
	//Check if vertex v1 and v2 exists
	if (graph->adj_matrix[v1][v1] == -1 || graph->adj_matrix[v2][v2] == -1)
	{
		return 0;
	}
	int i=0;
	//Initialise all elements in visited array 
	for(i=0;i<MAX_VERTICES;i++)
	{
		graph->visited[i]=0;
	}
	
	//Get the successors of v1
	int *p=graph_get_successors(graph,v1);
	int vertex=0;
	i=0;
	//for each of the successor, run depth first search on it
	while(p[i]!=-1)
	{
		vertex=p[i];
		if(graph->visited[vertex]==0)
		{
			dfs(graph,vertex);
		}
		i++;
	}
	
	//If v2 is visited, then that means there is a path from v1 to v2
	if(graph->visited[v2]==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void dfs(Graph *graph, int v1)
{
	//Set the visited flag for v1 as 1
	graph->visited[v1]=1;
	//Get the successors of v1
	int *p=graph_get_successors(graph,v1);
	int i=0;
	int vertex=0;
	//for each of the successor, run depth first search on it
	while(p[i]!=-1)
	{
		vertex=p[i];
		if(graph->visited[vertex]==0)
		{
			dfs(graph,vertex);
		}
		i++;
	}
}

void graph_print(Graph *graph)
{
	if (graph == NULL)
	{
		return;
	}
	if (graph_num_vertices(graph)==0)
	{
		return;
	}
	int i=0;
	int j=0;
	printf("\n");
	printf("    ");
	//printing the vertices
	for (i = 0; i < MAX_VERTICES; ++i)
	{
		if (graph->adj_matrix[i][i]>=0)
		{
			printf("%2d ", i);
		}
	}
	printf("\n   ");
	for (i = 0; i < MAX_VERTICES; ++i)
	{
		if (graph->adj_matrix[i][i]>=0)
		{
			printf("---");
		}
	}
	printf("\n");
	for (i = 0; i < MAX_VERTICES; ++i)
	{
		//Check if vertex exists
		if (graph->adj_matrix[i][i]>=0)
		{
			printf("%2d| ",i);
			//if vertex exists, we iterate through thr row elements
			for (j = 0; j < MAX_VERTICES; ++j)
			{
				//Check if vertex exists
				if (graph->adj_matrix[j][j]>=0)
				{
					//If edge exists, print the edge, else print *
					if (graph->adj_matrix[i][j]>=0)
					{
						printf("%2d ",graph->adj_matrix[i][j] );
					}
					else
					{
						printf(" * ");
					}
				}
			}
			printf("\n");
		}
	}
}
void graph_output_dot(Graph *graph, char *filename)
{
	//Check if graph and filename are NULL
	if (graph == NULL || filename == NULL)
	{
		return;
	}
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
		return;
	}
	//Check if file pointer array
	int i=0;
	int j=0;
	fprintf(fp, "digraph {\n");
	for (i = 0; i < MAX_VERTICES; i++)
	{
		//Check if vertex exists
		if (graph->adj_matrix[i][i] > -1)
		{
			//Cehck for self edge, if edge does not exist, print the vertex, else print the edge's weight
			if (graph->adj_matrix[i][i] == 0)
			{
				fprintf(fp, "%d;\n",i );
			}
			else
			{
				fprintf(fp, "%d -> %d [label = %d];\n",i,i,graph->adj_matrix[i][i]);	
			}
			//Iterate through all the elements in the vetrex's column
			for (j = 0; j < MAX_VERTICES; ++j)
			{
				//Check if it's not a vertex, and check if edge exists
				if (i!=j && graph->adj_matrix[i][j] >= 0)
				{
					fprintf(fp, "%d -> %d [label = %d];\n",i,j,graph->adj_matrix[i][j]);
				}
			}
		}	
	}
	fprintf(fp, "}\n");

    //Close file
	fclose(fp);
}

int graph_load_file(Graph *graph, char *filename)
{
	//Check if graph is NULL and if filename is NULL
	if (graph == NULL || filename == NULL)
	{
		return -1;
	}
	int i=0;
	int j=0;
	//Initialize the adj_matrix
	for(i = 0; i < MAX_VERTICES; i++) 
    { 
    	for(j = 0; j < MAX_VERTICES; j++) 
    	{
    		graph->adj_matrix[i][j] = -1;
    	}
    }

	graph -> max_vertex = 0;
	//Initialize the visited array
	for(i = 0; i < MAX_VERTICES; i++) 
	{ 
    	graph->visited[i] = 0;
    }

    //Open the file to read
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) 
    {
		return -1;
	}
	
	char buffer[10];
	char *split = NULL;

	int vertex1=0;
	int vertex2=0;
	int edge_weight=0;
	//For each line
	while(feof(fp) == 0) 
	{ 
	// Run till EOF is reached
		fgets(buffer, sizeof(buffer), fp);
		//get the first part of the line till ','
		split = strtok(buffer, ",");
		if(split != NULL) 
		{
			//store the first part in vertex1
			sscanf(split, "%d", &vertex1);
			//add vertex to graph
			graph_add_vertex(graph, vertex1);
		}
		
		//Get the second part of the line till ','
		split=strtok(NULL, ",");
		if(split != NULL) 
		{
			//store the second part in vertex2 
			sscanf(split, "%d", &vertex2);
			//add vertex to graph
			graph_add_vertex(graph, vertex2);
		}
		//Get the third part of the line
		split = strtok(NULL, ",");
		if(split != NULL) 
		{
			//Store the third part in edge weight
			sscanf(split, "%d", &edge_weight);
			//add the edge in graph
			graph_add_edge(graph, vertex1, vertex2, edge_weight);
		}
	}
	fclose(fp);
	return 0;


}
int graph_save_file(Graph *graph, char *filename)
{
	//Check if graph or filename are NULL
	if (graph == NULL || filename == NULL)
	{
		return -1;
	}

	FILE *fp = fopen(filename, "w+");
	if(fp == NULL) {
		//Check for file pointer error
		return -1;
	}
	int i = 0;
	int j = 0;
	//Iterate through all the elements in adj_matrix
	for ( i = 0; i < MAX_VERTICES; i++)
	{
		for ( j = 0; j < MAX_VERTICES; j++)
		{
			if (graph->adj_matrix[i][j] != -1)
			{
				//Check if the element is a vertex with no self-edge
				if (graph->adj_matrix[i][j] == 0)
				{
					fprintf(fp, "%d\n", i);
				}
				else
				{
					//If element is an edge, print the edge vertices and the edge weight
					fprintf(fp, "%d,%d,%d\n", i, j, graph->adj_matrix[i][j]);
				} 
			}
		}
	}
	
	fclose(fp);
	return 0;
}







