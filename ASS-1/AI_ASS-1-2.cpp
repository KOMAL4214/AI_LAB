#include<bits/stdc++.h>
using namespace std;
vector<string> bfs(unordered_map<string,vector<string>> &g){
    int n=g.size();
    vector<string> ans;
    unordered_map<string,bool> visited;
    queue<string> q;
    ans.reserve(n);
    string src="raj";
    visited[src]=true;
    q.push(src);
    while(!q.empty()){
        string s=q.front();
        q.pop();
        ans.emplace_back(s);
        for(auto v : g[s]){
            if(!visited[v]){
                q.push(v);
                visited[v]=true;
            }
        }
    } 
    return ans;
}

void dfs1(unordered_map<string,vector<string>> &g,unordered_map<string,bool> &visited,string &s,vector<string> &ans){
    visited[s]=true;
    ans.emplace_back(s);
    for(auto cv : g[s]){
        if(visited[cv]==false){
            dfs1(g,visited,cv,ans);
        } 
    }
}

vector<string> dfs(unordered_map<string,vector<string>> &g){
    int n=g.size();
    vector<string> ans;
    unordered_map<string,bool> visited;
    ans.reserve(n);
    for(auto v : g){
        string s=v.first;
        if(visited[s]==false){
            dfs1(g,visited,s,ans);
        }
    }
    return ans;
}

int main(){
    unordered_map<string,vector<string>> g;
    g["raj"]={"neha","sunil"};
    g["akash"]={"sunil","priya"};
    g["sunil"]={"raj","maya","sneha","akash"};
    g["sneha"]={"sunil","rahul","neha",};
    g["maya"]={"sunil","rahul","arjun1"};
    g["priya"]={"raj","neha","aarav","akash"};
    g["neha"]={"raj","akash","aarav","sneha"};
    g["neha1"]={"priya","neha","rahul","aarav"};
    g["rahul"]={"neha","neha1","sneha","pooja","maya","arjun"};
    g["aarav"]={"neha","neha1","arjun"};
    g["arjun"]={"rahul","neha1","aarav"};
    g["arjun1"]={"maya","pooja"};
    g["pooja"]={"rahul","arjun","arjun1"};
    vector<string> result1=bfs(g);
    cout<<"BFS:"<<endl;
    for(auto i : result1) cout<<i<<" ";
    cout<<endl;
    vector<string> result2=dfs(g);
    cout<<"DFS:"<<endl;
    for(auto i  : result2) cout<<i<<" ";
}