#include<iostream>
using namespace std;

int main()
{
    int arr[4] = {1,2,3,4};
    int count =0;
    while(arr)
    {
        count++;
        cout<<count;
    }
    cout<<count;

}