#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX_NUM 100 // 最大节点数量

typedef struct ArcNode  // 双向链表链接与顶点相连的节点
{
    int adjvex; // 相邻节点在数组中的位置下表
    float distance; // 相邻节点与顶点的距离
    int lineId; // 所处的线路
    struct ArcNode *prior;  // 前一个与顶点相邻的节点
    struct ArcNode *next;   // 后一个与顶点相邻的节点
} ArcNode;

typedef struct VNode    // 顶点节点
{   
    char name[20];  // 节点的站名
    ArcNode *firstArc;  // 第一个相邻的节点
} VNode;

typedef struct ALGraph  // 邻接表储存的有向图
{
    VNode *vertices[MAX_VEX_NUM];    // 顶点节点
    int heads[MAX_VEX_NUM]; // 起始节点下标
    int vexnum; // 顶点节点的个数
    int headnum;    // 起始节点的数量
} ALGraph;

void initGraph(ALGraph *Graph);   // 初始化图
void initNode(VNode *Node, char *name);     // 初始化节点
int inGraph(ALGraph *Graph, char *name); // 判断name站点是否在图中
void addVex(ALGraph *Graph, VNode *Node);   // 将站点加入图中
void addArc(ALGraph *Graph, VNode *Node1, VNode *Node2, int lineId, float distance);    // 为相邻的两个站点添加线路

int main()
{
    int n, i;
    scanf("%d", &n);
    ALGraph *StationGraph = malloc(sizeof(ALGraph));  // 创建地铁线路图
    initGraph(StationGraph);
    for (i = 0; i < n; i++)
    {
        int lineId; // 线路ID
        char name[20];  // 站点名字
        float distance = -1.0; // 距离
        VNode *priorNode = NULL; // 前一个站点，用于连接后一个站点
        scanf("%d", &lineId);
        scanf("%s", name);
        while (distance != 0)
        {
            VNode *curNode; // 当前站点
            if (inGraph(StationGraph, name) != -1)  // 如果name站点已经在图中
            {
                curNode = StationGraph->vertices[inGraph(StationGraph, name)];  // 从图中取出该站点
            }
            else    // 当name站点不在图中时
            {
                curNode = malloc(sizeof(VNode)); // 创建新的站点
                initNode(curNode, name);
                addVex(StationGraph, curNode);  // 将节点加入到图中
            }
            addArc(StationGraph, priorNode, curNode, lineId, distance);   // 在当前站点与前一个站点见添加线路
            priorNode = curNode;
            scanf("%f", &distance);
            if (distance == 0)
            {
                break;
            }
            scanf("%s", name);
        }
    }
    // 输出图
    for (i = 0; i < StationGraph->headnum; i++)
    {
        int priorvex = -1;  // 前一个站点的下标
        int vex = StationGraph->heads[i];   // 当前站点的下标
        int lineId = StationGraph->vertices[vex]->firstArc->lineId;   // 取出lineId
        VNode *curNode = StationGraph->vertices[vex];   // 当前节点
        printf("%d", lineId);
        char *name = curNode->name;
        float distance;
        printf(" %s", name);
        while (1)
        {
            ArcNode *tmp = curNode->firstArc;   // 当前节点的邻接站点
            while (tmp != NULL) // 找到lineId与当前线路lineId相同，且指向后的邻接站点
            {
                if (tmp->lineId != lineId || tmp->adjvex == priorvex)
                {
                    tmp = tmp->next;
                }
                else
                {
                    break;
                }
            }
            
            if (tmp != NULL)    // 若当前站点不为结尾站点，则存在指向后的路线，输出该路线信息
            {
                priorvex = vex;
                vex = tmp->adjvex;
                curNode = StationGraph->vertices[vex];
                name = curNode->name;
                distance = tmp->distance;
                printf(" %.02f %s", distance, name);
            }
            else    // 如果为结尾站点，遍历下一条线路
            {
                printf("\n");   // 换行下一条线路
                break;
            }
        }
    }
    return 0;
}


void initGraph(ALGraph *Graph)   // 初始化图
{
    Graph->vexnum = 0;  // 初始化图中储存的顶点数目
    Graph->headnum = 0; // 初始化图中的起始站点数为0
}

void initNode(VNode *Node, char *name)     // 初始化节点
{
    strcpy(Node->name, name);   // 站点名
    Node->firstArc = NULL;  // 初始化时站点无邻接点
}

int inGraph(ALGraph *Graph, char *name) // 判断name站点是否在图中
{
    int i;
    for (i = 0; i < Graph->vexnum; i++) // 遍历图的所有节点
    {
        if (strcmp(name, Graph->vertices[i]->name) == 0)  // 如果name在图中，返回其在数组中的下标
        {
            return i;
        }
    }
    return -1;  // 否则返回-1
}

void addVex(ALGraph *Graph, VNode *Node)    // 将节点储存到图中
{
    Graph->vertices[Graph->vexnum] = Node;
    Graph->vexnum++;   // 图中的顶点数量+1
}

void addArc(ALGraph *Graph, VNode *Node1, VNode *Node2, int lineId, float distance)    // 为相邻的两个站点添加线路
{
    if (distance != -1.0)   // 为-1是代表该节点为第一个节点，不存在前一个节点
    {
        int adjvex1 = inGraph(Graph, Node1->name);  // 前一个节点在数组中的下标
        int adjvex2 = inGraph(Graph, Node2->name);  // 后一个节点在数组中的下标
        ArcNode *arcNode1 = malloc(sizeof(ArcNode));    // 前一个节点的邻接节点为后一个节点
        ArcNode *arcNode2 = malloc(sizeof(ArcNode));    // 后一个节点的邻接节点为前一个节点
        arcNode1->adjvex = adjvex2;
        arcNode1->lineId = lineId;
        arcNode1->distance = distance;
        arcNode1->next = NULL;
        if (Node1->firstArc != NULL)    // 将新的邻接节点添加到节点邻接链表末尾
        {
            ArcNode *tmp = Node1->firstArc;
            while(tmp->next != NULL) tmp = tmp->next;
            arcNode1->prior = tmp;
            tmp->next = arcNode1;
        }
        else
        {
            arcNode1->prior = Node1->firstArc;
            Node1->firstArc = arcNode1;
        }
        arcNode2->adjvex = adjvex1;
        arcNode2->lineId = lineId;
        arcNode2->distance = distance;
        arcNode2->next = NULL;
        if (Node2->firstArc != NULL)    // 将新的邻接节点添加到节点邻接链表末尾
        {
            ArcNode *tmp = Node2->firstArc;
            while(tmp->next != NULL) tmp = tmp->next;
            arcNode2->prior = tmp;
            tmp->next = arcNode2;
        }
        else
        {
            arcNode2->prior = Node2->firstArc;
            Node2->firstArc = arcNode2;
        }
    }
    else    // 如果是第一个节点，将其加入到起始节点中
    {
        int adjvex = inGraph(Graph, Node2->name);
        Graph->heads[Graph->headnum] = adjvex;
        Graph->headnum++;
    }
}