#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define lli long long int
pair<lli,lli> p[1000005];       //CAN HANDLE 1000005 rows of data .
int main()
{
    cout<<"PLEASE ENTER THE NUMBER OF ROWS OF DATA : ";
    lli n;
    cin>>n;
    if(n<=0)
    {
        cout<<"PLEASE ENTER VALID NUMBER OF ROWS\n PROGRAM WILL EXITS NOW .........."<<endl;
        return 0;
    }
    printf("PLEASE ENTER %d ROWS OF DATA IN FORM OF PAIR : \'PRICE\' \'COUNT\' eg. 200 12\n",n);
    for(int i=0;i<n;i++)
        cin>>p[i].first>>p[i].second;
    sort(p,p+n);
    lli mean=0;
    for(int i=0;i<n;i++)
    {
        mean+=p[i].second;
    }
    mean=mean/n;
    lli r_variance=0;//raw data variance
    for(int i=0;i<n;i++)
    {
        r_variance+=pow((p[i].second-mean),2);
    }
    lli s_d=sqrt(r_variance);               //raw data standard deviation
    cout<<"\nRaw Data Details:-\n";
    cout<<"Mean is : "<<mean<<" Variance is :"<<r_variance<<" Standard Deviation is :"<<s_d<<endl;
    cout<<"\nEnter the Expected number of rows NOTE: ENTER 0 for default number of rows : "<<endl;
    lli rows;
    cin>>rows;       //Expected number of rows in price filter needed to be entered here.
    lli factor;     //factor needed to reduce the group.
    if(rows==0)
        factor=1;
    else
        factor=n/rows;
    mean*=factor;
    vector<pair<lli,lli> > range;   //List to store the price ranges
    vector<lli> r_count;            //List to store the number of items in a that price range.
    pair<lli,lli> pr;               //Pair to store start price and end price.
    pr.first=1;
    int c=0,i=0,c_lim=s_d;
    for(i=0;i<n;i++)                //Loop used to calculate the price groups and items in them.
    {                               //Different if conditions used to handle different kinds of cases
        int res=c;                  //which includes few corner cases too.
        c+=p[i].second;
        if(res==0 && c>mean+c_lim)
        {
            pr.second=p[i].first;
            r_count.pb(c);
            range.pb(pr);
            pr.first=p[i].first+1;
            c=0;
        }
        else if(c>mean+c_lim)
        {
            c-=p[i].second;
            pr.second=p[i-1].first;
            r_count.pb(c);
            range.pb(pr);
            pr.first=p[i-1].first+1;
            c=0;
            i--;
        }
    }
    if(c!=0)                        //Again one more condition to handle corner case.
    {
        pr.second=p[i-1].first;
        r_count.pb(c);
        range.pb(pr);
    }
    cout<<"\nEXPECTED PRICE GROUPS ARE BELOW :- "<<endl;
    cout<<"PRICE-GROUP | COUNT"<<endl;
    lli mv=0;
    for(int i=0;i<r_count.size();i++)
    {
        cout<<range[i].first<<" - "<<range[i].second<<" : "<<r_count[i]<<endl;
        mv+=r_count[i];
    }
    mv/=r_count.size();             //Mean of Price Filter data.
    lli variance=0;                 //Variance of data.
    for(int i=0;i<r_count.size();i++)
    {
        variance+=pow((r_count[i]-mv),2);
    }
    variance/=r_count.size();
    cout<<"\nFor the given ranges : \n";
    cout<<"Mean is : "<<mv<<endl;
    cout<<"Variance is : "<<variance<<endl;
    cout<<"S.Deviation is :"<<sqrt(variance)<<endl;
}
