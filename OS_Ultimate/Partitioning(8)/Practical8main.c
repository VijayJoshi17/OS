#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int count(FILE* fp){
    char line[100];
    fgets(line,100,fp);
    int cnt = 1;
    for(int i = 0; i<strlen(line); i++){
        if(line[i]=='\n') break;
        if(line[i]==',') cnt++;
    }
    return cnt;
}

void readline(FILE* fp, int cnt, int* arr){
    char line[100];
    fgets(line,100,fp);
    char *token = strtok(line,",");
    arr[0] = atoi(token);
    for(int i = 0; i<cnt; i++){
        token = strtok(NULL,",");
        arr[i+1] = atoi(token);
    }
}

void fixed_size_partition(int ch, int* memory, int* process, int n, int m){
    int bit[n];
    for(int i = 0; i<n; i++) bit[i] = 1;
    int int_frag = 0, ext_frag = 0;
    if(ch==1){
        for(int i = 0; i<m; i++){
            int max = 0, maxind=-1;
            for(int j = 0; j<n; j++){
                if(bit[j] && memory[j]>max){
                    maxind = j;
                    max = memory[j];
                }
            }
            if(maxind==-1 || memory[maxind]<process[i]){
                ext_frag += process[i];
            }
            else{
                bit[maxind]=0;
                int_frag += (memory[maxind]-process[i]);
            }
        }
    }
    else if(ch==2){
        for(int i = 0; i<m; i++){
            int min = 1000000, minind=-1;
            for(int j = 0; j<n; j++){
                if(bit[j] && memory[j]<min && process[i]<=memory[j]){
                    minind = j;
                    min = memory[j];
                }
            }
            if(minind==-1){
                ext_frag += process[i];
            }
            else{
                bit[minind]=0;
                int_frag += (memory[minind]-process[i]);
            }
        }

    }
    else if(ch==3){
        for(int i = 0; i<m; i++){
            int ind = -1;
            for(int j = 0; j<n; j++){
                if(bit[j] && process[i]<=memory[j]){
                    ind = j;
                    break;
                }
            }
            if(ind==-1){
                ext_frag += process[i];
            }
            else{
                bit[ind]=0;
                int_frag += (memory[ind]-process[i]);
            }
        }
    }
    printf("\nInternal Fragmentation: %d\n",int_frag);
    printf("External Fragmentation: %d\n",ext_frag);
}
void variable_size_partition(int ch, int* memory, int* process, int n, int m){
    int ext_frag = 0;
    if(ch==1){
        for(int i = 0; i<m; i++){
            int max = 0, maxind=-1;
            for(int j = 0; j<n; j++){
                if(memory[j]>max && process[i]<=memory[j]){
                    maxind = j;
                }
            }
            if(maxind==-1){
                ext_frag += process[i];
            }
            else{
                memory[maxind] -= process[i];
            }
        }
    }
    else if(ch==2){
        for(int i = 0; i<m; i++){
            int min = 1000000, minind=-1;
            for(int j = 0; j<n; j++){
                if(memory[j]<min && process[i]<=memory[j]){
                    minind = j;
                    min = memory[j];
                }
            }
            if(minind==-1){
                ext_frag += process[i];
            }
            else{
                memory[minind] -= process[i];
            }
        }
    }
    else{
        for(int i = 0; i<m; i++){
            int ind = -1;
            for(int j = 0; j<n; j++){
                if(process[i]<=memory[j]){
                    ind = j;
                    break;
                }
            }
            if(ind==-1){
                ext_frag += process[i];
            }
            else{
                memory[ind] -= process[i];
            }
        }
    }
    printf("\nInternal Fragmentation: 0\n");
    printf("External Fragmentation: %d\n",ext_frag);
}

int main(){
    FILE* fp = fopen("Practical8.txt","r");
    int n = 0,m=0;
    n = count(fp);
    m = count(fp);
    int memory[n], process[m];
    fp = fopen("prac8data.txt","r");
    readline(fp,n,memory);
    readline(fp,m,process);
    while(1)
    {
    printf("\nChoose the Partitioning Scheme:- \n");
    printf("1. Fixed size partitioning\n");
    printf("2. Variable size partitioning\n");
    printf("3. Exit \n");
    int ch1,ch2;
    scanf("%d",&ch1);
    if(ch1!=3){
    printf("Choose the memory allocation technique:- \n");
    printf("1. Worst-Fit\n");
    printf("2. Best-Fit\n");
    printf("3. First-Fit\n");
    scanf("%d",&ch2);
    }
    switch(ch1){
        case 1:
            if(ch2>=1 && ch2<=3) fixed_size_partition(ch2,memory,process,n,m);
            else printf("INVALID INPUT!\n");
            break;
        case 2:
            if(ch2>=1 && ch2<=3) variable_size_partition(ch2,memory,process,n,m);
            else printf("INVALID INPUT!\n");
            break;
        case 3:
            printf("\nThank You :)\n");
            exit(0);
            break;

        default:
            printf("INVALID INPUT!\n");        
    }
    }
}