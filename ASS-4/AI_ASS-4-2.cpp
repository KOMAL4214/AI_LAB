#include<bits/stdc++.h>
using namespace std;
struct rule{
    int id;
    string cond;
    string action;
};
struct node{
    int x,y;
    int h;
    vector<pair<int,int>> path;
};
class priorityqueue{
    public:
    vector<node> pq;
        void push(node n){   
            pq.push_back(n);
        }
        node pop(){
            int minindex=0;
            for(int i=1;i<pq.size();i++){
                if(pq[i].h<pq[minindex].h){
                    minindex=i;
                }
            }
            node best=pq[minindex];
            pq.erase(pq.begin()+minindex);
            return best;
        }
        bool empty(){
            return pq.empty();
        }
};
int heuristic(int x,int y,int gx,int gy){
    return abs(gx-x)+abs(gy-y);
}

int main(){
    vector<rule> rules={
        {1,"robot at entry","insert start node into OPEN list"},
        {2,"OPEN list not empty","select node with minimum heuristic"},
        {3,"Selected node is Exit","Stop search and output path"},
        {4,"Selected node is not Exit","Expand neighbors"},
        {5,"Neighbor is Wall/Room","Ignore neighbor"},
        {6,"Neighbor already visited","Ignore neighbor"},
        {7,"Valid neighbor","Insert into OPEN list"},
        {8,"OPEN list empty","Stop search (No path found)"}
    };
    cout<<"robot evacuation table"<<endl;
    for(auto r : rules){
        cout<<"rule "<<r.id<<":"<<endl;
        cout<<"condition: "<<r.cond<<endl;
        cout<<"action: "<<r.action<<endl;
    }
    vector<vector<int>> floor={
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,1,0,0,0,0,1,1,0,0,1},
        {1,0,0,0,0,0,1,0,1,1,1,0,1},
        {1,1,1,1,0,1,0,0,0,0,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,1,0,0,1,0,1,1,1},
        {1,0,0,1,0,1,0,1,0,1,0,0,1},
        {1,0,0,1,0,1,0,1,1,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    int rows=floor.size();
    int cols=floor[0].size();
    int sx=7,sy=4;
    int gx=4,gy=11;
    vector<vector<bool>> vis(rows,vector<bool>(cols,false));
    priorityqueue pq;
    node start;
    start.x=sx;
    start.y=sy;
    start.h=heuristic(sx,sy,gx,gy);
    start.path.push_back({sx,sy});
    pq.push(start);
    int exp=0;
    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    cout<<"\n best_first_search evacuation"<<endl;
    while(!pq.empty()){
        node curr=pq.pop();
        exp++;
        int x=curr.x;
        int y=curr.y;
        if(vis[x][y]){
            continue;
        }
        vis[x][y]=true;
        if(x==gx && y==gy){
            cout<<"evacuation_path"<<endl;
            for(auto p : curr.path){
                cout<<"("<<p.first<<","<<p.second<<")";
            }
            cout<<"\ncells explored:"<<exp<<endl;
            return 0;
        }
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<rows && ny>=0 && ny<cols){
                if(!vis[nx][ny] && floor[nx][ny]==0){
                    node next;
                    next.x=nx;
                    next.y=ny;
                    next.h=heuristic(nx,ny,gx,gy);
                    next.path=curr.path;
                    next.path.push_back({nx,ny});
                    pq.push(next);
                }
            }
        }
    }
    cout<<"exit not reachable";
    return 0;
}