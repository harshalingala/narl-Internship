/*this program performs incoherent integration on input*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NB 6
#define NT 4
#define no_of_beams 24
#define no_of_fft 512
int main(){
	FILE *f,*fp[10];
	int i,j,a,b,z,d,di;
	char str[100];
	float tem,temp,powspe[200][600],m0[200],m1[200],m2[200];
	for (i=0;i<NB;i++){
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\ran\\results%d.dat",i+1);	//output file	
	f=fopen(str,"w");
	for(a=0;a<NT;a++){
		sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\results%d.dat",i+NB*a+1);//input files
		fp[a+1]=fopen(str,"r");
	}
	for(a=0;a<150;a++){
	for(b=0;b<no_of_fft;b++){
		powspe[a][b]=0;
	for(d=0;d<NT;d++){
	fscanf(fp[d+1],"%d",&di);
	fscanf(fp[d+1],"%f",&temp);
	powspe[a][b]=powspe[a][b]+temp-a;
	}
	powspe[a][b]=powspe[a][b]/NT;
	fprintf(f,"%d	%f\n",di,powspe[a][b]+a);
	}
	fprintf(f,"\n\n");
	}
	z=no_of_fft/2;
	for(a=0;a<150;a++){
		m0[a]=0;
		m1[a]=0;
		m2[a]=0;
	for(b=z-30;b<z+30;b++){
	m0[a]=m0[a]+powspe[a][b];
	m1[a]=m1[a]+(b-no_of_fft/2)*powspe[a][b];
	m2[a]=m2[a]+(b-no_of_fft/2)*(b-no_of_fft/2)*powspe[a][b];
	}//caluclates expectation and variance
	m1[a]=m1[a]/m0[a];
	m2[a]=(m2[a]/m0[a])-(m1[a]*m1[a]);
	z=m1[a]+no_of_fft/2;
		fprintf(f,"%f	%d\n",m1[a],a);
	}
	fclose(f);
		for(a=0;a<4;a++){
		fclose(fp[a+1]);
	}
	}
}
