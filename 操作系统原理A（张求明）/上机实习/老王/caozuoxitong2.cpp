#include<iostream>
using namespace std;


int main()
{   
    cout<<"           �ѷ�����Դ����	         ��Դ������"<<endl;
    cout<<"         A        B         C	  A        B         C"<<endl;
    cout<<"P1	 2        1         2	  3        4         7"<<endl;
    cout<<"P1	 2        1         2	  3        4         7"<<endl;
    cout<<"P2	 4        0         2	  1        3         4"<<endl;
    cout<<"P3	 3        0         5	  0        0         3"<<endl;
    cout<<"P4	 2        0         4	  2        2         1"<<endl;
    cout<<"P5	 3        1         4	  1        1         0"<<endl;
    int SafeCheck(int *Rest,int Continue[5][3],int alloc[5][3]);
    int available[3]= {2,3,3};//�ɷ�����Դ��
    int alloc[5][3]= {{2,1,2},{4,0,2},{3,0,5},{2,0,4},{3,1,4}};//�ѷ���
    int need[5][3]= {{3,4,7},{1,3,4},{0,0,3},{2,2,1},{1,1,0}};//����
    int request[3]= {0,0,0};//����
    int finish[5]= {0,0,0,0,0};
    int No;
    while(1)
    {
        int i,j;
        cout<<"�������Pi�������i���������Դ��: ";
        cin>>No>>request[0]>>request[1]>>request[2];	
        No=No-1;
        for(i=0; i<3; i++)
        {
            if(request[i]<=need[No][i]&&request[i]<=available[i]) continue;
            else break;
        }
        if(i<3)
        {
            cout<<"�ɷ�����Դ���� ��������"<<endl;
            continue;
        }
        else
        {
            for(j=0; j<3; j++)
            {
                available[j]=available[j]-request[j];
                alloc[No][j]=alloc[No][j]+request[j];
                need[No][j]=need[No][j]-request[j];
            }
        }
        if(SafeCheck(available,need,alloc))
        {
            for(j=0; j<3; j++)
            {
                available[j]=available[j]+request[j];
                alloc[No][j]=alloc[No][j]-request[j];
                need[No][j]=need[No][j]+request[j];
            }
            cout<<"ϵͳ���벻��ȫ״̬ ������Ч"<<endl;
        }
        else	cout<<"����ɹ�"<<endl;

    }

}
int SafeCheck(int *Rest,int Continue[5][3],int alloc[5][3]){
    int a,b,j,c;
    int work[3];
    int finish[5]= {0,0,0,0,0};

    for(b=0; b<3; b++){
        work[b]=Rest[b];
    }
    for(a=0; a<5; a++){
        for(b=0; b<5; b++)
        {
            if(finish[b]==0){
                for(j=0; j<3; j++){
                    Continue[b][j]<=work[j];
                }
                if(j<3){
                    for(c=0; c<3; c++) work[c]=work[c]+alloc[b][c];
                    finish[b]=1;
                }
            }
        }
    }
    if(b<5) return(1);
    else return(0);
}
