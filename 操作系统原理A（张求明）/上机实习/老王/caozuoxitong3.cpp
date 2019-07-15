#include<iostream>  
#include<iomanip>                 
using namespace std;
enum ZHUANGTAI { kongxian, zhanyong }; 
struct distrabuteArea {  
	int qishidizhi;               
    int daxiao;              
    int zuoyehao;             
    ZHUANGTAI state;            // ����״̬
    distrabuteArea *pre;       // ����ǰ��ָ��
    distrabuteArea *nxt;       // ��������ָ��
}disHead; 

void intdisArea() 
{  
//�����ʼ�����ڴ�
	distrabuteArea *fir = (distrabuteArea *)malloc(sizeof(distrabuteArea)); 
    // ���׸�������ֵ
    fir->qishidizhi   = 0; 
    fir->daxiao   = 512; 
    fir->state  = kongxian; 
    fir->zuoyehao = -1;  
    fir->pre    = &disHead; 
    fir->nxt    = NULL; 
    // ��ʼ������ͷ����Ϣ
    disHead.pre = NULL; 
    disHead.nxt = fir; 
} 


int shoucishiying(int zuoyehao, int daxiao) 
{  
    distrabuteArea *p = disHead.nxt; 
    while(p != NULL) 
    {  
        if(p->state == kongxian && p->daxiao >= daxiao) { 
        // �ҵ�Ҫ����Ŀ��з���
		{  
        // �����СΪdaxiao������
                distrabuteArea *node = (distrabuteArea *)malloc(sizeof(distrabuteArea));  
                node->qishidizhi = p->qishidizhi + daxiao; 
                node->daxiao = p->daxiao - daxiao; 
                node->state = kongxian; 
                node->zuoyehao = -1; 
                // �޸ķ������ڵ�ָ��
                node->pre = p;  
                node->nxt = p->nxt; 
                if(p->nxt != NULL) { 
                    p->nxt->pre  = node; 
                }  
                p->nxt = node; 
                // �����������
                p->daxiao = daxiao; 
                p->state = zhanyong; 
                p->zuoyehao = zuoyehao;  

				}  
            cout<<"����ɹ�"<<endl; 
            return 1; 
        }  
        p = p->nxt; 
    }  
    cout<<"�Ҳ������ʵ��ڴ����������ʧ��"<<endl; 
    return 0; 
} 

int zuijia(int zuoyehao, int daxiao) 
{  
    distrabuteArea *tar = NULL; 
    int tarSize = 512 + 1;  
    distrabuteArea *p = disHead.nxt; 
    while(p != NULL) 
    {  
       // Ѱ����ѿ�������
        if(p->state == kongxian && p->daxiao >= daxiao && p->daxiao < tarSize) { 
            tar = p;  
            tarSize = p->daxiao; 
        }  
        p = p->nxt; 
    }  

    if(tar != NULL) {  
        // �ҵ�Ҫ����Ŀ��з���
	{  
                // �����СΪdaxiao������
                distrabuteArea *node = (distrabuteArea *)malloc(sizeof(distrabuteArea));  
                node->qishidizhi = tar->qishidizhi + daxiao; 
                node->daxiao = tar->daxiao - daxiao; 
                node->state = kongxian; 
                node->zuoyehao = -1; 
                // �޸ķ������ڵ�ָ��
                node->pre = tar;  
                node->nxt = tar->nxt; 
                if(tar->nxt != NULL) { 
                    tar->nxt->pre  = node;  
                }  
                tar->nxt = node; 
                // �����������
                tar->daxiao = daxiao; 
                tar->state = zhanyong; 
                tar->zuoyehao = zuoyehao; 
            }  
            cout<<"����ɹ�"<<endl; 
            return 1; 
    } else {  
        cout<<"�Ҳ������ʵ��ڴ����������ʧ��"<<endl; 
        return 0; 
    } 
} 

int zuihuai(int zuoyehao, int daxiao)
{
    distrabuteArea *tar = NULL; 
    int tarSize = 512 + 1;  
    distrabuteArea *p = disHead.nxt; 
	while(p != NULL) 
    {  
       // Ѱ������������
        int tempsize;
        if(p->state == kongxian && p->daxiao >=tempsize) { 
			 tar = p;  
             tarSize = p->daxiao;
             tempsize=p->daxiao; 
        }  
        p = p->nxt; 
	} 
	if(tar != NULL && tarSize>=daxiao) {  
        // �ҵ�Ҫ����Ŀ��з���
	{  
                // �����СΪdaxiao������
                distrabuteArea *node = (distrabuteArea *)malloc(sizeof(distrabuteArea));  
                node->qishidizhi = tar->qishidizhi + daxiao; 
                node->daxiao = tar->daxiao - daxiao; 
                node->state = kongxian; 
                node->zuoyehao = -1; 
                // �޸ķ������ڵ�ָ��
                node->pre = tar;  
                node->nxt = tar->nxt; 
                if(tar->nxt != NULL) { 
                    tar->nxt->pre  = node;  
                }  
                tar->nxt = node; 
                // �����������
                tar->daxiao = daxiao; 
                tar->state = zhanyong; 
                tar->zuoyehao = zuoyehao; 
            }  
            cout<<"����ɹ�"<<endl; 
            return 1; 
    } else {  
        cout<<"�Ҳ������ʵ��ڴ����������ʧ��"<<endl; 
        return 0; 
    } 
}

int neicunhuishou(int zuoyehao) 
{  
    int flag = 0;  
    distrabuteArea *p = disHead.nxt, *pp; 
    while(p != NULL) 
    {  
        if(p->state == zhanyong && p->zuoyehao == zuoyehao) { 
            flag = 1;  
            if((p->pre != &disHead && p->pre->state == kongxian)  
                && (p->nxt != NULL && p->nxt->state == kongxian)) { 
                // ���¶��ǿ��з���
                // �Ⱥϲ�������
                pp = p; 
                p = p->pre;  
                p->daxiao =p->daxiao+ pp->daxiao; 
                p->nxt = pp->nxt; 
                pp->nxt->pre = p; 
                free(pp);  
                // ��ϲ�������
                pp = p->nxt;  
                p->daxiao = p->daxiao+pp->daxiao; 
                p->nxt = pp->nxt; 
                if(pp->nxt != NULL) { 
                    pp->nxt->pre = p; 
                }  
                free(pp);  
            } else if((p->pre == &disHead || p->pre->state == zhanyong)  
                && (p->nxt != NULL && p->nxt->state == kongxian)) { 
                // �����ǿ��з���
                pp = p->nxt;  
                p->daxiao =p->daxiao +pp->daxiao; 
                p->state = kongxian; 
                p->zuoyehao = -1; 
                p->nxt = pp->nxt; 
                if(pp->nxt != NULL) { 
                    pp->nxt->pre = p; 
                }  
                free(pp);  
            } else if((p->pre != &disHead && p->pre->state == kongxian) 
                && (p->nxt == NULL || p->nxt->state == zhanyong)) { 
                // �����ǿ��з���
                pp = p; 
                p = p->pre;  
                p->daxiao = p->daxiao+pp->daxiao; 
                p->nxt = pp->nxt; 
                if(pp->nxt != NULL) { 
                    pp->nxt->pre = p; 
                }  
                free(pp); 
            } else {  
                // ���¶���ռ�÷���
                p->state = kongxian; 
                p->zuoyehao = -1; 
            } 
        }  
        p = p->nxt; 
    }  
    if(flag == 1) { 
        cout<<"���ճɹ�"<<endl; 
        return 1; 
    } else {  
        cout<<"û��Ŀ����ҵ"<<endl; 
        return 0; 
    } 
} 


void xianshi() 
{  
    cout<<"��ǰ���ڴ����������£�"<<endl; 
    cout<<endl;  
    cout<<"��ʼ��ַ"<<" "<<"�ռ��С"<<" "<<"����״̬"<<"         "<<"��ҵ��"<<endl; 
    distrabuteArea *p = disHead.nxt; 
    while(p != NULL) 
    {  
        cout<<endl;  
        cout<<p->qishidizhi<<'\t'; 
        cout<<p->daxiao<<'\t';  
        printf("%s \t        ", p->state == kongxian ? "kongxian" : "zhanyong"); 
        if(p->zuoyehao > 0) {  
            cout<<p->zuoyehao; 
        } else {  
            cout<<"        "; 
        }  
        cout<<endl;  
        p = p->nxt; 
    } 
} 

int main() 
{  
    int option, ope, zuoyehao, daxiao; 
    intdisArea(); 
    while(1) 
    {  
		cout<<"0.�״���Ӧ�㷨"<<endl;
		cout<<"1.�����Ӧ�㷨"<<endl;
		cout<<"2.���Ӧ�㷨"<<endl;  
        cin>>option; 
        if(option == 0) {  
            cout<<"�״���Ӧ�㷨"<<endl; 
            break;  
        } else if(option == 1) {  
            cout<<"�����Ӧ�㷨"<<endl; 
            break; 
        } else if(option == 2){
			cout<<"���Ӧ�㷨"<<endl;
			break;
		}
		else {  
            cout<<"���������� 0/1"<<endl; 
        } 
    }  
    while(1) 
    {  
        cout<<endl;   
        cout<<"  1: �������       2: �ͷŷ���       0: �˳�"<<endl;  
        cin>>ope; 
        if(ope == 0) break; 
        if(ope == 1) {  
            cout<<"��������ҵ�ţ�"<<endl; 
            cin>>zuoyehao;  
            cout<<"��������ҵ������ڴ��С��"<<endl; 
			int size0;
            cin>>size0;
			daxiao=size0+1;
            if(daxiao <= 0) {  
                cout<<"���󣺷����ڴ��С����Ϊ��ֵ"<<endl; 
                continue; 
            }  
            if(option == 0) {  
                shoucishiying(zuoyehao, daxiao); 
            } else if(option ==1){  
                zuijia(zuoyehao, daxiao); 
            }  else{
				zuihuai(zuoyehao, daxiao);
			}
            xianshi(); 
        } else if(ope == 2) { 
            cout<<"������Ҫ���յ���ҵ�ţ�"<<endl; 
            cin>>zuoyehao; 
            neicunhuishou(zuoyehao); 
            xianshi(); 
        } else {  
            cout<<"�������"<<endl; 
        } 
    }  
    cout<<"����"<<endl; 
    return 0; 
} 


 
