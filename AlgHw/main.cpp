#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

#define N 1000

struct activity
{
    int start;
    int finish;
    int weight;
    int pos;
};

bool comp(activity m, activity n)
{
    return m.finish>n.finish;
}

int dp[N];

int main()
{
    int n, maxi=-1;
    int DP[N];
    activity a[N];
    cout << " Enter something" << endl;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        cout << "More stuff?" << endl;
        scanf("%d %d %d", &a[i].start, &a[i].finish, &a[i].weight);
        a[i].pos=i+1;
    }
    sort(a, a+n, comp);
    for(int i=0; i<n; i++)
        dp[i]=a[i].weight;
    for(int i=1; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(a[j].finish<=a[i].start)
                dp[i]=max(dp[i], dp[j]+a[i].weight);
            maxi=max(dp[i], maxi);
        }
    }
    printf("%d\n", maxi);
    int act[N];
    int k=0;
    for(int i=n-1;i>=0;i--)
    {
        if(dp[i]==maxi)
        {
            maxi-=a[i].weight;
            act[k++]=a[i].pos;
        }
    }
    for(int i=k-1;i>=0;i--)
        printf("%d ", act[i]);

    return 0;
}