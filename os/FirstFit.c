/*Sebastian Abraham
49 CS-B
CSCAN*/
#include <stdio.h>
void main() {
 int n, queue[20], dh, tdh, thm = 0, s, l = 0,
r = 0, right[10], left[10];
 printf("Enter the number of requests : ");
 scanf("%d", &n);
 printf("Enter the requests : ");
 for (int i = 0; i < n; i++) {
 scanf("%d", &queue[i]);
 }
 printf("Enter the current position of disk
head : ");
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
 printf("Enter the direction \n1. Right to
Left\n2. Left to Right : ");
 int direc;
 scanf("%d", &direc);
 tdh = dh;
 if (direc == 1) {
 for (int i = l - 1; i >= 0; i--) {
 printf("\n%d :\t%d--->%d", left[i],
dh, left[i]);
 dh = left[i];
 }
 if (dh != 0) {
 printf("\n \t%d--->0", dh);
 dh = 0;
 }
 printf("\n \t%d--->%d", dh, s - 1);
 dh = s - 1;
 for (int i = r - 1; i >= 0; i--) {
 printf("\n%d :\t%d--->%d", right[i],
dh, right[i]);
 dh = right[i];
 }
 thm = tdh;
 if (r - 1 != -1) {
 thm += s - 1;
 thm += (s - 1 - right[0]);
 }
 } else {
 for (int i = 0; i < r; i++) {
 printf("\n%d :\t%d--->%d", right[i],
dh, right[i]);
 dh = right[i];
 }
 if (dh != s - 1) {
 printf("\n \t%d--->%d", dh, s - 1);
 dh = s - 1;
 }
 printf("\n \t%d--->0", dh);
 dh = 0;
 for (int i = 0; i < l; i++) {
 printf("\n%d :\t%d--->%d", left[i],
dh, left[i]);
 dh = left[i];
 }
 thm = (s - 1 - tdh);
 if (l - 1 != -1) thm += (s - 1 + left[l -
1]);
 }
 printf("\nTotal head movements : %d\n",
thm);
}