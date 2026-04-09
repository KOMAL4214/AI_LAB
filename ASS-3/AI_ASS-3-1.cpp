#include<bits/stdc++.h>
using namespace std;

struct rules{
    string location;
    int room_state;
    string reply;
};

string cleaning(string current_location,int room_state,vector<rules>& rule_table){
    for(auto rule : rule_table){
        if(rule.location==current_location && rule.room_state==room_state){
            return rule.reply;
        }
    }
    return "no_cleaning_required";
}

int main(){
    vector<rules> rule_table = {
        {"A",1,"clean"},
        {"B",1,"clean"},
        {"C",1,"clean"},
        {"A",0,"move right"},
        {"B",0,"move right"},
        {"C",0,"move left"}
    };
    string current_location;
    cout<<"enter the current location :"<<endl;
    cin>>current_location;
    int a,b,c;
    int cost=0,steps=0;
    cout<<"enter the states of the rooms:"<<endl;
    cout<<"dirty->1;clean->0"<<endl;
    cin>>a>>b>>c;
    cout<<"locaton/percept"<<"\t\t"<<"action"<<endl;
    cout<<"---------------"<<"\t\t"<<"------"<<endl;
    for(int i=0;i<10;i++){
        int room_state;
        if(current_location=="A") room_state=a;
        else if(current_location=="B") room_state=b;
        else room_state=c;
        cout<<current_location<<","<<room_state<<"\t\t\t";
        string reply=cleaning(current_location,room_state,rule_table);
        cout<<reply<<endl;
        if(reply=="clean"){
            cost+=2;
            if(current_location=="A") a=0;
            if(current_location=="B") b=0;
            if(current_location=="C") c=0;
        }
        else if(reply=="move right"){
            cost++;
            if(current_location=="A") current_location="B";
            else if(current_location=="B") current_location="C";
        }
        else if(reply=="move left"){
            cost++;
            if(current_location=="C") current_location="B";
            else if(current_location=="B") current_location="A";
        }
        steps++;
    }
    cout<<"cost :"<<cost<<"\t"<<"steps :"<<steps;
}