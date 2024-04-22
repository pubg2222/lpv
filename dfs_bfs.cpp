#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <queue>

using namespace std;
double start,stop,start_p,stop_p;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void printArray(vector<int> ans){
	for(int i=0; i<ans.size(); i++){
		cout<< ans[i] << " ";
	}
}

vector<int> dfs(int node) {
	start_p=omp_get_wtime();
	stack<int> s;
	vector<int> ans;
	s.push(node);

	while (!s.empty()) {
		int curr_node;
		#pragma omp critical
		{
			curr_node = s.top();
			s.pop();
		}

		if (!visited[curr_node]) {
			#pragma omp critical
			{
				visited[curr_node] = true;
			}
			#pragma omp critical
			{
				ans.push_back(curr_node);
			}

			for (int i = 0; i < graph[curr_node].size(); i++) {
				int adj_node = graph[curr_node][i];
				if (!visited[adj_node]) {
					#pragma omp critical
					{
						s.push(adj_node);
					}
				}
			}
		}
	}
	stop_p= omp_get_wtime();
	return ans;
}

vector<int> dfsSeq(int node) {
	start=omp_get_wtime();
	vector<int> ans;
	stack<int> s;
	s.push(node);

	while (!s.empty()) {
	    	int curr_node = s.top();
	    	s.pop();

	    	if (!visited[curr_node]) {
			visited[curr_node] = true;
			
			if (visited[curr_node]) {
				ans.push_back(curr_node);
		    	}
			for (int i = 0; i < graph[curr_node].size(); i++) {
			    	int adj_node = graph[curr_node][i];
			    	if (!visited[adj_node]) {
					s.push(adj_node);
			    	}
			}
	    	}
	}
	stop= omp_get_wtime();
	return ans;
}

vector<int> bfsSeq(int node) {
	start=omp_get_wtime();
	vector<int> ans;
	queue<int> q;
	q.push(node);
	visited[node] = true;
	while (!q.empty()) {
	    	int size = q.size();
	    	for(int i=0; i<size; i++){
	    		int front = q.front();
	    		q.pop();
	    		ans.push_back(front);
	    		for(int a : graph[front]){
	    			if(!visited[a]){
	    				
	    				visited[a] = true;
	    				q.push(a);
	    			}
	    		}
	    	}
	}
	stop= omp_get_wtime();
	return ans;
}

vector<int> bfs(int node){
	start_p = omp_get_wtime();
	queue<int> q;
	vector<int> ans;
	q.push(node);
	visited[node] = true;
	while (!q.empty()) {
		int size = q.size();
		#pragma omp for
		for (int i = 0; i < size; ++i) {
			int front = q.front();
			q.pop();
			ans.push_back(front);  // Process current vertex
			// Enqueue adjacent unvisited vertices
			for (int a : graph[front]) {
				if (!visited[a]) {
					visited[a] = true;
					q.push(a);
				}
			}
		}
	}
	stop_p = omp_get_wtime();
	return ans;
}

int main() {
	int n, m, start_node;
	cout << "Enter No of Node,Edges,and start node:" ;
	cin >> n >> m >> start_node;
         //n: node,m:edges
         
	cout << "Enter Pair of edges:" ;
	for (int i = 0; i < m; i++) {
    		int u, v;
    		cin >> u >> v;
		//u and v: Pair of edges
    		graph[u].push_back(v);
    		graph[v].push_back(u);
	}

	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
    		visited[i] = false;
	}
	cout<<"\nDFS \ntraversal (Sequential) : ";
	vector<int> ans = dfsSeq(start_node);
	printArray(ans);
	cout << "\nTime (Sequential)  = " << stop-start;
	
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
    		visited[i] = false;
	}
	cout<<"\ntraversal (parallel) : ";
    	ans = dfs(start_node);
    	printArray(ans);
    	cout << "\nTime (Parallel)  = " << stop_p-start_p;
	
	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
    		visited[i] = false;
	}
    	cout<<"\nBFS \ntraversal (Sequential) : ";
	ans = bfsSeq(start_node);
	printArray(ans);
	cout << "\nTime (Sequential)  = " << stop-start;
	

	#pragma omp parallel for
	for (int i = 0; i < n; i++) {
    		visited[i] = false;
	}
	cout<<"\ntraversal (parallel) : ";
    	ans = bfs(start_node);
    	printArray(ans);
    	cout << "\nTime (Parallel)  = " << stop_p-start_p<<"\n";
	return 0;
}




