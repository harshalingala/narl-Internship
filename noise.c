/*thisprogram uses Hildebrand & Sekhon methood to remove noise from signal*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define no_of_beams 24
#define no_of_fft 512
int main(){
	FILE *fp;
	FILE *f;
	FILE *n;
	float val,thre[150];
	int i,z,d;
	int a,b,c;
	float m1,m2;
	float powspe[200][600],noise[600],smo[200];
	float p,q,exp[150];
	char str[100];
	for(d=1;d<no_of_beams+1;d++){
		sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\results%d.dat",d);//input file
	fp=fopen(str,"r");
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\comparision\\results%d.dat",d);//destination file
	f=fopen(str,"w");
	sprintf(str,"C:\\Users\\Harsha\\Documents\\New\\noise\\results%d.dat",d);//destination file of noise
	n=fopen(str,"w");
	c=0;
	for(a=0;a<150;a++){
	for(b=0;b<no_of_fft;b++){
	fscanf(fp,"%d",&i);
	fscanf(fp,"%f",&val);
    powspe[a][b]=val-a; 
	}
	}
	for(a=0;a<150;a++){
		thre[a]=0.5;
		while(thre[a]>0){//loop runs to find threshold
		val=0;
		c=0;
		for(b=0;b<no_of_fft;b++){
		if(powspe[a][b]<thre[a]){noise[c]=powspe[a][b];
		c++;}	
		}
		for(b=0;b<c;b++){
			val=val+noise[b];
		}
		m1=0;
		for(b=0;b<c;b++){
			m1=m1+b*noise[b];
		}
		m1=m1/val;
		m2=0;
		for(b=0;b<c;b++){
			m2=m2+b*b*noise[b];
		}
		m2=(m2/val)-(m1*m1);
		if((m2/(c*c/12))>0.998&&(m2/(c*c/12))<1.002){break;}//if white condition is checked loop breaks
		thre[a]=thre[a]-0.000001;//decreases threshold for next loop
	}
	printf("%d  %f\n",a,thre[a]);	
	for(b=0;b<no_of_fft;b++){
	    if(powspe[a][b]<=thre[a]){fprintf(n,"%d	%f\n",b-no_of_fft/2,powspe[a][b]+a);
		powspe[a][b]=0;}//removes noise from signal
	    else{fprintf(n,"%d	%f\n",b-no_of_fft/2,thre[a]+a);
		powspe[a][b]=powspe[a][b]-thre[a];}
	    fprintf(f,"%d	%f\n",b-no_of_fft/2,powspe[a][b]+a);
	}
	fprintf(f,"\n\n");
	fprintf(n,"\n\n");
	}
	i=no_of_fft/2;
	for(a=0;a<150;a++){
		thre[a]=0;
		exp[a]=0;
		for(b=i-70;b<i+70;b++){
			thre[a]=thre[a]+powspe[a][b];
			exp[a]=exp[a]+(b-no_of_fft/2)*powspe[a][b];
			smo[a]=smo[a]+(b-no_of_fft/2)*(b-no_of_fft/2)*powspe[a][b];
		}
		exp[a]=exp[a]/thre[a];
		smo[a]=(smo[a]/thre[a])-exp[a]*exp[a];
		printf("variance of %d:%f\n",a,smo[a]);
		fprintf(f,"%f	%d\n",exp[a],a);
	    i=exp[a]+no_of_fft/2;
	}
	fclose(fp);
	fclose(f);
	fclose(n);
    printf("%d\n",d);
}
	return 1;
}
