//
//  005-线性表算法题.c
//  DataStructures
//
//  Created by Leo on 2023/5/24.
//

#include "ListNode.h"

//2.1 初始化单链表线性表
Status InitList1(LinkList *L){

	//产生头结点,并使用L指向此头结点
	*L = (LinkList)malloc(sizeof(Node));
	//存储空间分配失败
	if(*L == NULL) return ERROR;
	//将头结点的指针域置空
	(*L)->next = NULL;

	return SUCCESS;
}

//2.2 单链表插入
/*
 初始条件:顺序线性表L已存在,1≤i≤ListLength(L);
 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1;
 */
Status ListInsert1(LinkList *L,int i,ElemType e){

	int j;
	LinkList p,s;
	p = *L;
	j = 1;

	//寻找第i个结点
	while (p && j<i) {
		p = p->next;
		++j;
	}

	//第i个元素不存在
	if(!p || j>i) return ERROR;

	//生成新结点s
	s = (LinkList)malloc(sizeof(Node));
	//将e赋值给s的数值域
	s->data = e;
	//将p的后继结点赋值给s的后继
	s->next = p->next;
	//将s赋值给p的后继
	p->next = s;

	return SUCCESS;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
	LinkList p=L->next;
	while(p)
	{
		printf("%d  ",p->data);
		p=p->next;
	}
	printf("\n");
	return SUCCESS;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList1(LinkList *L)
{
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
	return SUCCESS;
}


/*

 作业1:
 题目:
 将2个递增的有序链表合并为一个有序链表; 要求结果链表仍然使用两个链表的存储空间,不另外占用其他的存储空间. 表中不允许有重复的数据

 关键词:递增有序链表,不允许有重复数据,保留递增关系(后插法)
	  不占用额外的存储空间指的是不能开辟新节点,赋值在链接到链表上;

 算法思想:
 (1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
 (2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时,依次摘取其中较小值重新链表在Lc表的最后.
 (3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素,这样确保合并后表中无重复的元素;
 (4)当一个表达到表尾结点为空时,非空表的剩余元素直接链接在Lc表最后.
 (5)最后释放链表Lb的头结点;

 */

void MergeList(LinkList *La, LinkList *Lb, LinkList *Lc){
	//目标:将2个递增的有序链表La,Lb 合并为一个递增的有序链表Lc

	LinkList pa,pb,pc,temp;
	//pa 是链表La的工作指针,pb 是链表Lb的工作指针, 初始化为首元结点;
	pa = (*La)->next;
	pb = (*Lb)->next;

	*Lc = pc = *La;
	while (pa && pb) {
		if (pa->data < pb->data) {
			//取较小者La中的元素,将pa链接在pc的后面,pa指针后移
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else if(pa->data > pb->data){
			//取较小者Lb的元素,将pb链接在pc后面, pb指针后移
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}else
		{
			//相等时取La中的元素,删除Lb的元素;
			pc->next = pa;
			pc = pa;
			pa = pa ->next;
			temp = pb->next;
			free(pb);
			pb = temp;
		}
	}

	//将非空表的剩余元素之间链接在Lc表的最后
	pc->next = pa?pa:pb;

	//释放Lb的头结点
	free(*Lb);

}

/*
 作业2:
 题目:
 已知两个链表A和B分别表示两个集合.其元素递增排列. 设计一个算法,用于求出A与B的交集,并存储在A链表中;
 例如:
 La = {2,4,6,8}; Lb = {4,6,8,10};
 Lc = {4,6,8}

 关键词:依次摘取2个表中相等的元素重新进行链接,删除其他不等的元素;


 算法思想:
 (1)假设待合并的链表为La和Lb,合并后的新表使用头指针Lc(Lc的表头结点设为La的表头结点)指向. Pa 和 Pb 分别是La,Lb的工作指针.初始化为相应链表的首元结点
 (2)从首元结点开始比较, 当两个链表La 和Lb 均未到达表尾结点时.
 (3)如果两个表中的元素相等,只摘取La表中的元素,删除Lb表中的元素;
 (4)如果其中一个表中的元素较小,删除此表中较小的元素. 此表的工作指针后移;
 (5)当链表La和Lb有一个先到达表尾结点为空时,依次删除另一个非空表中的所有元素,最后释放链表lb;

 */
void Intersection(LinkList *La, LinkList *Lb, LinkList *Lc){

	//目标: 求2个递增的有序链表La,Lb的交集, 使用头指针Lc指向带回;
	LinkList pa,pb,pc,temp;

	//pa 是链表La的工作指针,pb 是链表Lb的工作指针, 初始化为首元结点;La的头结点作为Lc的头结点;
	pa = (*La)->next;
	pb = (*Lb)->next;
	*Lc = pc = *La;

	while (pa && pb) {

		if (pa->data == pb->data) {
			//相等,交集并入结果链表中;
			//(1).取La中的元素,将pa链接到pc的后面,pa指针后移;
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			//(2)删除Lb中对应相等的元素
			temp = pb;
			pb = pb->next;
			free(temp);
		}else if(pa->data < pb->data){

			//删除较小值La的元素;
			temp = pa;
			pa = pa->next;
			free(temp);
		}else{
			//删除较小值Lb中的元素
			temp = pb;
			pb = pb->next;
			free(temp);
		}
	}

	//Lb为空,删除非空表La中的所有元素
	while (pa) {

		temp = pa;
		pa = pa->next;
		free(temp);
	}

	//La为空,删除非空表Lb中的所有元素
	while (pb) {
		temp = pb;
		pb = pb->next;
		free(temp);
	}


	pc->next = NULL;
	free(*Lb);
}

/*
 作业3:
 题目:
 设计一个算法,将链表中所有节点的链接方向"原地旋转",即要求仅仅利用原表的存储空间. 换句话说,要求算法空间复杂度为O(1);
 例如:L={0,2,4,6,8,10}, 逆转后: L = {10,8,6,4,2,0};

 关键词:不能开辟新的空间,只能改变指针的指向; 可以考虑逐个摘取结点,利用前插法创建链表的思想,将结点一次插入到头结点的后面; 因为先插入的结点为表尾,后插入的结点为表头,即可实现链表的逆转;


 算法思想:
 (1)利用原有的头结点*L,p为工作指针, 初始时p指向首元结点. 因为摘取的结点依次向前插入,为确保链表尾部为空,初始时将头结点的指针域置空;
 (2)从前向后遍历链表,依次摘取结点,在摘取结点前需要用指针q记录后继结点,以防止链接后丢失后继结点;
 (3)将摘取的结点插入到头结点之后,最后p指向新的待处理节点q(p=q);
 */

void Inverse(LinkList *L){
	//目的: 逆转带头结点单链表L;
	LinkList p,q;
	//p指向首元结点;
	p = (*L)->next;
	//头结点的指针域置空
	(*L)->next = NULL;

	//遍历链表
	while (p!=NULL) {

		//q执行p的后继
		q = p->next;
		//p->next = (*L)->next
		p->next = (*L)->next;
		//*p 插入到头结点之后;
		(*L)->next = p;
		//处理下一个结点
		p = q;
	}
}


/*
 作业4:
 题目:
 设计一个算法,删除递增有序链表中值大于等于mink且小于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素;

 关键词: 通过遍历链表能够定位带删除元素的下边界和上边界, 即可找到第一个值大于mink的结点和第一个值大于等于maxk的结点;


 算法思想:
 (1)查找第一个值大于mink的结点,用q指向该结点,pre 指向该结点的前驱结点;
 (2)继续向下遍历链表, 查找第一个值大于等于maxk的结点,用p指向该结点;
 (3)修改下边界前驱结点的指针域, 是其指向上边界(pre->next = p);
 (4)依次释放待删除结点的空间(介于pre和p之间的所有结点);
 */

void DeleteMinMax(LinkList *L, int mink, int maxk){
	//目标: 删除递增有序链表L中值大于等于mink 和小于等于maxk的所有元素

	LinkList p,q,pre;
	pre = *L;
	LinkList temp;

	//p指向首元结点
	p = (*L)->next;

	//1.查找第一值大于mink的结点
	while (p && p->data < mink) {
		//指向前驱结点
		pre = p;
		p = p->next;
	}

	//2.查找第一个值大于等于maxk的结点
	while (p && p->data<=maxk) {
		p = p->next;
	}

	//3.修改待删除的结点指针
	q = pre->next;
	pre->next = p;

	while (q != p) {
		temp = q->next;
		free(q);
		q = temp;
	}
}

/*
 题目5:
 设将n(n>1)个整数存放到一维数组R中, 试设计一个在时间和空间两方面都尽可能高效的算法;将R中保存的序列循环左移p个位置(0<p<n)个位置, 即将R中的数据由(x0,x1,......,xn-1)变换为(xp,xp+1,...,xn-1,x0,x1,...,xp-1).

 例如: pre[10] = {0,1,2,3,4,5,6,7,8,9},
	  n = 10,p = 3;
	  pre[10] = {3,4,5,6,7,8,9,0,1,2}

 算法思路:
 1. 先将n个数据原地逆置 9,8,7,6,5,4,3,2,1,0;
 2. 将n个数据拆解成[9,8,7,6,5,4,3] [2,1,0]
 2. 将前n-p个数据和后p个数据分别原地逆置; [3,4,5,6,7,8,9] [0,1,2]

 复杂度分析:
 时间复杂度: O(n); 时间复杂度:O(1);
 */

void Reverse(int *pre,int left ,int right){

	//将数组R中的数据原地逆置

	//i等于左边界left,j等于右边界right;
	int i = left,j = right;
	int temp;

	//交换pre[i] 和 pre[j] 的值
	while (i < j) {

		//交换
		temp = pre[i];
		pre[i] = pre[j];
		pre[j] = temp;

		//i右移,j左移
		i++;
		j--;
	}
}

void LeftShift(int *pre,int n,int p){

	//将长度为n的数组pre 中的数据循环左移p个位置
	if (p>0 && p<n) {
		//1. 将数组中所有元素全部逆置
		Reverse(pre, 0, n-1);
		//2. 将前n-p个数据逆置
		Reverse(pre, 0, n-p-1);
		//3. 将后p个数据逆置
		Reverse(pre, n-p, n-1);

	}
}


/*
  题目6:
 已知一个整数序列A = (a0,a1,a2,...an-1),其中(0<= ai <=n),(0<= i<=n). 若存在ap1= ap2 = ...= apm = x,且m>n/2(0<=pk<n,1<=k<=m),则称x 为 A的主元素. 例如,A = (0,5,5,3,5,7,5,5),则5是主元素; 若B = (0,5,5,3,5,1,5,7),则A 中没有主元素,假设A中的n个元素保存在一个一维数组中,请设计一个尽可能高效的算法,找出数组元素中的主元素,若存在主元素则输出该元素,否则输出-1.

 题目分析:
 主元素,是数组中的出现次数超过一半的元素; 当数组中存在主元素时,所有非主元素的个数和必少于一半. 如果让主元素和一个非主元素配对, 则最后多出来的元素(没有元素与之匹配就是主元素.

 算法思路:
 1. 选取候选主元素, 从前向后依次扫描数组中的每个整数, 假定第一个整数为主元素,将其保存在Key中,计数为1. 若遇到下一个整数仍然等于key,则计数加1. 否则计数减1. 当计数减到0时, 将遇到的下一个整数保存到key中, 计数重新记为1. 开始新一轮计数. 即可从当前位置开始重上述过程,直到将全部数组元素扫描一遍;
 2. 判断key中的元素是否是真正的主元素, 再次扫描数组, 统计key中元素出现的次数,若大于n/2,则为主元素,否则,序列中不存在主元素;

 算法分析:
 时间复杂度: O(n)
 空间复杂度: O(1)
 */

int MainElement(int *A, int n){

	//目标: 求整数序列A中的主元素;
	//count 用来计数
	int count = 1;
	//key 用来保存候选主元素, 初始A[0]
	int key = A[0];

	//(1) 扫描数组,选取候选主元素
	for (int i = 1; i < n; i++) {

		//(2) 如果A[i]元素值 == key ,则候选主元素计数加1;
		if (A[i] == key) {
			count++;
		}else{
			//(3) 当前元素A[i] 非候选主元素,计数减1;
			if(count >0){
				count--;

			}else{
			   //(4) 如果count 等于0,则更换候选主元素,重新计数
				key = A[i];
				count = 1;
			}

		}
	}

	//如果count >0
	if (count >0){

		//(5)统计候选主元素的实际出现次数
		for (int i = count = 0; i < n; i++)
			if (A[i] == key) count++;
	}

	//(6)判断count>n/2, 确认key是不是主元素
	if (count > n/2) return key;
	else return -1; //不存在主元素

}

/*
 题目7:
 用单链表保存m个整数, 结点的结构为(data,link),且|data|<=n(n为正整数). 现在要去设计一个时间复杂度尽可能高效的算法. 对于链表中的data 绝对值相等的结点, 仅保留第一次出现的结点,而删除其余绝对值相等的结点.例如,链表A = {21,-15,15,-7,15}, 删除后的链表A={21,-15,-7};

 题目分析:
	要求设计一个时间复杂度尽量高效的算法,而已知|data|<=n, 所以可以考虑用空间换时间的方法. 申请一个空间大小为n+1(0号单元不使用)的辅助数组. 保存链表中已出现的数值,通过对链表进行一趟扫描来完成删除.
 算法思路:
 1. 申请大小为n+1的辅助数组t并赋值初值为0;
 2. 从首元结点开始遍历链表,依次检查t[|data|]的值, 若[|data|]为0,即结点首次出现,则保留该结点,并置t[|data|] = 1,若t[|data|]不为0,则将该结点从链表中删除.

 复杂度分析:
 时间复杂度: O(m),对长度为m的链表进行一趟遍历,则算法时间复杂度为O(m);
 空间复杂度: O(n)
 */
void DeleteEqualNode(LinkList *L,int n){

	//目标: 删除单链表中绝对值相等的结点;
	//1. 开辟辅助数组p.
	int *p = alloca(sizeof(int)*n);
	LinkList r = *L;

	//2.数组元素初始值置空
	for (int i = 0; i < n; i++) {
		*(p+i) = 0;
	}

	//3.指针temp 指向首元结点
	LinkList temp = (*L)->next;

	//4.遍历链表,直到temp = NULL;
	while (temp!= NULL) {

		//5.如果该绝对值已经在结点上出现过,则删除该结点
		if (p[abs(temp->data)] == 1) {

			//临时指针指向temp->next
			r->next = temp->next;
			//删除temp指向的结点
			free(temp);
			//temp 指向删除结点下一个结点
			temp = r->next;
		}else
		{
			//6. 未出现过的结点,则将数组中对应位置置为1;
			p[abs(temp->data)] = 1;
			r = temp;
			//继续向后遍历结点
			temp = temp->next;
		}
	}

}

void run005(void) {
	
	printf("线性表练习篇!\n");

//	Status iStatus;
//	LinkList La,Lb,Lc,L;
//	InitList1(&La);
//	InitList1(&Lb);

//    ---------作业1--------
//    printf("******题目1:********\n");
//    //设计2个递增链表La,Lb
//    for(int j = 10;j>=0;j-=2)
//    {
//        iStatus = ListInsert1(&La, 1, j);
//    }
//    printf("La:\n");
//    ListTraverse(La);
//
//    for(int j = 11;j>0;j-=2)
//    {
//        iStatus = ListInsert1(&Lb, 1, j);
//    }
//    printf("Lb:\n");
//    ListTraverse(Lb);
//
//    MergeList(&La, &Lb, &Lc);
//    printf("Lc:\n");
//    ListTraverse(Lc);

	/*---------作业2--------*/
//    printf("******题目2:********\n");
//    ListInsert1(&La, 1, 8);
//    ListInsert1(&La, 1, 6);
//    ListInsert1(&La, 1, 4);
//    ListInsert1(&La, 1, 2);
//    printf("La:\n");
//    ListTraverse(La);
//
//
//    ListInsert1(&Lb, 1, 10);
//    ListInsert1(&Lb, 1, 8);
//    ListInsert1(&Lb, 1, 6);
//    ListInsert1(&Lb, 1, 4);
//    printf("Lb:\n");
//    ListTraverse(Lb);
//
//    Intersection(&La, &Lb, &Lc);
//    printf("Lc:\n");
//    ListTraverse(Lc);

	 /*---------作业3--------*/
//    printf("******题目3:********\n");
//    InitList1(&L);
//    for(int j = 10;j>=0;j-=2)
//    {
//        iStatus = ListInsert1(&L, 1, j);
//    }
//    printf("L逆转前:\n");
//    ListTraverse(L);
//
//    Inverse(&L);
//    printf("L逆转后:\n");
//    ListTraverse(L);
//
//     /*---------作业4--------*/
//    printf("******题目4:********\n");
//    InitList1(&L);
//    for(int j = 10;j>=0;j-=2)
//    {
//        iStatus = ListInsert1(&L, 1, j);
//    }
//    printf("L链表:\n");
//    ListTraverse(L);
//
//    DeleteMinMax(&L, 4, 10);
//    printf("删除链表mink与maxk之间结点的链表:\n");
//    ListTraverse(L);
//
//     /*---------作业5--------*/
//    printf("******题目5:********\n");
//    int pre[10] = {0,1,2,3,4,5,6,7,8,9};
//    LeftShift(pre, 10, 3);
//    for (int i=0; i < 10; i++) {
//        printf("%d ",pre[i]);
//    }
//    printf("\n");

//     /*---------作业6--------*/
	printf("******题目6:********\n");
	int  A[] = {0,5,5,3,5,7,5,5};
	int  B[] = {0,5,5,3,5,1,5,7};
	int  C[] = {0,1,2,3,4,5,6,7};

	int value = MainElement(A, 8);
	printf("数组A 主元素为: %d\n",value);
	value = MainElement(B, 8);
	printf("数组B 主元素为(-1表示数组没有主元素): %d\n",value);
	value = MainElement(C, 8);
	printf("数组C 主元素为(-1表示数组没有主元素): %d\n",value);

//     /*---------作业7--------*/
//    //21,-15,15,-7,15
//    printf("******题目7:********\n");
//    InitList1(&L);
//    ListInsert1(&L, 1, 21);
//    ListInsert1(&L, 1, -15);
//    ListInsert1(&L, 1, 15);
//    ListInsert1(&L, 1, -7);
//    ListInsert1(&L, 1, 15);
//
//    DeleteEqualNode(&L, 21);
//    ListTraverse(L);

}
