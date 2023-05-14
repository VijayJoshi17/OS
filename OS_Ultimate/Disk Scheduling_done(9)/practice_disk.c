#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

#define MAX_SIZE 1000 // Maximum number of integers to read

void fcfs(int array[], int size, int head) {
    int i, seek_time = 0;
    printf("Sequence: %d ", head); // Print initial head position
    for (i = 0; i < size; i++) {
        seek_time += abs(array[i] - head); // Calculate seek time
        head = array[i]; // Update head position
        printf("%d ", head); // Print current head position
    }
    printf("\nTotal seek time using FCFS: %d\n", seek_time); // Print seek time
}

void sstf(int array[], int size, int head) {
    int i, j, min, seek_time = 0, min_index;
    int temp_array[MAX_SIZE];
    for (i = 0; i < size; i++) {
        temp_array[i] = array[i]; // Copy contents of array to temporary array
    }
    printf("Sequence: %d ", head); // Print initial head position
    for (i = 0; i < size; i++) {
        min = INT_MAX; // Set minimum to maximum value initially
        for (j = 0; j < size; j++) {
            if (abs(temp_array[j] - head) < min) { // Find request with shortest seek time
                min = abs(temp_array[j] - head);
                min_index = j;
            }
        }
        seek_time += min; // Add seek time to total
        head = temp_array[min_index]; // Update head position
        printf("%d ", head); // Print current head position
        temp_array[min_index] = INT_MAX; // Set processed request to maximum value
    }
    printf("\nTotal seek time using SSTF: %d\n", seek_time); // Print seek time
}


void SCAN(int array[], int size, int head, int max_cylinder, int direction) {
    int seek_time = 0, i, j, pos = 0, temp;
    int visited[max_cylinder + 1];

    // Initialize visited array
    for (i = 0; i <= max_cylinder; i++) {
        visited[i] = 0;
    }

    // Find position of head
    for (i = 0; i < size; i++) {
        if (array[i] < head) {
            pos = i;
        }
    }

    // Move towards the right
    for (i = pos; i < size && direction == 1; i++) {
        visited[array[i]] = 1;
        seek_time += abs(array[i] - head);
        head = array[i];
    }

    // Move towards the left
    for (i = pos-1; i >= 0 && direction == -1; i--) {
        visited[array[i]] = 1;
        seek_time += abs(array[i] - head);
        head = array[i];
    }

    // Print results
    printf("SCAN algorithm (direction=%d)\n", direction);
    printf("Sequence: %d ", head);
    for (i = head+1; i <= max_cylinder; i++) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }
    for (i = max_cylinder; i >= head; i--) {
        if (visited[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    printf("Total seek time: %d\n", seek_time);
}

void LOOK(int array[], int size, int head, int direction) {
    int seek_time = 0, i, j, pos = 0, temp;
    int visited[size];

    // Initialize visited array
    for (i = 0; i < size; i++) {
        visited[i] = 0;
    }

    // Find position of head
    for (i = 0; i < size; i++) {
        if (array[i] <= head) {
            pos = i;
        }
    }

    // Move in direction of requests
    for (i = pos; i >= 0 && i < size && direction == 1; i++) {
        visited[array[i]] = 1;
        seek_time += abs(array[i] - head);
        head = array[i];

        if (i == 0 || i == size-1) {
            direction *= -1;
        }
    }

    for (i = pos-1; i >= 0 && i < size && direction == -1; i--) {
        visited[array[i]] = 1;
        seek_time += abs(array[i] - head);
        head = array[i];

        if (i == 0 || i == size-1) {
            direction *= -1;
        }
    }

    // Print results
    printf("LOOK algorithm (direction=%d)\n", direction);
    printf("Sequence: ");
    for (i = 0; i < size; i++) {
        if (visited[array[i]]) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
    printf("Total seek time: %d\n", seek_time);
}



int main() {
    FILE *fp;
    int array[MAX_SIZE];
    int i, num, size, head;

    fp = fopen("practice_disk.txt", "r"); // Open file for reading
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    i = 0;
    while (fscanf(fp, "%d", &num) != EOF && i < MAX_SIZE) { // Read integers from file
        array[i] = num; // Store integer in array
        i++;
    }

    fclose(fp); // Close file

    size = i; // Store size of array
    printf("Array contents:\n");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]); // Print contents of array
    }
    printf("\n");

    printf("Enter the initial head position: ");
    scanf("%d", &head); // Read initial head position from user

    fcfs(array, size, head); // Call FCFS function
    sstf(array, size, head); // Call SSTF function
    int direction,max_cylinder;
    printf("\nEnter 0 (rigth to left) or 1 (left to right): ");
    scanf("%d",&direction);
    printf("Enter max. size: ");
    scanf("%d",&max_cylinder);
    SCAN(array, size, head,max_cylinder,direction); // Call SCAN function
    LOOK(array, size, head,direction); // Call LOOK function

    return 0;
}
