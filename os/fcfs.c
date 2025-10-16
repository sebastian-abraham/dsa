/*Sejith R Nath
51 CS-B
FCFS*/
#include <stdio.h>
struct fcfs {
int pid ,at,bt,ct,wt,tat;
}temp[100],a;
void main(){
int n,t=0,stat=0 , swt =0;
printf("Enter the number of process : ");
scanf("%d",&n);
for(int i =0 ; i<n ; i++){
printf("Enter the AT and BT of process :%d ",i);
scanf("%d%d",&temp[i].at,&temp[i].bt);
temp[i].pid = i;
}
for(int i =0 ; i<n-1 ; i++){
for (int j =0 ; j<n-i-1 ; j++){
if(temp[j].at>temp[j+1].at){
a= temp[j];
temp[j]=temp[j+1];
temp[j+1]=a;
}}}
temp[0].ct=temp[0].at+temp[0].bt;
for (int i =1 ; i<n ; i++){
if(temp[i-1].ct>temp[i].at){
temp[i].ct=temp[i-1].ct+temp[i].bt;
}
else{
temp[i].ct=temp[i].bt+temp[i].at;
}}
for (int i =0 ; i<n ; i++){
temp[i].tat=temp[i].ct-temp[i].at;
temp[i].wt=temp[i].tat-temp[i].bt;
stat+=temp[i].tat;
swt+=temp[i].wt;
}
printf("Pid\tAt\tBt\tCt\tTat\tWt");
for (int i =0 ; i<n ; i++){
printf("\n%d\t%d\t%d\t%d\t%d\t%d",temp[i].pid,temp[i].at,temp[i].bt,temp[i].ct,temp[i].tat,temp[i].wt);
}
t=0;
printf("\nGantt Chart:\n ");
for (int i = 0; i < n; i++) {
printf(" ");
for (int j = 0; j < temp[i].bt; j++) printf("--");
printf(" ");
}
printf("\n|");
for (int i = 0; i < n; i++) {
printf(" ");
for (int j = 0; j < temp[i].bt - 1; j++)
printf(" ");
printf("P%d", temp[i].pid);
for (int j = 0; j < temp[i].bt - 1; j++) printf(" ");
printf("|");
}
printf("\n ");
for (int i = 0; i < n; i++) {
printf(" ");
for (int j = 0; j < temp[i].bt; j++) printf("--");
printf(" ");
}
printf("\n");
printf("0");
for (int i = 0; i < n; i++) {
for (int j = 0; j < temp[i].bt * 2; j++) printf(" ");
printf("%d", temp[i].ct);
}
printf("\n");
printf("\nAverage TAT :%.2f\nAverage Wt :%.2f\n",(float)stat/n,(float)swt/n);
}


