#include "graph.h"
// Nicholas Fay
// May 14th 
// This function initializes an adjacency list for
// a graph.
// 
// Note that adj list is an array of """adj_node_t*""" which is passed
// in by reference.
// That is, you are passing in a pointer (i.e, *) to an array (i.e., *)
// of adj_node_t*, which is why list is of type adj_node_t***
void init_adj_list(adj_node_t ***list, int rows)
{
    // Part 2 - Fill in this function
    // this malloc's memory for the adjacency list.
    *list = malloc(sizeof(adj_node_t*) * rows);
    // set everything in the list to be NULL at first.
    for(int i = 0; i < rows; i++) {
	    (*list)[i] = NULL;
    }
}

// This function creates a new adj_node_t node
// and initializes it with node->vid = vid
// and node->next = NULL;
// The function then returns this node
adj_node_t *create_node(int vid)
{
    // Part 3 - Fill in this function
    // creates the node, malloc's memory for the node
    adj_node_t *new_node = (adj_node_t*) malloc(sizeof(adj_node_t));
    // set the nodes vid/next
    new_node->vid = vid;
    new_node->next = NULL;
    // return the created node
    return new_node;
}


// Pass in the list and the row to which you need to add a new node
// First check that the adjacency list for the current row is not
// empty (i.e., NULL). If it is NULL, it is the first adjacent node.
// Otherwise, traverse the list until you reach the end, and then add
// the new node
void add_node(adj_node_t** list, int row, adj_node_t* node)
{
    // Part 4 - Fill in this function
    // if the adjacency list is empty/NULL, it is the first node
    adj_node_t *temp = list[row];
    if(list[row] ==  NULL) {
        list[row] = node;
        return;
    // if the list is not empty then loop through until you find an empty space.
    } else {
        // while the next node is not Null, update temp to be the next node
        while(temp->next != NULL) {
		    temp = temp->next;
	    }
	    // set the empty space to hold the node we are adding
	    temp->next = node;
	    return;
    }
}

// deqeueu a node from a queue
// and return the vertex id of the first member
// when list returns, it points to the next member in the queue
int remove_node(adj_node_t **list)
{
    // Part 6 - Implement this function
    // if the list is Null return -1
    if(list == NULL) {
	  return -1;
    }
    // the head node is the first in the queue (queue: first in, first out)
    adj_node_t *h_node = *list;
    // store the heads vertex id in a variable
    int vert_id = h_node->vid;
    // remove the head node from the queue. Dequeue
    (*list) = (*list)->next;
    // free the removed node that we Dequeued
    free(h_node);
    // returns the head nodes id that we Dequeued
    return vert_id;
}


// This function constructs an adjacency list for a graph.
//
// adj_mat is a 2D array that represents the adjacency matrix
//
// list is passed in by reference from the main function so that
// it can be malloc'd via the init_adj_list function (see aobve)
//
// After initializing it go through each row and add its adjacent 
// nodes
void construct_adj_list(int **adj_mat, int rows, int cols, adj_node_t ***list)
{
    // verify that the adj matrix is correct
    if(rows != cols) {
        printf("Adjacency matrix is not square\n");
        exit(EXIT_FAILURE);
    }
    init_adj_list(list, rows);
    // Part 1 - Fill in the rest of this function
    // loop through the matrix
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            // if there is an edge between the two nodes (that what a 1 represents)
            if(adj_mat[i][j] == 1) {
                // create then add the node it to the adj list
                adj_node_t *created_node = create_node(j);
                add_node(*list, i, created_node);
            }
        }
    }
    // You will need to implement create_node() and
    // add_node() and use them to implement this function
}

// This takes in an adjacency list and prints out the list
void print_adj_list(adj_node_t **list, int rows)
{
    assert(list);

    printf("---- Print Adj. List ----\n");
    for(int i = 0; i < rows; i++) {
        printf("|%d| -> ", i);
        adj_node_t* next = list[i];
        while(next != NULL) {
            printf("%d -> ", next->vid);
            next = next->next;
        }
        printf("END\n");
    }
    printf("--------\n\n");
}

void free_adj_list(adj_node_t **list, int rows)
{
    // Part 7 - Implement this function
    for(int i = 0; i < rows; i++) {
        // create a temp node and next to be freed node.
	    adj_node_t *next = list[i];
	    adj_node_t *temp;
	    // While there is a next node to be freed
	    while(next) {
	        // update temp
		    temp = next->next;
		    // free the next, then update next to the temp var that holds the next node we need to free
		    free(next);
		    next = temp;
	    }
    }
    //free the actual list
    free(list);
}

void print_bfs_result(int rows, int *color, int *distance, int *parent)
{
    assert(color);
    assert(distance);
    assert(parent);

    printf("---- Print BFS Result ----\n");
    printf("Vert\tCol\tDis\tParent\n");
    for(int i = 0; i < rows; i++) {
        printf("%d\t%d\t%d\t%d\n", i, color[i], distance[i], parent[i]);
    }
    printf("--------\n\n");
}


// Do BFS here, given the source node and the
// graph's adjacency list
int bfs(adj_node_t **list, int rows, int source,
        int *color, int *distance, int *parent)
{
    // Make sure the source is a valid vertex
    if(source >= rows) {
        printf("Invalid source vertex\n");
        return 0;
    }
    // Make sure the adjacency list is not empty
    if(list == NULL) {
        printf("There is nothing in the adjacency list\n");
        return 0;
    }
    // Make sure all these are properly allocated
    assert(color);
    assert(distance);
    assert(parent);

    // Part 5 - Fill in the rest of this function
    // init all the vertices color, distance, and parent
    for(int i = 0; i < rows; i++) {
        color[i] = 0;
        distance[i] = -1;
        parent[i] = -1;
    }
    // This is because it will be the first vertex in the queue
    color[source] = 1;
    // 0 because it is the source node
    distance[source] = 0;
    // Null because it has no parents
    parent[source] = -1;
    // Null q is initialized
    adj_node_t *q = NULL;
    // create the source node
    adj_node_t *source_n = create_node(source);
    // add the source node to the queue
    add_node(&q, 0, source_n);
    // while the queue is not empty
    while(q != NULL) {
        //remove the node and get its id
	    int dq_vid = remove_node(&q);
	    adj_node_t *poped = list[dq_vid];
	    for(;poped != NULL; poped = poped->next) {
            // get the vertex id from the poped node
            int vertex_id = poped->vid;
            if(color[vertex_id] == 0) {
                // vertex has been visited so color change
                color[vertex_id] = 1;
                // set distance for the node
                distance[vertex_id] = distance[dq_vid] + 1;
                // set parent for the node
                parent[vertex_id] = dq_vid;
                adj_node_t *v = create_node(vertex_id);
                // add the node to the queue after creating it.
                add_node(&q, 0, v);
	        }
	        color[dq_vid] = 2;
	    }
    }
    #if DEBUG
    print_bfs_result(rows, color, distance, parent);
    #endif
    return 0;
}






