#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<math.h>

struct node{
  int s;
  struct node *next;
};

void readData(struct node **l){
    struct node *p,*q,*r;
    FILE *fp;
    fp=fopen("Disk.txt","r");
    int x;
    while(fscanf(fp,"%d",&x)!=EOF){
           p=(struct node*)malloc(sizeof(struct node));
           p->s=x;
           p->next=NULL;
           if((*l)==NULL){
            (*l)=p;
            q=p;
           }
           else{
            q->next=p;
            q=p;
           }
    }
}

void print(struct node *l){
    while(l!=NULL){
        printf("%d ",l->s);
        l=l->next;
    }
    printf("\n");
}
void fcfs(struct node **l){
    struct node *x=(*l),*y=NULL,*z,*t;
    int p;
    int seek=0;
    printf("Enter the value of initial head position: ");
    scanf("%d",&p);
    while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    printf("\nTotal number of seek operations: %d\n",seek);
    printf("\nSeek sequence: \n");
    print(y);
}

void sort(struct node **l,int u){
    struct node *x=(*l),*y;
    while(x!=NULL){
        y=(*l);
        while(y!=NULL){
             if(x->s<y->s && u==1){
                int d=x->s;
                x->s=y->s;
                y->s=d;
             }
             if(x->s>y->s && u==2){
                int d=x->s;
                x->s=y->s;
                y->s=d;
             }
             y=y->next;
        }
        x=x->next;
    }
}
struct node *search(struct node *l,int x){
      while(l!=NULL){
        if(l->s>=x){
            return l;
        }
        l=l->next;
      }
      return NULL;
}

void scan(struct node **l){
    struct node *x=(*l),*y=NULL,*z,*t,*q;
    int p,f,c;
    int seek=0;
    printf("\n1. LEFT to RIGHT\n2. RIGHT to LEFT\nPress: ");
    scanf("%d",&c);
    if(c==1){
         printf("Enter the value of initial head position: ");
    scanf("%d",&p);
      f=p;
    x=search(*l,p);
    while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    sort(&(*l),2);
    q=(*l);
    while(q!=NULL){
        if(q->s<=f){
            break;
        }
        q=q->next;
    }
    x=q;
     while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    printf("\nTotal number of seek operations: %d\n",seek);
    printf("\nSeek sequence: \n");
    print(y);
    }
    else if(c==2){
    sort(&(*l),2);
    printf("Enter the value of initial head position: ");
    scanf("%d",&p);
    f=p;
    while(x!=NULL){
        if(x->s<p){
            break;
        }
        x=x->next;
    }
    while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    seek+=(p);
    p=0;
    z=(struct node*)malloc(sizeof(struct node));
           z->s=0;
           z->next=NULL;
           t->next=z;
           t=z;
    sort(&(*l),1);
    x=search(*l,f);
     while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    printf("\nTotal number of seek operations: %d\n",seek);
    printf("\nSeek sequence: \n");
    print(y);
    }
    else {
        printf("Invalid input..!!!!\n");
    }
}

void cscan(struct node **l){
    struct node *x=(*l),*y=NULL,*z,*t,*q;
    int p,f;
    int seek=0;
    printf("Enter the value of initial head position: ");
    scanf("%d",&p);
    f=p;
    sort(&(*l),1);
    x=search(*l,p);
     while(x!=NULL){
        int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    seek+=(p);
    p=0;
    z=(struct node*)malloc(sizeof(struct node));
           z->s=0;
           z->next=NULL;
           t->next=z;
           t=z;
    x=(*l);
    while(x->s<f){
       int d=fabs(p-x->s);
        seek+=d;
        p=x->s;
        z=(struct node*)malloc(sizeof(struct node));
           z->s=x->s;
           z->next=NULL;
        if(y==NULL){
           y=z;
           t=z;
        }
        else{
          t->next=z;
          t=z;
        }
        x=x->next;
    }
    printf("\nTotal number of seek operations: %d\n",seek);
    printf("\nSeek sequence: \n");
    print(y);
}
int main(){
   struct node *l=NULL;
  readData(&l);
  printf("\n======================================================\n\n");
  printf("          DISK SHEDULING ALGORITHMS\n");
  printf("\n======================================================\n\n");
  printf("Request sequenece: \n");
  print(l);
  int ch;
  while(1){
    printf("\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit\nPress: ");
    scanf("%d",&ch);
    if(ch==1){
        fcfs(&l);
    }
    else if(ch==2){
        scan(&l);
    }
    else if(ch==3){
        cscan(&l);
    }
    else if(ch==4){
        printf("\n   THANK YOU :)\n\n");
        break;
    }
  }
}