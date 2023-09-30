#include <iostream>
using namespace std;
#define MAX 10

void dispG(int n, double bt[], double art[], double wt[], double tt[]) {

    double ganttChart[MAX] = {0};
    cout << endl << endl << "Gantt Chart : " << endl;

    cout << endl << "|    ";
    for(int i=0; i<n; i++) {
        cout << "P" << i << "    |    ";
    }
    ganttChart[0] = art[0];
    for(int i=1; i<=n; i++)
    {
        ganttChart[i] = ganttChart[i-1] + bt[i-1];
    }
    cout << endl << art[0] << " ";
    for(int i=1; i<=n; i++) {
        cout << "         " << ganttChart[i];
    }
}
void fcfs(int n, double bt[], double art[], double wt[], double tt[]) {

    wt[0] = 0;
    for(int i=1; i<n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }
    cout << endl << "Process\t\tBurstTime\tWaitingTime\tTurnAroundTime";
    for(int i={}; i<n; i++) {
        tt[i] = wt[i] + bt[i];
        cout << endl << "P" << i << "\t\t"<< bt[i] << "\t\t"<< wt[i] << "\t\t"<< tt[i];
    }
    float sum_w = {};
    float sum_t = {};
    for(int i={}; i<n; i++) {
        sum_w += wt[i];
        sum_t += tt[i];
    }
    cout << endl << endl << "Average waiting time     = " << (sum_w / n);
    cout << endl << "Average turn around time = " << (sum_t / n);

    dispG(n, bt, art, wt, tt);
}

int main() {

    int n = {};
    cout << "Enter the no. of processes : ";
    cin >> n;

    double bt[MAX];
    double art[MAX];
    double wt[MAX];
    double tt[MAX];

    for(int i=0; i<n; i++) {
        cout << "burst time for process"<<i<<" : ";
        cin >> bt[i];
        art[i] = i;
    }
    fcfs(n, bt, art, wt, tt);
    return 0;
}
