#ifndef MYGRAPH_H
#define MYGRAPH_H
#include<QDebug>
#include <iostream>
#include<iomanip>
#include<stdlib.h>
#include<stack>
#include <set>
using namespace std;
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 20 //最大顶点数
#define INFINITE -1//用-1代表邻接矩阵中的无穷大
typedef int Status;
//边
typedef struct ArcNode {
    int weight;             //边权
    int ee;
    int el;
}ArcNode;
//点
typedef struct VNode {
    int data;	                    //点数据
    VNode* nextVex;                 //邻接表下一个顶点
}VNode, AdjList[MAX_VERTEX_NUM];    //表头结点
//图
class MyGraph {
public:
    AdjList vexs; 			//顶点向量
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 		//邻接矩阵
    int vexNum;             //图的顶点数
    int arcNum; 	        //图的弧数
    int* topoVexs; 		    //拓扑向量
    int* cPVexs; 		    //关键路径向量
    int* indegree;          //点的入度
    int* indegreeC;          //点的入度
    int* ve;                //事件的最早发生时间
    int* vl;                //事件的最迟发生时间
    bool ifO;               //是否有回路
    stack <int> T;
    std::set<int> cPVexsT;
    //算入度
    void FindInDegree(MyGraph& G);
    //创建邻接表
    void CreateAdjlist(MyGraph& G);
    //求各顶点最早发生时间ve和得到一个拓扑序列顶点栈，以及判断是否有回路
    void TopologicalOrder(MyGraph& G);
    //求顶点时间最迟发生时间vl，以及输出关键活动。
    Status CriticalPath(MyGraph& G);
    //创建图
    Status CreatDG(MyGraph& G);
    //打印邻接表
    void PrintMGraph(MyGraph G);
};

#endif // MGRAPH_H
