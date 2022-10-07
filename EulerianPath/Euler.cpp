#include"graph.h"
#include"graphFun.h"
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;


int main(int argv, char* argc[]) {
	ALGraph G;

	clock_t t1 = clock();

	//���붥������������
	cout << "�����붥����:";
	cin >> G.vexNum;

	cout << "�����������";
	cin >> G.arcNum;

	cout << "ȷ��1Ϊ����ͼ��0Ϊ����ͼ��";
	cin >> G.kind;

	//���붥���
	G.vertices = new VNode[G.vexNum];
	for (int i = 0; i < G.vexNum; ++i) {
		cout << "�������" << i + 1 << "���������Ϣ:";
		cin >> G.vertices[i].data;
		G.vertices[i].firstArc = nullptr;
	}
	//����߽ڵ�
	for (int i = 0; i < G.arcNum; ++i) {
		char vexData1, vexData2;
		cout << "�������" << i + 1 << "���ߵ�������յ�:";
		cin >> vexData1 >> vexData2;

		int v1 = LocateVex(G, vexData1);
		int v2 = LocateVex(G, vexData2);
		if (v1 != -1 && v2 != -1 && G.kind == 0) {//���������ڽӱ���Ҫ�洢�����ڵ�
			ArcNode* p1 = new ArcNode;
			ArcNode* p2 = new ArcNode;
			p1->adjvex = v2;
			p1->nextArc = G.vertices[v1].firstArc;
			G.vertices[v1].firstArc = p1;

			p2->adjvex = v1;
			p2->nextArc = G.vertices[v2].firstArc;
			G.vertices[v2].firstArc = p2;

		}

		if (v1 != -1 && v2 != -1 && G.kind == 1) {//��������ͼ�����ڽӱ������洢һ���ڵ�
			ArcNode* p1 = new ArcNode;
			p1->adjvex = v2;
			p1->nextArc = G.vertices[v1].firstArc;
			G.vertices[v1].firstArc = p1;

		}

	}

	//����ŷ����·
	vector<char> euler = Euler(G, 0);

	system("cls");
	//��ʾŷ����·��
	if (euler.empty()) {
		cout << "��ͼ��ŷ����·" << endl;
	}

	else {
		for (auto it = euler.cbegin(); it != euler.cend(); it++) {
			cout << (*it);
			if (it != euler.cend() - 1) {
				cout << "����>";
			}
		}
		cout << endl;
	}

	clock_t t2 = clock();
	cout << "ִ��ʱ�䣺" << (double)(t2 - t1) / CLOCKS_PER_SEC << "ms" << endl;

	system("pause");
	return EXIT_SUCCESS;

}