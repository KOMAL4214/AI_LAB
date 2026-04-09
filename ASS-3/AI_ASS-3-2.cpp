#include<bits/stdc++.h>
using namespace std;

struct rule{
    string inbound;
    string outbound;
    string obstacles;
    string manual;
    string actuation;
};

string actuation(string inbound,string outbound,string obstacles,string manual,vector<rule>& rule_table){
    for(auto rule : rule_table){
        if((rule.inbound==inbound||rule.inbound=="any_signal") && (rule.outbound==outbound||rule.outbound=="any_signal") && (rule.obstacles==obstacles||rule.obstacles=="any_signal") && (rule.manual==manual||rule.manual=="any_signal")){
            return rule.actuation;
        }
    }
    return "no_actuation";
}

int main(){
    vector<rule> rule_table={
        {"any_signal","any_signal","any_signal","man_eme","gate:close siren:on signal:red"},//manual_emergency
        {"det","any_signal","obs_det","no_man_eme","gate:close siren:on signal:red"},//train coming+obstacles on the crossing line
        {"det","any_signal","no_obs_det","no_man_eme","gate:close siren:on signal:green"},//normal train entering
        {"not_det","det","no_obs_det","no_man_eme","gate:open siren:off signal:green"},//normal train leaving
        {"not_det","not_det","det","no_man_eme","gate:open siren:off signal:green"},//no trains are coming or leaving only vec hicles are passing through the crossing
    };
    string inbound,outbound,obstacles,manual;
    cout<<"enter the percepts in the order inbound-outbound-obstacles-manual :"<<endl;
    cout<<"for inbound/outbound you should enter->anysignal/det/not_det"<<endl;
    cout<<"for obstacles you should enter->any_signal/obs_det/no_obs_det"<<endl;
    cout<<"for manual you should enter->any_signal/no_man_eme/man_eme"<<endl;
    cin>>inbound>>outbound>>obstacles>>manual;
    cout<<"percept\t\t\t\t\t\taction"<<endl;
    cout<<"-------\t\t\t\t\t\t------"<<endl;
    cout<<inbound<<","<<outbound<<","<<obstacles<<","<<manual<<"\t";
    string action=actuation(inbound,outbound,obstacles,manual,rule_table);
    cout<<action<<endl;
}