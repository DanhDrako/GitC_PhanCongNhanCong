#include<stdio.h>
#include<conio.h>
#define size 100

typedef struct{
	//cn: công nhân, cv: công việc, tg: thời gian
	int CN, CV, TG;
}PhanCong;

typedef struct{
	//tg: thời gian, tt: trạng thái
	//dữ liệu được đọc từ file sẽ vào trường tg, trường tt ban đầu = 0, sau đó nếu có việc làm = 1.
	int TG, TT;
}Data;

void ReadData(Data a[][size], int *n)
{
	FILE *f;
	f=fopen("textfile.txt","r");
	if(f==NULL)
	{
		printf("Loi file !");
		return;
	}
	fscanf(f, "%d", n);

	int i,j;
	for(int i=0;i<*n;i++){
		for(int j=0;j<*n;j++){
			fscanf(f, "%d", &a[i][j].TG);
			a[i][j].TT=0;
		}
	}
	fclose(f);
}

void PrintfData(Data a[size][size], int n)
{
	int i,j;
	printf("\nMa tran thoi gian da cho:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%3d", a[i][j].TG);
		printf("\n");
	}
}

void Cap_Nhat_Cong_Viec(Data a[][size], int n, int j)
{
	int i;
	for(int i=0;i<n;i++){
		a[i][j].TT=1;
	}
}

int Min_of_Row(Data a[][size], int n, int i, int *j)
{
	int TGMin=32767, k;
	for(k=0;k<n;k++){
		if(a[i][k].TT==0 && a[i][k].TG<TGMin){
			TGMin=a[i][k].TG;
			*j=k;
		}
	}
	return TGMin;
}

void Greedy(Data a[][size], int n, PhanCong PA[])
{
	int i,j;
	for(int i=0;i<n;i++){
		PA[i].CN= i+1;
		PA[i].TG=Min_of_Row(a,n,i,&j);
		PA[i].CV=j+1;
		Cap_Nhat_Cong_Viec(a,n,j);
	}
}

void PrintPA(PhanCong PA[], int n)
{
	int i, sum=0;
	printf("\nKy thuat Tham an: Nguoi chon viec\nPhuong an phan cong nhu sau:\n");

	printf("Cong nhan	Cong viec	Thoi gian thuc hien\n");
	for(int i=0;i<n;i++){
		printf("%4d		%4d%15d\n",PA[i].CN,PA[i].CV,PA[i].TG);
		sum+=PA[i].TG;
	}
	printf("Tong thoi gian thuc hien la: %d\n",sum);
}

int main()
{
	Data a[size][size];
	int n;
	ReadData(a, &n);
	PhanCong PA[n];
	PrintfData(a,n);
	Greedy(a,n,PA);
	PrintPA(PA,n);
	return 0;
}