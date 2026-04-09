#include<bits/stdc++.h>
using namespace std;
struct p{
    string s;
    vector<string> path;
    int cost;
    unordered_set<string> visited;
};
void bfs(string src, string dest,unordered_map<string,vector<pair<string,int>>> &g){
    queue<p> q;
    q.push({src,{src},0,{src}});
    while(!q.empty()){
        p curr=q.front();
        q.pop();
        if(curr.s==dest){
            for(auto city : curr.path){
                cout<<city<<"--->";
            }
            cout<<"total_path_cost:"<<curr.cost<<endl;
            continue;
        }
        for(auto neigh : g[curr.s]){
            string next_city=neigh.first;
            int c=neigh.second;
            if(!curr.visited.count(next_city)){
                p next_q_ele;
                next_q_ele.s=next_city;
                next_q_ele.path=curr.path;
                next_q_ele.path.push_back(next_city);
                next_q_ele.cost=curr.cost;
                next_q_ele.cost+=c;
                next_q_ele.visited=curr.visited;
                next_q_ele.visited.insert(next_city);
                q.push(next_q_ele);
            }
        }
    }
}

int bfs_exp_path(string src,string dest,unordered_map<string,vector<pair<string,int>>> &g){
    queue<p> q;
    q.push({src,{src},0});
    unordered_set<string> visited;
    visited.insert(src);
    int total_exp_cost=0;
    while(!q.empty()){
        p curr=q.front();
        q.pop();
        if(curr.s==dest){
            break ;
        }
        total_exp_cost+=curr.cost;
        for(auto neigh : g[curr.s]){
            string next_city=neigh.first;
            int c=neigh.second;
            if(!visited.count(next_city)){
                p next_q_ele;
                visited.insert(next_city);
                next_q_ele.s=next_city;
                next_q_ele.path=curr.path;
                next_q_ele.path.push_back(next_city);
                next_q_ele.cost=curr.cost+c;
                q.push(next_q_ele);
            }
        }
    }
    return total_exp_cost;
}

void dfs(string curr, string dest,unordered_map<string,vector<pair<string,int>>> &g ,unordered_set<string> &visited ,vector<string> &dfs_path ,int cost){
    if(curr==dest){
        for(auto city : dfs_path){
            cout<<city<<"--->";
        }
        cout<<"total_path_cost:"<<cost<<endl;
        return;
    }
    for(auto &neigh : g[curr]){
        string next_city=neigh.first;
        int c=neigh.second;
        if(!visited.count(next_city)){
            visited.insert(next_city);
            dfs_path.push_back(next_city);
            dfs(next_city,dest,g,visited,dfs_path,cost+c);
            dfs_path.pop_back();
            visited.erase(next_city);
        }
    }
}

int main(){
    unordered_map<string,vector<pair<string,int>>> g;
    g["chicago"] = {{"detroit",283},{"cleveland",345},{"indianapolis",182}};
    g["indianapolis"] = {{"chicago",182},{"columbus",176}};
    g["cleveland"] = {{"chicago",345},{"detroit",169},{"columbus",144},{"pittsburgh",134},{"buffalo",189}};
    g["detroit"] = {{"chicago",283},{"cleveland",169},{"buffalo",256}};
    g["columbus"] = {{"indianapolis",176},{"pittsburgh",185},{"cleveland",144}};
    g["pittsburgh"] = {{"cleveland",134},{"columbus",185},{"buffalo",215},{"philadelphia",305},{"baltimore",247}};
    g["baltimore"] = {{"pittsburgh",247},{"philadelphia",101}};
    g["philadelphia"] = {{"baltimore",101},{"pittsburgh",305},{"new york",97},{"syracuse",253}};
    g["buffalo"] = {{"detroit",256},{"cleveland",189},{"pittsburgh",215},{"syracuse",150}};
    g["new york"] = {{"philadelphia",97},{"syracuse",254},{"boston",215},{"providence",181}};
    g["providence"] = {{"new york",181},{"boston",50}};
    g["boston"] = {{"syracuse",312},{"providence",50},{"new york",215},{"portland",107}};
    g["portland"] = {{"boston",107}};
    g["syracuse"] = {{"buffalo",150},{"philadelphia",253},{"new york",254},{"boston",312}};

    string src="syracuse" , dest="chicago";
    cout<<"BFS TO FIND ALL POSSIBLE PATHS BETWEEN SRC AND DEST"<<endl;
    bfs(src,dest,g);
    cout<<"DFS TO FIND ALL POSSIBLE PATHS BETWEEN SRC AND DEST"<<endl;\
    unordered_set<string> visited;
    vector<string> dfs_path;
    visited.insert(src);
    dfs_path.push_back(src);
    dfs(src,dest,g,visited,dfs_path,0);
    cout<<"BFS TOTAL EXPLORATION PATH BETWEEN SRC AND DEST"<<endl;
    cout<<bfs_exp_path(src,dest,g);
}