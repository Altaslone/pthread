#include<stdio.h>
#include<math.h>
#include"pt.h"

static struct pt inputPT,calculatePT;
static float num1,num2,floatR,fRF,fractionalP;
static int   intR;
static char  op;

static PT_THREAD(input(struct pt *pt)){
	PT_BEGIN(pt);
	printf("Input first number!\n");
	scanf("%f",&num1);
	printf("Input a operation!\n");
	getchar();
        scanf("%c",&op);
	printf("Input another number!\n");
        scanf("%f",&num2);
	PT_END(pt);
}

static PT_THREAD(calculate(struct pt *pt)){
	PT_BEGIN(pt);
	
	if( '+' == op){	
		floatR=num1+num2;
		fractionalP=modff(floatR,&fRF);
		if(fractionalP=!0){
			printf("%.5f\n",floatR);
		}
		else{
			intR=(int)floatR;
			printf("%d\n",intR);
		}
	}
	if( '-' == op){	
		floatR=num1-num2;
		fractionalP=modff(floatR,&fRF);
		printf("%f\n",fractionalP);
		printf("%f\n",fRF);
		if(fractionalP!=0){
			printf("%.5f\n",floatR);
		}
		else{
			intR=(int)floatR;
			printf("%d\n",intR);
		}
	}
	if( '*' == op){	
		floatR=num1*num2;
		fractionalP=modff(floatR,&fRF);
		if(fractionalP!=0){
			printf("%0.5f\n",floatR);
		}
		else{
			intR=(int)floatR;
			printf("%d\n",intR);
		}
	}
	if( '/' == op){	
		floatR=num1/num2;
		fractionalP=modff(floatR,&fRF);
		if(fractionalP!=0){
			printf("%.5f\n",floatR);
		}
		else{
			intR=(int)floatR;
			printf("%d\n",intR);
		}	
	}
	PT_END(pt);
}

void main(void){
	PT_INIT(&inputPT);
	PT_INIT(&calculatePT);
	
	if(PT_SCHEDULE(input(&inputPT))==0){
		PT_SCHEDULE(calculate(&calculatePT));
	}
}

