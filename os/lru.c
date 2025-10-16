/*Sejith R Nath
51 CS-B
LRU*/
#include <stdio.h>
void main()
{
int page[10], frame[10],time[10],count=0, p,f, ph=0,pf=0 ,top=0,n,i,j,k;
printf("Enter the number of pages : ");
scanf("%d",&p);
printf("Enter the number of frames : ");
scanf("%d",&f);
printf("Enter the page numbers : ");
for(int i =0 ; i< p; i++)
{
scanf("%d",&page[i]);
}
for(int i =0 ; i< f ; i++)
{
frame[i]=-1;
time[i]=0;
}
for (int i = 0 ; i< p; i++)
{
int found = 0;
for (int j =0 ; j< f ; j++)
{
if(frame[j]==page[i])
{
found = 1;
ph++;
time[j]=count++;
break;
}
}
if(!found)
{
int efound =0;
for( k =0 ; k<f ; k++)
{
if(frame[k] == -1)
{
efound=1;
break;
}
}
if(efound)
{
frame[k]=page[i];
time[k]=count++;
}
else
{
int mini = 0,ltime;
ltime = time[mini];
for(int k =0 ; k<f ; k++)
{
if(time[k]<ltime)
{
ltime = time[k];
mini=k;
}
}
frame[mini]=page[i];
time[mini]=count++;
}
pf++; 
printf("F");
}
else
{
printf("H");
}
printf(" %d  ",page[i]);
for(int k =0 ; k< f ; k++)
{
if(frame[k] == -1)
printf(" -");
else
printf(" %d",frame[k]);
}
printf("\n");
}
printf("Page Faults Ratio : %.2f\n", (float)pf / p);
printf("Page Hits Ratio   : %.2f\n", (float)ph / p);
}
