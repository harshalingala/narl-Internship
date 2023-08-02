/*this program u v w of wind at different heights*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
int main()
{
	float powspe[20][200],dis[200],val,di,u,v,w;
	FILE *fp,*f,*n;
	int i,j,a,d,z;
	char str[100];
	for(d=1;d<25;d++){
		sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\linear\\results%d.dat",d);//input file of one beam
		fp=fopen(str,"r");
		d++;
		sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\linear\\results%d.dat",d);//input file of opposite beam
		f=fopen(str,"r");
		for(a=0;a<150;a++){
			fscanf(f,"%f",&val);
			fscanf(fp,"%f",&di);
			powspe[d/2][a]=(val-di)/2;
			fscanf(f,"%f",&val);
			fscanf(fp,"%f",&di);
			dis[a]=di;	
		}
		fclose(fp);
		fclose(f);
	}
	for(i=0;i<4;i++){
		sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\velocity\\results%d.dat",i+1);//output file
		n=fopen(str,"w");
		for(a=0;a<150;a++){
			di=dis[a];
			w=powspe[3*i+2][a];
			u=powspe[3*i+1][a];
            u=(u-w*cos(PI/18))/(sin(PI/18));
			v=powspe[3*i+3][a];
			v=(v-w*cos(PI/18))/(sin(PI/18));	
			fprintf(n,"%f	%f	%f	%f	%f\n",u/11,v/11,w/11,sqrt(u*u+v*v+w*w)/11,di);//prints u,v,w,speed,height in the output file 
		}
		fclose(n);
	}
	return 1;
}
