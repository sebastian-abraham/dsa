/*Sejith R Nath
51 CS-B
BANKERS ALGORITHM*/
#include <stdio.h>
int main() {
 int n, m, i, j, k;
 printf("Enter the number of processes: ");
 scanf("%d", &n);
 printf("Enter the number of resources: ");
 scanf("%d", &m);
int alloc[n][m], max[n][m], need[n][m], avail[m], f[n], ans[n];
 int ind = 0;

 printf("Enter the allocation matrix:\n");
 for(i = 0; i < n; i++)
  for(j = 0; j < m; j++)
   scanf("%d", &alloc[i][j]);

 printf("Enter the maximum matrix:\n");
 for(i = 0; i < n; i++)
  for(j = 0; j < m; j++)
   scanf("%d", &max[i][j]);

 printf("Enter the available resources:\n");
 for(j = 0; j < m; j++)
  scanf("%d", &avail[j]);

 for(i = 0; i < n; i++)
  for(j = 0; j < m; j++)
   need[i][j] = max[i][j] - alloc[i][j];

 printf("Need Matrix:\n");
 for(i = 0; i < n; i++) {
  for(j = 0; j < m; j++)
   printf("%d ", need[i][j]);
  printf("\n");
 }

 for(k = 0; k < n; k++) f[k] = 0;
for(k = 0; k < n; k++) {
  for(i = 0; i < n; i++) {
   if(f[i] == 0) {
    int flag = 0;
    for(j = 0; j < m; j++) {
     if(need[i][j] > avail[j]) {
      flag = 1;
      break;
     }
    }
    if(flag == 0) {
     ans[ind++] = i;
     for(j = 0; j < m; j++) avail[j] += alloc[i][j];
     f[i] = 1;
    }
   }
  }
 }
 int flag = 1;
 for(i = 0; i < n; i++) {
  if(f[i] == 0) {
   flag = 0;
   printf("The following system is not safe.\n");
   break;
  }
 }
 if(flag == 1) {
  printf("The following system is safe.\n");
  printf("Safe sequence: ");
  for(i = 0; i < n; i++) printf("P%d ", ans[i]);
  printf("\n");
 }
 return 0;}

