#include <stdio.h>
#include <string.h>
#include <io.h>
#include <string.h> 
#include <ctype.h>
#include <stdlib.h>
int delet(char f[]);
void search(char *path);
int getnum_char(char f[]);
int getnum_row(char f[]);
int getnum_word(char f[]);
int getnum_zhushirow(char f[]);
int getnum_null(char f[]);
void  allinformation(char f[]);
int main(int i,char *argv[]){
	if(i!=3&&i!=2)
	printf("命令错误,格式wc.exe [parameter] [file_name]\n您可输入wc.exe -h 查看相关参数和帮助");
	if(i == 2&&strcmp("-h",argv[1])==0){
		printf(" -w 返回文件词的数目\n -c 返回文件字符数\n -l 返回文件的行数 \n -s 递归处理目录下符合条件的.c文件\n -a 返回文件详细信息"); 
	}

	else if(i == 3){
	if(strcmp("-c",argv[1])==0){ 
	printf("%s文件中的字符数为%d\n",argv[2], getnum_char(argv[2]));	
	} 
	if(strcmp("-w",argv[1])==0)
	{
		printf("%s文件中单词数为%d\n",argv[2],getnum_word(argv[2])); 
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
	printf("%s文件中的总行为%d\n",argv[2],total);
	printf("文件中的注释行为%d\n",zs);
	printf("文件中的空行为%d\n",kh) ;
	printf("文件中的代码行为%d\n",dm) ;
	}
	if(strcmp("-s",argv[1])==0){
		int i = 0;
		char a[30] = {};
		while(argv[2][i]!='.'&&argv[2][i+1] != 'c'){
			a[i] = argv[2][i];
			i++;
		}
		search(a);
	}
	return 0;
	}
} 

void  allinformation(char f[]){//文件的更多注释 
	int total,zs,kh,dm;  
	printf("%s文件中的字符数为%d\n",f, getnum_char(f));	
	printf("文件中单词数为%d\n",getnum_word(f)); 
	printf("文件中的行数为%d\n",getnum_row(f));
    total = getnum_row(f);
    zs = getnum_zhushirow(f);
    kh = getnum_null(f);
    dm = total - zs -kh;
    
	printf("文件中的总行为%d\n",total);
	printf("文件中的注释行为%d\n",zs);
	printf("文件中的空行为%d\n",kh) ;
	printf("文件中的代码行为%d\n",dm) ;
}

void search(char *path){//找规定目录下.c文件 
	struct _finddata_t data;
	long hnd = _findfirst(path,&data);
	if(hnd < 0 ){
		perror(path);
	}
	int nRet = (hnd<0)? -1:1;
	while(nRet >=0){
		char *nextpath = NULL;
		if(data.name[0]=='.'){
			nRet = _findnext(hnd,&data);
			continue;
		}
		if(data.attrib == _A_SUBDIR){//是目录 
		nextpath = (char *) malloc ((strlen(path)+strlen(data.name))*sizeof(char));
		char *path2 = (char *) malloc (strlen(path)*sizeof(char));
		for(int i=0;i<strlen(path)-1;i++)
			path2[i] = path[i];
		sprintf(nextpath,"%s%s\\*",path2,data.name);
		free(path2);
		search(nextpath);
		}else{//是文件 
		for (int i=0;i<strlen(data.name);i++){
			if(data.name[i]=='.'&&data.name[i+1]=='c'){
			char *path3 = (char *) malloc((strlen(path))*sizeof(char));
			for(int i=0;i<strlen(path)-1;i++)
			{
				path3[i] = path[i];
			}
			char *filepath = (char *) malloc ((strlen(path3)+strlen(data.name)+2)*sizeof(char));
			sprintf(filepath,"%s%s",path3,data.name);//拼接.c文件的路径 
			allinformation(filepath);
			free(filepath);
			free(path3);
			}
		}	
		}
		free(nextpath);
		nRet = _findnext(hnd,&data);
	}
	_findclose(hnd);	
}

int getnum_char(char f[]){//求显示字符数 
	FILE *fp;
	char ch;
	int num = 0;
	fp = fopen(f,"r");
	if(fp==NULL){
		printf("文件读取失败");
		return -1; 
	}
	while((ch=getc(fp))!=EOF){
		if(!isspace(ch)){//把空白符去掉 
			num++;
		}
	}
	fclose(fp);
    return num;
}
	
int getnum_row(char f[]){//总行 
	FILE *fp;
	int num = 0;
	fp = fopen(f,"r");
	if(fp==NULL){
		printf("文件读取失败");
		return -1; 
	}
	if(getnum_char(f)<=0){
		fclose(fp);
		return 0;
	}else{
	char a[100]={};
	while(!feof(fp)){
	fgets(a,100,fp);
	num++;
	}
	fclose(fp);
	return num-1; 
	}
}


int getnum_word(char f[]){//求词数 
	FILE *fp;
	bool flag = true;
	int  ch;
	int num = 0;
	fp = fopen(f,"r");
	while((ch=getc(fp))!=EOF){
		if((ch>='a'&&ch<='z')||(ch<='Z'&&ch>='A')||(ch>='0'&&ch<='9'||ch=='_')){
			if(flag==true){
			num++;
			flag = false;
			}	
		}else{
			flag = true;
		}
	}
	fclose(fp);	
    return num;
} 

  
int getnum_zhushirow(char f[]){//求注释行 
	bool tag = true;
	bool j = false;
	bool end_tag = false;
	FILE *fp;
	int  ch,dh;
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
	if(hangzhushi)//最后一行注释 
	num++;
	dh = delet(f);
	fclose(fp);
	return num-dh;
	return num;
}


int getnum_null(char f[]){//求空行 
	int num=0;
	FILE *fp;
	if(fp==NULL){
	printf("文件读取失败");
	return -1; 
	}
	fp = fopen(f,"r");
	char a[100];
	if(getnum_char(f)>0){
	while(!feof(fp)){
	fgets(a,100,fp);
	if(a[0]=='\n'||(a[0]=='}'&&a[2]!='/')||(a[0]=='{'&&strlen(a)==2)){//空行情况 
		num++;	
	}
	}
	if(strlen(a)==2&&a[0]=='}')//degbug发现最后没注释时候重复输出，最后作此操作 
	num--;
}
	fclose(fp);
	return num;		
}

int delet(char f[]){
	int num=0;
	FILE *fp;
	if(fp==NULL){
	printf("文件读取失败");
	return -1; 
	}
	fp = fopen(f,"r");
	char a[100];
	if(getnum_char(f)>0){
	while(!feof(fp)){
	fgets(a,100,fp);
	for(int i=0;i<strlen(a)-1;i++){
		if(a[i]=='/'&&a[i+1]=='/'){//即求跟在代码后面行注释 
			if(i>=2)
			num++;
		}
	}
}
}
	fclose(fp);
	return num;	
}




 
 
