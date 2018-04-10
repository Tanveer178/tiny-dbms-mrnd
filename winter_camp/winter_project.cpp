#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100
struct StudentMarks
{
	int rollno, m1, m2, m3, m4;
	char* name;
	float avg, cgpa;

};
struct StudentInfo
{
	int rollno;
	char* address;
	char* city;
	char* pincode;
	char* phno;

};
struct node
{
	char* nme;
	char* rno;
	struct node* next;
};
struct hash{
	struct node* head;
};

struct node* createNode(char* r, char* n)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->nme = n;
	temp->rno = r;
	temp->next = NULL;
	return temp;
}
int spos = 0, pos = 0, mrksize = 10, infosize = 10;
struct StudentMarks** marksList;
struct StudentInfo** infoList;
struct hash* hashtable;
int generateKey(int num)
{
	int sum = 0;
	while (num != 0)
	{
		sum += num % 10;
		num = num / 10;
		//printf("%d",sum);
	}
	return sum;
}
void hashPut(char* r, char* n)
{

	int i = 0, key, flag = 0;
	while (i != 10)
	{
		struct node* search = hashtable[i].head;
		while (search != NULL)
		{
			if (strcmp(search->rno, r) == 0)
			{
				search->nme = n;
				flag = 1;
				break;
			}
			search = search->next;
		}
		if (flag == 1)
			break;
		i++;
	}
	if (flag != 1)
	{
		key = generateKey(atoi(r)) % 10;
		struct node* temp = createNode(r, n);
		if (hashtable[key].head == NULL)
		{
			hashtable[key].head = temp;
			//printf("node created");
			//printf("%s", temp->rno);
			//printf("%s", temp->nme);
		}
		else
		{
			struct node* prev = hashtable[key].head;
			while (prev->next != NULL)
			{
				prev = prev->next;
			}
			prev->next = temp;

			//hashtable[key]=temp;
			//printf("%s",hashtable[1].head->rno);
		}
	}
}
void hashGet(char* r)
{
	int key = generateKey(atoi(r)) % 10;
	struct node* search = hashtable[key].head;
	// printf("%s",hashtable[1].head->rno);
	while (search != NULL)
	{

		if (strcmp(search->rno, r) == 0)
		{

			printf("%s\n", search->nme);
			break;
		}
		search = search->next;
	}
}
char* getLine(FILE* fp)
{
	char* res = (char*)malloc(MAX_SIZE * sizeof(char));
	char c;
	int i;
	for (i = 0;;)
	{
		c =fgetc(fp);
		if (c == '\n' || c == EOF)
			break;
		res[i++] = c;
	}
	res[i] = '\0';
	return res;
}
void storeInStructMarks(struct StudentMarks** marksList, char* res, int pos)
{
	char* pt1 = strtok(res, ",");
	int ins = 0;
	while (pt1 != NULL)
	{
		if (ins == 0)
		{
			marksList[pos]->rollno = atoi(pt1);
		}
		else if (ins == 1){
			marksList[pos]->name = pt1;

		}
		else if (ins == 2)
		{
			marksList[pos]->m1 = atoi(pt1);

		}
		else if (ins == 3)
		{
			marksList[pos]->m2 = atoi(pt1);

		}
		else if (ins == 4)
			marksList[pos]->m3 = atoi(pt1);
		else if (ins == 5)
			marksList[pos]->m4 = atoi(pt1);
		ins++;
		marksList[pos]->avg = 0.0;
		marksList[pos]->cgpa = 0.0;
		pt1 = strtok(NULL, ",");

		if (ins == 6)
			break;
	}
}
void storeInStructInfo(struct StudentInfo** infoList, char* res, int pos)
{
	char* pt = strtok(res, ",");
	int ins = 0;
	while (pt != NULL)
	{
		if (ins == 0){
			infoList[pos]->rollno = atoi(pt);

		}
		else if (ins == 1)
			infoList[pos]->phno = pt;
		else if (ins == 2)
			infoList[pos]->address = pt;
		else if (ins == 3)
			infoList[pos]->city = pt;
		else if (ins == 4)
			infoList[pos]->pincode = pt;
		ins++;
		pt = strtok(NULL, ",");
		if (ins == 5)
			break;
	}
}
void displayMarks(struct StudentMarks** marksList)
{
	int i;
	printf("ROLL_NO      NAME     M1  M2  M3  M4 AVG  CGPA\n");
	for (i = 0; i<spos; i++)
	{
		printf("%3d %16s %3d %3d %3d %3d %.2f %.2f\n", marksList[i]->rollno, marksList[i]->name, marksList[i]->m1, marksList[i]->m2, marksList[i]->m3, marksList[i]->m4, marksList[i]->avg, marksList[i]->cgpa);
	}
}
void displayInfo(struct StudentInfo** infoList)
{
	int i;
	for (i = 0; i<pos; i++)
		printf("%3d %20s %20s %20s %20s\n", infoList[i]->rollno, infoList[i]->phno, infoList[i]->address, infoList[i]->city, infoList[i]->pincode);
}
int dispDup(FILE* fp)
{

	int ch, i;
	char* res;
	int flag = 0;
	res = getLine(fp);
	res = getLine(fp);
	char* pt = strtok(res, ",");
	for (i = 0; i<spos; i++)
	{
		if (marksList[i]->rollno == atoi(pt))
		{
			printf("duplicates found\n");
			printf("choice\n1.Update\n2.Drop");
			scanf("%d", &ch);
			if (ch == 1)
			{
				flag = atoi(pt);
				break;
			}
		}
	}
	if (flag == 0)
		return 0;
	else
		return flag;
}
void loadMarks(char* fname)
{
	FILE* fp;
	fp = fopen(fname, "r");
	char* res;
	//char* res1;
	int i = 0;
	res = getLine(fp);
	while (res[0] != '\0')
	{
		res = getLine(fp);
	}
	rewind(fp);
	if (marksList == NULL)
	{
		marksList = (struct StudentMarks**)malloc(mrksize*sizeof(struct StudentMarks*));
		for (i = 0; i<mrksize; i++)
			marksList[i] = (struct StudentMarks*)malloc(sizeof(struct StudentMarks));
	}
	if (spos == mrksize)
	{
		//printf("here");
		mrksize *= 2;
		struct StudentMarks** tmp = (struct StudentMarks**)malloc(mrksize*sizeof(struct StudentMarks*));
		for (i = 0; i<mrksize; i++)
			tmp[i] = (struct StudentMarks*)malloc(sizeof(struct StudentMarks));
		for (i = 0; i<mrksize / 2; i++)
			tmp[i] = marksList[i];
		marksList = tmp;
		// free(tmp);
	}

	int dupval = dispDup(fp);
	if (spos == 0 || dupval == 0)
	{
		rewind(fp);
		res = getLine(fp);
		res = getLine(fp);
		while (res[0] != '\0')
		{
			storeInStructMarks(marksList, res, spos);
			spos++;
			res = getLine(fp);
		}
	}
	if (dupval != 0)
	{
		rewind(fp);
		res = getLine(fp);
		res = getLine(fp);
		int dupos = dupval - 1;
		while (res[0] != '\0')
		{
			storeInStructMarks(marksList, res, dupos);
			dupos++;
			res = getLine(fp);
		}
		//hash();
	}

}


void loadInfo(char* fname)
{
	FILE* fp2;
	fp2 = fopen(fname, "r");
	char* res;
	int i = 0;
	res = getLine(fp2);
	while (res[0] != '\0')
	{
		res = getLine(fp2);
	}
	rewind(fp2);
	if (infoList == NULL)
	{
		infoList = (struct StudentInfo**)malloc(infosize*sizeof(struct StudentInfo*));
		for (i = 0; i<infosize; i++)
			infoList[i] = (struct StudentInfo*)malloc(sizeof(struct StudentInfo));
	}
	if (pos == infosize)
	{
		// printf("here");
		infosize *= 2;
		struct StudentInfo** tmp = (struct StudentInfo**)malloc(infosize*sizeof(struct StudentInfo*));
		for (i = 0; i<infosize; i++)
			tmp[i] = (struct StudentInfo*)malloc(sizeof(struct StudentInfo));
		for (i = 0; i<infosize / 2; i++)
			tmp[i] = infoList[i];
		infoList = tmp;
		// free(tmp);
	}
	res = getLine(fp2);
	res = getLine(fp2);
	while (res[0] != '\0')
	{
		storeInStructInfo(infoList, res, pos);
		pos++;
		res = getLine(fp2);
	}
}
/*void dispAvg(struct StudentMarks** marksList)
{
int i;
for(i=0;i<spos;i++)
printf("%3d %16s %3d %3d %3d %3d %.2f\n",marksList[i]->rollno,marksList[i]->name,marksList[i]->m1,marksList[i]->m2,marksList[i]->m3,marksList[i]->m4,marksList[i]->avg);
}*/
void compAvg(struct StudentMarks** marksList)
{
	int i = 0;
	for (i = 0; i<spos; i++)
	{
		marksList[i]->avg = (marksList[i]->m1 + marksList[i]->m2 + marksList[i]->m3 + marksList[i]->m4) / 4.0;
	}

	// dispAvg(marksList);

}
int findGpa(int mrks)
{
	if (mrks>90 && mrks <= 100)
		return 10;
	else if (mrks>80 && mrks <= 90)
		return 9;
	else if (mrks>70 && mrks <= 80)
		return 8;
	else if (mrks>600 && mrks <= 70)
		return 7;
	else if (mrks>50 && mrks <= 60)
		return 6;
	else if (mrks>40 && mrks <= 50)
		return 5;
	else if (mrks>30 && mrks <= 40)
		return 4;
	else if (mrks>20 && mrks <= 30)
		return 3;
	else if (mrks>10 && mrks <= 20)
		return 2;
	else if (mrks>0 && mrks <= 10)
		return 1;
	else
		return 0;

}
/*void dispCgpa(struct StudentMarks** marksList)
{
int i;
for(i=1;i<spos;i++)
printf("%3d %16s %3d %3d %3d %3d %.2f %.2f\n",marksList[i]->rollno,marksList[i]->name,marksList[i]->m1,marksList[i]->m2,marksList[i]->m3,marksList[i]->m4,marksList[i]->avg,marksList[i]->cgpa);
}*/

void compCgpa(struct StudentMarks** marksList)
{
	int i = 0;
	for (i = 0; i<spos; i++)
	{
		marksList[i]->cgpa = (findGpa(marksList[i]->m1) + findGpa(marksList[i]->m2) + findGpa(marksList[i]->m3) + findGpa(marksList[i]->m4)) / 4.0;

	}
	//dispCgpa(marksList);

}
void save(struct StudentMarks** marksList)
{
	char fname3[100];
	int i = 0;
	printf("enter saving filename: ");
	scanf("%s", &fname3);
	FILE* fp3;
	fp3 = fopen(fname3, "w");
	for (i = 0; i<spos; i++)
		fprintf(fp3, "%d %s %d %d %d %d %f %f\n", marksList[i]->rollno, marksList[i]->name, marksList[i]->m1, marksList[i]->m2, marksList[i]->m3, marksList[i]->m4, marksList[i]->avg, marksList[i]->cgpa);

}
void join(struct StudentMarks** marksList, struct StudentInfo** infoList)
{
	int i, j, flag = 0;
	for (i = 0; i<spos; i++)
	{
		for (j = 0; j < pos; j++)
		{
			if (marksList[i]->rollno == infoList[j]->rollno)
			{
				printf("%3d %16s %3d %3d %3d %3d %.2f %.2f %20s %20s %20s %20s\n", marksList[i]->rollno, marksList[i]->name, marksList[i]->m1, marksList[i]->m2, marksList[i]->m3, marksList[i]->m4, marksList[i]->avg, marksList[i]->cgpa, infoList[j]->phno, infoList[j]->address, infoList[j]->city, infoList[j]->pincode);
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			printf("%3d %16s %3d %3d %3d %3d %.2f %.2f NA  NA  NA  NA\n", marksList[i]->rollno, marksList[i]->name, marksList[i]->m1, marksList[i]->m2, marksList[i]->m3, marksList[i]->m4, marksList[i]->avg, marksList[i]->cgpa);
		flag = 0;


	}
}

void printQuery(int mr, int i, int opr, int val)
{
	if (opr == 1 && mr>val)
		printf("%16s  %3d\n", marksList[i]->name, mr);
	if (opr == 2 && mr<val)
		printf("%16s  %3d\n", marksList[i]->name, mr);
	if (opr == 3 && mr >= val)
		printf("%16s  %3d\n", marksList[i]->name, mr);
	if (opr == 4 && mr <= val)
		printf("%16s  %3d\n", marksList[i]->name, mr);
	if (opr == 5 && mr == val)
		printf("%16s  %3d\n", marksList[i]->name, mr);

}
void printFQuery(float mr, int i, int opr, float val)
{
	if (opr == 1 && mr>val)
		printf("%16s  %.2f\n", marksList[i]->name, mr);
	if (opr == 2 && mr<val)
		printf("%16s  %.2f\n", marksList[i]->name, mr);
	if (opr == 3 && mr >= val)
		printf("%16s  %.2f\n", marksList[i]->name, mr);
	if (opr == 4 && mr <= val)
		printf("%16s  %.2f\n", marksList[i]->name, mr);
	if (opr == 5 && mr == val)
		printf("%16s  %.2f\n", marksList[i]->name, mr);

}
void queryEval(char* col, int opr, int ival, float fval)
{
	int i;
	for (i = 0; i<spos; i++)
	{
		if (strcmp(col, "rollno") == 0)
			printQuery(marksList[i]->rollno, i, opr, ival);
		if (strcmp(col, "m1") == 0)
			printQuery(marksList[i]->m1, i, opr, ival);
		if (strcmp(col, "m2") == 0)
			printQuery(marksList[i]->m2, i, opr, ival);
		if (strcmp(col, "m3") == 0)
			printQuery(marksList[i]->m3, i, opr, ival);
		if (strcmp(col, "m4") == 0)
			printQuery(marksList[i]->m4, i, opr, ival);
		if (strcmp(col, "avg") == 0)
			printFQuery(marksList[i]->avg, i, opr, fval);
		if (strcmp(col, "cgpa") == 0)
			printFQuery(marksList[i]->cgpa, i, opr, fval);
	}
}
void queryEvalName(char* sval)
{
	int i;
	for (i = 0; i < spos; i++)
	{
		char* evalname = marksList[i]->name;
		int j = 0,k = 0;
		while (evalname[j] != '\0')
		{
			if (sval[k] == evalname[j])
			{
				j++;
				k++;
			}
			else
			j++;
		}
		if (sval[k] == '\n')
			printf("%s\n", marksList[i]->name);
	}
}

void opAnalyzer(char* col, char* op, int ival, float fval,char* sval)
{
	if (strcmp(op, "GT") == 0 || strcmp(op, "gt") == 0)
		queryEval(col, 1, ival, fval);
	else if (strcmp(op, "LT") == 0 || strcmp(op, "lt") == 0)
		queryEval(col, 2, ival, fval);
	else if (strcmp(op, "GE") == 0 || strcmp(op, "ge") == 0)
		queryEval(col, 3, ival, fval);
	else if (strcmp(op, "LE") == 0 || strcmp(op, "le") == 0)
		queryEval(col, 4, ival, fval);
	else if (strcmp(op, "EQ") == 0 || strcmp(op, "eq") == 0)
		queryEval(col, 5, ival, fval);
	else if (strcmp(op, "contains") == 0)
		queryEvalName(sval);
	else if (strcmp(op, "startswith") == 0)
		queryEvalName(sval);
}

void queryTokenizer(char* query)
{
	char* col;
	char* op;
	char* sval;
	int ival;
	float fval;
	char* pt = strtok(query, " ");
	int ins = 0;
	while (pt != NULL)
	{
		if (ins == 0)
		{
			col = pt;
			//printf("%s\n",col);
		}
		else if (ins == 1)
		{
			op = pt;
			//printf("%s\n",op);
		}
		else if (ins == 2)
		{
			ival = atoi(pt);
			fval = atof(pt);
			sval = pt;
			//printf("%d",val);
		}
		ins++;
		pt = strtok(NULL, " ");
		if (ins == 3)
			break;
	}
	opAnalyzer(col, op, ival, fval,sval);
}
char* findStri(char* ip, int i,int count)
{
	char* str = (char*)malloc(10 * sizeof(char));
	int j = 0;
	if (count != 3)
	{
		while (ip[i] != ' ')
		{
			str[j] = ip[i];
			j++;
			i++;
		}
		str[j] = '\0';
		return str;
	}
	if (count == 3)
	{
		while (ip[i] !='\0')
		{
			str[j] = ip[i];
			j++;
			i++;
		}
		str[j] = '\0';
		return str;
	}
}
char* findStrg(char* grmr, int i)
{
	char* str = (char*)malloc(10 * sizeof(char));
	int j = 0;
	while (grmr[i] != ' '&& grmr[i]!='\0')
	{
		str[j] = grmr[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return str;

}
void parse(char* ip, char* grmr)
{
	int i = 0, j = 0, flag = 0,count=0;

	while (ip[i] != '\0')
	{
		while (ip[i] == grmr[j] && grmr[j] != ' ')
		{
			i++;
			j++;
			// printf("%d %d",i,j);
		}
		//printf("%s", findStrg(grmr, j++));
		hashPut(findStrg(grmr, ++j), findStri(ip, ++i,++count));
		//if(flag!=1)
		if (grmr[j+1] == '\0')
			break;
		while (grmr[j] != ' ')
			j++;	
		while (ip[i] != ' ')
			i++;
		i++;
		j++;
	}
	struct node* search = hashtable[3].head;
	queryTokenizer(search->nme);
}
void dispMenu()
{
	int ch, chload;
	printf("choice:\n1.load\n2.show rows\n3.compute avg\n4.compute cgpa\n5.save\n6.join and show\n7.simple query\n8.hash query\n9.complex query\n10.exit\n");
	scanf("%d", &ch);
	if (ch == 1
		){
		printf("choice:\n1.marks_file\n2.info_file\n");
		scanf("%d", &chload);
		char fname1[MAX_SIZE];
		char fname2[MAX_SIZE];

		if (chload == 1)
		{
			printf("enter filename:");
			scanf("%s", &fname1);
			loadMarks(fname1);
		}
		else if (chload == 2)
		{
			printf("enter filename:");
			scanf("%s", &fname2);
			loadInfo(fname2);
		}
		dispMenu();
	}
	else if (ch == 2)
	{
		printf("choice:\n1.marks_file\n2.info_file\n");
		scanf("%d", &chload);
		if (chload == 1)
			displayMarks(marksList);
		else if (chload == 2)
			displayInfo(infoList);
		dispMenu();
	}
	else if (ch == 3){
		compAvg(marksList);
		dispMenu();
	}
	else if (ch == 4){
		compCgpa(marksList);
		dispMenu();
	}
	else if (ch == 5){
		save(marksList);
		printf("........SAVED.......");
		dispMenu();
	}
	else if (ch == 6)
	{
		join(marksList, infoList);
		dispMenu();
	}
	else if (ch == 7)
	{
		char query[20];
		printf("enter query:");
		fgets(query, 20, stdin);
		fgets(query, 20, stdin);
		//printf("%s",query);
		queryTokenizer(query);
		dispMenu();

	}
	else if (ch == 8)
	{
		int ch, i;
		char roll[10], na[10];
		printf("choice:\n1.Put\n2.Get");
		scanf("%d", &ch);
		if (ch == 1)
		{
			printf("enter rollno");
			scanf("%s", &roll);
			printf("enter name");
			scanf("%s", &na);
			hashPut(roll, na);
			dispMenu();

		}
		if (ch == 2)
		{
			printf("enter rollno");
			scanf("%s", &roll);
			hashGet(roll);
			dispMenu();
		}
	}
	else if (ch == 9)
	{
		char ip[30];
		printf("enter query:");
		fgets(ip, 50, stdin);
		fgets(ip, 50, stdin);
		char* grmr = "select 1 from 2 where 3";
		parse(ip, grmr);
		dispMenu();
	}
	else if (ch == 10)
		exit(0);
}
int main()
{
	int i;
	hashtable = (struct hash*)malloc(10 * sizeof(struct hash));
	for (int i = 0; i<10; i++)
		hashtable[i].head = NULL;
	dispMenu();
	getchar();
	return 0;
}
