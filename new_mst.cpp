#include <iostream>
#include <math.h>
#include <limits.h>
using namespace std;
#define r 15
#define pos 105
int rear[r+2]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int head[pos+2]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int MAX =5000;
int queue_bfs[500];

class node{
public:
    int x;
    int y;
    
};


void display(int queue_array[], int i)
{
    if(head[i] == -1)
        cout<<"Queue is empty"<<endl;
    else
    {
        printf("Queue[%d] is : \n",i);
        for(int j = head[i]; j <= rear[i]; j++)
        {printf("%d",queue_array[j]);}
    }
    printf("\n");
}
void enqueue(int item , int queue_array[],int i)
{
    if(rear[i] == MAX-1)
        printf("Queue Overflow \n");
    else
    {
        if(head[i]== -1)
        {head[i] = 0;}
        rear[i] = rear[i]+1;
        queue_array[rear[i]] = item;
    }
}
int dequeue(int queue_array[], int i)
{
    if(head[i] == -1 || head[i] > rear[i])
    {
        printf("Queue Underflow \n");
    }
    if(head[i]!=-1)
    {
        int k = queue_array[head[i]];
        head[i] = head[i]+1 ;
        return k;
    }
    return -1;
}


int delete_element(int arr[], int n, int x,int s)
{
    int i;
    for (i=0; i<n; i++)
        if (arr[i] == x)
            break;
    if (i < n)
    {
        n = n - 1;
        for (int j=i; j<n; j++)
            arr[j] = arr[j+1];
    }
    rear[s]=rear[s]-1;
    
    return n;
}


struct points {
    int coord_1;
    int coord_2;
    double weight;
};
struct neighbours {
    int neigh[r-1];
};
struct mst{
    struct points p[r-1];
};

struct points edges[pos];
struct neighbours neighbour[r];
struct mst mt;

void equate(struct points *p1, struct points *p2)
{
    *p2 = *p1;
}

int bfs_mst(struct neighbours n[], int coord_1, int coord_2)
{
    if(head[coord_1]!=-1)
    {int temp = coord_1;
        int dist[r];
        for (int i = 0 ; i<r;i++)
        {
            dist[i]=989;
        }
        int v=0;
        enqueue(temp,queue_bfs,r);
        while(head[r]<=rear[r] && head[r]!=-1)
        {
            
            v = dequeue(queue_bfs,r);
            int i = 0;
            int j;
            int temp_1[500];
            int l =0;
            while(l<=rear[v])
            {
                enqueue(n[v].neigh[l],temp_1,r+1);
                l++;
            }
            
            while(i<l)
            {
                j = dequeue(temp_1,r+1);
                dist[v]=v;
                if(dist[j]!=j)
                {enqueue(j,queue_bfs,r);
                    temp = j;}
                i++;
            }
            
        }
        if (dist[coord_2]==989)
        {
            return 0;
        }
        else
        {
            
            return 1;}}
    else
        return 0;
    
    
}
struct mst form_mst(struct points p1[],struct neighbours n[], struct mst m)
{
    int k = r-2;
    for (int i = 0 ; i<pos;i++)
    {
        
        if(k<0)
        {
            break;
        }
        else
        {if (i == 0 || i ==1)
        {
            enqueue(p1[i].coord_2,n[p1[i].coord_1].neigh,p1[i].coord_1);
            enqueue(p1[i].coord_1,n[p1[i].coord_2].neigh,p1[i].coord_2);
//            m.p[k].coord_1= p1[i].coord_1;
//            m.p[k].coord_2= p1[i].coord_2;
//            m.p[k].weight= p1[i].weight;
            equate(&p1[i], &m.p[k]);
            k--;
        }
        else
        {
            if(bfs_mst(n,p1[i].coord_1,p1[i].coord_2)==0)
            {
                enqueue(p1[i].coord_2,n[p1[i].coord_1].neigh,p1[i].coord_1);
                enqueue(p1[i].coord_1,n[p1[i].coord_2].neigh,p1[i].coord_2);
//                m.p[k].coord_1= p1[i].coord_1;
//                m.p[k].coord_2= p1[i].coord_2;
//                m.p[k].weight= p1[i].weight;
                equate(&p1[i], &m.p[k]);
                k--;
            }
            
        }
        }
        return m;
    }
    
    for (int i = 0 ; i <r-1;i++)
    {
        {
            cout<<m.p[i].coord_1<<"-"<<m.p[i].coord_2<<endl;
        }
    }
    
    
}

void swap (struct points *p1, struct points *p2)
{
    struct points temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

double euclid (node node1, node node2) {
    int temp_x;
    int temp_y;
    double dist;
    temp_x = pow(abs(node1.x - node2.x), 2);
    temp_y = pow(abs(node1.y - node2.y), 2);
    dist = sqrt(temp_x + temp_y);
    return dist;
}


int edges_calculator (int vertices) {
    int temp;
    temp = vertices*(vertices - 1) / 2;
    return temp;
}

void clustering_1(mst m,neighbours n[],int k)
{
    int j =0;
    int a_temp_coord_1[k];
    int a_temp_coord_2[k];
    while(k>0)
    {
        a_temp_coord_1[j]=m.p[j].coord_1;
        a_temp_coord_2[j]=m.p[j].coord_2;
        
        delete_element(n[a_temp_coord_1[j]].neigh,rear[a_temp_coord_1[j]],a_temp_coord_2[j],a_temp_coord_1[j]);
        delete_element(n[a_temp_coord_2[j]].neigh,rear[a_temp_coord_2[j]],a_temp_coord_1[j],a_temp_coord_2[j]);
        if(rear[a_temp_coord_1[j]]==-1)
        {
            enqueue(a_temp_coord_1[j],n[a_temp_coord_1[j]].neigh,a_temp_coord_1[j]);
        }
        if(rear[a_temp_coord_2[j]]==-1)
        {
            enqueue(a_temp_coord_2[j],n[a_temp_coord_2[j]].neigh,a_temp_coord_2[j]);
        }
        k--;
        j++;
    }
    int j_1 = j;
    int j_2 =j;
    for (int i =0; i<j_1;i++)
    {
        for (int k = i+1;k<j_1;k++)
        {
            if(a_temp_coord_1[i]==a_temp_coord_1[k])
            {
                for(int f=k;f<j_1;f++)
                {
                    a_temp_coord_1[f]=a_temp_coord_1[f+1];
                }
                j_1--;
            }
        }
    }
    for (int i =0; i<j_2;i++)
    {
        for (int k = i+1;k<j_2;k++)
        {
            if(a_temp_coord_2[i]==a_temp_coord_2[k])
            {
                for(int f=k;f<j_2;f++)
                {
                    a_temp_coord_2[f]=a_temp_coord_2[f+1];
                }
                j_2--;
            }
        }
    }
    for (int i =0; i<j_1;i++)
    {
        for(int k=0; k<j_2;k++)
        {
            if(a_temp_coord_1[i]==a_temp_coord_2[k])
            {
                for(int f=k;f<j_2;f++)
                {
                    a_temp_coord_2[f]=a_temp_coord_2[f+1];
                }
                j_2--;
            }
        }
    }
    
    for (int h = 0 ; h<j_1;h++)
    {for (int i =0; i<r;i++)
    {
        //        %d\n",a_temp_coord_1[h],i,bfs(n,a_temp_coord_1[h],i));
        if(bfs_mst(n,a_temp_coord_1[h],i)==1)
        {
            printf("cluster %d  is: %d\n",h+1,i);
        }
    }
    }
    for (int h = 0 ; h<2;h++)
    {for (int i =0; i<r;i++)
    {
        if(bfs_mst(n,a_temp_coord_2[h],i)==1)
        {
            printf("cluster %d  is: %d\n",h+j_1+1,i);
        }
    }
    }
}



int main() {
    
    struct mst temp;
    srand(time(0));
    int num_ver = 15;
    cout<<num_ver<<endl;
    
    node nodes[num_ver];
    for(int i=0;i<num_ver;i++)
    {
        if (i < 5) {
            nodes[i].x=rand()%20;
            nodes[i].y=rand()%20;
        }
        
        else if ((i>= 5) && (i < 10)) {
            nodes[i].x=(30+rand()%20);
            nodes[i].y=(30+rand()%20);
        }
        
        else {
            nodes[i].x=(60+rand()%20);
            nodes[i].y=(60+rand()%20);
        }
        
    }
    int num_edges = edges_calculator(num_ver);
    
    int no_edges = 0;
    for (int i = 0; i < num_ver; i++) {
        for (int j = i+1; j < num_ver; j++) {
            edges[no_edges].coord_1 = i;
            edges[no_edges].coord_2 = j;
            edges[no_edges].weight = euclid(nodes[i], nodes[j]);
            no_edges++;
        }
    }
    
    for (int i = 0; i < no_edges; i++) {
        for (int j = i-1; j >= 0; j--) {
            if (edges[j].weight >= edges[j+1].weight) {
                swap(&edges[j], &edges[j+1]);
            }
        }
    }
    for (int i = 0 ; i<num_ver;i++)
    {
        printf("coord[%d] = (%d, %d)\n", i, nodes[i].x,nodes[i].y);
    }
    
    for (int i = 0; i < no_edges; i++) {
        printf("Edge[%d] - %d - %d - %.2lf\n",
               i, edges[i].coord_1,
               edges[i].coord_2, edges[i].weight);
    }
    
    cout<<endl;
    temp = form_mst(edges,neighbour,mt);
    clustering_1(temp,neighbour,2);
    return 0;
}
