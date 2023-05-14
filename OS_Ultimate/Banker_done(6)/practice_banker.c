#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

int main(){
    FILE *fp1,*fp2,*fp3;
    int allocation[10][10],max[10][10],available[10],f[10];
    fp1 = fopen("allocation.txt","r");
    if (fp1 == NULL) {
        printf("Unable to open file\n");
        return 1;
    }
    fp2 = fopen("max.txt","r");
        if (fp2 == NULL) {
        printf("Unable to open file\n");
        return 1;
    }
    fp3 = fopen("available.txt","r");
        if (fp3 == NULL) {
        printf("File not fount");
        return 1;
    }

    int c,r1,c1,r2,c2,r3,c3;
    fscanf(fp1, "%d %d", &r1, &c1);
    while ((c = getc(fp1)) != EOF && c != '\n');
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            fscanf(fp1, "%d", &allocation[i][j]);
        }
    }
    fscanf(fp2, "%d %d", &r2, &c2);
    while ((c = getc(fp2)) != EOF && c != '\n');
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            fscanf(fp2, "%d", &max[i][j]);
        }
    }

    int index = 0, num;
    while (fscanf(fp3, "%d", &num) == 1) {
        available[index++] = num;
    }


    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    printf("Allocation Matrix :\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("Max Matrix :\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
    printf("Availabe :\n");
    for (int i = 0; i < index; i++) {
        printf("%d ", available[i]);
    }
        printf("\n");

    // Banker's Algo.
    int i,j,k,n=r1,m=c1;
    // Initialize the finish vector to all zeros
    for (int i = 0; i < r1; i++) {
        f[i] = 0;
    }
    int need[n][m],ans[n],ind=0;  
    for (i = 0; i < n; i++)  
    {  
        for (j = 0; j < m; j++)  
            need[i][j] = max[i][j] - allocation[i][j];  
    }  
    int y = 0;  
    for (k = 0; k < 5; k++)  
    {  
        for (i = 0; i < n; i++)  
        {  
            if (f[i] == 0)  
            {  
                int flag = 0;  
                for (j = 0; j < m; j++)  
                {  
                    if (need[i][j] > available[j])  
                    {  
                        flag = 1;  
                        break;  
                    }  
                }  
                if (flag == 0)  
                {  
                    ans[ind++] = i;  
                    for (y = 0; y < m; y++)  
                        available[y] += allocation[i][y];  
                    f[i] = 1;  
                }  
            }  
        }  
    }  
    int flag = 1;  
    for (int i = 0; i < n; i++)  
    {  
        if (f[i] == 0)  
        {  
            flag = 0;  
            printf("The following system is not safe");  
            break;  
        }  
    }  
    if (flag == 1)  
    {  
        printf("Following is the SAFE Sequence\n");  
        for (i = 0; i < n - 1; i++)  
            printf(" P%d ->", ans[i]);  
        printf(" P%d", ans[n - 1]);  
    }  
    return (0); 
}