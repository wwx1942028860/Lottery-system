#include"head.h"

/*彩票链表的初始化*/
Lottery* lot(){
	Lottery* a_head=calloc(1,sizeof(Lottery));
	a_head->next=a_head;
	a_head->prev=a_head;
	return a_head;
}

/*实现管理员账户登录与管理员管理功能加载*/
void loginadmin(Lottery*a_head,User*head,History*b_head,int*id){
	char name[50]={0};
	char pswd[50]={0};
	printf("请输入管理员账号：\n");
	scanf("%s",name);
	while(getchar()!='\n');
	if(strcmp(name,"admin")==0){
		printf("请输入密码：\n");
		//scanf("%s",pswd);
		printPswd(pswd);
		//while(getchar()!='\n');
			if(strcmp(pswd,"admin")==0){
				printf("登陆成功！\n");
				sleep(2);
				system("clear");
				adminface(a_head,head,id);//调用管理员功能界面
			}
	}
	return;
}

/*实现彩票的发布*/
void issurelot(Lottery*a_head,int*id){
	double price=0;
	int num=0;
	int win1[5]={0};
	Lottery* newnode=calloc(1,sizeof(Lottery));
	Lottery* q=a_head->next;
	newnode->next=NULL;
	newnode->prev=NULL;
	newnode->ldata.id=(*id); //赋值期号；
	//if((*id)>1){
	while(q!=a_head){
		if(strcmp(q->ldata.state,"未开奖")==0){
			printf("上期彩票还未开奖，不能发行彩票！\n");
			return;
		}
		q=q->next;
	}
	//}
	printf("请输入彩票每注的金额：\n");
	scanf("%lf",&price);
	while(getchar()!='\n');
	  
	newnode->ldata.price=price; //赋值每注金额；
	strcpy(newnode->ldata.state,"未开奖");
	newnode->ldata.num=0; 	
	newnode->ldata.bonus=2000;
	//memset(newnode->ldata.win,0,); //将中奖号码先初始化为0
	newnode->ldata.flag=0;
	
	//尾插法
	Lottery*p=a_head->prev;
	p->next=newnode;
	newnode->next=a_head;
	newnode->prev=p;
	a_head->prev=newnode;
	printf("发布成功！\n");
	(*id)++;
	sleep(1);
	//return;
	system("clear");
}
/*实现第n期彩票的查找*/
Lottery* findlot(Lottery*a_head){
	int id=0;
	printf("请输入期号：\n");
	scanf("%d",&id);
	while(getchar()!='\n');
	Lottery* p=a_head->next;
	while(p!=a_head){
		if(p->ldata.id==id){
			break;
		}else{
			printf("期号输入错误，请重新输入\n");
		}
		p=p->next;
	}
	return p;
}

/*实现第n期彩票的打印*/
void printlot(Lottery*a_head){
	int i=0;
	Lottery*p=findlot(a_head);
	printf("以下为第%d期彩票信息：\n",p->ldata.id);
	printf("彩票的价格为%.2lf元/注\n",p->ldata.price);
	if(strcmp(p->ldata.state,"已开奖")==0){
		printf("本期已经开奖，本期的中奖号码为：\n");
		for(i=0;i<5;i++){
			printf("%d\t",p->ldata.win[i]);
		}
		printf("\n");
	}
	printf("本期共售出%d张彩票\n",p->ldata.num);
	printf("本期的奖池金额为%.2lf元\n",p->ldata.bonus);
}
/*查看往期彩票功能*/
void look(Lottery*a_head){
	int id=0;
	printf("请输入查看的期号：\n");
	scanf("%d",&id);
	while(getchar()!='\n');
	Lottery*p=a_head->next;
	while(p!=a_head){
		if(id == p->ldata.id){
			if(strcmp(p->ldata.state,"已开奖")==0){
				printf("该期已经开奖\n");
				printf("该期的中奖号码为：%d %d %d %d\n",p->ldata.win[0],p->ldata.win[1],p->ldata.win[2],p->ldata.win[3]); 
				printf("该期奖金池额度为：%lf元\n",p->ldata.bonus);
				printf("该期的发行总数为：%d张\n",p->ldata.num);
				break;
			}
			printf("该期还未开奖！\n");
			break;
			//strcpy(p->ldata.state,"该期还未开奖");		
		}
		p=p->next;
	}
}
/*实现第n期彩票的保存*/
void savelot(Lottery*a_head){
	FILE* fp=fopen("./admin.txt","w");
	//FILE*fp=fopen("./DB2.bin","wb");// 二进制
	Lottery*p=a_head->next;
	while(p!=a_head){
		fprintf(fp,"%d %d %lf %s %lf %d %d %d %d\n",p->ldata.id,p->ldata.num,p->ldata.bonus,p->ldata.state,p->ldata.price,p->ldata.win[0],p->ldata.win[1],p->ldata.win[2],p->ldata.win[3]);
		//fwrite(&p->data,sizeof(Data),1,fp);  // 二进制
		p=p->next;
	}
	fclose(fp);
}

/*实现彩票数据的加载*/
void loadlot(Lottery*a_head,int *id){
	LData datalot={0};
	FILE* fp=fopen("./admin.txt","r");
	//FILE* fp=fopen("./DB2.bin","rb");  // 二进制
	while(1){
		if(fp==NULL){return;}
		if(fscanf(fp,"%d %d %lf %s %lf %d %d %d %d\n",&datalot.id,&datalot.num,&datalot.bonus,datalot.state,&datalot.price,&datalot.win[0],&datalot.win[1],&datalot.win[2],&datalot.win[3])!=9){
			(*id)=datalot.id+1 ;
			break;
		}
		//if(fread(&data,sizeof(Data),1,fp)==0){break;}  // 二进制
		Lottery* newnode=calloc(1,sizeof(Lottery));
		newnode->ldata=datalot;
		Lottery* p=a_head->prev;
		p->next=newnode;
		newnode->next=a_head;
		newnode->prev=p;
		a_head->prev=newnode;
				
	}
	fclose(fp);
}

/*实现按照余额查找彩民*/
void findper(User*head){
	printf("此项功能为查找一定余额区间的彩民！\n");
	int money1=0;
	int money2=0;
	int temp=0;
	printf("请输入余额1:\n");
	scanf("%d",&money1);
	while(getchar()!='\n');
	printf("请输入余额2:\n");
	scanf("%d",&money2);
	while(getchar()!='\n');
	//if(money1<0 || money2 <0){break;}
	if(money2<money1){
		temp=money1;
		money1=money2;
		money2=temp;
	};
	User*p=head->next;
	while(p!=head){
		if(p->data.money >= money1 && p->data.money <= money2){
			printf("-----------------\n");
			printf("账户名称：%s\n",p->data.name);
			printf("账户余额：%.2lf元\n",p->data.money);
			printf("-----------------\n");
		}
		p=p->next;
	}
}

/*实现对彩民的排序，按照账户余额*/
void sortman(User*head){
	User*p=head->next;
	if(p==head){return;}
	Data temp={0};
	int flag=0;	
	while(1){
		flag=0;
		p=head->next;
		while(p->next!=head){
			if(p->data.money > p->next->data.money){
				temp=p->data;
				p->data=p->next->data;
				p->next->data=temp;					
				flag=1;
				//printf("1\n");
			}			
			p=p->next;		
		}
		if(flag==0){break;}
	}
}


/*打印所有彩民*/
void printall(User*head){
	User*p=head->next;
	while(p!=head){
		printf("-----------------\n");
		printf("姓名：%s\n",p->data.name);
		printf("余额：%.2lf\n",p->data.money);
		p=p->next;	
	}
}
/*释放堆空间*/
void freeLottery(Lottery* a_head){
	Lottery* p=a_head;
	while(p->next!=a_head){	
		p=p->next;
		free(p->prev);
	}
	free(p);
}




























