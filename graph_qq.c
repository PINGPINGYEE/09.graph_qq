
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int visitCount;

typedef struct {
    int n;
    int adjMat[MAX][MAX];
} GraphType;

void init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX; r++)
        for (c = 0; c < MAX; c++)
            g->adjMat[r][c] = 0;
}

void insertVertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX)
    {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�");
        return;
    }
    g->n++;
}

void insertEdge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n)
    {
        fprintf(stderr, "�׷���: ���� ��ȣ ����");
        return;
    }
    g->adjMat[start][end] = 1;
    g->adjMat[end][start] = 1;
}

void printAdjMat(GraphType* g)
{
    for (int i = 0; i < g->n; i++)
    {
        for (int j = 0; j < g->n; j++)
            printf("%d ", g->adjMat[i][j]);
        printf("\n");
    }
}

typedef struct {
    int data[MAX];
    int front, rear;
} QueueType;

void initQueue(QueueType* q) {
    q->front = q->rear = 0;
}

int isEmpty(QueueType* q) {
    return (q->front == q->rear);
}

int isFull(QueueType* q) {
    return ((q->rear + 1) % MAX == q->front);
}

void enqueue(QueueType* q, int item) {
    if (isFull(q)) {
        fprintf(stderr, "ť�� ��ȭ�����Դϴ�.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (isEmpty(q)) {
        fprintf(stderr, "ť�� ��������Դϴ�.\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX;
    return q->data[q->front];
}

int visited[MAX];
int parent[MAX];

// dfs ���� ����Ͽ� ����
void dfsMatStack(GraphType* g, int start, int end)
{
    int w;
    int* stack = (int*)malloc(g->n * sizeof(int)); // stack �����Ҵ�
    int top = -1;

    stack[++top] = start; // stack�� ù �� push
    visited[start] = 1;
    parent[start] = -100; // ���� ����� ���� �ʱⰪ

    while (top != -1) {

        int v = stack[top--]; // pop

        if (v == end) {
            int path[MAX];
            int pathIndex = 0;
            while (v != -100) { // �ʱⰪ�� ���������� ��� ���
                path[pathIndex++] = v;
                v = parent[v];
            }
            printf("\n�������\n");
            for (int i = pathIndex - 1; i >= 0; i--) {
                printf("%d ", path[i]);
                if (i > 0) {
                    printf("-> ");
                }
            }
            printf("\nŽ�� ���� : %d\n", end);
            break;
        }

        for (w = 0; w < g->n; w++) {
            if (g->adjMat[v][w] && !visited[w]) {
                stack[++top] = w; // stack�� push
                visited[w] = 1;
                parent[w] = v;
                printf("���� %d -> ", w);
                visitCount++;
            }
        }
    }
    free(stack);
}

// queue�� �̿��� bfs
void bfsMatQueue(GraphType* g, int start, int end) {
    int w;
    QueueType q;
    initQueue(&q);

    enqueue(&q, start); // queue�� �ʱⰪ input
    visited[start] = 1;
    parent[start] = -100; // ���� ����� ���� ���ذ�

    while (!isEmpty(&q)) {
        int v = dequeue(&q); // v�� dequeue������ ����
        //printf("���� %d -> ", v);
        if (v == end) {
            int path[MAX];
            int pathIndex = 0;
            while (v != -100) { // ���ذ��� ������ ������ ��� ���
                path[pathIndex++] = v;
                v = parent[v];
            }
            printf("\n�������\n");
            
            for (int i = pathIndex - 1; i >= 0; i--) {
                printf("%d ", path[i]);
                if (i > 0) {
                    printf("-> ");
                }
            }
            printf("\nŽ�� ���� : %d\n", end);
            break;
        }

        for (w = 0; w < g->n; w++) {
            if (g->adjMat[v][w] && !visited[w]) { // g�� �׷�������, visit�� �ƴ� ���� Ž��
                enqueue(&q, w); // enqueue
                visited[w] = 1;
                parent[w] = v;
                printf("���� %d -> ", w);
                visitCount++;
            }
        }
    }
}


int main() {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);
    for (int i = 0; i < 11; i++)
        insertVertex(g, i);
    insertEdge(g, 0, 5);
    insertEdge(g, 0, 9);
    insertEdge(g, 0, 2);
    insertEdge(g, 0, 4);
    insertEdge(g, 0, 6);
    insertEdge(g, 1, 5);
    insertEdge(g, 1, 4);
    insertEdge(g, 1, 7);
    insertEdge(g, 1, 10);
    insertEdge(g, 2, 3);
    insertEdge(g, 2, 4);
    insertEdge(g, 3, 4);
    insertEdge(g, 3, 5);
    insertEdge(g, 4, 5);
    insertEdge(g, 4, 6);
    insertEdge(g, 4, 7);
    insertEdge(g, 6, 7);
    insertEdge(g, 6, 8);
    insertEdge(g, 7, 10);
    insertEdge(g, 8, 9);
    insertEdge(g, 8, 10);

    printf("--�޴�--\n");
    printf("1. ���� �켱 Ž��\n");
    printf("2. ���� �켱 Ž��\n");
    printf("3. ����\n");
    int num;
    int start, end;
    while (1) {
        printf("\n�޴��� �Է��ϼ���: ");
        scanf_s("%d", &num);
        if (num == 1) {
            printf("\n\n���� ���� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &end);
            printf("\n\nDFS ������� ��� Ž��\n");
            visitCount = 0;
            for (int i = 0; i < g->n; i++) {
                visited[i] = 0;
                parent[i] = -1;
            }
            dfsMatStack(g, start, end);
            printf("\n�湮�� ����� �� Ƚ��: %d\n", visitCount);
        }
        else if (num == 2) {
            printf("\n\n���� ���� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &end);
            printf("\n\nBFS ������� ��� Ž��\n");
            visitCount = 0;
            for (int i = 0; i < g->n; i++) {
                visited[i] = 0;
                parent[i] = -1;
            }
            bfsMatQueue(g, start, end);
            printf("\n�湮�� ����� �� Ƚ��: %d\n", visitCount);
        }
        else if (num == 3) {
            break;
        }
    }

    free(g);
    return 0;
}