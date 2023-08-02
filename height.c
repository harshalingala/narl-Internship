/*this program associates height to each rangebin*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
int main(){
	FILE *fp;
	FILE *f;
	int d,a,b,i,z;
	float deg,val,powspe[200][600],var[200],exp[200];
	char str[100];
	for(d=1;d<25;d++){
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\smooth\\results%d.dat",d);//input file
	fp=fopen(str,"r");
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\height\\results%d.dat",d);//output file
	f=fopen(str,"w");
	if(d%6==3||d%6==4){deg=0;}
	else{deg=PI/18;}
	for(a=0;a<150;a++){
	for(b=0;b<512;b++){
	fscanf(fp,"%d",&i);
	fscanf(fp,"%f",&val);
	fscanf(fp,"%d",&z);
    powspe[a][b]=val; 
	}
	}
	for(a=0;a<150;a++){
	fscanf(fp,"%f",&val);
	fprintf(f,"%f	",val);
	fscanf(fp,"%d",&i);
	val=(3.6+0.15*i)*cos(deg);
	fprintf(f,"%f\n",val);
	}
	fclose(fp);
	fclose(f);}
	return 1;
}
