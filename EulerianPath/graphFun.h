#pragma once
#include"graph.h"
#include<vector>
using namespace std;

//����data�������ڽӱ��е�λ��
int LocateVex(ALGraph& G, char data_);
//����v�ĵ�һ���ڽӶ���
int FirstAdjVex(ALGraph& G, int v);
//����v�������w����һ���ڵ�
int NextAdjVex(AlGraph& G, int v, int w);
//ɾ����
void DeleteArch(ALGraph& G, char v1, char v2);
//���ӱ�
void InsertArch(ALGraph& G, char v1, char v2);
//DFS�㷨
void DFS(ALGraph& G, int v, vector<int>& visit);
//�ж�ɾ���ߺ���ͼ����ͨ��
bool IsBridge(ALGraph& G, int v, vector<int>& visit, vector<int>& pre_visit);
//����ŷ����·
vector<char> Euler(ALGraph& G, int v);