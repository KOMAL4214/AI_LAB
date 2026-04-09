#include<bits/stdc++.h>
using namespace std;

struct node{
    string state;
    int depth;
};

struct stacknode{
    node data;
    stacknode* next;
    stacknode(node val){
        data=val;
        next=NULL;
    }
};

class Stack{
    stacknode* topnode;
    public:
    Stack(){
        topnode=NULL;
    }
    bool empty(){
        return topnode==NULL;
    }
    void push(node value){
        stacknode* newnode=new stacknode(value);
        newnode->next=topnode;
        topnode=newnode;
    }
    node top(){
        return topnode->data;
    }
    void pop(){
        if(topnode==NULL){
            return;
        }
        stacknode* temp=topnode;
        topnode=topnode->next;
        delete temp;
    }
};

bool isvalid(int x,int y){
    return (x>=0&&x<3&&y>=0&&y<3);
}

int dfs(string start,string goal){
    int x_dir[4]={0,0,-1,1};
    int y_dir[4]={-1,1,0,0};
    Stack s;
    unordered_set<string> visited;
    node startnode;
    startnode.state=start;
    startnode.depth=0;
    s.push(startnode);
    visited.insert(start);
    int explored=0;
    while(!s.empty()){
        node curr=s.top();
        s.pop();
        explored++;
        if(curr.state==goal){
            cout<<"goal is reached"<<endl;
            cout<<"depth is :"<<curr.depth<<endl;
            return explored;
        }
        int pos=curr.state.find('0');
        int x=pos/3;
        int y=pos%3;
        for(int i=3;i>=0;i--){
            int newx=x+x_dir[i];
            int newy=y+y_dir[i];
            if(isvalid(newx,newy)){
                string next=curr.state;
                swap(next[x*3+y],next[newx*3+newy]);
                if(visited.find(next)==visited.end()){
                    visited.insert(next);
                    node nextnode;
                    nextnode.state=next;
                    nextnode.depth=curr.depth+1;
                    s.push(nextnode);
                }
            }
        }
    }
    return -1;
}

int main(){
    string start_state="724506831";
    string goal_state="012345678";
    int tot_exp_states=dfs(start_state,goal_state);
    cout<<"total_explored_states :"<<tot_exp_states;   
}