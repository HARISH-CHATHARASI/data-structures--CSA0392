#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Queue data structure for BFS
struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

// Graph data structure
struct Graph {
    int vertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
};

// Initialize a queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return (queue->front == -1);
}

// Add an item to the queue
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_VERTICES - 1)
        printf("Queue is full");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Remove an item from the queue
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// Initialize a graph with the given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int start, int end) {
    graph->matrix[start][end] = 1;
    // For an undirected graph, you might also want to set graph->matrix[end][start] = 1;
}

// Breadth-First Search to find the shortest path
void BFS(struct Graph* graph, int startVertex, int endVertex) {
    int visited[MAX_VERTICES] = {0};
    int predecessor[MAX_VERTICES] = {-1};
    struct Queue* queue = createQueue();

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->matrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                predecessor[i] = currentVertex;
                enqueue(queue, i);
            }
        }
    }

    // Print the shortest path from startVertex to endVertex
    printf("Shortest path from %d to %d:\n", startVertex, endVertex);
    int path[MAX_VERTICES];
    int pathLength = 0;
    int current = endVertex;

    while (current != -1) {
        path[pathLength] = current;
        current = predecessor[current];
        pathLength++;
    }

    for (int i = pathLength - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
}

int main() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    BFS(graph, 0, 5);

    return 0;
}
