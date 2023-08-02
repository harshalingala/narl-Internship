
#include <stdio.h>
#include <stdlib.h>
struct header
	{
		short int a[50];
		float b[5];
		short int c[5];
		char d[14];
		
	};
int main(){
	int counter;
	FILE *f;
	struct header rec;
	FILE *powspe=fopen("C:\\Users\\Harsha\\Documents\\New\\powspe.dat","w");
   f=fopen("C:\\Users\\Harsha\\Documents\\MuneeswaraiahData.d99","rb");
	if (!f)
	{
		printf("Unable to open file!");
		return 1;
	}
	float pow[600][600],max,m1[150],m0[150],m2[150];
    int i,j,z;
    i=0;
    j=0;
    z=0;
    FILE *fp[30];
    FILE *e;
char fil[100];
	fread(&rec.a,sizeof(short int),46,f);
	fread(&rec.b,sizeof(float),4,f);
	fread(&rec.c,sizeof(short int),3,f);
	fread(&rec.d,sizeof(char),14,f);
	while(!feof(f)){
		z++;
		if(rec.a[30]==2){
			sprintf(fil,"C:\\Users\\Harsha\\Documents\\New\\comparision\\results%d.dat",z);			
			printf("%s\n",fil);
    fp[z] = fopen(fil, "w");
	fp[0]=fp[z];			
		printf("power spectrum:\n");
        for(i=0;i<rec.a[2];i++){
        	m0[i]=0;
        	m1[i]=0;
        	m2[i]=0;
        	for(j=0;j<(rec.a[3]);j++){
        	fread(&pow[i][j],sizeof(float),1,f);
			m0[i]=m0[i]+pow[i][j];
			}
			pow[i][0]=(pow[i][1]+pow[i][rec.a[3]])/2;
			max=pow[i][0];
        	for(j=0;j<(rec.a[3]);j++){
        		if(max<pow[i][j]){max=pow[i][j];}
			}
      	for(j=rec.a[3]/2;j<(rec.a[3]);j++){
      		m1[i]=m1[i]+(j-rec.a[3])*pow[i][j];
      		m2[i]=m2[i]+(j-rec.a[3])*(j-rec.a[3])*pow[i][j];      		
        	fprintf(powspe,"%d	%f	%d\n",j-rec.a[3],(pow[i][j]/max)+i,z);
		    fprintf(fp[0],"%d	%f	%d\n",j-rec.a[3],(pow[i][j]/max)+i,z);	
        	}
			for(j=0;j<(rec.a[3]/2);j++){
				m1[i]=m1[i]+(j*pow[i][j]);
				m2[i]=m2[i]+(j*j*pow[i][j]);
        	fprintf(powspe,"%d	%f	%d\n",j,(pow[i][j]/max)+i,z);
		    fprintf(fp[0],"%d	%f	%d\n",j,(pow[i][j])/max+i,z);	
        	}
        	fprintf(powspe,"\n\n");
	    	fprintf(fp[0],"\n\n");
		}
		for(i=0;i<rec.a[2];i++){
			m1[i]=m1[i]/m0[i];
			fprintf(fp[0],"%f	%d\n",m1[i],i);
		}
		fprintf(fp[0],"\n\n");
	/*	for(i=0;i<rec.a[2];i++){
			m2[i]=(m2[i]/m0[i])-m1[i]*m1[i];
			fprintf(fp[0],"%f	%d\n",m2[i],i);
		}*/
		fclose(fp[z]);
		}
		for(counter=0;counter<=45;counter++){
			printf("%d--%d\n",counter+1,rec.a[counter]);
		}
		for ( counter=0; counter <= 3; counter++)
		{
			printf("%d--%f\n",counter+47,rec.b[counter]);	
		}
		for(counter=0;counter<=2;counter++){
			printf("%d--%d\n",counter+51,rec.c[counter]);
		}
	fread(&rec.a,sizeof(short int),46,f);
	fread(&rec.b,sizeof(float),4,f);
	fread(&rec.c,sizeof(short int),3,f);
	fread(&rec.d,sizeof(char),14,f);					
	}
	printf("%d",z);
	fclose(f);
	fclose(powspe);
	return 0;
}
