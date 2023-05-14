#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct node{
    int s;
    int f;
    struct node *next;
};
void readFile(struct node **m,struct node **l){
      struct node *t=(*m),*u,*v;
      FILE *fp;
      fp=fopen("Memory.txt","r");
      while(1){
        char a[10];
        fscanf(fp,"%s",a);
        if(strcmp(a,"Process")==0){
              break;
        }
        if(strcmp(a,"Memory")==0) continue;
        int b=atoi(a);
        u=(struct node*)malloc(sizeof(struct node));
        u->s=b;
        u->f=0;
        u->next=NULL;
        if(*m==NULL){
            (*m)=u;
            v=u;
        }
        else{
            v->next=u;
            v=u;
        }
      }
      while(1){
        char a[10];
        fscanf(fp,"%s",a);
        if(strcmp(a,"End")==0){
              break;
        }
        int b=atoi(a);
        u=(struct node*)malloc(sizeof(struct node));
        u->s=b;
        u->f=0;
        u->next=NULL;
        if(*l==NULL){
            (*l)=u;
            v=u;
        }
        else{
            v->next=u;
            v=u;
        }
      }
}

void print(struct node *k){
    while(k!=NULL){
        printf("%d ",k->s);
        k=k->next;
    }
    printf("\n\n");
}

void f_first(struct node **m,struct node **l){
      struct node *t=*m,*u=*l;
      int int_f=0,ext_f=0;
      while(u!=NULL){
          t=*m;
          while(t!=NULL){
            if(u->s<=t->s && t->f==0){
                 t->f=1;
                 int_f+=(t->s-u->s);
                 break;
            }
            t=t->next;
          }
          if(t==NULL) ext_f+=u->s;
          u=u->next;
      }
      printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);
}

void v_first(struct node **m,struct node **l){
        struct node *t=*m,*u=*l,*v;
        int int_f=0,ext_f=0;
        while(u!=NULL){
           t=(*m);
           while(t!=NULL){
             if(u->s<=t->s){
              v=(struct node*)malloc(sizeof(struct node));
              v->s=t->s-v->s;
              v->next=t->next;
              t->next=v;
              break;
             }
             t=t->next;
           }
           if(t==NULL) ext_f+=u->s;
           u=u->next;
        }
        printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);
}

void f_best(struct node **m,struct node **l){
  struct node *t=(*m),*u=(*l);
  int diff=__INT32_MAX__;
  int int_f=0,ext_f=0;
  while(u!=NULL){
    t=(*m);
    struct node *y=NULL;
    diff=__INT32_MAX__;
    while(t!=NULL){
      if(t->s-u->s<=diff && t->f==0 && t->s-u->s>=0){
        y=t;
        diff=t->s-u->s;
      }
      t=t->next;
    }
    if(y==NULL){
      ext_f+=u->s;
    }
    else{
      y->f=1;
      int_f+=(y->s-u->s);
    }
    u=u->next;
  }
   printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);
}

void v_best(struct node **m,struct node **l){
  struct node *t=(*m),*u=(*l),*v;
  int diff=__INT32_MAX__;
  int int_f=0,ext_f=0;
  while(u!=NULL){
    diff=__INT32_MAX__;
    struct node *y=NULL;
    t=(*m);
    // print(t);
    while(t!=NULL){
       if(t->s-u->s<=diff && t->s-u->s>=0){
        y=t;
        diff=t->s-u->s;
      }
      t=t->next;
    }
    if(y==NULL){
      ext_f+=u->s;
    }
    else{
      v=(struct node*)malloc(sizeof(struct node));
              v->s=y->s-u->s;
              v->next=y->next;
              y->next=v;
    }
    u=u->next;
  }
  printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);
}
struct node *Worst(struct node **t,struct node *u){
  struct node *y=NULL,*v=*t,*r;
  int diff=0;
  while(v!=NULL){
    if(v->s-u->s>=diff && v->f==0){
          diff=v->s-u->s;
    }
    v=v->next;
  }
  v=*t;
  while((*t)!=NULL){
        if((*t)->s-u->s==diff && (*t)->f==0){
          (*t)->f=1;
          r=*t;
          (*t)=v;
          return r;
        }
        (*t)=(*t)->next;
  }
  return y;
}
// void f_worst(struct node **m,struct node **l){
//     struct node *t=(*m),*u=(*l);
//   int diff=0;
//   int int_f=0,ext_f=0;
//   while(u!=NULL){
//     struct node *y=Worst(&(*m),u);
//     if(y==NULL){
//       ext_f+=u->s;
//     }
//     else{
//       int_f+=(y->s-u->s);
//     }
//     u=u->next;
//   }
//    printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);   
// }
void f_worst(struct node **m,struct node **l){
  struct node *t=(*m),*u=(*l);
  int diff=0;
  int int_f=0,ext_f=0;
  while(u!=NULL){
    t=(*m);
    struct node *y=NULL;
    diff=0;
    while(t!=NULL){
      if(t->s-u->s>=diff && t->f==0 && t->s-u->s>=0){
        y=t;
        diff=t->s-u->s;
      }
      t=t->next;
    }
    if(y==NULL){
      ext_f+=u->s;
    }
    else{
      y->f=1;
      int_f+=(y->s-u->s);
    }
    u=u->next;
  }
   printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);
}

void v_worst(struct node **m,struct node **l){
  struct node *t=(*m),*u=(*l),*v;
  int diff=0;
  int int_f=0,ext_f=0;
  while(u!=NULL){
    diff=0;
    struct node *y=NULL;
    t=(*m);
    // print(t);
    while(t!=NULL){
       if(t->s-u->s>=diff && t->s-u->s>=0){
        y=t;
        diff=t->s-u->s;
      }
      t=t->next;
    }
    if(y==NULL){
      ext_f+=u->s;
    }
    else{
      v=(struct node*)malloc(sizeof(struct node));
              v->s=y->s-u->s;
              v->next=y->next;
              y->next=v;
    }
    u=u->next;
  }
  printf("\nInternal fragmentation = %d\nExtrenal fragmentation = %d\n\n",int_f,ext_f);

}

void clearData(struct node **l,struct node **m){
  struct node *y=(*l);
  if(y==NULL) return;
  (*l)=(*l)->next;
  free(y);
  while((*l)!=NULL){
        y=(*l);
        (*l)=(*l)->next;
        free(y);
  }
  y=(*m);
  if(y==NULL) return;
  (*m)=(*m)->next;
  free(y);
  while((*m)!=NULL){
        y=(*m);
        (*m)=(*m)->next;
        free(y);
  }
}
int main()
{
  struct node *m=NULL,*l=NULL;
  readFile(&m,&l);
  printf("\n");
  printf("============================================================\n\n");
  printf("           Memory Allocation Techniques\n\n");
  printf("============================================================\n");
  printf("Available memory is :\n");
  print(m);
  printf("Process request memory is : \n");
  print(l);
  int ch;
  while(1){
  printf("1. Fixed size partition\n2. variable size partition\n3. Exit\nPress: ");
  scanf("%d",&ch);
  if(ch==1){
    printf("\n1. First-fit\n2. Best-fit\n3. Worst-fit\n4. Exit\nPress: ");
    scanf("%d",&ch);
    if(ch==1){
  f_first(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
    }
    else if(ch==2){
  f_best(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
  }
  else if(ch==3){
  f_worst(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
  }
  else break;
  }
  else if(ch==2){
    printf("\n1. First-fit\n2. Best-fit\n3. Worst-fit\n4. Exit\nPress: ");
    scanf("%d",&ch);
    if(ch==1){
  v_first(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
    }
    else if(ch==2){
  v_best(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
  }
  else if(ch==3){
  v_worst(&m,&l);
  clearData(&l,&m);
   readFile(&m,&l);
  }
  else break;
  }
  else break;
  }
  printf("\nThank you :)\n\n");
}