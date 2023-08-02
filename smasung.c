#include<stdio.h>
#include<string.h>
int main(){
	char a[20],c[20];
	sprintf(c,"dfs");
	sprintf(a,"asdg");
	strcat(a,c);
	printf("%s",a);
	return 1;
}
