#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct nodo {
  int info;
  long w;
  struct nodo *next;
};

long scanint()  
{
    long c = getchar_unlocked(), x=0;
    while(c!='\n'&& c!=','){
      x = (x<<1) + (x<<3) + c - 48;
      c = getchar_unlocked();//questo mi si prende il newline
    }
    return x;
} 
void stampa_iter(struct nodo *q){
  struct nodo *temp;
  temp=q;
  while(temp!=NULL){
    printf("(%d, %ld) ", temp->info, temp->w);
    temp=temp->next;
  }
  printf("\n");
}

struct nodo *leggi_lista(int n) {
  int i;
  long x;
  struct nodo *p, *primo;
  primo = NULL;
  for (i=0; i<n; i++) {
    x=scanint();
    //printf("%ld\n", x);
    if(x!=0 && i!=0){
      p = malloc(sizeof(struct nodo));
      p->w=x;
      p->info=i;
      p->next = primo;
      primo = p;
    }
  }
  return(primo);
}

void leggi_grafo(struct nodo *G[], int n) {
  int i;
  for (i=0; i<n; i++) {
    //printf("Lista di adiacenza del vertice %d.\n", i);
    G[i] = leggi_lista(n);
    //stampa_iter(G[i]);
  }
}

struct nodo *dequeue(struct nodo **q){
    struct nodo *cur = *q;
    *q=cur->next;
    return cur;
}

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


void enqueue(int n, long p, struct nodo **q){
    struct nodo *temp=malloc(sizeof(struct nodo));
    temp->info = n;
    temp->w=p;
    struct nodo *cur = *q;
    if(*q==NULL|| cur->w>p){
        temp->next=*q;
        *q=temp;
    }
    else{
        
        while(cur->next!=NULL && cur->next->w<p){
            cur=cur->next;
        }
        temp->next=cur->next;
        cur->next=temp;
    }
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



long dijkstra(struct nodo *coda, int dim, struct nodo *G[], long vect[dim]){
  struct nodo *q=malloc(sizeof(struct nodo)), *cur, *min, *temp;
  int i;
  long cost=0;
  q->w=0;
  q->info=0;
  q->next=coda;
  coda = q;
  while(coda!=NULL){
    min=dequeue(&coda);
    //("%d, %ld, %ld\n", min->info, min->w, vect[min->info]);
    if(vect[min->info]==0||vect[min->info]>min->w){
      vect[min->info]=min->w;
      //printf("%ld\n", vect[min->info]);
      cur=G[min->info];
      while(cur!=NULL){
        enqueue(cur->info, (cur->w)+(min->w), &coda);
        //stampa_iter(coda);
        temp=cur;
        cur=cur->next;
        free(temp);
      }
    
    }
    free(min);

  }
  for(i=0;i<dim;i++){
    cost=cost+vect[i];
  }
  return cost;
}


int main(void) {
  int dim,k,trash, i=0,j=0;
  char str[13],c;
  struct nodo *coda=NULL;
  struct nodo *class=NULL;
  trash = scanf("%d %d", &dim, &k);
  c=getchar_unlocked();
  long vect[dim], cost;
  struct nodo *G[dim];
  if(trash){};
  while((c=getchar_unlocked())!=EOF){
    while(c!='\n'){
      str[j]=c;
      j++;
      c=getchar_unlocked();
    }
    str[j]='\0';
    j=0;
    //printf("%s\n", str);
    if(strcmp(str, "TopK")==0){
      stampa_class(class, k);
    }
    else if(strcmp(str, "AggiungiGrafo")==0){
      memset(vect, 0, dim*sizeof(long));
      leggi_grafo(G, dim);
      cost = dijkstra(coda, dim, G, vect);
      //printf("Il costo è %ld\n", cost);
      enqueueC(k,i,cost, &class);
      i++;
    }
    else if(strcmp(str, "stop")==0){
      break;
    } 
  }
  return(0);
} 