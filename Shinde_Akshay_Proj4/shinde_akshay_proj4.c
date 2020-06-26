//standard library inclusion
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define MAX_VALUE 9999

//global variable declaration
int vertices;

//function declaration
int prim_algorithm(int **g_matrix);

int print_path(int index_q, int index_r, int **p_matrix);

int make_queue(int *queue);

int get_min_node(char *chk_non_tree_node, int *queue, int *cost);

typedef struct edge_wt_str {
    int wt;
    int edge_src;
    int edge_dest;
} edge_wt_typ;

edge_wt_typ *edge_wt;

int kruskal_algorithm(int **g_matrix);

int find3(int node, int *set);

int union3(int rep_node1, int rep_node2, int *height_matrix, int *set);

/*
 This function  will take input from user and will generate random number.
*/

int main() {

    //variable declaration
    int user_input;
    int diagonal_element;



    //srand function used to get proper random numbers
    srand((unsigned) time(NULL));
    //random generation of num between 5 to 10
    while (vertices < 5 || vertices > 10) {
        vertices = (rand() % 10) + 5;
    }

    printf("\n\nRandomly selected %d vertices\n", vertices);

    //size allocated to pointer input and pointer matrix
    int **A = malloc(vertices * sizeof(*A));
    for (int i = 0; i < vertices; i++) {
        A[i] = malloc(vertices * sizeof(*A[i]));
    }

    //generating random number using rand() function and adding the same into input matrix
    //need to assign number in such a way that matrix maintain symmetry as A[j][i] = A[i][j];
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) {
                A[i][j] = 0;
            }
            else {
                A[i][j] = (rand() % 10) + 1;
                A[j][i] = A[i][j];
            }
            // printf("%d\t",A[i][j]);
        }
        // printf("\n");
    }

    // Display random matrix
    printf("\n\nRandom Matrix\n\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d\t",A[i][j]);
        }
        printf("\n");
      }



    while(user_input != 0)
    {
      printf("Please Select Algorithm\n 1.Prim\n 2.Kruskal\n");
      scanf("%d", &user_input);

      if (user_input == 0) {
        printf("\nPlease enter valid input as 1 for prim or 2 for kruskal. Exiting...\n\n");
        return 0;
      }

      // calling Prim's algorithm function
      if (user_input == 1) {
          prim_algorithm(A);
      }

      // calling Kruskal's algorithm function
      if (user_input == 2) {
          kruskal_algorithm(A);
      }
    }

    //free up the heap space of pointers
    for (int i = 0; i < vertices; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}

int prim_algorithm(int **g_matrix) {
    //loop counter declaration
    int u, v;
    //local variable declaration
    int cost[vertices];
    int prev[vertices];
    char check_tree[vertices];
    int queue[vertices];
    int tree_node = 0;

    //initialize array with some impossible values
    for (u = 0; u < vertices; u++) {
        cost[u] = MAX_VALUE;
        prev[u] = MAX_VALUE;
        //initially all nodes will be non tree
        check_tree[u] = 'N';
    }

    //pick any node - here taking 0th node
    cost[0] = 0;

    //make_queue - add all vertices into queue
    make_queue(queue);

    //check if there is any non tree node - then queue is not empty - using check_tree array simultaneously
    for (u = 0; u < vertices; u++) {
        tree_node = get_min_node(check_tree, queue, cost);
        //make the minimum cost node as tree node
        check_tree[tree_node] = 'T';
        //traverse through all node
        for (v = 0; v < vertices; v++) {
            //if node is not tree node and there is edge between nodes get the weight of edge from edge matrix
            if (v != tree_node && g_matrix[tree_node][v] > 0 && check_tree[v] == 'N') {
                if (cost[v] > g_matrix[tree_node][v]) {
                    cost[v] = g_matrix[tree_node][v];
                    prev[v] = tree_node;
                }
            }
        }
    }
    //printing elements
    printf("\nPrim's Algorithm:");
    printf("\n\nEdge\t\t\tEdge Weight\n");
    for (u = 0; u < vertices; u++) {
        if (prev[u] != MAX_VALUE) {
            printf("V%d -- V%d\t\t\t%d\n", prev[u], u, g_matrix[u][prev[u]]);
        }
    }
    printf("\n");
    return 0;
}

/*
 This function adds all nodes in queue
 */
int make_queue(int *queue) {
    for (int i = 0; i < vertices; i++) {
        queue[i] = i;
    }
    return 0;
}

/*
 This function return node with minimum cost
 */
int get_min_node(char *chk_non_tree_node, int *queue, int *cost) {
    //local variable declaration
    int min_wt = MAX_VALUE;
    int min_wt_node;
    //traverse through all nodes
    for (int u = 0; u < vertices; u++) {
        //if node is non tree ....calculate the cost of node and return node with minimum cost
        if (chk_non_tree_node[u] == 'N') {
            if (((min_wt) > cost[u])) {
                min_wt = cost[u];
                min_wt_node = u;
            }
        }
    }
    return min_wt_node;
}

int kruskal_algorithm(int **g_matrix) {
    //loop counter declaration
    int u, v;

    //local variable declaration
    int counter = 0;
    int rep_node_1;
    int rep_node_2;
    int height[vertices];
    int set[vertices]; //index is node and array value is representative element
    int edges = 0;
    int diagonal_element = vertices + 1;
    int num_of_edges = (vertices * (vertices - 1)) / 2;
    edge_wt_typ temp_edge_wt;
    edge_wt = malloc(num_of_edges * sizeof(edge_wt_typ));

    //edge_wt_typ edge_wt[num_of_edges];

    //initialize every node with it's same value for set and with 0 for height
    for (u = 0; u < vertices; u++) {
        set[u] = u;
        height[u] = 0;
    }

    //initialize temp struct values
    temp_edge_wt.edge_dest = 9999;
    temp_edge_wt.edge_src = 9999;
    temp_edge_wt.wt = 9999;

    //get the edge and wt
    for (u = 0; u < vertices; u++) {
        for (v = 0; v < vertices; v++) {
            if (u == v) {
                diagonal_element = v;
            } else if (v > diagonal_element) {
                edge_wt[counter].wt = g_matrix[u][v];
                edge_wt[counter].edge_src = u;
                edge_wt[counter].edge_dest = v;
                counter++;
            }
        }
        diagonal_element = vertices + 1;
    }

    //sort edges
    for (u = 0; u < num_of_edges; u++) {
        for (v = u + 1; v < num_of_edges; v++) {
            if (edge_wt[v].wt < edge_wt[u].wt) {
                temp_edge_wt = edge_wt[u];
                edge_wt[u] = edge_wt[v];
                edge_wt[v] = temp_edge_wt;
            }
        }
    }

    //check every edge
    printf("\nKruskal's Algorithm:");
    printf("\n\nEdge\t\t\tEdge Weight\n");
    for (u = 0; u < num_of_edges; u++) {
        if (edge_wt[u].wt != 0 && (edges < (vertices - 1))) {
            rep_node_1 = find3(edge_wt[u].edge_src, set);
            rep_node_2 = find3(edge_wt[u].edge_dest, set);

            if (rep_node_1 != rep_node_2) {
                //add edge
                edges = edges + 1;
                union3(rep_node_1, rep_node_2, height, set);
                printf("V%d -- V%d\t\t\t%d\n", edge_wt[u].edge_src, edge_wt[u].edge_dest, edge_wt[u].wt);
            }
        }
    }

    printf("\n");
    free(edge_wt);

    return 0;
}


//find representative element of every node
int find3(int node, int *set) {
    int root = node;
    int parent;

    while (root != set[root]) {
        root = set[root];
    }

    //compress path
    while (root != node) {
        parent = set[node];
        set[node] = root;
        node = parent;
    }
    return root;
}

//add edge between nodes using union
int union3(int rep_node1, int rep_node2, int *height_matrix, int *set) {
    int ht_node1 = height_matrix[rep_node1];
    int ht_node2 = height_matrix[rep_node2];

    if (ht_node1 == ht_node2) {
        height_matrix[rep_node2] = height_matrix[rep_node2] + 1;
        set[rep_node1] = rep_node2;
    } else {
        if (ht_node1 < ht_node2) {
            set[rep_node1] = rep_node2;
        } else {
            set[rep_node2] = rep_node1;
        }
    }
    return 0;
}
