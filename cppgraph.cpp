#include <bits/stdc++.h>
using namespace std;
  
// A structure to represent a node in adjacency list 
struct AdjListNode { 
    int pid;
    string fname;
    string lname;
    char gen;
    struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList { 
    struct AdjListNode* head; // pointer to head node of list 
}; 
  
// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
struct Graph { 
    int V; 
    struct AdjList* array; 
}; 
 
// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int persid,string fn,string ln,char g) 
{ 
    struct AdjListNode* newNode = new struct AdjListNode; 
    newNode->pid=persid; 
    newNode->fname=fn;
    newNode->lname=ln;
	newNode->gen=g; 
    newNode->next = NULL; 
    return newNode; 
} 
  
// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
    int i;
    struct Graph* graph = new struct Graph;
    graph->V = V; 
  
    // Create an array of adjacency lists.  Size of array will be V 
    graph->array =new struct AdjList;  
    // Initialize each adjacency list as empty by making head as NULL 
    for (i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
}

// Adds an edge to an undirected graph 
void addEdge(struct Graph* g,struct AdjListNode *src,struct AdjListNode *dest) 
{ 
    AdjListNode *t1,*t2;
    t1=new struct AdjListNode;
    t2=new struct AdjListNode;
    t1->pid=src->pid;
    t1->fname=src->fname;
    t1->lname=src->lname;
    t1->gen=src->gen;
    t2->pid=dest->pid;
    t2->fname=dest->fname;
    t2->lname=dest->lname;
    t2->gen=dest->gen;
    // Add an edge from src to dest.  A new node is added to the adjacency 
    // list of src.  The node is added at the begining  
    t2->next = g->array[t1->pid].head; 
    g->array[t1->pid].head =t2; 
    // Since graph is undirected, add an edge from dest to src also  
    t1->next = g->array[t2->pid].head; 
    g->array[t2->pid].head =t1; 
}



//prints the graph
void printgraph(struct Graph *g)
{
	int i;
	int p=g->V;
	for (i = 0; i <p; i++)
	{
		cout<<"\nAdjacency List of vertex "<<i<<endl;
		struct AdjListNode *t;
		t=g->array[i].head;
		while(t!=NULL)
		{
		    cout<<"Pesrson Id:";
			cout<<t->pid<<endl;
			cout<<"Name-";
			cout<<t->fname;
			cout<<" ";
			cout<<t->lname;
			cout<<"\nGender-"<<t->gen<<endl;
			cout<<endl;
			t=t->next;
		}
		cout<<"\n";
	}    
}



//A function to show Friend List
void showfriend(struct Graph *g,int tempId)
{
		struct AdjListNode *t;
		t=g->array[tempId].head;
		while(t!=NULL)
		{
		    cout<<"Pesrson Id:";
			cout<<t->pid<<endl;
			cout<<"Name-";
			cout<<t->fname;
			cout<<" ";
			cout<<t->lname;
			cout<<"\nGender-"<<t->gen<<endl;
			cout<<endl;
			t=t->next;
		}
		cout<<"\n";   
}

//A function to add a node to blocking list
void addtobl(struct Graph *bg,struct AdjListNode *an,int tId)
{
	AdjListNode *t1;
    t1=new struct AdjListNode;
    t1->pid=an->pid;
    t1->fname=an->fname;
    t1->lname=an->lname;
    t1->gen=an->gen;  
    // add the node to the list
    t1->next = bg->array[tId].head; 
    bg->array[tId].head =t1;
}

//A function to remove single node
void remsn(struct Graph *eg,int tempId,int btempId)
{
	struct AdjListNode *t,*t1;
	t=eg->array[tempId].head;
	t1=t;
	if(t->pid==btempId)
	{
		if(t->next==NULL)
		{
		eg->array[tempId].head=NULL;
		delete t;
		return;
	    }
		else
		{
			eg->array[tempId].head=t->next;
			t->next=NULL;
			delete t;
			return;
		}	
	}
	int x=0;
	while(t->pid!=btempId)
	{
		if(x>0)
		t1=t1->next;
		t=t->next;
		x=x+1;	
	}
	if(t->next==NULL)
	{
		t1->next=NULL;
		delete t;
		return;
	}
	else
	{
		t1->next=t->next;
		t->next=NULL;
		delete t;
		return;
	}
	
}

//A function to show friend suggestions
void showfm(struct Graph *eg,int tempId)
{
	int p=eg->V;
//	list <int> vis;
//	for(int i=0;i<p;i++)
//		vis.push_back(0);
   int vis[p];
	for(int i=0;i<p;i++)
	vis[i]=0;
//	cout<<"visited print\n";
//	int sz=vis.size();
//	for(int i=0;i<p;i++)
//	cout<<vis[i]<<" ";
//	cout<<endl;
	
	
	struct AdjListNode *fm;
	fm=new struct AdjListNode;
	fm=NULL;
	
	
	struct AdjListNode *t;
	t=eg->array[tempId].head;
	vis[tempId]++;
	
	
//	vector <int> f1;
    int f1[p];
    int k=0;
	while(t!=NULL)
	{
		//f1.push_back(t->pid);
		f1[k++]=t->pid;
		vis[t->pid]++;
		t=t->next;
	}	
//	int len = f1.size();
//	cout<<"visited print\n";
//	for(int i=0;i<p;i++)
//	cout<<vis[i]<<" ";
//	cout<<endl;
	
//	cout<<"f1 print\n";
//	for(int i=0;i<k;i++)
//	cout<<f1[i]<<" ";
//	cout<<endl;
	
	
	for(int i=0;i<k;i++)
	{
		t=eg->array[f1[i]].head;
		while(t!=NULL)
		{
			if(vis[t->pid]==0)
			{
			   struct AdjListNode *nw;
			   nw=newAdjListNode(t->pid,t->fname,t->lname,t->gen);
			   nw->next=fm;
			   fm=nw;
			   vis[t->pid]++;
			  // cout<<"fm->pid"<<fm->pid;
			}
			t=t->next;
		}
	}
	t = fm;
	while(t!=NULL)
	{
		    cout<<"Pesrson Id:";
			cout<<t->pid<<endl;
			cout<<"Name-";
			cout<<t->fname;
			cout<<" ";
			cout<<t->lname;
			cout<<"\nGender-"<<t->gen<<endl;
			cout<<endl;
			t=t->next;
	}	
}


//A function to show User profile
void showuser(AdjListNode *t)
{
	cout<<"\nYour Profile:\n";
	cout<<"Pesrson Id:";
	cout<<t->pid<<endl;
	cout<<"Name-";
	cout<<t->fname;
	cout<<" ";
	cout<<t->lname;
	cout<<"\nGender-"<<t->gen<<endl;
	cout<<endl;
}


int main()
{
	struct Graph *g,*bg;
	int nv;
	cout<<"Enter no. of vertices:";
	cin>>nv;
	g=createGraph(nv);
	cout<<"Graph Created\n";
	cout<<"Enter details of all vertices:\n";
	struct AdjListNode *v[nv];
	for(int i=0;i<nv;i++)
	{
		string fn,ln;
		char g;
		cout<<i<<"th vertex\n";
		cout<<"Enter name:";
		cin>>fn>>ln;
		cout<<"Specify Gender(Male-M or Female-F):";
		cin>>g;	
		v[i]=newAdjListNode(i,fn,ln,g); 
	}
	int en;
	cout<<"Enter no of edges:";
	cin>>en;
	cout<<"Provide Edge configuration:(for V[i]<-->v[j] specify i and j)\n";
	for(int i=0;i<en;i++)
	{
		int s,d;
		cin>>s>>d;
	    addEdge(g,v[s],v[d]);
    }
    
    bg=createGraph(nv);
    int tempId,btempId;
    while(1)
    {
     cout<<"\nSelect Your choice-\n";
     cout<<"\n1.Show the Full Graph(Adjacency List Representation).";
     cout<<"\n2.Show Friend List.";
     cout<<"\n3.Show Friend List and suggested Friends(Acc. to Mutual Friends.)";
     cout<<"\n4.Block/Remove a Person.";
     cout<<"\n5.Block/Remove a Group.";
	 cout<<"\n6.Unblock a Person.";
	 cout<<"\n7.See Blocked/Removed List.";
	 cout<<"\n8.Exit the program.";
	 cout<<endl;
	 cout<<"Enter Your choice:";
	 int c;
	 cin>>c; 
	 switch(c)
	 {
	 	case 1:
	 		printgraph(g);
	 		break;
	 	case 2:
	 		cout<<"Enter Your Id:";
	 		cin>>tempId;
	 		showuser(v[tempId]);
	 		cout<<"--------------------------------------------------------";
	 		cout<<"\nYour Friend List- "<<endl;
	 		showfriend(g,tempId);
	 		break;
	 	case 3:
	 		cout<<"Enter Your Id:";
	 		cin>>tempId;
	 		showuser(v[tempId]);
	 		cout<<"--------------------------------------------------------";
	 		cout<<"\nsuggested friends\n";
	 		cout<<"________________________\n";
	 		showfm(g,tempId);
	 		break;
	 	case 4:
	 		cout<<"Enter Your Id:";
	 		cin>>tempId;
	 		showuser(v[tempId]);
	 		cout<<"--------------------------------------------------------";
	 		cout<<"\nYour Friend List- "<<endl;
	 		showfriend(g,tempId);
	 		cout<<"________________________________";
	 		cout<<"\nEnter personId to Remove/block:";
	 		cin>>btempId;
	 		remsn(g,tempId,btempId);
	 		addtobl(bg,v[btempId],tempId);
	 		cout<<"\nYour Blocked/removed person list:\n";
	 		showfriend(bg,tempId);
	 		break;
	 	case 5:
	 		break;
	 	case 6:
	 		cout<<"Enter Your Id:";
	 		cin>>tempId;
	 		cout<<"\nYour Blocked/removed person list:\n";
	 		showfriend(bg,tempId);
	 		cout<<"Enter personId to Unblock:";
	 		cin>>btempId;
	 		addtobl(g,v[btempId],tempId);
	 		remsn(bg,tempId,btempId);
	 		cout<<"sucessfully unblocked.";
	 		break;
	 	case 7:
	 		cout<<"Enter Your Id:";
	 		cin>>tempId;
	 		showuser(v[tempId]);
	 		cout<<"--------------------------------------------------------";
	 		cout<<"\nYour Blocked/removed person list:\n";
	 		showfriend(bg,tempId);
	 		break;
	 	case 8:
	 		exit(0);
	 	default:
	 		cout<<"Choose Correct.";
	 		//break;
	 }
   }	  
	return 0;
}
