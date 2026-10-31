
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_NODES 50
#define MAX_NAME 64

int graph[MAX_NODES][MAX_NODES];
char names[MAX_NODES][MAX_NAME];
int n;

int readInt(const char *prompt, int min, int max) {
    char line[128];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);

        if (!fgets(line, sizeof(line), stdin))
            exit(1);

        errno = 0;
        value = strtol(line, &end, 10);

        while (isspace((unsigned char)*end))
            end++;

        if (errno == 0 && end != line &&
            *end == '\0' && value >= min && value <= max)
            return (int)value;

        printf("Invalid input! Enter a number between %d and %d.\n",
               min, max);
    }
}

void readName(int index) {
    char line[128];

    while (1) {
        printf("Enter file/directory name %d: ", index + 1);

        if (!fgets(line, sizeof(line), stdin))
            exit(1);

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0 || strlen(line) >= MAX_NAME) {
            printf("Name must contain 1 to 63 characters.\n");
            continue;
        }

        int duplicate = 0;

        for (int i = 0; i < index; i++) {
            if (strcmp(names[i], line) == 0) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate) {
            printf("Duplicate name! Enter a unique name.\n");
            continue;
        }

        strcpy(names[index], line);
        break;
    }
}

void displayNodes(void) {
    printf("\n========== FILE SYSTEM NODES ==========\n");

    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, names[i]);

    printf("=======================================\n");
}

void displayGraph(void) {
    printf("\n========== ADJACENCY MATRIX ==========\n\n");

    printf("%-14s", "");

    for (int i = 0; i < n; i++)
        printf("%-5d", i + 1);

    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%-14s", names[i]);

        for (int j = 0; j < n; j++)
            printf("%-5d", graph[i][j]);

        printf("\n");
    }

    printf("\n1 = Connection, 0 = No connection\n");
}

void printTraversal(int order[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s", names[order[i]]);

        if (i < count - 1)
            printf(" -> ");
    }

    printf("\n");
}

int bfs(int start, const char *target) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int order[MAX_NODES];
    int front = 0, rear = 0, count = 0;
    int found = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        order[count++] = current;

        if (strcmp(names[current], target) == 0)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n========== BFS TRAVERSAL ==========\n");
    printTraversal(order, count);

    printf("BFS Search: %s\n",
           found ? "FILE FOUND" : "FILE NOT FOUND");

    return found;
}

void dfsVisit(int current, int visited[],
              int order[], int *count,
              const char *target, int *found) {

    visited[current] = 1;
    order[(*count)++] = current;

    if (strcmp(names[current], target) == 0)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !visited[i]) {
            dfsVisit(i, visited, order, count, target, found);
        }
    }
}

int dfs(int start, const char *target) {
    int visited[MAX_NODES] = {0};
    int order[MAX_NODES];
    int count = 0;
    int found = 0;

    dfsVisit(start, visited, order, &count, target, &found);

    printf("\n========== DFS TRAVERSAL ==========\n");
    printTraversal(order, count);

    printf("DFS Search: %s\n",
           found ? "FILE FOUND" : "FILE NOT FOUND");

    return found;
}

int main(void) {
    int edges, from, to, start;
    char target[MAX_NAME];

    printf("\n========================================\n");
    printf("     FILE SYSTEM BFS AND DFS SEARCH\n");
    printf("========================================\n");

    n = readInt("\nEnter number of nodes (1-50): ",
                1, MAX_NODES);

    printf("\n--- Enter File/Directory Names ---\n");

    for (int i = 0; i < n; i++)
        readName(i);

    edges = readInt("\nEnter number of connections (0-2500): ",
                    0, n * n);

    printf("\n--- Enter Connections ---\n");
    printf("Use node numbers from the displayed list.\n");
    printf("Connections are directed: Parent -> Child.\n");

    displayNodes();

    for (int i = 0; i < edges; i++) {
        printf("\nConnection %d:\n", i + 1);

        from = readInt("From node number: ", 1, n);
        to = readInt("To node number: ", 1, n);

        if (graph[from - 1][to - 1]) {
            printf("Connection already exists.\n");
            i--;
            continue;
        }

        graph[from - 1][to - 1] = 1;
    }

    displayGraph();

    displayNodes();

    start = readInt("\nEnter starting node number: ", 1, n) - 1;

    printf("Enter the file/directory name to search: ");

    if (!fgets(target, sizeof(target), stdin))
        return 1;

    target[strcspn(target, "\n")] = '\0';

    if (strlen(target) == 0) {
        printf("Search name cannot be empty.\n");
        return 1;
    }

    printf("\nStarting Node: %s\n", names[start]);
    printf("Target: %s\n", target);

    printf("\n******** SEARCH RESULTS ********\n");

    int bfsResult = bfs(start, target);
    int dfsResult = dfs(start, target);

    printf("\n========== FINAL RESULT ==========\n");

    printf("BFS: %s\n", bfsResult ? "FOUND" : "NOT FOUND");
    printf("DFS: %s\n", dfsResult ? "FOUND" : "NOT FOUND");

    printf("\nProgram completed successfully!\n");

    return 0;
}
