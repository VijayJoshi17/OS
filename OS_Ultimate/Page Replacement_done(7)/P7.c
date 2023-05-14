#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct node{
  int x,c;
  struct node *next;
  struct node *prev;
};

struct node *readFile(struct node **l){
    FILE *fp;
    fp=fopen("Pages.txt","r");
    int p;
    struct node *n,*t,*x=(*l),*q;
    while(fscanf(fp,"%d",&p)!=EOF){
      q=(struct node*)malloc(sizeof(struct node));
      q->next=NULL;
      q->prev=NULL;
      q->x=p;
       if((*l)==NULL){
        (*l)=q;
        n=(*l);
       }
       else{
            n->next=q;
            q->prev=n;
            n=q;
       }
    }
    return n;
}
int len(struct node *k){
  int d=1;
  if(k==NULL) return 0;
  struct node *u=(k);
  k=k->next;
  while(k!=u){
        d++; 
        k=k->next;
  }
  // printf("L\n");
  return d;
}
int search(struct node *k,int y){
  if(k==NULL) return -1;
   if(k->x==y){
    return 1;
   }
   else{
    struct node *u=(k);
    k=k->next;
    while(k!=u){
          if(k->x==y){
            return 1;
            }
          k=k->next;
    }
   }
   return -1;
}

void printL(struct node *k){
   struct node *u=k;
   printf("%d ",k->x);
   k=k->next;
   while(k!=u){
    printf("%d ",k->x);
    k=k->next;
   }
   printf("\n");
}
void FIFO(struct node **l){
   int n;
   printf("Enter no of frames: ");
   scanf("%d",&n);
   int page_fault=0,q=0;
   struct node *k=NULL,*r,*t=(*l),*w,*cur=k;
   while(t!=NULL){
     if(len(k)<n){
         if(search(k,t->x)==-1){
         r=(struct node*)malloc(sizeof(struct node));
         r->x=t->x;
         r->next=k;
         if(k==NULL){
          k=r;
          cur=k;
          k->next=r;
          k->prev=r;
          w=r;
         }
         else{
           w->next=r;
           r->prev=w;
           w=r;
         }
         page_fault++;
         }
     }
     else{
      if(search(k,t->x)==-1){
        page_fault++;
        
        cur->x=t->x;
        cur=cur->next;
      }
     }
    q++;
     t=t->next;
   }
   printf("\nNo of page faults are = %d\n",page_fault);
   float hit_ratio =((float)(page_fault)/q)*100;
   printf("Hit ratio = %f\nMiss ratio = %f",hit_ratio,100-hit_ratio);
}
int searchOptimul(struct node *u,int x){
  while(u!=NULL){
    // printf("U\n");
    if(u->x==x) return 1;
    u=u->next;
  }
  return -1;
}
int lenoptimul(struct node *u){
  int l=0;
  while(u!=NULL){
    u=u->next;
    l++;
  }
  return l;
}
struct node *optiNode(struct node *y,struct node *c,struct node *k,int n){
      struct node *u=NULL,*w,*t,*e,*s=c;
      while(c!=y){
        // printf("SF\n");
        // if(c==NULL) printf("N\n");
        if(search(k,c->x)==1){
          // printf("S\n");
          return c;
        }
        c=c->prev;
      }
      return s;
}
void optimul(struct node **l,struct node *y){
  int n;
   printf("Enter no of frames: ");
   scanf("%d",&n);
   int page_fault=0,q=0;
   struct node *k=NULL,*r,*t=(*l),*w,*cur=k;
   while(t!=NULL){
     if(len(k)<n){
         if(search(k,t->x)==-1){
         r=(struct node*)malloc(sizeof(struct node));
         r->x=t->x;
         r->next=k;
         if(k==NULL){
          k=r;
          cur=k;
          k->next=r;
          k->prev=r;
          w=r;
         }
         else{
           w->next=r;
           r->prev=w;
           w=r;
         }
         page_fault++;
         }
     }
     else{
      if(search(k,t->x)==-1){
      // printf("F\n");
        struct node *c=optiNode(t,y,k,n),*v=k;
        if(v->x==c->x){
          v->x=t->x;
        }
        else{
          v=v->next;
          while(v!=k){
            if(v->x==c->x){
          v->x=t->x;
          break;
        }
        v=v->next;
          }
        }
        page_fault++;
      }
     }
    //  printf("%d ",len(k));
    //  printL(k);
    q++;
     t=t->next;
   }
   printf("\nNo of page faults are = %d\n",page_fault);
   float hit_ratio =((float)(page_fault)/q)*100;
   printf("Hit ratio = %f\nMiss ratio = %f",hit_ratio,100-hit_ratio);
}
struct node *LRUNode(struct node *t,struct node *y,struct node *k,int n){
    struct node *u=t;
    while(u!=y){
      if(search(k,u->x)==1){
        return u;
      }
      u=u->next;
    }
    return t;
}
void LRU(struct node **l){
  int n;
   printf("Enter no of frames: ");
   scanf("%d",&n);
   int page_fault=0,q=0;
   struct node *k=NULL,*r,*t=(*l),*w,*cur=k;
   while(t!=NULL){
     if(len(k)<n){
         if(search(k,t->x)==-1){
         r=(struct node*)malloc(sizeof(struct node));
         r->x=t->x;
         r->next=k;
         if(k==NULL){
          k=r;
          cur=k;
          k->next=r;
          k->prev=r;
          w=r;
         }
         else{
           w->next=r;
           r->prev=w;
           w=r;
         }
         page_fault++;
         }
     }
     else{
      if(search(k,t->x)==-1){
      // printf("F\n");
        struct node *c=LRUNode(*l,t,k,n),*v=k;
        if(v->x=c->x){
          v->x=t->x;
        }else{
          v=v->next;
          while(v!=k){
            if(c->x==k->c){
              c->x=t->x;
              break;
            }
            v=v->next;
          }
        }
        page_fault++;
      }
     }
    q++;
     t=t->next;
   }
   printf("\nNo of page faults are = %d\n",page_fault);
   float hit_ratio =((float)(page_fault)/q)*100;
   printf("Hit ratio = %f\nMiss ratio = %f",hit_ratio,100-hit_ratio);
}
int main()
{
   struct node *l=NULL,*y;
  y=readFile(&l);
  printf("\n          Page replacement algorithms\n\n");
  while(1){
    int ch;
    printf("\n\n1. FCFS\n2. Optimul\n3. LRU\n4. Exit");
    printf("Enter choice: ");
    scanf("%d",&ch);
    if(ch==1){
        FIFO(&l);
     }
    else if(ch==2){
        optimul(&l,y);
     }
    
    else if(ch==3){
      LRU(&l);
    }
    else if(ch==4){
      printf("\nTHANK YOU :)\n");
      break;
    }
    else{
      printf("Enter valid choice");
    }
  }
}