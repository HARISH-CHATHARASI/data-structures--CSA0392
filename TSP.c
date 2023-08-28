#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 10

int num_cities;
int adjacency_matrix[MAX_CITIES][MAX_CITIES];
int visited[MAX_CITIES];
int path[MAX_CITIES];
int min_distance = INT_MAX;

void tsp(int current_city, int depth, int current_distance) {
    if (depth == num_cities) {
        if (adjacency_matrix[current_city][0] != 0) {
            current_distance += adjacency_matrix[current_city][0];
            if (current_distance < min_distance) {
                min_distance = current_distance;
                for (int i = 0; i < num_cities; i++) {
                    path[i] = visited[i];
                }
            }
        }
        return;
    }

    for (int i = 0; i < num_cities; i++) {
        if (!visited[i] && adjacency_matrix[current_city][i] != 0) {
            visited[i] = 1;
            tsp(i, depth + 1, current_distance + adjacency_matrix[current_city][i]);
            visited[i] = 0;
        }
    }
}

int main() {
    printf("Enter the number of cities: ");
    scanf("%d", &num_cities);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < num_cities; i++) {
        for (int j = 0; j < num_cities; j++) {
            scanf("%d", &adjacency_matrix[i][j]);
        }
        visited[i] = 0;
    }

    visited[0] = 1; // Start from the first city
    tsp(0, 1, 0);

    printf("Optimal TSP path: ");
    for (int i = 0; i < num_cities; i++) {
        printf("%d ", path[i]);
    }
    printf("0\n"); // Return to the starting city

    printf("Minimum distance: %d\n", min_distance);

    return 0;
}
