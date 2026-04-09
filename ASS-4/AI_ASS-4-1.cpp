#include<bits/stdc++.h>
using namespace std;
//structure for storing city,heurisitc and the path
struct node{
  int city;
  int h;
  vector<int> path;  
};
//priority queue
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

int main(){
    string cities[14]={
        "chicago","detroit","cleveland","buffalo","syracuse","pittsburgh","newyork","philedalphia","boston","indianapolis","columbus","baltimore","portland","providence"
    };
    //chicago,detroit,cleveland,buffalo,syracuse,pittsburgh,newyork,philedelphia,boston,indianapolis,columbus,baltimore,portland,providence
    int heuristic[14]={4,3,3,2,1,3,1,2,0,5,4,3,1,1};
    vector<int> citymap[14];
    citymap[0]={1,2,9}; 
    citymap[1]={0,2,3};          
    citymap[2]={0,1,10,5};      
    citymap[3]={1,2,5,4};       
    citymap[4]={3,8,6};         
    citymap[5]={2,3,10,7,11};  
    citymap[6]={4,7,8,13};          
    citymap[7]={5,6,11};
    citymap[8]={4,6,12,13};            
    citymap[9]={0};             
    citymap[10]={2,5};          
    citymap[11]={5,7};
    citymap[12]={8};
    citymap[13]={6,8};      
    int start=0;
    int goal=8;
    priorityqueue pq;
    vector<bool> vis(12,false);
    node startnode;
    startnode.city=start;
    startnode.h=heuristic[start];
    startnode.path.push_back(start);
    pq.push(startnode);
    int exp=0;
    cout<<"best first search using hop heuristic"<<endl;
    while(!pq.empty()){
        node curr=pq.pop();
        exp++;
        int currcity=curr.city;
        if(vis[currcity]){
            continue;
        }
        vis[currcity]=true;
        if(currcity==goal){
            cout<<"path is :"<<endl;
            for(int i=0;i<curr.path.size();i++){
                cout<<cities[curr.path[i]];
                if(i!=curr.path.size()-1){
                    cout<<"->";
                }
            }
            cout<<"\nexplored:"<<exp<<endl;
            return 0;
        }
        for(int neigh : citymap[currcity]){
            if(!vis[neigh]){
                node next;
                next.city=neigh;
                next.h=heuristic[neigh];
                next.path=curr.path;
                next.path.push_back(neigh);
                pq.push(next);
            }
        }
    }
    cout<<"goal not found"<<endl;
    return 0;
}