# File-System-BFS-DFS


# File System Representation and Search Using BFS and DFS

## Activity Information

- Activity ID: SY-S3-B-09
- Language: C Programming
- Topic: Graph Data Structure
- Algorithms: Breadth-First Search (BFS) and Depth-First Search (DFS)

## Project Description

This project represents a file system as a directed graph using an adjacency matrix.

Each file or directory is represented as a node, and connections between directories and files are represented as directed edges.

The program implements BFS and DFS algorithms to traverse the graph and search for a specified file or directory from a given starting node.

## Features

- File and directory representation using graph nodes.
- Graph implementation using an adjacency matrix.
- Add connections between nodes.
- Display the adjacency matrix.
- BFS traversal using a queue.
- DFS traversal using recursion.
- Search for a specified file using BFS and DFS.
- Display traversal order and search results.
- Input validation and duplicate-name prevention.

## Technologies Used

- C Programming
- Graph Data Structure
- Adjacency Matrix
- Breadth-First Search
- Depth-First Search

## Compilation and Execution

### Linux / Termux / macOS

```bash
gcc main.c -o filesystem
./filesystem
```

### Windows

```bash
gcc main.c -o filesystem.exe
filesystem.exe
```

## Sample Input

```text
Enter number of nodes (1-50): 4

Enter file/directory name 1: Root
Enter file/directory name 2: Documents
Enter file/directory name 3: Photos
Enter file/directory name 4: resume.pdf

Enter number of connections (0-2500): 3

Connection 1:
From node number: 1
To node number: 2

Connection 2:
From node number: 1
To node number: 3

Connection 3:
From node number: 2
To node number: 4

Enter starting node number: 1
Enter the file/directory name to search: resume.pdf
```

## Sample Output

```text
========== BFS TRAVERSAL ==========
Root -> Documents -> Photos -> resume.pdf
BFS Search: FILE FOUND

========== DFS TRAVERSAL ==========
Root -> Documents -> resume.pdf -> Photos
DFS Search: FILE FOUND

========== FINAL RESULT ==========
BFS: FOUND
DFS: FOUND

Program completed successfully!
```

## Algorithm Complexity

Let V represent the number of vertices and E represent the number of edges.

| Operation | Time Complexity |
|---|---|
| Graph creation | O(V²) |
| BFS | O(V²) |
| DFS | O(V²) |
| Adjacency matrix storage | O(V²) |

## Conclusion

The project demonstrates how a file system can be represented using a graph and how BFS and DFS algorithms can be used to search and traverse files and directories.

Both algorithms successfully identify reachable files from the selected starting node.

---

**Academic Activity: SY-S3-B-09**
