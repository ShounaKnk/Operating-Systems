#include<iostream>
using namespace std;
int n, m, s=0;
int alloc[10][10], maxi[10][10], available[10], need[10][10], work[10], count=0, ss[10];
int finish[10], check1=0, check2=0;

void safeseq()
{
    for(int j=0; j<m; j++)
        work[j] = available[j];
    for(int i=0; i<n; i++)
        finish[i] = 0;
    while(count != n)
    {
        for(int i=0; i<n; i++)
        {
            check1=0;
            for(int j=0; j<m; j++)
            {
                if(finish[i]==0 && (need[i][j] <= work[j]))
                    check1++;
                if(check1 == m)
                {
                    for(int j=0; j<m; j++)
                    {
                        work[j] += alloc[i][j];
                        finish[i]=1;
                    }
                    ss[s]=i;
                    s++;
                    count++;
                }
                
            }
        }
        
    }
    for(int i=0; i<n; i++)
    {
        if(finish[i]==1)
            check2++;
        if(check2 == n)
        {
            cout<<"safe sequence exists"<<endl;
            cout<<"safe sequence: ";
            for(int i=0; i<n; i++)
                cout<<"P"<<ss[i]<<"  ";
        }
        else
            cout<<"safe sequence doesnt exists"<<endl;
    }
}


int main()
{
    cout<<"enter no. of processes: "; cin>>n;
    cout<<"enter no. of resources:"; cin>>m;

    cout<<"Enter the allocated resources"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"P"<<i<<": "<<endl;
        for(int j=0; j<m; j++)
        {
            cout<<"==>R"<<j<<": "; cin>>alloc[i][j];
        }
        cout<<endl;
    }

    cout<<"Enter the maximum resources"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"P"<<i<<": "<<endl;
        for(int j=0; j<m; j++)
        {
            cout<<"==>R"<<j<<": "; cin>>maxi[i][j];
        }
        cout<<endl;
    }
    cout<<"Enter the available resource: "<<endl;
    for(int j=0; j<m; j++)
    {
        cout<<"==>R"<<j<<": "; cin>>available[j];
    }
    cout<<endl<<endl;

    cout<<"Need Matrix:"<<endl;
    for(int j=0; j<m; j++)
    {
        cout<<"R"<<j<<"\t";
    }
    cout<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            need[i][j] = maxi[i][j] - alloc[i][j];
            cout<<need[i][j]<<"\t";
        }
        cout<<endl;
    }
    safeseq();
}
