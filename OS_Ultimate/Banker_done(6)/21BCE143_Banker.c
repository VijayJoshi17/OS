#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct node{
     char n[10];
     int a,b,c,n1;
     struct node *next;
};

struct Node{
    char n[10];
    struct Node *next;
};

void add_node(struct Node **g,char *s){
    struct Node *t;
    t=(struct Node*)malloc(sizeof(struct Node));
    strcpy(t->n,s);
    t->next=NULL;
    if((*g)==NULL){
       (*g)=t;
    }
    else{
        struct Node *r=(*g);
        while(r->next!=NULL){
            r=r->next;
        }
        r->next=t;
    }
}
void printSafe(struct Node *g){
  printf("Safe sequence is: \n\n");
  while(g!=NULL){
    printf("%s ",g->n);
    g=g->next;
  }
  printf("\n\n");
}
void readFile1(struct node **l,struct node **m,struct node **s){
        FILE *fp;
        fp=fopen("Banker.txt","r");
        struct node *t,*r;
        char a[10];
        int b,c,d;
        while(1){
            fscanf(fp,"%s",a);
            if(strcmp(a,"Max")==0) continue;
            if(strcmp(a,"Allocated")==0) break;
            fscanf(fp,"%d %d %d",&b,&c,&d);
            t=(struct node*)malloc(sizeof(struct node));
            strcpy(t->n,a);
            t->a=b;
            t->b=c;
            t->c=d;
            t->next=NULL;
            if((*l)==NULL){
                (*l)=t;
                r=t;
            }
            else{
                r->next=t;
                r=t;
            }
        }
        while(1){
            fscanf(fp,"%s",a);
            if(strcmp(a,"Available")==0) break;
            fscanf(fp,"%d %d %d",&b,&c,&d);
            t=(struct node*)malloc(sizeof(struct node));
            strcpy(t->n,a);
            t->a=b;
            t->b=c;
            t->c=d;
            t->next=NULL;
            if((*m)==NULL){
                (*m)=t;
                r=t;
            }
            else{
                r->next=t;
                r=t;
            }
        }
        fscanf(fp,"%d %d %d",&b,&c,&d);
        (*s)=(struct node*)malloc(sizeof(struct node));
        (*s)->a=b;
        (*s)->b=c;
        (*s)->c=d;
        (*s)->next=NULL;
}

void need(struct node **l,struct node **m,struct node **n){
    struct node *b=(*l),*d=(*m),*t,*x;
    while(b!=NULL && d!=NULL){
        t=(struct node*)malloc(sizeof(struct node));
        strcpy(t->n,b->n);
        t->a=b->a-d->a;
        t->b=b->b-d->b;
        t->c=b->c-d->c;
        t->n1=0;
        t->next=NULL;
        if((*n)==NULL){
            (*n)=t;
            x=t;
        }
        else{
            x->next=t;
            x=t;
        }
        b=b->next;
        d=d->next;
    }
}
void printList(struct node *l){
    while(l!=NULL){
        printf("%s %d %d %d\n",l->n,l->a,l->b,l->c);
        l=l->next;
    }
}
int len(struct node *l){
    int l1=0;
    while(l!=NULL) l=l->next,l1++;
   return l1;
}
void bankers(struct node **l,struct node **m,struct node **n,struct node **s){
         struct node *a=*s,*b=*n,*c=*m;
         struct Node *g=NULL;
         int x=len(*n),y=0,ch=0,k=0;
         while(x!=y){
            b=(*n);
            c=(*m);
            while(b!=NULL && c!=NULL){
                ch=0;
                if(a->a>=b->a && a->b>=b->b && a->c>=b->c && b->n1==0){
                       add_node(&g,b->n);
                       b->n1=1;
                       a->a+=c->a;
                       a->b+=c->b;
                       a->c+=c->c;
                       y++;
                       ch=1;
                       break;
                }
                b=b->next;
                c=c->next;
            }
            if(ch==0){
                printf("\n\nDeadlock is detected...\n\n");
                k=1;
                break;
            }
         }
         if(k==0){
            printf("\nNo deadlock...\n\n");
            printSafe(g);
         }
}
int main()
{
  struct node *l=NULL,*m=NULL,*n=NULL,*s=NULL;
  readFile1(&l,&m,&s);
//   printf("Max\n");
//   printList(l);
//   printf("\nAllocated\n");
//   printList(m);
  need(&l,&m,&n);
//   printf("Need\n");
//   printList(n);
  bankers(&l,&m,&n,&s);
}