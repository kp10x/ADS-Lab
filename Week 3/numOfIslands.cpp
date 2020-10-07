#include<bits/stdc++.h>
using namespace std;
class Union{
	vector<int> parent;
	public:
	int count;
	Union(int n){
		for(int i=0; i<n; i++){
			parent.push_back(i);
		}
		count = 0;
	}
	int find(int x){
		if(parent[x] == x)
			return x;
		return parent[x] = find(parent[x]);
	}
	void connect(int x, int y){
		int rootx = find(x);
		int rooty = find(y);
		if(rootx != rooty){
			parent[rootx] = rooty;
			count--;
		}
		
	}
	void setCount(int n){
		count = n;
	}

};

int numIslands(vector<vector<int>> arr)
{
	int count = 0;
	int m = arr.size();
	int n = arr[0].size();
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(arr[i][j])
				count++;
		}
	}
	Union *u = new Union(m*n);
	u->setCount(count);
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(arr[i][j]){
				if(i>0 && arr[i-1][j]){
					u->connect(n*i+j, n*(i-1)+j);
				}
				if(i<m-1 && arr[i+1][j]){
					u->connect(n*i+j, n*(i+1)+j);
				}
				if(j>0 && arr[i][j-1]){
					u->connect(n*i+j, n*i+j-1);
				}
				if(j<n-1 && arr[i][j+1]){
					u->connect(n*i+j, n*i+j+1);
				}
				if(i>0 && j>0 && arr[i-1][j-1]){
					u->connect(n*i+j, n*(i-1)+j-1);
				}
				if(i<m-1 && j<n-1 && arr[i+1][j+1]){
					u->connect(n*i+j, n*(i+1)+j+1);
				}
				if(i>0 && j<n-1 && arr[i-1][j+1]){
					u->connect(n*i+j, n*(i-1)+j+1);
				}
				if(i<m-1 && j>0 && arr[i+1][j-1]){
					u->connect(n*i+j, n*(i+1)+j-1);
				}
			}
				
		}
	}
	return u->count;
}

int main(){
	vector<vector<int>>arr;
	int m,n,val;
	cout<<"Enter the no. of rows: ";
	cin>>m;
	cout<<"Enter the no. of columns: ";
	cin>>n;
	cout<<"Enter the boolean matrix"<<endl;
	for(int i=0;i<m; i++){
		vector<int> row;
		for(int j=0; j<n; j++){
			cin>>val;
			row.push_back(val);
		}
		arr.push_back(row);
	}

	cout<<"Number of Islands: "<< numIslands(arr)<<endl;
	return 0;

}