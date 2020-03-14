#include <stdio.h>
#include <string.h>
int getnum_char(char f[]);
int getnum_row(char f[]);
int getnum_word(char f[]);
int getnum_zhushirow(char f[]);
int getnum_null(char f[]);
int main(int i,char *argv[]){
	if(i!=3)
	printf("命令错误");
	else{
	if(strcmp("-c",argv[1])==0){
	printf("打印文件字符数"); 
	printf("%s文件中的字符数为%d\n",argv[1], getnum_char(argv[2]));	
	} 
	if(strcmp("-w",argv[1])==0)
	{
		printf("单词数为%d\n",getnum_word(argv[2])); 
	}
	if(strcmp("-l",argv[1])==0){
	printf("%s文件中的行数为%d\n",argv[2],getnum_row(argv[2]));
	}
	if(strcmp("-a",argv[1])==0){
    int total,zs,kh,dm; 
    total = getnum_row(argv[2]);
    zs = getnum_zhushirow(argv[2]);
    kh = getnum_null(argv[2]);
    dm = total - zs -kh;
	printf("文件中的总行为%d\n",total);
	printf("文件中的注释行为%d\n",zs);
	printf("文件中的空行为%d\n",kh) ;
	printf("文件中的代码行为%d\n",dm) ;
	}
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
	}
	int g = 0;
	if(getnum_word(f)>0){
	num++;
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
			flag = true;//读入第一个/ 		 
		}
		if(flag&&j){  //读入第二行 
			if(ch == '*'){ //多段注释
				duanzhushi = true;
			}
			if(ch == '/'){//单行注释 
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
	return num;
}


int getnum_null(char f[]){
	int num=0;
	FILE *fp;
	fp = fopen(f,"r");
	char a[100]={};
	while(!feof(fp)){
	fgets(a,100,fp);
	if(a[0]=='\n')
	num++;
	}
	return num;		
}	

