#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node * NewNode(char *nodename)
{
	Node* p = (Node*)malloc(sizeof(struct Node));
	p->childnum=0;
	p->type = 0;
	strcpy(p->strval,nodename);
	return p;
}
Node * NewNodeSyn(char *nodename,int linenum)
{
	Node* p = (Node*)malloc(sizeof(struct Node));
	p->childnum=0;
	p->type = 1;
	p->linenum = linenum;
	strcpy(p->strval,nodename);
	return p;
}
Node *NewNodeInt(int value)
{
	Node *p = (Node *)malloc(sizeof(struct Node));
	p->childnum = 0;
	strcpy(p->strval,"INT");
	p->type = 2;
	p->intval = value;
	return p;
}
Node *NewNodeFloat(float value)
{
	Node *p = (Node *)malloc(sizeof(struct Node));
	p->childnum = 0;
	p->type = 3;
	p->floatval = value;
	strcpy(p->strval,"FLOAT");
	return p;
}
Node *NewNodeId(char *nodename,char *idname)
{
	Node *p = (Node *)malloc(sizeof(struct Node));
	p->childnum = 0;
	strcpy(p->strval,nodename);
	p->type = 4;
	strcpy(p->idval,idname);
	return p;
}
Node* MergeNode1(Node *father ,Node* child)
{
	father->child[father->childnum] = child;
	father->childnum++;
	return father;
}
Node *MergeNode2(Node *father,Node *child1,Node* child2)
{
		father->child[father->childnum++]=child1;
		father->child[father->childnum++]=child2;
	return father;
}
Node *MergeNode3(Node *father,Node *child1,Node* child2,Node* child3)
{
		father->child[father->childnum++]=child1;
		father->child[father->childnum++]=child2;
		father->child[father->childnum++]=child3;
	return father;
}
Node *MergeNode4(Node* father,Node *c1,Node* c2,Node* c3,Node* c4)
{
		father->child[father->childnum++] = c1;
		father->child[father->childnum++] = c2;
		father->child[father->childnum++] = c3;
		father->child[father->childnum++] = c4;
	return father;
}
Node *MergeNode5(Node* father,Node *c1,Node* c2,Node* c3,Node* c4,Node *c5)
{
		father->child[father->childnum++] = c1;
		father->child[father->childnum++] = c2;
		father->child[father->childnum++] = c3;
		father->child[father->childnum++] = c4;
		father->child[father->childnum++] = c5;
	return father;
}
Node *MergeNode7(Node* father,Node *c1,Node* c2,Node* c3,Node* c4,Node *c5,Node* c6,Node* c7)
{
		father->child[father->childnum++] = c1;
		father->child[father->childnum++] = c2;
		father->child[father->childnum++] = c3;
		father->child[father->childnum++] = c4;
		father->child[father->childnum++] = c5;
		father->child[father->childnum++] = c6;
		father->child[father->childnum++] = c7;
	return father;
}
int PrintTab(int num)
{
	int i=0;
	for(;i<num;i++)
	{
		printf("  ");
	}
}
void DisplayTree(Node *head,int n)
{
	if(head == NULL)
		return ;
	int i=0;
	PrintTab(n);
	switch (head->type)
	{
		case 0: printf("%s\n",head->strval); break;
		case 1: printf("%s  (%d)\n",head->strval,head->linenum);break;
		case 2: printf("%s: %d\n",head->strval,head->intval);break;
		case 3: printf("%s: %f\n",head->strval,head->floatval);break;
		case 4: printf("%s: %s\n",head->strval,head->idval);break;
		default : printf("should not reach!\n");
	}
	for(;i<head->childnum;i++)
	{
		DisplayTree(head->child[i],n+1);
	}
}
