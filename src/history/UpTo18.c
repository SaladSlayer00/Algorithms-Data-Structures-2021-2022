#include<stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodo {
  int info;
  long w;
  struct nodo *next;
};

void stampa_class(struct nodo *classifica, int k){
  struct nodo *temp;
  int i=0;
  temp=classifica;
  while(temp!=NULL && i<k){
    printf("%d", temp->info);
    temp=temp->next;
    if(temp!=NULL){
      printf(" ");
    }
    i++;
  }
  printf("\n");
}

void enqueueC(int k, int n, long p, struct nodo **q){
    struct nodo *temp=malloc(sizeof(struct nodo));
    int i=0;
    temp->info = n;
    temp->w=p;
    struct nodo *cur = *q;
    if(*q==NULL|| cur->w>p){
        temp->next=*q;
        *q=temp;
    }
    else{
        
        while(cur->next!=NULL && cur->next->w<=p){
            cur=cur->next;
            i++;
        }
        if(i<k){
          temp->next=cur->next;
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
    long c = getchar_unlocked(), x=0;
    while(c!='\n'&& c!=','){
      x = (x<<1) + (x<<3) + c - 48;
      c = getchar();//questo mi si prende il newline
    }
    return x;
} 

void stampa_vett(int d, long vect[d]){
  int i;
  for(i=0;i<d;i++){
    printf("%ld ", vect[i]);
  }
  printf("\n");
}

long dijkstra(int n, long G[n][n], long distance[n], int visited[n]){
    int mindistance,nextnode=0,i,j, change=1;
    distance[0]=0;
    for(i=1;i<n;i++){
    distance[i]=G[0][i];
    }
    //stampa_vett(n,distance);
    visited[0]=1;
    while((j=sum_v(n,visited))<n && change==1){
      //printf("Visitati:%d\n", j);
      change=0;
        mindistance=-1;
        for(i=1;i<n;i++){
            if(distance[i]!=0 && (distance[i]<mindistance || mindistance==-1)&&!visited[i]){
                mindistance=distance[i];
                nextnode=i;
                //printf("Prossimo nodo: %d\n", nextnode);
                change=1;
            }
        }       
        visited[nextnode]=1;
        for(i=1;i<n;i++){
            if(!visited[i] && G[nextnode][i]!=0){
                if(mindistance+G[nextnode][i]<distance[i]||distance[i]==0){
                    distance[i]=mindistance+G[nextnode][i];
                }
            }
        }
        //stampa_vett(n,distance);

    }
//print the path and distance of each node
    long sum=0;
    for(i=0;i<n;i++){
        sum=sum+distance[i];
    }
    //printf("\nCosto: %ld\n", sum);
    return sum;
}

int main(void) {
  int dim,k,trash, i,j,a=0,b=0;
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
    //printf("%s\n", str);
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