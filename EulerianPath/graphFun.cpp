#include"graph.h"
#include<iostream>
#include<vector>
#include "graphFun.h"
using namespace std;

//����data�������ڽӱ��е�λ��
int LocateVex(ALGraph& G, char data_) {
	for (int i = 0; i < G.vexNum; ++i) {
		if (G.vertices[i].data == data_) {
			return i;
		}
	}
	return -1;
}

//����v�ĵ�һ���ڽӶ���
int FirstAdjVex(ALGraph& G, int v) {
	if (G.vertices[v].firstArc != nullptr)		return G.vertices[v].firstArc->adjvex;;
	return -1;

}

//����v��������ڽӵ�w����һ���ڵ�
int NextAdjVex(AlGraph& G, int v, int w) {
	for (auto p = G.vertices[v].firstArc; p; p = p->nextArc) {
		if (p->adjvex == w && p->nextArc)	return p->nextArc->adjvex;
	}
	return -1;
}

//ɾ����
void DeleteArch(ALGraph& G, char v1, char v2) {
	int i = LocateVex(G, v1);
	int j = LocateVex(G, v2);

	//��Ϊ����ͼ��ɾ����Ӧ�������߽ڵ�
	if (G.kind == 0) {
		if (G.vertices[i].firstArc && G.vertices[i].firstArc->adjvex == j) {
			auto temp = G.vertices[i].firstArc->nextArc;
			delete G.vertices[i].firstArc;
			G.vertices[i].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[i].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == j) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}
		}


		if (G.vertices[j].firstArc && G.vertices[j].firstArc->adjvex == i) {
			auto temp = G.vertices[j].firstArc->nextArc;;
			delete G.vertices[j].firstArc;
			G.vertices[j].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[j].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == i) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}

		}
	}

	//��Ϊ����ͼ��ɾ����Ӧ��һ���߽ڵ�
	else if (G.kind == 1) {//��Ϊ����ͼ��ɾ����Ӧ�������߽ڵ�
		if (G.vertices[i].firstArc && G.vertices[i].firstArc->adjvex == j) {
			auto temp = G.vertices[i].firstArc->nextArc;
			delete G.vertices[i].firstArc;
			G.vertices[i].firstArc = temp;
		}
		else {
			for (ArcNode* p = G.vertices[i].firstArc; p; p = p->nextArc) {
				if (p->nextArc && p->nextArc->adjvex == j) {
					auto q = p->nextArc;
					p->nextArc = q->nextArc;
					delete q;
					break;
				}
			}
		}


	}

	//�����Լ�
	--G.arcNum;
}

//ͼ���ӣ�ͷ�壩��
void InsertArch(ALGraph& G, char v1, char v2) {
	int i = LocateVex(G, v1);
	int j = LocateVex(G, v2);

	//����ͼ���������߽ڵ�
	if (i != -1 && j != -1 && G.kind == 0) {
		ArcNode* p1 = new ArcNode;
		ArcNode* p2 = new ArcNode;
		p1->adjvex = j;
		p1->nextArc = G.vertices[i].firstArc;
		G.vertices[i].firstArc = p1;

		p2->adjvex = i;
		p2->nextArc = G.vertices[j].firstArc;
		G.vertices[j].firstArc = p2;

	}

	//����ͼ����һ���߽ڵ�
	if (i != -1 && j != -1 && G.kind == 1) {
		ArcNode* p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextArc = G.vertices[i].firstArc;
		G.vertices[i].firstArc = p1;

	}
	++G.arcNum;
}

//DFS�㷨
void DFS(ALGraph& G, int v, vector<int>& visit) {
	if (G.arcNum == 0) {
		return;
	}
	visit[v] = true;
	auto p = G.vertices[v].firstArc;
	for (int w = FirstAdjVex(G, v); p; p = p->nextArc) {
		if (p != nullptr) w = p->adjvex;
		if (visit[w] == false)	DFS(G, w, visit);


	}

}

//����visit��������
bool IsBridge(ALGraph& G, int v, vector<int>& visit, vector<int>& pre_visit)
{
	visit.assign(G.vexNum, 0);
	DFS(G, v, visit);//����ɾ���ߵ��յ������ȱ���

	if (pre_visit == visit)  return false;
	return true;
}

//����ŷ����·
vector<char> Euler(ALGraph& G, int v) {

	//�ձ����ؿ�
	if (G.vexNum == 0) return {};

	vector<int> visit(G.vexNum, 0);

	//����ͨͼ�����ؿ�
	DFS(G, v, visit);
	if (find(visit.begin(), visit.end(), 0) != visit.end())	return{};
	visit.assign(G.vexNum, 0);

	//����ȶ������Ȳ�������ȣ����ؿ�
	for (int i = 0; i < G.vexNum; ++i) {

		//����ͼ���ж�������ȶ���
		if (G.kind == 0) {
			int degree = 0;//����

			for (auto p = G.vertices[i].firstArc; p; p = p->nextArc) {
				degree++;
			}

			if (degree % 2 == 1) {
				return {};
			}
		}

		//����ͼ���ж������ж������==���
		if (G.kind == 1) {
			int inDegree = 0;//����
			int outDegree = 0;//���

			//�������
			for (auto p = G.vertices[i].firstArc; p; p = p->nextArc) {
				++outDegree;
			}

			//�������
			for (int j = 0; j < G.vexNum; ++j) {
				for (auto p = G.vertices[j].firstArc; p; p = p->nextArc) {
					if (p->adjvex == i) {
						++inDegree;
					}
				}
			}

			if (inDegree != outDegree) {
				return {};
			}
		}

	}


	//����ŷ����·,��ʼ����ŷ����·
	
	vector<char> circuit;
	vector<int> pre_visit;
	int allArcNum = G.arcNum;
	int start = v;

	while (circuit.size() <= allArcNum - 1) {//����·���ϲ����ɻ�·
				
		circuit.push_back(G.vertices[v].data);
		auto tempv = G.vertices[v].firstArc->adjvex;

		if (G.vertices[v].firstArc != nullptr && (G.vertices[v].firstArc->nextArc) == nullptr) {//����ڵ�ֻ��һ����
			DeleteArch(G, G.vertices[v].data, G.vertices[tempv].data);
			v = tempv;
			continue;//ɾ���ñߺ��������һ�ڵ�
		}
		pre_visit.assign(G.vexNum, 0);
		DFS(G, tempv, pre_visit);
		DeleteArch(G, G.vertices[v].data, G.vertices[tempv].data);//ɾ���ڽӱ���һ����

		if (IsBridge(G, tempv, visit, pre_visit)) {//����˱�Ϊ��
			InsertArch(G, G.vertices[tempv].data, G.vertices[v].data);//���²���˱�

			for (auto p = G.vertices[v].firstArc->nextArc, q = G.vertices[v].firstArc; q && p; p = p->nextArc, q = q->nextArc) {//���Ϊ�Ų��ұ߲�Ψһ

				tempv = p->adjvex;

				pre_visit.assign(G.vexNum, 0);
				DFS(G, tempv, pre_visit);

				DeleteArch(G, G.vertices[v].data, G.vertices[p->adjvex].data);//����ɾ����һ����

				if (IsBridge(G, tempv, visit, pre_visit)) {//���Ϊ��
					//�ڶ�Ӧλ�����²���ñ�(����ͼ��
					if (G.kind == 0) {
						auto pData1 = new ArcNode;
						auto pData2 = new ArcNode;

						pData1->adjvex = tempv;
						pData1->nextArc = q->nextArc;
						q->nextArc = pData1;
						p = q->nextArc;

						pData2->adjvex = G.vertices[v].data;
						pData2->nextArc = G.vertices[tempv].firstArc;
						G.vertices[tempv].firstArc = pData2;
						++G.arcNum;
					}
					//�ڶ�Ӧλ�����²���ñ�(����ͼ)
					if (G.kind == 1) {
						auto pData1 = new ArcNode;

						pData1->adjvex = tempv;
						pData1->nextArc = q->nextArc;
						q->nextArc = pData1;
						p = q->nextArc;
						++G.arcNum;
					}


				}

				else {//�����Ϊ��
					v = tempv;//����һ�ڵ�
					break;//�����˽ڵ�ı�����
				}
			}
		}

		else {//��Ϊ�ţ�����һ������
			v = tempv;
		}

	}

	circuit.push_back(G.vertices[start].data);
	return circuit;
}
