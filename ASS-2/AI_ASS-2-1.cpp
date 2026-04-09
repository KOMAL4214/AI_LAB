#include<bits/stdc++.h>
using namespace std;

struct Node {
    string state;
    int depth;
    Node* next;
};

class Queue{
private:
    Node* front;
    Node* rear;
public:
    Queue(){
        front=NULL;
        rear=NULL;
    }
    void enqueue(string s,int d){
        Node* temp=new Node();
        temp->state=s;
        temp->depth=d;
        temp->next=NULL;
        if(rear==NULL){
            front=rear=temp;
        }else{
            rear->next=temp;
            rear=temp;
        }
    }
    pair<string,int> dequeue(){
        if(front==NULL){
            return {"",-1};
        }
        Node* temp=front;
        pair<string,int> data={temp->state,temp->depth};
        front=front->next;
        if(front==NULL){
            rear=NULL;
        }
        delete temp;
        return data;
    }
    bool isEmpty(){
        return front==NULL;
    }
};

bool isvalid(int x,int y){
    return (x>=0&&x<3&&y>=0&&y<3);
}

int bfs(string start,string goal){
    int x_dir[4]={-1, 1, 0, 0};
    int y_dir[4]={0, 0, -1, 1};
    Queue q;
    unordered_set<string> visited;
    q.enqueue(start, 0);
    visited.insert(start);
    int tot_states_exp=0;
    while(!q.isEmpty()){
        auto data = q.dequeue();
        string curr = data.first;
        int dep = data.second;
        tot_states_exp++;
        if(curr==goal){
            cout<<"goal state reached"<<endl;
            cout<<"depth is : "<<dep<<endl;
            return tot_states_exp;
        }
        int pos=curr.find('0');
        int x=pos/3;
        int y=pos%3;
        for(int i=0;i<4;i++){
            int newx=x+x_dir[i];
            int newy=y+y_dir[i];
            if(isvalid(newx, newy)){
                string next=curr;
                swap(next[x*3 + y],next[newx*3 + newy]);
                if(visited.find(next) == visited.end()){
                    visited.insert(next);
                    q.enqueue(next,dep+1);
                }
            }
        }
    }
    return -1;
}

int main() {
    string start_state="724506831";
    string goal_state="012345678";
    int tot_states_exp=bfs(start_state,goal_state);  
    cout <<"Total states explored : "<<tot_states_exp<<endl;
}