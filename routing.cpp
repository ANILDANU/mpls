//Ide-dev=C++ 5.11   both windows command prompt and linux terminal can be used. please read readme file


#include<bits/stdc++.h>
using namespace std;
int V=24;
int parent[100],par[100],flag,label[100]; 

struct connection{     //this structur represents the each entry in the connection file
	int source,destination,path_cost;
	list<int> label_list;
};

struct fd{  //this structure represents the each entry in the forwarding table
	int interface_in,label_in,interface_out,label_out,cid;
};

map<int,list<fd> > f_table;  //this is used for storing the forwarding table entry where key is router no

map<int,connection> c_table;  //this variable will store the imformation regarding each established connection where key is the connection id

int forwording(int node,int iface_in,int l_in,int iface_out,int id)// this function is used to create forwarding table for each router
{
	fd entry;
	label[node]++;
	entry.interface_in=iface_in;
	entry.label_in=l_in;
	if(node==iface_out)
	entry.interface_out=-1;
	else
	entry.interface_out=iface_out;
	if(label[node]==l_in)
	label[node]++;
	if(node==iface_out)
	entry.label_out=-1;
	else
	entry.label_out=label[node];
	entry.cid=id;
	f_table[node].push_back(entry);
	
	return label[node];
}


//below function are for dijkstra algorithm
int minDistance(int dist[],  
                bool sptSet[]) 
{ 
      
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && 
                   dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
// Function to print shortest path from source to j using parent array 

void printPath(int parent[], int j,ofstream &fout) 
{ 
      
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  
    printPath(parent, parent[j],fout); 
    fout<<j<<" ";
   // printf("%d ", j); 
} 
  
// A utility function to print the constructed distance array 

void printSolution(int dist[], int n,  
                      int parent[],int src) 
{ 
    ofstream fout,f;
    fout.open("shortest_path1.txt",ios::app);
    f.open("shortest_path2.txt",ios::app);
   //printf("Vertex\t Distance\tPath"); 
    for (int i = 0; i < V; i++) 
    { 
    	if(i!=src){
        	if(flag==-1){
                    //printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); 
                    fout<<src<<" "<<i<<" "<<dist[i]<<" "<<src<<" ";
       				printPath(parent, i,fout); 
        			fout<<"\n";
   			}
    		else
   			{
    			if(i==flag){
    				if(dist[i]<0|| dist[i]==INT_MAX)
    				break;
    				//printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); 
					f<<src<<" "<<i<<" "<<dist[i]<<" "<<src<<" ";	
					printPath(parent, i,f); 
        			f<<"\n";
    			}
			}
    	}
    } 
    fout.close();
} 
  
// Funtion that implements Dijkstra's single source shortest path 
// algorithm for a graph represented using adjacency matrix representation 
void dijkstra(int graph[100][100], int src) 
{ 
      
    // The output array. dist[i] 
    // will hold the shortest 
    // distance from src to i 
    int dist[V];  
  
    // sptSet[i] will true if vertex 
    // i is included / in shortest 
    // path tree or shortest distance  
    // from src to i is finalized 
    bool sptSet[V]; 
  
    // Parent array to store 
    // shortest path tree 
    
  
    // Initialize all distances as  
    // INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
    { 
        parent[src] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
  
    // Distance of source vertex  
    // from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path 
    // for all vertices 
    for (int count = 0; count < V - 1; count++) 
    { 
        // Pick the minimum distance 
        // vertex from the set of 
        // vertices not yet processed.  
        // u is always equal to src 
        // in first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex  
        // as processed 
        sptSet[u] = true; 
  
        // Update dist value of the  
        // adjacent vertices of the 
        // picked vertex. 
        for (int v = 0; v < V; v++) 
  
            // Update dist[v] only if is 
            // not in sptSet, there is 
            // an edge from u to v, and  
            // total weight of path from 
            // src to v through u is smaller 
            // than current value of 
            // dist[v] 
            if (!sptSet[v] && graph[u][v]!=-1 && dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    } 
  
    // print the constructed 
    // distance array 
    printSolution(dist, V, parent,src); 
} 


int main(int argc,char *argv[])
{
	
	ifstream f;
	ofstream ofs;
	ofs.open("shortest_path1.txt", std::ofstream::out | std::ofstream::trunc); //empty the file shortest path 1
	ofs.close();
	ofs.open("shortest_path2.txt", std::ofstream::out | std::ofstream::trunc);  // empty the file shortest path 2
	ofs.close();
	double link_bandwidth[V][V]={0},cost_path1[V][V],cost_path2[V][V],used_path[V][V];
	int approach=1;
	if(argc==1)
	return 0;
	
	//reading the command line argument
	char topology_filename[50],connection_filename[50],forwarding_table_file[50],routing_table[50],path_filename[50],distance_metric[50];
	strcpy(topology_filename,argv[2]);
	strcpy(connection_filename,argv[4]);
	strcpy(routing_table,argv[6]);
	strcpy(forwarding_table_file,argv[8]);
	strcpy(path_filename,argv[10]);
	strcpy(distance_metric,argv[12]);
	approach=atoi(argv[14]);

	

	f.open(topology_filename);  //open topology file
	if(f.fail())
	{
		cout<<"error";
		return 0;
	}
	
	int n,m;
	f>>n>>m;   // n is for no of nodes m is no of edges
	V=n;
	int a[100][100],b[100][100];  // a and b will store the true graph information
	
	for(int i=0;i<n;i++)  //initializing various arrays
	{
		label[i]=100;
		for(int j=0;j<n;j++){
			a[i][j]=-1;
			b[i][j]=-1;
			used_path[i][j]=0;
			link_bandwidth[i][j]=0;
		}
	}
	
	while(!f.eof())
	{
		int i,j,c,d;
		f>>i>>j>>c>>d;
		if(strlen(distance_metric)==3)   //if distance metric is hop then initialize a and b with 1 for each source and destination given in the file 
		{								//else initiallize with the cost given in the file
			a[i][j]=1;	
			a[j][i]=1;
			b[i][j]=1;
			b[j][i]=1;
		}
		else
		{
			a[i][j]=c;	
			a[j][i]=c;
			b[i][j]=c;
			b[j][i]=c;
		}
		link_bandwidth[i][j]=d;
		link_bandwidth[j][i]=d;
	} 
	
	for(int i=0;i<V;i++)   //find first shortest path for each vertex
	{
		flag=-1;
		dijkstra(a,i);
		for(int k=0;k<V;k++)   //store the actual parent
		{
			par[k]=parent[k];
		}
		for(int l=0;l<V;l++)  //find second shortest path one by one 
		{
			if(i==l)
			l++;
			if(l==V)
			break;
			for(int node=0;node<V;node++)    //retreive the actual parent and graph information
			{
				parent[node]=par[node];
				for(int k=0;k<V;k++)
					b[node][k]=a[node][k];
			}
			
			int j=l;
			while(parent[j]!=-1)    //remove path one by one 
			{
				b[j][parent[j]]=-1;
				b[parent[j]][j]=-1;
				j=parent[j];
			}
			flag=l;
			dijkstra(b,i);
		}
	}
	f.close();
	
	map<int ,map<int,list<int> > > path1,path2;
	f.open("shortest_path1.txt");
	string line;
	while(getline(f,line))
	{
		int src=-1,des=-1,cost=-1,key=-1;
		//cout<<line<<" \n"<<line.length()<<endl;
		stringstream check1(line);
		string s;
		while(getline(check1,s,' '))
		{
			stringstream str(s);
			if(src==-1)
			{
				str>>src;
				continue;
			}
			if(des==-1)
			{
				str>>des;
				continue;
			}
			if(cost==-1)
			{
				str>>cost;
				cost_path1[src][des]=cost;
				continue;
			}
			str>>key;
			path1[src][des].push_back(key);
		}
	}
	f.close();
		
	f.open("shortest_path2.txt");
	while(getline(f,line))
	{
		int src=-1,des=-1,cost=-1,key=-1;
		
		stringstream check1(line);
		string s;
		while(getline(check1,s,' '))
		{
			stringstream str(s);
			if(src==-1)
			{
				str>>src;
				continue;
			}
			if(des==-1)
			{
				str>>des;
				continue;
			}
			if(cost==-1)
			{
				str>>cost;
				cost_path2[src][des]=cost;
				continue;
			}
			str>>key;
			path2[src][des].push_back(key);
		}
	}
	f.close();
	
	//path calculated and stored in path1 and path2 variable 
	//create routing table file routingfile.txt
	ofstream fout;
	fout.open(routing_table);
	fout<<"Source\t"<<"Destination\t"<<"Cost \t"<<"Path\n";
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
		{
			if(i==j)
			continue;
			if(path1.find(i)!=path1.end())
			{
			fout<<i<<" \t"<<j<<" \t\t"<<cost_path1[i][j]<<" \t";
			list<int> :: iterator it;
			for(it=path1[i][j].begin();it!=path1[i][j].end();it++)
			{
				fout<<*it<<" ";
			}
			fout<<"\n";
			}
			if(path2[i].find(j)!=path2[i].end())
			{
				list<int> :: iterator it;
			fout<<i<<" \t"<<j<<" \t\t"<<cost_path2[i][j]<<" \t";
			for(it=path2[i][j].begin();it!=path2[i][j].end();it++)
			{
				fout<<*it<<" ";
			}
			fout<<"\n";
			}
		}
	}
	fout.close();
	
	
	//routing file created
	//now check connection file and create forwarding table and connectiopn table for each established connection 
	
	f.open(connection_filename);
	int total_connection;
	f>>total_connection;
	int src,des,count=0,c_id=0;
	double beq,b_min,b_av,b_max;
	while(!f.eof())
	{
		c_id++;
		f>>src>>des>>b_min>>b_av>>b_max;
		list<int> l_list;
		l_list.clear();
		if(approach)   //this is for optimistic and pessimistic connection
		{
			beq=b_max;
		}
		else
		{
			beq=b_av+0.25*(b_max-b_min);
			beq=min(b_max,beq);
		}
		list <int> :: iterator it; 
		bool check_path1=true,check_path2=true;
		it=path1[src][des].begin();
		it++;
		int src1=src,des1=des,pre_src=-1,label=-1;
		for(int len=0;len<path1[src][des].size();len++)
		{
			
			des1=*it;
			if(src1==des)
				break;
			if(link_bandwidth[src1][des1]<beq)  //checking whether the connection can be established or not
			{
				
				check_path1=false;
				break;
			}
			src1=des1;
			it++;
			
		}
		if(check_path1)  //if this is true than connection can be established along the path1
		{
			used_path[src][des]=1;
			src1=src;
			it=path1[src][des].begin();
			it++;
			for(int len=0;len<path1[src][des].size();len++)
			{
				des1=*it;
				if(src1==des)
				{
					label=forwording(src1,pre_src,label,src1,c_id);    //connection can be established so create the forwarding table entry at every router
					break;	
				}
				else
				{
					label=forwording(src1,pre_src,label,des1,c_id);
				}
				l_list.push_back(label);
				link_bandwidth[src1][des1]-=beq;  // decrease the bandwidth of every used link
				link_bandwidth[des1][src1]-=beq;
				pre_src=src1;
				src1=des1;
				it++;
			}
		}
		else  // if connection can not be established along first path then check the second path
		{
			list <int> :: iterator it;
			it=path2[src][des].begin();
			it++;
			int src1=src,des1=des,pre_src=-1,label=-1;
			for(int len=0;len<path2[src][des].size();len++)
			{
				if(path2[src].find(des)==path2[src].end())
				{
					check_path2=false;
					break;
				}
				des1=*it;
				if(src1==des)
				break;	
				if(link_bandwidth[src1][des1]<beq)
				{
				
					check_path2=false;
					break;
				}
				src1=des1;
				it++;
			}
			if(check_path2)  // if this is true it means connection can be established along the second path 
			{
				used_path[src][des]=2;
				src1=src;
				it=path2[src][des].begin();
				it++;
				for(int len=0;len<path2[src][des].size();len++)
				{
					des1=*it;
					if(src1==des)
					{
						label=forwording(src1,pre_src,label,src1,c_id);  //create entry in the forwarding table 
						break;	
					}
					else
					{
						label=forwording(src1,pre_src,label,des1,c_id);
					}
					l_list.push_back(label);    
					link_bandwidth[src1][des1]-=beq;     //decrease the bandwidth of the used link
					link_bandwidth[des1][src1]-=beq;
					pre_src=src1;
					src1=des1;
					it++;
				}
			}
		}
		if(check_path1||check_path2)   //if connection can be established along any of the path then store the entry in the connection variable
		{
			count++;
			c_table[c_id].source=src;
			c_table[c_id].destination=des;
			c_table[c_id].path_cost=0;
			c_table[c_id].label_list=l_list;
			
		}
	}
	f.close();
	
	fout.open(path_filename);
	fout<<"Total Connection : "<<total_connection<<" Admitted Connection : "<<count<<"\n"; //store the admitted connection information in the pathfile
	fout.close();
	cout<<endl<<"total connection:"<<total_connection<<" Admitted connection: "<<count<<endl;
	
	
	//write entries from forwarding variable to forwarding file
	fout.open(forwarding_table_file);
	fout<<"Router NO\t"<<"Connection_Id\t"<<"Interface_IN\t"<<"Label_In\t"<<"Interface_Out\t"<<"Label_Out\n";
	for(int i=0;i<V;i++)
	{
		list <fd> :: iterator it;
		for(it=f_table[i].begin();it!=f_table[i].end();it++)
		{
			fout<<i<<" \t \t"<<it->cid<<"\t\t"<<it->interface_in<<"\t\t "<<it->label_in<<"\t\t"<<it->interface_out<<"\t\t"<<it->label_out<<" \n";
		}
	}
	fout.close();
	
	//write the entries form the connection variable to connection file
	fout.open("connection.txt");
	fout<<"Connection_Id\t"<<"Source\t"<<"Destination\t"<<"path used\t"<<"path_cost\t"<<"Label_List\n";
	for(int i=1;i<=total_connection;i++)
	{
		if(c_table.find(i)!=c_table.end()){
			fout<<i<<"\t\t"<<c_table[i].source<<"\t"<<c_table[i].destination<<"\t\t";
			if(used_path[c_table[i].source][c_table[i].destination]==1)
			fout<<"1\t\t"<<cost_path1[c_table[i].source][c_table[i].destination]<<"\t\t";
			else
			fout<<"2\t\t"<<cost_path2[c_table[i].source][c_table[i].destination]<<"\t\t";
			list<int> :: iterator it;
			for(it=c_table[i].label_list.begin();it!=c_table[i].label_list.end();it++)
			{
				fout<<*it<<" ";
			}
			fout<<"\n";
		}
	}
	fout.close();
	
	return 0;
}
