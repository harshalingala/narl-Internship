/*this program reads binary data file and writes in destination file*/
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
	FILE *f,*n;
	struct header rec;	
	   f=fopen("C:\\Users\\Harsha\\Documents\\MuneeswaraiahData.d99","rb");//inputfile
	if (!f)
	{
		printf("Unable to open file!");
		return 1;
	}
	float pow[600][600],max,exp,den,tem,temp;
    int i,j,z,ty[25];
    i=0;
    j=0;
    z=0;
    FILE *fp[30];
char fil[20];
	fread(&rec.a,sizeof(short int),46,f);
	fread(&rec.b,sizeof(float),4,f);
	fread(&rec.c,sizeof(short int),3,f);
	fread(&rec.d,sizeof(char),14,f);//reads 128 bit header
	while(!feof(f)){//lop runs till end of file is reached
         z++;
         		ty[z]=rec.a[21];
			sprintf(fil,"C:\\Users\\Harsha\\Documents\\New\\results%d.dat",z);//destination file
			printf("%s\n",fil);
    fp[z] = fopen(fil, "w");
	fp[0]=fp[z];			
		printf("power spectrum:\n");
        for(i=0;i<rec.a[2];i++){
        	den=0;
        	exp=0;
        	for(j=0;j<(rec.a[3]);j++){
        	fread(&tem,sizeof(float),1,f);
        	pow[i][j]=tem;
        	if(pow[i][j]<0){pow[i][j]=0;	}
			den=den+pow[i][j];
			}
			pow[i][0]=(pow[i][1]+pow[i][rec.a[3]])/2;//removes clutter
			max=pow[i][0];
        	for(j=0;j<(rec.a[3]);j++){
        		if(max<pow[i][j]){max=pow[i][j];}
			}
      	for(j=rec.a[3]/2;j<(rec.a[3]);j++){
      		exp=exp+(j-rec.a[3])*pow[i][j];
		    fprintf(fp[0],"%d	%f\n",j-rec.a[3],(pow[i][j]/max)+i,z);	
        	}
			for(j=0;j<(rec.a[3]/2);j++){
				exp=exp+(j*pow[i][j]);
		    fprintf(fp[0],"%d	%f\n",j,(pow[i][j])/max+i,z);	
        	}
	    	fprintf(fp[0],"\n\n");
		}
	    fclose(fp[z]);
		for(counter=0;counter<=45;counter++){
			printf("%d--%d\n",counter+1,rec.a[counter]);
		}
		for ( counter=0; counter <= 3; counter++)
		{
			printf("%d--%f\n",counter+47,rec.b[counter]);	
		}
		for(counter=0;counter<=2;counter++){
			printf("%d--%d\n",counter+51,rec.c[counter]);
		}//prints header
	fread(&rec.a,sizeof(short int),46,f);
	fread(&rec.b,sizeof(float),4,f);
	fread(&rec.c,sizeof(short int),3,f);
	fread(&rec.d,sizeof(char),14,f);			//reads next header
	}
	printf("%d\n",z);
	for(i=1;i<=z;i++){printf("%d---%d\n",i,ty[i]);	}
	fclose(f);
	return 0;
}
