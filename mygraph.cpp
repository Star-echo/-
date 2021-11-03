#include "mygraph.h"
//算入度
void MyGraph::FindInDegree(MyGraph& G) {
    G.indegree = new int[G.vexNum];
    G.indegreeC = new int[G.vexNum];
    for (int i = 0; i < G.vexNum; i++) G.indegree[i] = 0,G.indegreeC[i] = 0;//初始化
    for (int j = 0; j < G.vexNum; j++) {
        for (int i = 0; i < G.vexNum; i++) {
            if (G.arcs[i][j].weight != 0 && G.arcs[i][j].weight != -1) G.indegree[j]++,G.indegreeC[j]++;
        }
    }
}
//创建邻接表
void MyGraph::CreateAdjlist(MyGraph& G) {
    VNode* p;
    for (int i = 0; i < G.vexNum; i++) G.vexs[i].nextVex = NULL;
    for (int i = 0; i < G.vexNum; i++) {
        for (int j = 0; j < G.vexNum; j++) {
            if (G.arcs[i][j].weight != 0 && G.arcs[i][j].weight != -1) {
                p = (VNode*)malloc(sizeof(VNode));
                if (p) {
                    p->data = j;
                    p->nextVex = G.vexs[i].nextVex;
                    G.vexs[i].nextVex = p;
                }
            }
        }
    }
    return;
}
//求各顶点最早发生时间ve和得到一个拓扑序列顶点栈，以及判断是否有回路
void MyGraph::TopologicalOrder(MyGraph& G) {
    FindInDegree(G);
    stack<int> s;
    G.ve = new int[G.vexNum];
    G.topoVexs = new int[G.vexNum];
    for (int i = 0; i < G.vexNum; i++) {
        G.ve[i] = 0;
        if (!G.indegree[i]) s.push(i);//入度为0入栈
    }
    int count = 0, i;
    VNode* q;
    VNode* k;
    while (!s.empty()) {
        i = s.top();
        s.pop();
        G.T.push(i);
        G.topoVexs[count++] = i;
        q = &G.vexs[i];
        for (k = G.vexs[i].nextVex; k != NULL; k = k->nextVex) {
            if (!(--G.indegree[k->data])) s.push(k->data);
            if (G.ve[i] + G.arcs[q->data][k->data].weight > G.ve[k->data]) {
                G.ve[k->data] = G.ve[i] + G.arcs[q->data][k->data].weight;
            }
        }
    }
    //for (int i = 0; i < G.vexNum; i++) cout << "ve" << i << " " << G.ve[i] << " " << endl;
    if (count < G.vexNum) G.ifO = 1;
}
//求顶点时间最迟发生时间vl，以及输出关键活动。
Status MyGraph::CriticalPath(MyGraph& G) {
    if (G.ifO) return ERROR;    //有环
    G.vl = new int[G.vexNum];
    G.cPVexs = new int[G.vexNum];
    int i;
    for (i = 0; i < G.vexNum; i++) G.vl[i] = G.ve[G.vexNum - 1];

    for (i = 0; i < G.vexNum; i++)
        for (int j = 0; j < G.vexNum; j++) G.arcs[i][j].ee = -1, G.arcs[i][j].el = -1;
    VNode* q;
    VNode* k;
    while (!G.T.empty()) {
        i = G.T.top(), G.T.pop();
        q = &G.vexs[i];
        for (k = G.vexs[i].nextVex; k != NULL; k = k->nextVex) {
            if (G.vl[k->data] - G.arcs[q->data][k->data].weight < G.vl[i])
                G.vl[i] = G.vl[k->data] - G.arcs[q->data][k->data].weight;
        }
        for (i = 0; i < G.vexNum; i++) {
            q = &G.vexs[i];
            for (k = G.vexs[i].nextVex; k != NULL; k = k->nextVex) {
                G.arcs[q->data][k->data].el = G.vl[k->data] - G.arcs[q->data][k->data].weight;
                G.arcs[q->data][k->data].ee = G.ve[i];
                if (G.arcs[q->data][k->data].el == G.arcs[q->data][k->data].ee) {
                    G.cPVexsT.insert(q->data);
                    G.cPVexsT.insert(k->data);
                }

            }
        }
    }
    for (i = 0; i < G.vexNum; i++) std::cout << "vl" << i << ": " << G.vl[i] << " " << endl;
    std::cout << "ee" << ": " << endl;
    for (i = 0; i < G.vexNum; i++) {
        for (int j = 0; j < G.vexNum; j++) std::cout << G.arcs[i][j].ee << " ";
        std::cout << endl;
    }
    std::cout << "el" << ": " << endl;
    for (i = 0; i < G.vexNum; i++) {
        for (int j = 0; j < G.vexNum; j++) std::cout << G.arcs[i][j].el << " ";
        std::cout << endl;
    }
    i = 0;
    for (set<int>::iterator it = G.cPVexsT.begin(); it != G.cPVexsT.end(); it++, i++) {
        G.cPVexs[i] = *it;
    }
    std::cout << "!!" << endl;
    for (i = 0; i < G.cPVexsT.size(); i++) std::cout << G.cPVexs[i] << " ";
    std::cout << endl;
    int ti, ni;
    for (i = 0; i < G.cPVexsT.size() - 1; ) {
        ti = G.cPVexs[i];
        ni = G.cPVexs[++i];
        std::cout << "顶点：" << G.vexs[ti].data << endl;
        std::cout << "Ve: " << G.ve[ti] << " Vl: " << G.vl[ti] << endl;
        std::cout << "E: " << G.arcs[ti][ni].ee << " ";
        std::cout << "L: " << G.arcs[ti][ni].el << " ";
        std::cout << "L-E: " << G.arcs[ti][ni].ee - G.arcs[ti][ni].el << endl;
        std::cout << "顶点：" << G.vexs[ni].data << endl;
        std::cout << "Ve: " << G.ve[ni] << " Vl: " << G.vl[ni] << endl;
    }
    return OK;
}

//打印邻接表
void MyGraph::PrintMGraph(MyGraph G) {
    VNode* p;
    std::cout << "邻接表如下：" << endl;
    for (int i = 0; i < G.vexNum; i++) {
        //cout << G.vexs[i].data << "-->";
        std::cout << i << "|-->";
        p = G.vexs[i].nextVex;
        while (p) {
            std::cout << (int)p->data << ' ';
            p = p->nextVex;
        }
        std::cout << endl;
    }
}

Status MyGraph::CreatDG(MyGraph& G) {
    CreateAdjlist(G);
    PrintMGraph(G);
    TopologicalOrder(G);
    if (G.ifO) return ERROR;
    else CriticalPath(G);
    return OK;
}

