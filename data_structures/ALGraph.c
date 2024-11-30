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
void printLine(ALGraph *Graph, int headn);                                           // 输出线路
int inLine(ALGraph *Graph, char *name, int lineId);                                  // 判断name站点是否在线路lineId上
void deleteVex(ALGraph *Graph, char *name, int lineId);                              // 删除线路lineId上的name站点
int addStation(ALGraph *Graph, int lineId);                                          // 添加站点
float findPath(ALGraph *Graph, ArcNode *path, char *name1, char *name2, int *trave);
// 查找name1和name2之间的距离, trave指向遍历过的站点，避免重复遍历   

void initGraph(ALGraph *Graph) // 初始化图
{
    Graph->vexnum = 0;  // 初始化图中储存的顶点数目
    Graph->headnum = 0; // 初始化图中的起始站点数为0
}

void initNode(VNode *Node, char *name) // 初始化节点
{
    strcpy(Node->name, name); // 站点名
    Node->firstArc = NULL;    // 初始化时站点无邻接点
}

int inGraph(ALGraph *Graph, char *name) // 判断name站点是否在图中
{
    int i;
    for (i = 0; i < Graph->vexnum; i++) // 遍历图的所有节点
    {
        if (strcmp(name, Graph->vertices[i]->name) == 0) // 如果name在图中，返回其在数组中的下标
        {
            return i;
        }
    }
    return -1; // 否则返回-1
}

void addVex(ALGraph *Graph, VNode *Node) // 将节点储存到图中
{
    Graph->vertices[Graph->vexnum] = Node;
    Graph->vexnum++; // 图中的顶点数量+1
}

void addArc(ALGraph *Graph, VNode *Node1, VNode *Node2, int lineId, float distance) // 为相邻的两个站点添加线路
{
    if (distance != -1.0) // 为-1是代表该节点为第一个节点，不存在前一个节点
    {
        int adjvex1 = inGraph(Graph, Node1->name);   // 前一个节点在数组中的下标
        int adjvex2 = inGraph(Graph, Node2->name);   // 后一个节点在数组中的下标
        ArcNode *arcNode1 = malloc(sizeof(ArcNode)); // 前一个节点的邻接节点为后一个节点
        ArcNode *arcNode2 = malloc(sizeof(ArcNode)); // 后一个节点的邻接节点为前一个节点
        arcNode1->adjvex = adjvex2;
        arcNode1->lineId = lineId;
        arcNode1->distance = distance;
        arcNode1->next = NULL;
        if (Node1->firstArc != NULL) // 将新的邻接节点添加到节点邻接链表末尾
        {
            ArcNode *tmp = Node1->firstArc;
            while (tmp->next != NULL)
                tmp = tmp->next;
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
        if (Node2->firstArc != NULL) // 将新的邻接节点添加到节点邻接链表末尾
        {
            ArcNode *tmp = Node2->firstArc;
            while (tmp->next != NULL)
                tmp = tmp->next;
            arcNode2->prior = tmp;
            tmp->next = arcNode2;
        }
        else
        {
            arcNode2->prior = Node2->firstArc;
            Node2->firstArc = arcNode2;
        }
    }
    else // 如果是第一个节点，将其加入到起始节点中
    {
        int adjvex = inGraph(Graph, Node2->name);
        Graph->heads[Graph->headnum] = adjvex;
        Graph->headnum++;
    }
}

int inLine(ALGraph *Graph, char *name, int lineId) // 判断name站点是否在线路lineId上
{
    int k = inGraph(Graph, name);
    if (k == -1)
    {
        return -1;
    }
    else
    {
        ArcNode *arc = Graph->vertices[k]->firstArc; // 取出该站点的邻接信息
        while (arc != NULL)
        {
            if (arc->lineId == lineId) // 如果站点在线路上，则返回其存储下标
            {
                return k;
            }
            arc = arc->next;
        }
    }
    return -1;
}

void printLine(ALGraph *Graph, int headn)
{
    int priorvex = -1;                                   // 前一个站点的下标
    int vex = Graph->heads[headn];                       // 当前站点的下标
    int lineId = Graph->vertices[vex]->firstArc->lineId; // 取出lineId
    VNode *curNode = Graph->vertices[vex];               // 当前节点
    printf("%d", lineId);
    char *name = curNode->name;
    float distance;
    printf(" %s", name);
    while (1)
    {
        ArcNode *tmp = curNode->firstArc; // 当前节点的邻接站点
        while (tmp != NULL)               // 找到lineId与当前线路lineId相同，且指向后的邻接站点
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

        if (tmp != NULL) // 若当前站点不为结尾站点，则存在指向后的路线，输出该路线信息
        {
            priorvex = vex;
            vex = tmp->adjvex;
            curNode = Graph->vertices[vex];
            name = curNode->name;
            distance = tmp->distance;
            printf(" %.02f %s", distance, name);
        }
        else // 如果为结尾站点，遍历下一条线路
        {
            printf("\n"); // 换行下一条线路
            break;
        }
    }
}

void deleteVex(ALGraph *Graph, char *name, int lineId) // 删除线路lineId上的name站点
{
    int k = inGraph(Graph, name);
    VNode *curNode = Graph->vertices[k];
    ArcNode *arc = curNode->firstArc;
    ArcNode *arc1 = NULL, *arc2 = NULL;
    while (arc != NULL)
    {
        if (arc->lineId == lineId)
        {
            if (arc1 == NULL)
            {
                arc1 = arc;
            }
            else
            {
                arc2 = arc;
            }
        }
        arc = arc->next;
    }
    if (arc2 == NULL) // 只有一个相邻的节点，该节点为头节点或者尾节点
    {
        int vexn = arc1->adjvex;
        int i;
        for (i = 0; i < Graph->headnum; i++) // 如果为头节点
        {
            if (k == Graph->heads[i])
            {
                Graph->heads[i] = vexn; // 将与其相邻的节点修改为头节点
            }
        }
        arc = Graph->vertices[vexn]->firstArc;
        while (arc != NULL)
        {
            if (arc->adjvex == k && arc->lineId == lineId) // 从邻接点中删除该条边
            {
                if (arc->prior != NULL)
                {
                    arc->prior->next = arc->next;
                }
                if (arc->next != NULL)
                {
                    arc->next->prior = arc->prior;
                    if (arc->prior == NULL) // arc为firstArc，需要将next设置为firstArc
                    {
                        Graph->vertices[vexn]->firstArc = arc->next;
                    }
                }
                free(arc);
                break;
            }
            arc = arc->next;
        }
        if (arc1->prior != NULL)
        {
            arc1->prior->next = arc1->next;
        }
        if (arc1->next != NULL)
        {
            arc1->next->prior = arc1->prior;
        }
        free(arc1);
    }
    else // 存在两个相邻节点
    {
        int vexn1 = arc1->adjvex, vexn2 = arc2->adjvex;
        float distance = arc1->distance + arc2->distance; // 新的距离
        ArcNode *tmparc1 = Graph->vertices[vexn1]->firstArc;
        while (tmparc1 != NULL)
        {
            if (tmparc1->adjvex == k && tmparc1->lineId == lineId)
            {
                tmparc1->adjvex = vexn2;      // 连接断开的线路
                tmparc1->distance = distance; // 为新连接的线路设置长度
                break;
            }
            tmparc1 = tmparc1->next;
        }
        ArcNode *tmparc2 = Graph->vertices[vexn2]->firstArc;
        while (tmparc2 != NULL)
        {
            if (tmparc2->adjvex == k && tmparc2->lineId == lineId)
            {
                tmparc2->adjvex = vexn1;      // 连接断开的线路
                tmparc2->distance = distance; // 为新连接的线路设置长度
                break;
            }
            tmparc2 = tmparc2->next;
        }
        if (arc1->prior != NULL)
        {
            arc1->prior->next = arc1->next;
        }
        if (arc1->next != NULL)
        {
            arc1->next->prior = arc1->prior;
        }
        free(arc1);
        if (arc2->prior != NULL)
        {
            arc2->prior->next = arc2->next;
        }
        if (arc2->next != NULL)
        {
            arc2->next->prior = arc2->prior;
        }
        free(arc2);
    }

}

int addStation(ALGraph *Graph, int lineId) // 添加站点
{
    float priorDistance, nextDistance;
    scanf("%f %f", &priorDistance, &nextDistance); // 输入到前一站和后一站的距离
    char name[20], priorName[20] = {"\0"};
    if (priorDistance != 0) // 如果前一站存在
    {
        scanf("%s", priorName);
        if (inLine(Graph, priorName, lineId) == -1) // 前一站不在线路中
        {
            return -1;
        }
    }
    scanf("%s", name);
    if (inLine(Graph, name, lineId) != -1) // 站点name已经在线路中
    {
        return -2;
    }
    VNode *curNode;
    curNode = malloc(sizeof(VNode)); // 创建新的站点
    initNode(curNode, name);
    addVex(Graph, curNode); // 将节点加入到图中
    if (priorDistance == 0) // 添加节点为头节点
    {
        int i;
        for (i = 0; i < Graph->headnum; i++)
        {
            // 找到该条线路的头节点，替换之
            VNode *headNode = Graph->vertices[Graph->heads[i]];
            if (inLine(Graph, headNode->name, lineId) != -1)
            {
                Graph->heads[i] = inGraph(Graph, name);                 // 修改头节点指向
                addArc(Graph, curNode, headNode, lineId, nextDistance); // 在新节点和原来头节点间添加边
            }
        }
    }
    else // 为普通节点
    {
        int priorVexn = inGraph(Graph, priorName);
        VNode *priorNode = Graph->vertices[priorVexn];
        ArcNode *tmparc = priorNode->firstArc;
        int nextVexn = -1;
        int first = -1;
        while (tmparc != NULL)
        {
            nextVexn = tmparc->adjvex; // 找到下一个站点
            if (inLine(Graph, Graph->vertices[nextVexn]->name, lineId) != -1)
            {
                // printf("\n%s\n", Graph->vertices[nextVexn]->name);
                if (first == -1)
                {
                    first = nextVexn;
                }
                else{
                    break;
                }
            }
            nextVexn = -1;
            tmparc = tmparc->next;
        }
        if (first != -1 && nextVexn == -1)
        {
            nextVexn = first;
        }
        if (nextVexn == -1) // 没有下一个站点，向末尾添加
        {
            addArc(Graph, curNode, priorNode, lineId, priorDistance); // 在新节点和上一个节点间添加边
        }
        else // 两头都有节点
        {
            VNode *nextNode = Graph->vertices[nextVexn]; // 下一个节点
            tmparc = priorNode->firstArc;
            while (tmparc != NULL)
            {
                if (tmparc->adjvex == nextVexn && tmparc->lineId == lineId) // 找到指向下一个节点的边，让其指向新节点
                {
                    tmparc->adjvex = inGraph(Graph, name); // 指向新节点
                    tmparc->distance = priorDistance;
                    break;
                }
                tmparc = tmparc->next;
            }
            addArc(Graph, curNode, priorNode, lineId, priorDistance); // 在新节点和上一个节点间添加边
            tmparc = nextNode->firstArc;
            while (tmparc != NULL)
            {
                if (tmparc->adjvex == priorVexn && tmparc->lineId == lineId) // 找到指向下一个节点的边，让其指向新节点
                {
                    tmparc->adjvex = inGraph(Graph, name); // 指向新节点
                    tmparc->distance = nextDistance;
                    break;
                }
                tmparc = tmparc->next;
            }
            addArc(Graph, curNode, nextNode, lineId, nextDistance); // 在新节点和上一个节点间添加边
        }
    }
    return 1;
}

float findPath(ALGraph *Graph, ArcNode *path, char *name1, char *name2, int *trave) // 查找name1和name2之间的距离
{
    // printf("==%s==", name1);
    int vexn1 = inGraph(Graph, name1);
    int vexn2 = inGraph(Graph, name2);
    path->adjvex = vexn1;
    path->prior = NULL;
    if (strcmp(name1, name2) == 0)
    {
        path->distance = 0;
        path->lineId = 0;
        path->next = NULL;
        return 0;
    }
    int thisTrave[MAX_VEX_NUM] = {0};
    int i;
    for (i = 0; i < MAX_VEX_NUM; i++)   // 复制遍历过的节点
    {
        thisTrave[i] = *(trave+i);  
    }
    // 查找线路
    float minDistance = -1;
    float tmpDistance = -1;
    ArcNode *minPath = NULL;
    ArcNode *tmp = Graph->vertices[vexn1]->firstArc;
    while (tmp != NULL) // 先将这一层所有站点加入thisTrave，防止下层再次遍历此层
    {
        thisTrave[tmp->adjvex] = 1;
        tmp = tmp->next;
    }
    tmp = Graph->vertices[vexn1]->firstArc;
    while (tmp != NULL)
    {
        if (*(trave+tmp->adjvex) == 1) // 已经遍历过的站点，跳过遍历
        {
            tmp = tmp->next;
            continue;
        }
        ArcNode *tmpPath = malloc(sizeof(ArcNode));
        char *tmpName = Graph->vertices[tmp->adjvex]->name;
        tmpDistance = findPath(Graph, tmpPath, tmpName, name2, thisTrave);  // 递归遍历相邻节点
        if (tmpDistance != -1 && (minDistance == -1 || tmpDistance + tmp->distance < minDistance)) // 新的距离为最短距离，交换min值
        {
            minDistance = tmpDistance + tmp->distance;  // tmp->distance为遍历节点到name1节点的距离
            path->distance = tmp->distance; // 记录name1站点到该站点的距离
            path->lineId = tmp->lineId;
            while (minPath != NULL)
            {
                ArcNode *tmpNode = minPath->next;
                free(minPath);
                minPath = tmpNode;
            }
            minPath = tmpPath;
        }
        tmp = tmp->next;
    }
    if (minDistance != -1)  // 存在路线
    {
        path->next = minPath;
        if (minPath != NULL)    // minPath为NULL时代表遍历到末尾
        {
            minPath->prior = path;
        }
        // printf("\n%s==%.02f\n",Graph->vertices[path->adjvex]->name, minDistance);
        return minDistance;
    }
    else    // 线路不存在
    {
        path = NULL;
        // printf("-1\n");
        return -1;
    }
}