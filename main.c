#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main(int argc,char* argv[]){
 FILE *fpi,*fpo;
 int k,natm;
 char ax[2];
 double theta[3],value;
 for(k=0;k<3;k++)theta[k]=0.0;
 
 if((fpi=fopen("angle.in","r"))==NULL){puts("No angle.in");exit(1);}
 while(fscanf(fpi,"%s %lf",ax,&value)!=EOF){
  if(!strcmp(ax,"x"))theta[0]=value;
  else if(!strcmp(ax,"y"))theta[1]=value;
  else if(!strcmp(ax,"z"))theta[2]=value;
  else{printf("Err:What is %s ?\n",ax);exit(1);}
 }
 fclose(fpi);

 {
  char buf[256];
  int iline=0;
  if((fpi=fopen(argv[1],"r"))==NULL){printf("No %s\n",argv[1]);exit(1);}
   while(fgets(buf,256,fpi) != NULL)iline++;
  natm=iline;
 }
 rewind(fpi);

 {
  int iatm=0;
  char elem[natm][3];
  double r[natm*3],rr[natm*3],sum;
  while(fscanf(fpi,"%s %lf %lf %lf",elem[iatm],&r[iatm*3],&r[iatm*3+1],&r[iatm*3+2])!=EOF)iatm++;
  fclose(fpi);

  for(k=0;k<3;k++){
   sum=0.0;
   for(iatm=0;iatm<natm;iatm++)sum+=r[iatm*3+k];
   for(iatm=0;iatm<natm;iatm++)r[iatm*3+k]-=sum/natm;
  }
  
  //fpo=fopen("debug.xyz","w");
  //for(iatm=0;iatm<natm;iatm++)fprintf(fpo,"%s\t%8.3f\t%8.3f\t%8.3f\n",elem[iatm],r[iatm*3],r[iatm*3+1],r[iatm*3+2]);
  //fclose(fpo);

  fpo=fopen("out.xyz","w");
  for(iatm=0;iatm<natm;iatm++){
   rr[iatm*3+1]=cos(theta[0])*r[iatm*3+1]-sin(theta[0])*r[iatm*3+2];
   rr[iatm*3+2]=sin(theta[0])*r[iatm*3+1]+cos(theta[0])*r[iatm*3+2];
   r[iatm*3+1]=rr[iatm*3+1];r[iatm*3+2]=rr[iatm*3+2];
   
   rr[iatm*3+2]=cos(theta[1])*r[iatm*3+2]-sin(theta[1])*r[iatm*3];
   rr[iatm*3]  =sin(theta[1])*r[iatm*3+2]+cos(theta[1])*r[iatm*3];
   r[iatm*3]=rr[iatm*3];r[iatm*3+2]=rr[iatm*3+2];
   
   rr[iatm*3]  =cos(theta[2])*r[iatm*3]-sin(theta[2])*r[iatm*3+1];
   rr[iatm*3+1]=sin(theta[2])*r[iatm*3]+cos(theta[2])*r[iatm*3+1];
   r[iatm*3]=rr[iatm*3];r[iatm*3+1]=rr[iatm*3+1];

   fprintf(fpo,"%2s\t%8.3f\t%8.3f\t%8.3f\n",elem[iatm],r[iatm*3],r[iatm*3+1],r[iatm*3+2]);
  }
  fclose(fpo);
 }
 return 0;
}
