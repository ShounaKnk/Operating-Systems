#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 10
using namespace std;

struct Process
{
    string name;
    double art;
    double bt;
    int priority;
    bool arrived;
};

void disptable(int n, int fp, double bt[], double at[], int priority[], double wt[], double tt[], vector<pair<string,double>>gchart)
{
    cout<< "Process\t\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnAround Time"<<endl;
    for(int i=0; i< n; i++)
    {
        cout<<"p"<<i+1<<"\t\t"<<bt[i]<<"\t\t"<<at[i]<<"\t\t"<<priority[i]<<"\t\t"<<wt[i]<<"\t\t"<<tt[i]<<endl;
    }
    cout<<endl;
    cout<<"Gantt Chart: "<<endl<<"|  ";
    for(int i =0; i< gchart.size();i++)
    {
        cout<<gchart[i].first<<"  |  ";
    }
    cout<<endl<<fp;
    for(int i =0; i< gchart.size();i++)
    {
        cout<<"      "<<gchart[i].second;
    }
    cout<<endl;
}

double findLastOccurrenceOf(vector <pair<string, double>> gchart, int key)
{
    double value;
    for(int i=gchart.size(); i>=0; i--) 
    {
        if(gchart[i].first == "P"+to_string(key)) 
        {
            value = gchart[i].second;
            return value; 
        }
    }
}
void calcs(int fp, vector <pair<string, double>> gchart, vector <Process> P)
{
    float awt = 0;
    float att = 0;
    int priority[MAX] = {0};
    double bt[MAX] = {0};
    double art[MAX] = {0};
    double wt[MAX] = {0};
    double compt[MAX] = {0};
    double tt[MAX] = {0};

    for( int i =1; i<=P.size(); i++) 
    { 
        compt[i-1] = findLastOccurrenceOf(gchart, i);
    }
    for( int i =0; i<P.size(); i++) 
    {
        priority[i] = P[i].priority;
        bt[i] = P[i].bt; 
        art[i] = P[i].art;
        wt[i] = compt[i] - P[i].bt - P[i].art;
        tt[i] = wt[i] + P[i].bt;
        awt += wt[i];
        att += tt[i]; 
    }
    disptable(P.size(), fp, bt, art, priority, wt, tt, gchart);
    cout << "-> Average waiting time     : " << awt/P.size()<< endl;
    cout<< "-> Average turn around time : " << att/P.size();
}
bool cmpP(const Process& a, const Process& b) 
{
    return a.priority < b.priority;
}
void sortQueue(queue <Process>& Q) 
{
    vector <Process> temp;
    while(!Q.empty()) 
    {
        temp.push_back(Q.front());
        Q.pop();
    }
    sort(temp.begin(), temp.end(), cmpP);
    for(const Process& p : temp) 
    {
        Q.push(p);
    }
}
void arrivedP(double time, vector <Process>& p, queue <Process>& Q) 
{
    for( int i =0; i<p.size(); i++) 
    {
        if((!p[i].arrived) && (p[i].art <= time)) 
        { 
            p[i].arrived = true;
            Q.push(p[i]); 
        }
    }
}
double findMinT(vector <Process> P) 
{
    double min = P[0].bt;
    for(Process p : P) 
    {
        if(p.bt < min) 
        { min = p.bt; }
    }
    return min;
}
void premptiveP(vector <Process>& p) 
{
    
    int fp = 100;
    double time = 0;
    double min_executionT = findMinT(p);
    queue <Process> Q;
    vector <pair<string, double>> gchart;
    string prevP = ""; 
    do 
    {
        arrivedP(time, p, Q);
        sortQueue(Q);

        if(fp == 100) 
        { fp = Q.front().art; }

        Q.front().bt -= min_executionT;
        time += min_executionT;

        if(Q.front().name == prevP) 
        { 
            gchart.back().second = time; 
        } else {
            gchart.push_back(make_pair(Q.front().name, time)); 
            prevP = Q.front().name; 
        }
        if (Q.front().bt == 0) { Q.pop(); }

    } while (!Q.empty());
    calcs(fp, gchart, p);
}

int main() 
{

    int n;
    cout << "Enter the no. of p : "; cin >> n;
    vector <Process> p(n);
    
    for( int i =0; i<n; i++) {
        cout << "Process P" << (i+1) << endl;
        cout << "  ==> Arrival Time : "; cin >> p[i].art;
        cout << "  ==> Burst Time   : "; cin >> p[i].bt;
        cout << "  ==> Priority     : "; cin >> p[i].priority;
        p[i].name = "P"+to_string(i+1);
        p[i].arrived = false;
        cout<<endl;
    }
    premptiveP(p);
    return 0;
}