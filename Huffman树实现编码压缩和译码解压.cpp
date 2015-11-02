# C-C-data-structure
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define max 1000
#define N 100000
using namespace std;
//结构体定义
typedef struct{
  unsigned int weight;
  unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char* *HuffmanCode;
int Countweight[max];
int TotalNumber;
char CountChar[max];
char Dic[max][max];
char step[N];
char step2[N];
//给HuffmanTree的各节点加权
void CountWeight(int &n);
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);
void Select(HuffmanTree HT,int n,int &s1,int &s2);
void CreateDic(HuffmanCode HC,int n);
void SaveDic(HuffmanCode HC,int n);
void Encode();
void Discode();
void Lastnumber();
void translate();
//各函数实现
void Select(HuffmanTree HT,int n,int &s1,int &s2){
    HT[0].weight=100;
    s1=0;s2=0;
    for(int i=1;i<n;++i)
     if(HT[i].parent==0)
      {
          if(HT[i].weight<HT[s2].weight)
                 {
                    if(HT[s2].weight<HT[s1].weight) s1=s2;
                      s2=i;}
                     else if(HT[i].weight<HT[s1].weight)
                          {s1=s2;s2=i;}
}
        int i; if(s1==0) {s1=s2+1;i=s1;s1=s2;s2=i;}
}
void CountWeight(int &n){
       FILE *fp;  char step;
       int i=0; int k=0;
       for(i=0;i<max;i++) Countweight[i]=0;
        fp=fopen("test.txt","r");
        while(step!=EOF){
        step=getc(fp);
        TotalNumber++;
        int judge=0;
        for(i=0;CountChar[i]!='\0';i++){
            if(CountChar[i]==step){Countweight[i]+=1;judge=1;}
        }
        if(judge==0){CountChar[strlen(CountChar)]=step;Countweight[strlen(CountChar)]++;}
       }
        Countweight[i]=0;  Countweight[0]+=1;   TotalNumber-=1;

        n=i;fclose(fp);
        }
 void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n){
     HuffmanTree p;
     char* cd=NULL;
     int m,i,s1,s2;
     if(n<1) return;
     m=2*n-1;
     HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
     for(i=1;i<=n;++i,++w)  {HT[i].weight=*w;HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;}

     for(;i<=m;++i) {HT[i].weight=0;HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;}


     for(i=n+1;i<=m;++i){
        Select(HT,i-1,s1,s2);//选择parent为0且weight最小的两个节点，其序号S1,S2

        HT[s1].parent=i;  HT[s2].parent=i;
        HT[i].lchild=s1;  HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;

        }


      HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
      cd=(char *)malloc(n*sizeof(char));
      cd[n-1]='\0';
      int start,c,f;
      for(i=1;i<=n;++i){
        start=n-1;
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
            if(HT[f].lchild==c) cd[--start]='0';
          else cd[--start]='1';
        HC[i]=(char *) malloc((n-start)*sizeof(char));
        strcpy(HC[i],&cd[start]);

      }
      free(cd);
 }
 void CreateDic(HuffmanCode HC,int n){
     for(int i=0,j=1;i<n;i++,j++)
        strcpy(Dic[CountChar[i]],HC[j]);
 }
 void SaveDic(HuffmanCode HC,int n){//字典1存放字母表，字典2存放n和对应编码;
      FILE *fp=fopen("DIC.txt","wb");
      for(int i=0;i<n;i++){
        fwrite(&CountChar[i],sizeof(char),1,fp);

      }
      fclose(fp);
      FILE *fp2=fopen("DIC2.txt","w+");
      fprintf(fp2,"%d\n",n);
      for(int i=1;i<n+1;i++) fprintf(fp2,"%s\n",HC[i]);
      fclose(fp2);
       fp2=fopen("test.txt","r");char c;int num=0;
        while(c!=EOF){
        c=getc(fp2);num++;

     }
     num=16-(num%16);
        FILE * fp3=fopen("SaveLast.txt","w+");
                fprintf(fp3,"%d",num);
                fclose(fp3);
}
 void Encode(){
      char c;  char add[2]; \
      add[0]='1';
      FILE *fp,*fp2; int Ctest_number;int n;
      fp=fopen("test.txt","r");
      fp2=fopen("test2.txt","wb");
      while(c!=EOF){
        c=getc(fp);
         strcat(step,Dic[c]);
     }

       Ctest_number=strlen(step);

       for(int i=0;i<(16-(Ctest_number)%16);i++){
                strcat(step,add);}//给step串补0


       char CharChange[16];
       for(int i=0;step[i]!='\0';){
         for(int i=0;i<16;i++)  CharChange[i]='\0';
         if((i%16)==0) for(int j=0;j<16;j++)  CharChange[j]=step[i++];

          if(strlen(CharChange)==17){

            int num=0;
          for(int i=0;i<15;i++){
              num+=(CharChange[i]-48)*pow(2,16-(i+1));

          }  if(CharChange[15]-48==1) num=num+1;
           fwrite(&num,sizeof(int),1,fp2);
          }
       }
         fclose(fp);
         fclose(fp2);int num;
      fp2=fopen("test2.txt","rb");while(!feof(fp2)){fread(&num,sizeof(int),1,fp2);}
     //    fp2=fopen("test2.txt","rb");
     //检验是否压缩成功
     //while(!feof(fp2)){fread(&num,sizeof(int),1,fp2); cout<<num<<" ";}
}
void Discode(){
    int i,k; char x[20]; char Lcatch[2]; Lcatch[0]='0';
   FILE*  fp2=fopen("test2.txt","rb");
    int n;
  while(!feof(fp2)){

        fread(&n,sizeof(int),1,fp2);

        for(int i=0;x[i]!='\0';i++ ) x[i]='\0';
        itoa(n,x,2);// x[16]='\0';
         int  add;
         add=16-strlen(x);
         for(i=0;i<add;i++) strcat(step2,Lcatch);
         strcat(step2,x);

}
fclose(fp2);
}
void Lastnumber(){
    FILE *fp=fopen("test2.txt","rb");
    int n;
    while(!feof(fp)){fread(&n,sizeof(int),1,fp);}
    char x[16];
    itoa(n,x,2);
  for(int i=strlen(x)-1,j=strlen(step2)-1;i>0;i--,j--) if(x[i]==step2[j]) step2[j]='\0';

for(int i=strlen(step2)-1,j=0;j<(strlen(step2)%16)+1;i--,j++) step2[i]='\0';
     fclose(fp);

}
void translate(){
    char key[max];
   char KEY[max][max];
    FILE * fp=fopen("DIC.txt","rb");

    for(int i=0;!feof(fp);i++){fread(&key[i],sizeof(char),1,fp);}


    fclose(fp);
      FILE * fp2=fopen("DIC2.txt","r");
    int  n;
    fscanf(fp2,"%d\n",&n);
    for(int i=0;i<n;i++){
        fscanf(fp2,"%s",&KEY[i]);
    }
     char compare[max];
     int i;
     FILE *fp5=fopen("SaveLast.txt","r");
     int o;  fscanf(fp5,"%d",&o);  fclose(fp5);
     o=o+2;
     for(int i=0,j=strlen(step2);i<o;i++,j--) step2[j]='\0';
     fp5=fopen("backtest.txt","w");
     for( i=0;i<=strlen(step2);){
        if(i>=strlen(step2)-2) break;
        for(int k=0;k<n;k++){
        for(int j=0;compare[j]!='\0';j++) compare[j]='\0';
        for(int m=0;m<strlen(KEY[k]);m++) compare[m]=step2[i+m];
            for(int l=0;l<n;l++){
                if(strcmp(KEY[l],compare)==0)
               {

                 putc(key[l],fp5);
                 i=i+strlen(KEY[l]);
                 break;}
            }
        }

     }

   fclose(fp5);
}
int main()
{    int n;
    HuffmanTree HT;
    HuffmanCode HC;
    CountWeight(n);
    HuffmanCoding(HT,HC,Countweight,n);
     SaveDic(HC,n);
    CreateDic(HC,n);
    Encode();
//    将Huffman树和解压的信息放在字典里
   //前面为压缩，后面为解压部分
    Discode();
    Lastnumber();
   translate();
    return 0;
}
