#include<bits/stdc++.h>
using namespace std;
struct state{
    int boys,girls,boat,depth;
    vector<string> path;
};
class mystack{
public:
    vector<state> arr;
    void push(state s){
        arr.push_back(s);
    }
    void pop(){
        if(!arr.empty())
            arr.pop_back();
    }
    state top(){
        return arr.back();
    }
    bool empty(){
        return arr.empty();
    }
};
int exp_dls=0;
int exp_ids=0;
bool valid(int boys,int girls){
    int boys_right=3-boys;
    int girls_right=3-girls;
    if(girls>0 && boys>girls) return false;
    if(girls_right>0 && boys_right>girls_right) return false;
    if(boys<0 || girls <0 || boys>3 || girls>3) return false;
    return true;
}
bool goal(state s){
    return (s.boys==0 && s.girls==0 && s.boat==1);
}
vector<pair<int,int>> moves={
    {1,0},{0,1},{2,0},{0,2},{1,1}
};
bool depth_limited_search(state start,int limit){
    mystack st;
    set<string> visited;
    st.push(start);
    while(!st.empty()){
        state cur=st.top();
        st.pop();
        exp_dls++;
        string key=to_string(cur.boys)+to_string(cur.girls)+to_string(cur.boat);
        if(visited.count(key)) continue;
        visited.insert(key);
        if(goal(cur)){
            cout<<"dls_found_solution"<<endl;
            for(auto s:cur.path) cout<<s<<endl;
            return true;
        }
        if(cur.depth==limit) continue;
        for(auto m:moves){
            int nb=cur.boys;
            int ng=cur.girls;
            int nboat=1-cur.boat;
            if(cur.boat==0){
                nb-=m.first;
                ng-=m.second;
            }
            else{
                nb+=m.first;
                ng+=m.second;
            }
            if(!valid(nb,ng)) continue;
            state next{nb,ng,nboat,cur.depth+1,cur.path};
            next.path.push_back(to_string(nb)+to_string(ng)+to_string(nboat));
            st.push(next);
        }
    }
    return false;
}
bool iterative_deepening_search_process(state start,int limit){
    mystack st;
    set<string> visited;
    st.push(start);
    while(!st.empty()){
        state cur=st.top();
        st.pop();
        exp_ids++;
        string key=to_string(cur.boys)+to_string(cur.girls)+to_string(cur.boat);
        if(visited.count(key)) continue;
        visited.insert(key);
        if(goal(cur)){
            cout<<"ids_found_solution"<<endl;
            for(auto s:cur.path) cout<<s<<endl;
            return true;
        }
        if(cur.depth==limit) continue;
        for(auto m:moves){
            int nb=cur.boys;
            int ng=cur.girls;
            int nboat=1-cur.boat;
            if(cur.boat==0){
                nb-=m.first;
                ng-=m.second;
            }
            else{
                nb+=m.first;
                ng+=m.second;
            }
            if(!valid(nb,ng)) continue;
            state next{nb,ng,nboat,cur.depth+1,cur.path};
            next.path.push_back(to_string(nb)+to_string(ng)+to_string(nboat));
            st.push(next);
        }
    }
    return false;
}
void iterative_deepening_search(state start){
    for(int depth=0;depth<=27;depth++){
        if(iterative_deepening_search_process(start,depth)){
            cout<<"\ndepth="<<depth<<endl;
            return;
        }
    }
}
int main(){
    state start{3,3,0,0,{"330"}};
    cout<<"running depth_limited_search(limit=3)"<<endl;
    if(!depth_limited_search(start,3)){
        cout<<"no_solution"<<endl;
    }
    cout<<"dls explored states="<<exp_dls<<endl;
    cout<<"running iterative_deepening_Search"<<endl;
    iterative_deepening_search(start);
    cout<<"iterative_deepening_search_explored_states="<<exp_ids<<endl;
    return 0;
}