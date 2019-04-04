#include<stdio.h>

int main(int argc,char** argv){
	int arr[8]={1,2,3,4,5,6,7,8}; //下注的号码
	int win[4]={1,2,3,4};  //开奖的号码
	int j=0,count=0;
	for(j=0;j<8;j++){
		if(j%4==0){count=0;}
		for(int i=0;i<4;i++){
			if(win[i]==arr[j]){
			count++;	
		}
				
	}
	if(j%4==3){printf("%d\n",count);}
	}
}
