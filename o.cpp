#include <stdio.h>
#include <string.h>
int getnum_char(char f[]);
int getnum_row(char f[]);
int main(int i,char *argv[]){
	printf("%d",i);
	if(i!=3)
	printf("�������");
	else{
	for(int k=0;k<=i;k++){
		printf("%s\n",argv[k]);
	}
	if(strcmp("-c",argv[1])==0){
	printf("��ӡ�ļ��ַ���"); 
	int g = 0;
	for(int j=0;j<=i;j++) 
	printf("%s",argv[j]);
	g = getnum_char(argv[2]);
	printf("%s�ļ��е��ַ���Ϊ%d\n",argv[1], g);	
	} 
	printf("%s�ļ��е�����Ϊ%d",argv[1],  getnum_row(argv[2])+1);
	return 0;
	
	}
} 
int getnum_char(char f[]){
		FILE *fp;
		int ch;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			num++;
			printf("%c",ch);
		}
        return num;
	}
	
int getnum_row(char f[]){
		FILE *fp;
		int  ch;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			if((char)ch=='\n')
			num++;
			printf("%c",ch);
		}
        return num;
} 

int getnum_word(char f[]){
		FILE *fp;
		int  ch;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			if((char)ch=='\n')
			num++;
			printf("%c",ch);
		}
        return num;
        666 
} 
