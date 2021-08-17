#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj(1000,vector<int>()); 


void Explore(vector<bool> &Visited, vector<bool> &failed, vector<bool> &rootCause, int vertex){
    Visited[vertex] = true;
    bool flag = true;
    for(int i=0;i<adj[vertex].size();i++){
        if(!Visited[adj[vertex][i]])
            Explore(Visited,failed,rootCause,adj[vertex][i]);
        if(failed[adj[vertex][i]])
            flag=false;
    }
    if(flag && failed[vertex]){
        rootCause[vertex]=true;
    }
    else if(!flag){
        failed[vertex]=true;
    }
}

void DFS(vector<bool> &failed, vector<bool> &rootCause, int n){
    vector<bool> Visited(n,false);
    for(int i=0;i<n;i++){
        if(!Visited[i])
            Explore(Visited,failed,rootCause,i);
    }
}

vector<int> findRootCause(int n, vector<bool> alerts){
    vector<bool> rootCause(n,false); 
    DFS(alerts,rootCause,n);
    vector<int> res;
    for(int i=0;i<n;i++){
        if(rootCause[i])
            res.push_back(i);
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    unordered_map<string,int> Id;
    for(int i=0;i<n;i++){
        string service;
        cin>>service;
        Id[service]=i;
    }
    int d;
    cin>>d;
    for(int i=0;i<d;i++){
        string dependency;
        cin>>dependency;
        string service_1;
        string service_2="";
        for(auto ch:dependency){
            if(ch!=',')
                service_2+=ch;
            else{
                service_1=service_2;
                service_2="";
            }   
        }
        //cout<<service_1<<" "<<service_2<<endl;
        adj[Id[service_1]].push_back(Id[service_2]);
    }
    
    int alerts;
    cin>>alerts;
    vector<bool> triggeredAlert(n,false);
    for(int i=0;i<alerts;i++){
        int count;
        cin>>count;
        for(int j=0;j<count;j++){
            string str;
            cin>>str;
            triggeredAlert[Id[str]]=true;
            //cout<<str<<" ";
        }
        vector<int> res = findRootCause(n,triggeredAlert);
        cout<<res.size()<<" ";
        for(int i=0;i<res.size();i++){
            for (auto& it : Id){
                if(it.second == res[i]){
                    cout<<it.first<<' ';
                }
            }
        }
        cout<<endl;
    }
}