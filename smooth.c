/*this reads input and performs 5 point smoothing on it*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define no_of_beams 24
#define no_of_fft 512
int main(){
	FILE *fp;
	FILE *f;
	int d,a,b,i,z;
	char str[100];
	float powspe[200][600],s,val,smo[200][600],m0[200],m1[200],m2[200];
	for(d=1;d<=no_of_beams;d++){
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\comparision\\results%d.dat",d);//input file
	fp=fopen(str,"r");
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\smooth\\results%d.dat",d);//output file
	f=fopen(str,"w");
	printf("%s\n",str);
	for(a=0;a<150;a++){
	for(b=0;b<no_of_fft;b++){
	fscanf(fp,"%d",&i);
	fscanf(fp,"%f",&val);
	fscanf(fp,"%d",&z);
    powspe[a][b]=val; 
	}
	}
		i=no_of_fft/2;
	for(a=0;a<150;a++){
		m0[a]=m1[a]=m2[a]=0;
		smo[a][0]=powspe[a][0];
		smo[a][1]=powspe[a][1];
		for(b=2;b<no_of_fft-2;b++){
			s=powspe[a][b-2]+powspe[a][b-1]+powspe[a][b]+powspe[a][b+1]+powspe[a][b+2];
			smo[a][b]=s/5;
	}
		smo[a][no_of_fft-2]=powspe[a][no_of_fft-2];
		smo[a][no_of_fft-1]=powspe[a][no_of_fft-1];
		for(b=0;b<no_of_fft;b++){
			fprintf(f,"%d	%f\n",b-no_of_fft/2,smo[a][b]+a);
		}
		fprintf(f,"\n\n");
		}
	
	i=no_of_fft/2;
	for(a=0;a<150;a++){
		m0[a]=0;
		m1[a]=0;
		for(b=i-50;b<i+50;b++){
			m0[a]=m0[a]+(smo[a][b]);
			m1[a]=m1[a]+(b-no_of_fft/2)*(smo[a][b]);
			m2[a]=m2[a]+(b-no_of_fft/2)*(b-no_of_fft/2)*(smo[a][b]);
		}
		m1[a]=m1[a]/m0[a];
		m2[a]=(m2[a]/m0[a])-m1[a]*m1[a];
		printf("variance of %d:%f\n",a,sqrt(m2[a]));
		fprintf(f,"%f	%d\n",m1[a],a);
	    i=m1[a]+no_of_fft/2;
	}//above loop caluclates expectation and variance
	fprintf(f,"\n\n");
	for(a=0;a<150;a++){
		fprintf(f,"%d	%d	%f	%d\n",0,0,m1[a]-sqrt(m2[a]),a);
		fprintf(f,"%d	%d	%f	%d\n",0,0,m1[a]+sqrt(m2[a]),a);
		fprintf(f,"\n\n");
	}
		printf("%d\n",d);
		fclose(fp);
		fclose(f);
		}
	return 1;
}
