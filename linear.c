#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
	int d,a,i;
	FILE *fp;
	FILE *f;
	float val[200],rdis[200],dis[200],x;
	char str[100];
	for(a=0;a<150;a++){
		rdis[a]=3.6+0.15*a;
	}
	for(d=1;d<25;d++){
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\height\\results%d.dat",d);
	fp=fopen(str,"r");
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\linear\\results%d.dat",d);
	f=fopen(str,"w");
	for(a=0;a<150;a++){
	fscanf(fp,"%f",&val[a]);
	fscanf(fp,"%f",&dis[a]);
	}
	for(a=0;a<150;a++){
		i=0;
		while(rdis[a]>dis[i]){i++;
		if(i==149){break;		}
		}
		x=val[i]-(((val[i]-val[i-1])/0.15)*(dis[i]-rdis[a]));
		fprintf(f,"%f	%f\n",x,rdis[a]);
	}
	fclose(fp);
	fclose(f);
	}
	return 1;
}
