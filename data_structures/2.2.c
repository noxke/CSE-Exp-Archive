#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX_NUM 100 // 最大节点数量

typedef struct ArcNode // 双向链表链接与顶点相连的节点
{
    int adjvex;            // 相邻节点在数组中的位置下标
    float distance;        // 相邻节点与顶点的距离
    int lineId;            // 所处的线路
    struct ArcNode *prior; // 前一个与顶点相邻的节点
    struct ArcNode *next;  // 后一个与顶点相邻的节点
} ArcNode;

typedef struct VNode // 顶点节点
{
    char name[20];     // 节点的站名
    ArcNode *firstArc; // 第一个相邻的节点
} VNode;

typedef struct ALGraph // 邻接表储存的有向图
{
    VNode *vertices[MAX_VEX_NUM]; // 顶点节点
    int heads[MAX_VEX_NUM];       // 起始节点下标
    int vexnum;                   // 顶点节点的个数
    int headnum;                  // 起始节点的数量
} ALGraph;

void initGraph(ALGraph *Graph);                                                      // 初始化图
void initNode(VNode *Node, char *name);                                              // 初始化节点
int inGraph(ALGraph *Graph, char *name);                                             // 判断name站点是否在图中
void addVex(ALGraph *Graph, VNode *Node);                                            // 将站点加入图中
void addArc(ALGraph *Graph, VNode *Node1, VNode *Node2, int lineId, float distance); // 为相邻的两个站点添加线路
void printLine(ALGraph *Graph, int headn);                                           // 输出线路
int inLine(ALGraph *Graph, char *name, int lineId);                                  // 判断name站点是否在线路lineId上
void deleteVex(ALGraph *Graph, char *name, int lineId);                              // 删除线路lineId上的name站点
int addStation(ALGraph *Graph, int lineId);                                          // 添加站点

int main()
{
    int n, i;
    scanf("%d", &n);
    ALGraph *StationGraph = malloc(sizeof(ALGraph)); // 创建地铁线路图
    initGraph(StationGraph);
    for (i = 0; i < n; i++)
    {
        int lineId;              // 线路ID
        char name[20];           // 站点名字
        float distance = -1.0;   // 距离
        VNode *priorNode = NULL; // 前一个站点，用于连接后一个站点
        scanf("%d", &lineId);
        scanf("%s", name);
        while (distance != 0)
        {
            VNode *curNode;                        // 当前站点
            if (inGraph(StationGraph, name) != -1) // 如果name站点已经在图中
            {
                curNode = StationGraph->vertices[inGraph(StationGraph, name)]; // 从图中取出该站点
            }
            else // 当name站点不在图中时
            {
                curNode = malloc(sizeof(VNode)); // 创建新的站点
                initNode(curNode, name);
                addVex(StationGraph, curNode); // 将节点加入到图中
            }
            addArc(StationGraph, priorNode, curNode, lineId, distance); // 在当前站点与前一个站点见添加线路
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
        printLine(StationGraph, i);
    }

    // 增、删站点
    char mode[20]; // 操作模式
    scanf("%s", mode);
    int lineId;
    scanf("%d", &lineId);
    if (strcmp(mode, "add") == 0) // 添加站点
    {
        int ret = addStation(StationGraph, lineId);
        if (ret == -1)
        {
            printf("增加失败，没有与输入的增加位置前一站点同名的站点\n");
            return 0;
        }
        else if (ret == -2)
        {
            printf("增加失败，已有同名站点\n");
            return 0;
        }
    }
    else if (strcmp(mode, "delete") == 0) // 删除站点
    {
        char name[20];
        scanf("%s", name);
        if (inLine(StationGraph, name, lineId) == -1) // 线路中没有name站点
        {
            printf("删除失败，没有同名站点\n");
            return 0;
        }
        deleteVex(StationGraph, name, lineId); // 删除线路上的该站点
    }
    for (i = 0; i < StationGraph->headnum; i++) // 输出该被修改的线路
    {
        int vex = StationGraph->heads[i];                         // 当前站点的下标
        int line = StationGraph->vertices[vex]->firstArc->lineId; // 取出lineId
        if (line == lineId)
        {
            printLine(StationGraph, i);
        }
    }
    return 0;
}

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