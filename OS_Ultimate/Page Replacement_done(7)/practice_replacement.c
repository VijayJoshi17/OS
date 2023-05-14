#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <limits.h>


void FIFO(int arr1[],int frames,int total_pages){
    int queue[frames],front = 0,rear = 0,hits=0,faults=0;
        for (int i = 0; i < frames; i++) {
        queue[i] = -1;
        }
        for (int i = 0; i < total_pages; i++) {
        int page = arr1[i];
        int flag = 0;
        for (int j = 0; j < frames; j++) {
            if (queue[j] == page) {
                flag = 1;
                hits++;
                break;
            }
        }

            if (flag == 0) {
            queue[rear] = page;
            rear = (rear + 1) % frames;
            faults++;
        }
        printf("Page %d -> ", page);
        for (int j = 0; j < frames; j++) {
            printf("%d ", queue[j]);
        }
        printf("\n");
}
    printf("Hits = %d, Faults = %d\n", hits, faults);
}


void LRU(int arr1[],int frames,int total_pages){
    int queue[frames];
    int counter[frames];
    int hits=0,faults=0;
    for (int i = 0; i < frames; i++) {
        queue[i] = -1;
        counter[i] = 0;
    }
    for (int i = 0; i < total_pages; i++) {
        int page = arr1[i];
        bool flag = false;
        for (int j = 0; j < frames; j++) {
            if (queue[j] == page) {
                flag = true;
                hits++;
                counter[j] = 0;
                break;
            }
        }
        if (!flag) {
            int min = counter[0];
            int index = 0;
            for (int j = 1; j < frames; j++) {
                if (counter[j] < min) {
                    min = counter[j];
                    index = j;
                }
            }
            queue[index] = page;
            counter[index] = 0;
            faults++;
        }
        for (int j = 0; j < frames; j++) {
            if (queue[j] != -1) {
                counter[j]++;
            }
        }
        printf("Page %d -> ", page);
        for (int j = 0; j < frames; j++) {
            printf("%d ", queue[j]);
        }
        printf("\n");
    }
    printf("Hits = %d, Faults = %d\n", hits, faults);
}

void Optimal(int arr1[],int frames,int total_pages){
    int queue[frames],hits=0,faults=0;
    for (int i = 0; i < frames; i++) {
        queue[i] = -1;
    }
    for (int i = 0; i < total_pages; i++) {
        int page = arr1[i];
        bool flag = false;
        for (int j = 0; j < frames; j++) {
            if (queue[j] == page) {
                flag = true;
                hits++;
                break;
            }
        }
        if (!flag) {
            int max = INT_MIN;
            int index = -1;
            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < total_pages; k++) {
                    if (queue[j] == arr1[k]) {
                        break;
                    }
                }
                if (k == total_pages) {
                    index = j;
                    break;
                }
                if (k > max) {
                    max = k;
                    index = j;
                }
            }
            queue[index] = page;
            faults++;
        }
        printf("Page %d -> ", page);
        for (int j = 0; j < frames; j++) {
            printf("%d ", queue[j]);
        }
        printf("\n");
    }
    printf("Hits = %d, Faults = %d\n", hits, faults);
}

void MRU(int arr1[],int frames,int total_pages){
    int queue[frames],hits=0,faults=0;
    for (int i = 0; i < frames; i++) {
        queue[i] = -1;
    }
    for (int i = 0; i < total_pages; i++) {
        int page = arr1[i];
        bool flag = false;
        for (int j = 0; j < frames; j++) {
            if (queue[j] == page) {
                flag = true;
                hits++;
                for (int k = j; k < frames - 1; k++) {
                    queue[k] = queue[k + 1];
                }
                queue[frames - 1] = page;
                break;
            }
        }
        if (!flag) {
            for (int j = frames - 1; j > 0; j--) {
                queue[j] = queue[j - 1];
            }
            queue[0] = page;
            faults++;
        }
        printf("Page %d -> ", page);
        for (int j = 0; j < frames; j++) {
            printf("%d ", queue[j]);
        }
        printf("\n");
    }
    printf("Hits = %d, Faults = %d\n", hits, faults);
}

int main(){
    FILE *fp1;
    char line[1000];
    char *token;
    char *delim = " ";
    int arr1[100]; // Assuming the file has at most 100 integers
    int i = 0,total_pages;
    fp1 = fopen("Pages.txt", "r"); // Replace with your file name and path
    if (fp1 == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp1)) {
        token = strtok(line, delim);
        while (token != NULL && i < 100) {
            arr1[i] = atoi(token); // Convert string to integer
            i++;
            token = strtok(NULL, delim);
        }
    }
    total_pages = i;
    fclose(fp1);
    // Print the array to verify
    printf("The sequesnce of pages: ");
    for (int j = 0; j < total_pages; j++) {
        printf("%d ", arr1[j]);
    }
    printf("\n");
    // frames
    int frames;
    printf("Enter number of frames: ");
    scanf("%d",&frames);
    printf("1: FIFO, 2: LRU(Least Recently Used), 3: Optimal, 4: MRU(Most Recently Used), 5: Exit\n");
    int choice;
    scanf("%d",&choice);
        if(choice==1){
            FIFO(arr1,frames,total_pages);
        }
        else if (choice==2){
            LRU(arr1,frames,total_pages);
        }
        else if(choice==3){
            Optimal(arr1,frames,total_pages);
        }
        else if (choice==4){
            MRU(arr1,frames,total_pages);
        }
        else if (choice==5){
            exit(0);
        }
        else {
            printf("Enter Appropriate value");
        }
    
}