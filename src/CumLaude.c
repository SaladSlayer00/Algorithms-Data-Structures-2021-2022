#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
  int index;
  long weight;
  struct nodo *next;
};

void stampa_class(struct nodo *classifica, int k){
  struct nodo *temp;
  int i=0;
  temp=classifica;
  while(temp!=NULL && i<k){
    printf("%d", temp->index);
    temp=temp->next;
    if(temp!=NULL){
      printf(" ");
    }
    i++;
  }
  printf("\n");
}

void enqueueC(int k, int n, long p, struct nodo **q){   
    int i=0;
    struct nodo *cur = *q, *sup, *prev;
    if(*q==NULL|| cur->weight>p){
        struct nodo *temp=malloc(sizeof(struct nodo));
        temp->index = n;
        temp->weight=p;
        temp->next=*q;
        *q=temp;
    }
    else{
        
        while(cur->next!=NULL && cur->next->weight<=p){
            cur=cur->next;
            i++;
        }
        if(i<k-1){
            struct nodo *temp=malloc(sizeof(struct nodo));
            temp->index = n;
            temp->weight=p;
            temp->next=cur->next;
            cur->next=temp;
        }
        else if(i==k-1){
            struct nodo *temp=malloc(sizeof(struct nodo));
            temp->index = n;
            temp->weight=p;
            temp->next=NULL;
            sup=cur->next;
            while(sup!=NULL){
                prev=sup;
                sup=sup->next;
                free(prev);
            }
            cur->next=temp;
        }
    }
}


int sum_v(int n, int v[n]){
    int i, sum=0;
    for(i=0;i<n;i++){
        sum=sum+v[i];
    }
    return sum;
}

long scanint()  
{
    long carattere = getchar_unlocked(), var=0;
    while(carattere!='\n'&& carattere!=','){
      var = (var<<1) + (var<<3) + carattere - 48;
      carattere = getchar();
    }
    return var;
} 

long dijkstra(int n, long mat[n][n], long distance[n], int visited[n]){
    int min,next=0,i,j, change=1;
    distance[0]=0;
    for(i=1;i<n;i++){
    distance[i]=mat[0][i];
    }
    visited[0]=1;
    while((j=sum_v(n,visited))<n && change==1){
      change=0;
        min=-1;
        for(i=1;i<n;i++){
            if(distance[i]!=0 && (distance[i]<min || min==-1)&&!visited[i]){
                min=distance[i];
                next=i;
                change=1;
            }
        }       
        visited[next]=1;
        for(i=1;i<n;i++){
            if(visited[i]==0 && mat[next][i]!=0){
                if(min+mat[next][i]<distance[i]||distance[i]==0){
                    distance[i]=min+mat[next][i];
                }
            }
        }
    }
    long sum=0;
    for(i=0;i<n;i++){
        sum=sum+distance[i];
    }
    return sum;
}

int main(void) {
  int dim,k,trash,i,j,a=0,b=0;
  char str[13],c;
  struct nodo *class=NULL;
  trash = scanf("%d %d", &dim, &k);
  c=getchar_unlocked();
  long vect[dim], cost, mat[dim][dim],x;
  int visit[dim];
  if(trash){};
  while((c=getchar())!=EOF){
    while(c!='\n'){
      str[b]=c;
      b++;
      c=getchar_unlocked();
    }
    str[b]='\0';
    b=0;
    if(strcmp(str, "TopK")==0){
      stampa_class(class, k);
    }
    else if(strcmp(str, "AggiungiGrafo")==0){
        for (i=0; i<dim; i++) {
            for(j=0;j<dim;j++){
                x=scanint();
                mat[i][j]=x;
            }
        }
        memset(visit, 0, dim*sizeof(int));
        cost = dijkstra(dim, mat, vect, visit);
        enqueueC(k,a,cost, &class);
        a++;
    }
    else if(strcmp(str, "stop")==0){
      break;
    } 
  }
  return(0);
}