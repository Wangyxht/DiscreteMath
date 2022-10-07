#ifndef Graph_H
#define Graph_H

#define UN_DIRECTED 0//����ͼ����Ϊ1
#define DIRECTED 1//����ͼ����Ϊ0
//�� ���
struct arcNode {
	int adjvex;//�ñ�ָ�򶥵�λ��
	arcNode* nextArc;//ָ����һ���߽ڵ��ָ��	
};

using ArcNode = arcNode;
//ͷ ���
struct Vnode {
	char data;//�������Ϣ
	ArcNode* firstArc;//ָ���һ���ߵ�ָ��

};
using VNode = Vnode;
using AdjList = Vnode*;

struct AlGraph {
	AdjList vertices;//����
	int arcNum;//����
	int vexNum;//�ڵ���
	int kind;//ͼ������
	AlGraph() :vertices(nullptr), arcNum(0), vexNum(0), kind(0) {};
};

using ALGraph = AlGraph;


#endif // !Graph_H

