#include <iostream>
using namespace std;
#define MAX 10

void sortp(int n, double bt[], double art[], int Porder[]) {

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n-i; j++) {
            if(art[j] > art[j+1])
            {
                int temp = art[j];
                art[j] = art[j+1];
                art[j+1] = temp;

                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                temp = Porder[j];
                Porder[j] = Porder[j+1];
                Porder[j+1] = temp;
            }
            else if(art[j] == art[j+1])
            {
                if(bt[j] > bt[j+1]) {
                    int temp = art[j];
                    art[j] = art[j+1];
                    art[j+1] = temp;

                    temp = bt[j];
                    bt[j] = bt[j+1];
                    bt[j+1] = temp;

                    temp = Porder[j];
                    Porder[j] = Porder[j+1];
                    Porder[j+1] = temp;
                }
            }
        }
    }
}
void dispG(double ganttChart[], int Porder[], int n) {
    cout << endl << endl << "Gantt Chart : " << endl;
    cout << endl << "|    ";
    for(int i=1; i<=n; i++) {
        cout << "P" << Porder[i] << "    |    ";
    }
    cout << endl;

    for(int i = 0; i <= n; i++) {
        cout << ganttChart[i] << "          ";
    }
    cout << endl;
}

void sjfa(int n, double bt[], double art[]) {

    float avgWT = 0;
    float avgTT = 0;
    int Porder[MAX] = {0};
    double wt[MAX] = {0};
    double ct[MAX] = {0};
    double tt[MAX] = {0};
    double gantchartv[MAX] = {0};

    for(int i=1; i<=n; i++) {
        Porder[i] = i;
    }
    sortp(n, bt, art, Porder);

    gantchartv[0] = art[1];
    for(int i=1; i<=n; i++) {
        gantchartv[i] = gantchartv[i-1] + bt[i];
        ct[i] = gantchartv[i];
    }

    for(int i=1; i<=n; i++) {
        wt[i] = ct[i] - bt[i] - art[i];
        tt[i] = wt[i] + bt[i];
        avgWT += wt[i];
        avgTT += tt[i];
    }
    avgWT /= n;
    avgTT /= n;
    cout << endl << "Process\t\tBurstTime\tArrival Time\tWaitingTime\tTurnAroundTime" << endl;
    for(int i=1; i<=n; i++) {
        cout << endl << "P" << Porder[i] << "\t\t" << bt[i] <<"\t\t"<<art[i]<< "\t\t"<< wt[i] << "\t\t"<< tt[i];
    }
    cout << endl << endl << "Average waiting time     : " << avgWT;
    cout << endl << "Average turn around time : " << avgTT;

    dispG(gantchartv, Porder, n);
}
int main() {

    int n;
    double bt[MAX] = {0};
    double art[MAX] = {0};

    cout << "Enter the no. of processes : ";
    cin >> n;
    for(int i=1; i<=n; i++){
        cout << "Process " << i << endl;
        cout << "AT : "; cin >> art[i];
        cout << "BT : "; cin >> bt[i];
        cout << endl;
    }
    sjfa(n, bt, art);
    return 0;
}
