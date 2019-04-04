#include"head.h"

int getch()  //他会返回输入字符的ascii码值
{  
		int c=0;  
		struct termios org_opts, new_opts;  
		int res=0;  
		res=tcgetattr(STDIN_FILENO, &org_opts);  
		assert(res==0);  
		memcpy(&new_opts, &org_opts, sizeof(new_opts));  
		new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT     | ECHOKE | ICRNL);  
		tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);  
		c=getchar();  
		res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);  
		assert(res==0);  
		return c;  
} 
// 实现密码的隐藏
void printPswd(char* pswd){
	int i=0;
	char res=0;
	while(1){
		res=getch();
		if((char)res=='\n'){
			pswd[i]='\0';
			printf("\n");
			break;
		}else if(i>0 && res==127){
			printf("\b \b");//先用空格把*覆盖掉，之后删除空格；
			i--;
		}else{
			printf("*");
			pswd[i]=(char)res;
			i++;
		}
	}
	return ;
}

User* regin(){
	User* head=calloc(1,sizeof(User));
	head->next=head;
	head->prev=head;
	return head;
}

/*购买链表的初始化*/
History* buylot(){
	History* b_head=calloc(1,sizeof(History));
	b_head->next=b_head;
	b_head->prev=b_head;
	return b_head;
}


/*实现查找彩民账号*/
User* finduser(User*head){
	char name[20]={0};
	printf("请输入账号：\n");
	scanf("%s",name);
	while(getchar()!='\n');
	User* p=head->next;
	while(p!=head){
		if(strcmp(p->data.name,name)==0){
			break;
		}
		p=p->next;
	}
	return p;
}
/*实现彩民账号的注册*/
void reginuser(User*head,Lottery*a_head){
	char name[37]={0};
	char pswd[20]={0};
	User* newnode=calloc(1,sizeof(User));
	newnode->next=NULL;
	newnode->prev=NULL;
	printf("请输入您的账号：\n");
	scanf("%s",name);
	while(getchar()!='\n');
	User* p=head->next;
	while(p!=head){
		if(strcmp(p->data.name,name)==0){
			printf("账号重复，请重新输入\n");
			return;
		}
		p=p->next;
	}
	printf("请输入密码:\n");
	printPswd(pswd);
	strcpy(newnode->data.pswd,pswd);
	strcpy(newnode->data.name,name);
	printf("注册成功！\n");
	system("clear");
	//尾插法
	p=head->prev;
	p->next=newnode;
	newnode->next=head;
	newnode->prev=p;
	head->prev=newnode;
	return ;	
}

/*实现彩民信息的保存*/
void saveuser(User*head){
	FILE* fp=fopen("./DB.txt","w");
	//FILE*fp=fopen("./DB2.bin","wb");// 二进制
	User*p=head->next;
	while(p!=head){
		fprintf(fp,"%s %s %lf\n",p->data.name,p->data.pswd,p->data.money);
		//fwrite(&p->data,sizeof(Data),1,fp);  // 二进制
		p=p->next;
	}
	fclose(fp);
}

/*实现彩民账户信息的加载*/
void loaduser(User*head){
	Data data={0};
	FILE* fp=fopen("./DB.txt","r");
	//FILE* fp=fopen("./DB2.bin","rb");  // 二进制
	while(1){
		if(fp==NULL){return;}
		if(fscanf(fp,"%s %s %lf",data.name,data.pswd,&data.money)!=3){break;}
		//if(fread(&data,sizeof(Data),1,fp)==0){break;}  // 二进制
		User* newnode=calloc(1,sizeof(User));
		newnode->data=data;
		User* p=head->prev;
		p->next=newnode;
		newnode->next=head;
		newnode->prev=p;
		head->prev=newnode;
	}
	fclose(fp);
}

/*实现彩民账户的登录*/
void loginuser(User* head,Lottery*a_head,History*b_head){
	int count=0,i=0,j=0;
	char str1[4];
	char str[4];
	char name[50]={0};
	char pswd[50]={0};
	srand(time(0));	
	while(1){
		printf("请输入您的账号：\n");
		scanf("%s",name);
		while(getchar()!='\n');
		User*p=head->next;
		while(p!=head){
			if(strcmp(name,p->data.name)==0){
				while(1){
					printf("请输入密码：\n");
					printPswd(pswd);
					count++;
					if(strcmp(pswd,p->data.pswd)==0){
						printf("登陆成功！\n");
						sleep(1);
						system("clear");
						userface(p,a_head,b_head);				
						return;
					}				
					if(count>3){
						while(1){
							/*char str[4];
							char a[36]="QWERTYUIOPLKJHGFDSAZXCVBNM0123456789";
							for(i=0;i<4;i++){
								j=rand()%36;
								str[i]=a[j];
							}
							str[i]='\0';
							printf("验证码为：%s\n",str);
							printf("请输入验证码：\n");
							scanf("%s",str1);
							while(getchar()!='\n');
							if(strcmp(str,str1)==0){break;}*/
							Secno();
							break;
						}		
					}
				}				
			}								
			p=p->next;
		}
		printf("您输入的账号不存在！\n");					
	}
	return;
}

/*实现验证码的生成与比较*/
void Secno(){
	int i,j;
	char str[5]={0};
	char str1[5]={0};
	char a[36]="QWERTYUIOPLKJHGFDSAZXCVBNM0123456789";
	while(1){
	for(i=0;i<4;i++){
		j=rand()%36;
		printf(" %d",j);
		str[i]=a[j];
	}
	//str[i]='\0';
	printf("验证码为：%s\n",str);
	printf("请输入验证码：\n");
	scanf("%s",str1);
	while(getchar()!='\n');
	if(strcmp(str,str1)==0){break;}	
	}
	return;
}
/*实现密码的修改*/
void updata(User*p){
	int count = 0;
	char pswd[20]={0};
	char pswd1[20]={0};
	char pswd2[20]={0};
	//User*p=finduser(head);
	//if(p==head){return;}
	while(count<2){
		printf("请输入旧密码\n");
		scanf("%s",pswd);		
			if(strcmp(pswd,p->data.pswd)==0){
				printf("请输入新密码:\n");
				scanf("%s",pswd1);
				while(getchar()!='\n');
				printf("请确认新密码:\n");
				scanf("%s",pswd2);
				while(getchar()!='\n');
				if(strcmp(pswd1,pswd2)==0){
					strcpy(p->data.pswd,pswd2);
					//printf("%s",p->data.pswd);
					printf("修改密码成功，请重新登陆！\n");
					//break;
					return;
				}
				printf("密码错误，请重新输入！\n");
			}
		count++;			
	}
	
}

/*进行充值账户*/
void recharge(User*p){
	double money=0;
	printf("请输入充值金额：\n");
	while(scanf("%lf",&money)!=1 || money<0){  //scanf可以返回值；
		fflush(stdin);     //如果不是数字，则清空缓存
		printf("输入错误，请重新输入！\n");
		scanf("%lf",&money);
		while(getchar()!='\n');
	}
	while(getchar()!='\n');
	p->data.money+=money;
	printf("充值成功，账户余额为:%.2lf\n",p->data.money);
	return ;
}
/*实现彩民信息的打印*/
void printuser(User*p){
	//User*p=finduser(head);
	printf("---------------\n");
	printf("name:%s\nPswd:%s\nMoney:%.2lf\n",p->data.name,p->data.pswd,p->data.money);
	printf("---------------\n");	
}
/*实现彩民账户与彩票购买记录的删除*/
void deluser(User*p){
	p->next->prev=p->prev;
	p->prev->next=p->next;
	free(p);
}
/*实现彩票购买记录的删除*/
void removehist1(User*p,History*b_head){	
	History*w=b_head->next;
	while(w!=b_head){
		if(strcmp(p->data.name,w->buydata.name)==0){
			w->next->prev=w->prev;
			w->prev->next=w->next;
		}
		w=w->next;
	}
	printf("删除成功，1s后退出用户界面\n");
	//free(w);  //问下放在这里可不可以
	sleep(1);
}
/*将堆空间释放*/
void freeUser(User* head){
	User* p=head;
	while(p->next!=head){	
		p=p->next;
		free(p->prev);
	}
	free(p);
}



