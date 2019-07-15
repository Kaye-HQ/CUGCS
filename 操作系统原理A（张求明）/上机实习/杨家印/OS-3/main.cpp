//
//  main.cpp
//  OS-3
//
//  Created by 杨 on 2018/6/12.
//  Copyright © 2018年 杨. All rights reserved.
//
#include <iostream>
#include <iomanip>
using namespace std;

int maxsize=512;
int minsize=5;     //碎片最小值
int count1=0;
int count2=0;
#define  M  10       //系统允许的空闲区表最大为m
#define  N  10       //系统允许的最大作业数量为n

struct{              //已分配表
    float address;   //已分配区起始地址
    float len;       //已分配区长度
    int flag;        //已分配区表登记栏标志，"0"表示空栏目
}used[N];

struct{              //空闲区表
    float address;   //空闲区起始地址
    float len;       //空闲区长度
    int flag;        //空闲区表登记栏标志，用"0"表示空栏目，用"1"表示未分配
}frees[M];


void init(void){            //初始化两个表
    int a;
    for(a=0; a<=N-1; a++)
    used[a].flag=0;         //已分配表的表项全部置为空表项
    frees[0].address=1000;  //初始位置设为1000，利于show()的排列
    frees[0].len=maxsize;   //初始内存大小
    frees[0].flag=1;        //空闲区表的表项全部为未分配
}

int distribute(int name, float n_len){          //动态分区
    int i, k=-1;                                //k用于定位在空闲表中选择的未分配栏
    float  ads,len;
    int count=0;
    i=0;
    while(i<=M-1){                              //寻找最佳的空闲分区
        if(frees[i].flag==1 && n_len<=frees[i].len){
            count++;
            if(count==1||frees[i].len < frees[k].len)
            k=i;
        }
        i=i+1;
    }
    if(k!=-1){
        if((frees[k].len-n_len)<=minsize)      //整体分配
        {
            frees[k].flag=0;
            ads=frees[k].address;
            len=frees[k].len;
        }
        else{                                   //切割空闲区
            ads=frees[k].address;
            len=n_len;
            frees[k].address+=n_len;
            frees[k].len-=n_len;
        }
        i=0;
        while(used[i].flag!=0){                 //寻找内存分配表中标志为空的项
        i=i+1;
        }
        if(i<=N-1){                             //找到，在已分配区表中登记一个表项
            used[i].address=ads;
            used[i].len=len;
            used[i].flag=name;
            count1++;
        }
        else{                                    //已分配区表长度不足
            if(frees[k].flag == 0){              //已做的整个分配撤销
                frees[k].flag=1;
                frees[k].address=ads;
                frees[k].len=len;
            }
            else{                                 //将已做的切割分配撤销
                frees[k].address=ads;
                frees[k].len+=len;
            }
            cout<<"内存分配区已满，分配失败！\n";
            return 0;
        }
    }
    else{
        cout <<"无法为该作业找到合适分区！\n";
        return 0;
    }
    return name;
}

int release(int name)                         //释放函数
{
    int y=0;
    float ads, len;
    int i,j,k;                                //j栏是下邻空闲区，k栏是上栏空闲区
    int x;
    while(y<=N-1&&used[y].flag!=name){
         y=y+1;
    }
    if(y<=N-1){
        ads=used[y].address;
        len=used[y].len;
        used[y].flag=0;
        count2++;
    }
    else{
        cout<<"该作业不存在！\n";
        return 0;
    }
    j=k=-1;
    i=0;
    while(!(i>=M||(k!=-1&&j!=-1))){       //修改空闲分区表
        if(frees[i].flag==1){
            if((frees[i].address+frees[i].len)==ads)
                k=i;                     //判断是否有上邻接
            if((ads+len)==frees[i].address)
                j=i;                     //判断是否有下邻接
        }
        i=i+1;
    }
    //合并空闲区
    if(k!=-1)                            //回收区有上邻接
    {
        if(j!=-1){                       //回收区也有下邻接，和上下邻接合并
            frees[k].len+=frees[j].len+len;
            frees[j].flag=0;             //将第j栏的标记置为'0'
        }
        else                             //不存在下邻接，和上邻接合并
            frees[k].len+=len;
    }
    else if(j!=-1){                      //只有下邻接，和下邻接合并
        frees[j].len+=len;
        frees[j].address=ads;
    }
    else{                                //上下邻接都没有
        x=0;
        while(frees[x].flag!=0)
            x=x+1;                       //在空闲区表中查找一个状态为'0'的栏目
        if(x<=M-1){                      //找到后，在空闲分区中登记回收的内存
            frees[x].address=ads;
            frees[x].len=len;
            frees[x].flag=1;
        }
        else{                            //空闲表已满，执行回收失败
            used[y].flag=name;
            cout<<"空闲区已满，回收失败！\n";
            return 0;
        }
    }
    return name;
}

void show(){                             //显示内存分配情况
    cout<<"地址"<<setw(10)<<"大小"<<setw(10)<<"状态"<<setw(15)<<"作业名"<<endl;
    for(int j=0;j<count1;j++)
        if(used[j].flag!=0)
            cout<<used[j].address<<setw(6)<<used[j].len<<setw(13)<<"已分配"<<setw(8)<<used[j].flag<<endl;
    for(int i=0;i<=count2;i++)
        if(frees[i].flag!=0)
            cout<<frees[i].address<<setw(6)<<frees[i].len<<setw(10)<<"空闲"<<endl;
    cout<<endl;
}
int main(){
    int a;
    int name;
    float memory;
    bool flag=false;
    cout<<endl;
    cout<<"选择操作:\n";
    init();
    while(!flag){
        cout<<"1、分配内存  2、回收内存  3、查看分配  0: 退出 \n";
        cout<<endl;;
        cout<<"选项:";
        cin>>a;
        if(a==0)
                flag=true;
        else if(a==1){
                cout<<"输入作业号和所需内存：";
                cin>>name>>memory;
                if(name!=0&&memory!=0){
                distribute(name,memory);
                    cout<<"该作业已成功获得分配空间!"<<endl;
                    cout<<endl;
                }
                else if(name==0)
                cout<<"作业号不能为零!\n请重新选择操作：\n";
                else if(memory==0)
                cout<<"内存分配数不能为零!\n请重新选择操作：\n";
        }
        else if(a==2){
                int ID;
                cout<<"输入要释放的作业号：";
                cin>>ID;
                if(ID!=0)
                    release(ID);
        }
        else{
                show();
        }
    }
    return 0;
}

