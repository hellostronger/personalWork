#include <stdio.h>
#include <string.h>
int getnum_char(char f[]);
int getnum_row(char f[]);
int getnum_word(char f[]);
int getnum_zhushirow(char f[]);
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
	printf("\n");
	printf("������Ϊ%d\n",getnum_word(argv[2])); 
	
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
		bool flag = true;
		int  ch;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			if(ch>='a'&&ch<='z'||ch<='Z'&&ch>='A'){
				if(flag==true){
					num++;
					flag = false;
				}	
			}else{
					flag = true;
				}
		}
        return num;
} 

int getnum_zhushirow(char f[]){
	  FILE *fp;
	  bool flag = true;
		int  ch;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			if(ch>='a'&&ch<='z'||ch<='Z'&&ch>='A'){
				if(flag==true){
					num++;
					flag = false;
				}	
			}else{
					flag = true;
				}
		}
        return num;
    }
    
    
int getnum_zhushirow(char f[]){
	bool tag = true;
		bool j = false;
		bool end_tag = false;
		FILE *fp;
		int  ch;
		bool flag = false;
		bool duanzhushi = false; 
		bool hangzhushi = false;
		int num = 0;
		fp = fopen(f,"r");
		while((ch=getc(fp))!=EOF){
			if(ch=='/'&&(!duanzhushi||!hangzhushi)){
				flag = true;//�����һ��/ 		 
		}
		if(flag&&j){  //����ڶ��� 
					if(ch == '*'){ //���ע��
						duanzhushi = true;
					}if(ch == '/'){//����ע�� 
						hangzhushi = true;
					}
					
				}
		
		if(duanzhushi){
			if(ch =='\n'){
			num++;	
			printf("%d\n",num);
			}
		}
		if(hangzhushi){
			if(ch =='\n'){
				num++;
				hangzhushi=false;
				flag = false;
				j = false;	
			}
			printf("%d666\n",num);
				}
		if(ch == '*'&&duanzhushi){
			end_tag = true;
		}
		if(ch == '/'&&end_tag){
			duanzhushi = false;
			end_tag = false;
			flag = false;
			j = false; 
		}	
		if (flag == true)
		j = true;	
	}
	printf("�ļ���%d��ע��",num); 
}
	


