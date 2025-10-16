/*Sejith R Nath
51 CS-B
PRIORITY*/
#include<stdio.h>
struct prio{
int pid ,at,bt,ct,wt,tat,flg,p;
}temp[100],a;
void main(){
int n,t=0,stat=0 , swt =0;
printf("Enter the number of process : ");
scanf("%d",&n);
for(int i =0 ; i<n ; i++){
printf("Enter the AT  BT  and Priority of process :%d ",i);
scanf("%d%d%d",&temp[i].at,&temp[i].bt,&temp[i].p);
temp[i].pid = i;
temp[i].flg= 0;
}
for(int i =0 ; i<n-1 ; i++){
for (int j =0 ; j<n-i-1 ; j++){
if(temp[j].at>temp[j+1].at){
a= temp[j];
temp[j]=temp[j+1];
temp[j+1]=a;
}
}
}
for (int i=0 ; i<n ;){
int index = -1 , minp = 99999;
for (int j =0 ; j< n ; j++){
if(temp[j].at<=t && temp[j].p<minp && temp[j].flg==0){
index = j;
minp= temp[j].p;
}
}
if(index == -1){
t++;
}else{
i++;
temp[index].ct=t+temp[index].bt;
t=temp[index].ct;
temp[index].flg= 1;
temp[index].tat=temp[index].ct-temp[index].at;
temp[index].wt=temp[index].tat-temp[index].bt;
stat+=temp[index].tat;
swt+=temp[index].wt;
}
}
printf("Pid\tAt\tBt\tPriority\tCt\tTat\tWt");
for (int i =0 ; i<n ; i++){
printf("\n%d\t%d\t%d\t%d\t\t%d\t%d\t%d",temp[i].pid,temp[i].at,temp[i].bt,temp[i].p,temp[i].ct,temp[i].tat,temp[i].wt);
}
printf("\nAverage TAT :%.2f\nAverage Wt :%.2f\n",(float)stat/n,(float)swt/n);
}




















