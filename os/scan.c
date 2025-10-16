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







/*Sejith R Nath
51 CS-B
CSCAN*/
#include <stdio.h>

void main() {
    int n, queue[20], dh, tdh, thm = 0, s, l = 0, r = 0, right[10], left[10];

    printf("Enter the number of requests : ");
    scanf("%d", &n);

    printf("Enter the requests : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the current position of disk head : ");
    scanf("%d", &dh);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j + 1] < queue[j]) {
                int t = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (queue[i] >= dh) {
            right[r++] = queue[i];
        } else {
            left[l++] = queue[i];
        }
    }

    printf("Enter the disk size : ");
    scanf("%d", &s);

    printf("Enter the direction \n1. Right to Left\n2. Left to Right : ");
    int direc;
    scanf("%d", &direc);

    tdh = dh;

    if (direc == 1) {
        for (int i = l - 1; i >= 0; i--) {
            printf("\n%d :\t%d--->%d", left[i], dh, left[i]);
            dh = left[i];
        }
        if (dh != 0) {
            printf("\n  \t%d--->0", dh);
            dh = 0;
        }
        printf("\n  \t%d--->%d", dh, s - 1);
        dh = s - 1;
        for (int i = r - 1; i >= 0; i--) {
            printf("\n%d :\t%d--->%d", right[i], dh, right[i]);
            dh = right[i];
        }
        thm = tdh;
        if (r - 1 != -1) {
            thm += s - 1;
            thm += (s - 1 - right[0]);
        }
    } else {
        for (int i = 0; i < r; i++) {
            printf("\n%d :\t%d--->%d", right[i], dh, right[i]);
            dh = right[i];
        }
        if (dh != s - 1) {
            printf("\n  \t%d--->%d", dh, s - 1);
            dh = s - 1;
        }
        printf("\n  \t%d--->0", dh);
        dh = 0;
        for (int i = 0; i < l; i++) {
            printf("\n%d :\t%d--->%d", left[i], dh, left[i]);
            dh = left[i];
        }
        thm = (s - 1 - tdh);
        if (l - 1 != -1) thm += (s - 1 + left[l - 1]);
    }

    printf("\nTotal head movements : %d\n", thm);
}
