#include<stdio.h>
#include"pt.h"

static struct pt inputPT,calculatePT;
static float num1,num2,result;
static char op;

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
	printf("The result is ");
	if( '+' == op){	result=num1+num2;	printf("%f + %f = %f\n",num1,num2,result);	}
	if( '-' == op){	result=num1-num2;	printf("%f - %f = %f\n",num1,num2,result);	}
	if( '*' == op){	result=num1*num2;	printf("%f * %f = %f\n",num1,num2,result);	}
	if( '/' == op){	result=num1/num2;	printf("%f / %f = %f\n",num1,num2,result);	}
	PT_END(pt);
}

void main(void){
	PT_INIT(&inputPT);
	PT_INIT(&calculatePT);
	
	if(PT_SCHEDULE(input(&inputPT))==0){
		PT_SCHEDULE(calculate(&calculatePT));
	}
}

