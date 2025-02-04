#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_MESSAGES 100

// Define a structure for representing the graph
typedef struct {
    char nodeName[50];
    int adjList[MAX_NODES]; // adjacency list to represent edges
    int numConnections;
} Node;

// Define a structure for control messages
typedef struct {
    char sender[50];
    char receiver[50];
    char message[255];
} ControlMessage;

// Graph and control messages data
Node network[MAX_NODES];
ControlMessage controlMessages[MAX_MESSAGES];

// Function to prompt user for input
void prompt_user_input(int *numNodes, int *numEdges, int *numMessages) {
    printf("Enter the number of nodes in the Ad Hoc network: ");
    scanf("%d", numNodes);

    // Input nodes
    for (int i = 0; i < *numNodes; i++) {
        printf("Enter name of node %d: ", i + 1);
        scanf("%s", network[i].nodeName);
        network[i].numConnections = 0;  // Initialize number of connections to 0
    }

    // Input edges (connections)
    printf("Enter the number of connections between nodes: ");
    scanf("%d", numEdges);

    for (int i = 0; i < *numEdges; i++) {
        char node1[50], node2[50];
        printf("Enter first node for connection %d: ", i + 1);
        scanf("%s", node1);
        printf("Enter second node for connection %d: ", i + 1);
        scanf("%s", node2);

        // Find indices of node1 and node2
        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < *numNodes; j++) {
            if (strcmp(network[j].nodeName, node1) == 0) {
                idx1 = j;
            }
            if (strcmp(network[j].nodeName, node2) == 0) {
                idx2 = j;
            }
        }

        if (idx1 != -1 && idx2 != -1) {
            network[idx1].adjList[network[idx1].numConnections++] = idx2;
            network[idx2].adjList[network[idx2].numConnections++] = idx1; // Since it's an undirected graph
        }
    }

    // Input control messages
    printf("Enter the number of control messages: ");
    scanf("%d", numMessages);

    for (int i = 0; i < *numMessages; i++) {
        printf("Enter sender node for control message %d: ", i + 1);
        scanf("%s", controlMessages[i].sender);
        printf("Enter receiver node for control message %d: ", i + 1);
        scanf("%s", controlMessages[i].receiver);
        printf("Enter control message %d: ", i + 1);
        scanf(" %[^\n]s", controlMessages[i].message);  // To read entire line (including spaces)
    }
}

// Function to display control messages
void display_control_messages(int numMessages) {
    printf("\nControl Messages in the Network:\n");
    for (int i = 0; i < numMessages; i++) {
        printf("Message %d: From %s to %s -> %s\n", i + 1, controlMessages[i].sender, controlMessages[i].receiver, controlMessages[i].message);
    }
}

// Function to display network topology
void display_graph(int numNodes) {
    printf("\nAd Hoc Network Topology:\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%s: ", network[i].nodeName);
        for (int j = 0; j < network[i].numConnections; j++) {
            printf("%s ", network[network[i].adjList[j]].nodeName);
        }
        printf("\n");
    }
}

// Function to plot network traffic (simple bar chart using ASCII)
void plot_network_traffic(int numNodes, int numMessages) {
    int traffic[MAX_NODES] = {0};

    // Count traffic (messages sent and received)
    for (int i = 0; i < numMessages; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (strcmp(network[j].nodeName, controlMessages[i].sender) == 0) {
                traffic[j]++;
            }
            if (strcmp(network[j].nodeName, controlMessages[i].receiver) == 0) {
                traffic[j]++;
            }
        }
    }

    printf("\nControl Message Traffic (Message Sent/Received per Node):\n");
    for (int i = 0; i < numNodes; i++) {
        printf("%s: ", network[i].nodeName);
        for (int t = 0; t < traffic[i]; t++) {
            printf("*");
        }
        printf(" (%d messages)\n", traffic[i]);
    }
}

int main() {
    int numNodes, numEdges, numMessages;

    // Prompt user for input and gather network details
    prompt_user_input(&numNodes, &numEdges, &numMessages);

    // Display the network graph (topology)
    display_graph(numNodes);

    // Display the control messages
    display_control_messages(numMessages);

    // Plot the network traffic (simple ASCII representation)
    plot_network_traffic(numNodes, numMessages);

    return 0;
}
