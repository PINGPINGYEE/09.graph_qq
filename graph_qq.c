
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
        fprintf(stderr, "그래프: 정점의 개수 초과");
        return;
    }
    g->n++;
}

void insertEdge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n)
    {
        fprintf(stderr, "그래프: 정점 번호 오류");
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

// 아래부터 queue생성
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
        fprintf(stderr, "큐가 포화상태입니다.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->data[q->rear] = item;
}

int dequeue(QueueType* q) {
    if (isEmpty(q)) {
        fprintf(stderr, "큐가 공백상태입니다.\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX;
    return q->data[q->front];
}

int visited[MAX];
int parent[MAX];

// dfs 스택 사용하여 제작
void dfsMatStack(GraphType* g, int start, int end)
{
    int w;
    int* stack = (int*)malloc(g->n * sizeof(int)); // stack 동적할당
    int top = -1;

    stack[++top] = start; // stack에 첫 값 push
    visited[start] = 1;
    parent[start] = -100; // 이후 출력을 위한 초기값

    while (top != -1) {

        int v = stack[top--]; // pop

        if (v == end) {
            int path[MAX];
            int pathIndex = 0;
            while (v != -100) { // 초기값과 같을때까지 경로 출력
                path[pathIndex++] = v;
                v = parent[v];
            }
            printf("\n최종경로\n");
            for (int i = pathIndex - 1; i >= 0; i--) {
                printf("%d ", path[i]);
                if (i > 0) {
                    printf("-> ");
                }
            }
            printf("\n탐색 성공 : %d\n", end);
            break;
        }

        for (w = 0; w < g->n; w++) {
            if (g->adjMat[v][w] && !visited[w]) {
                stack[++top] = w; // stack에 push
                visited[w] = 1;
                parent[w] = v;
                printf("정점 %d -> ", w);
                visitCount++;
            }
        }
    }
    free(stack);
}

// queue를 이용한 bfs
void bfsMatQueue(GraphType* g, int start, int end) {
    int w;
    QueueType q;
    initQueue(&q);

    enqueue(&q, start); // queue에 초기값 input
    visited[start] = 1;
    parent[start] = -100; // 이후 출력을 위한 기준값

    while (!isEmpty(&q)) {
        int v = dequeue(&q); // v를 dequeue값으로 설정
        //printf("정점 %d -> ", v);
        if (v == end) {
            int path[MAX];
            int pathIndex = 0;
            while (v != -100) { // 기준값이 나오기 전까지 경로 출력
                path[pathIndex++] = v;
                v = parent[v];
            }
            printf("\n최종경로\n");
            
            for (int i = pathIndex - 1; i >= 0; i--) {
                printf("%d ", path[i]);
                if (i > 0) {
                    printf("-> ");
                }
            }
            printf("\n탐색 성공 : %d\n", end);
            break;
        }

        for (w = 0; w < g->n; w++) {
            if (g->adjMat[v][w] && !visited[w]) { // g가 그래프동안, visit가 아닐 동안 탐색
                enqueue(&q, w); // enqueue
                visited[w] = 1;
                parent[w] = v;
                printf("정점 %d -> ", w);
                visitCount++;
            }
        }
    }
}

// main 함수
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

    printf("--메뉴--\n");
    printf("1. 깊이 우선 탐색\n");
    printf("2. 넓이 우선 탐색\n");
    printf("3. 종료\n");
    int num;
    int start, end;
    while (1) {
        printf("\n메뉴를 입력하세요: ");
        scanf_s("%d", &num);
        if (num == 1) {
            printf("\n\n시작 값과 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &end);
            printf("\n\nDFS 방식으로 경로 탐색\n");
            visitCount = 0;
            for (int i = 0; i < g->n; i++) {
                visited[i] = 0;
                parent[i] = -1;
            }
            dfsMatStack(g, start, end); // dfs
            printf("\n방문한 노드의 총 횟수: %d\n", visitCount);
        }
        else if (num == 2) {
            printf("\n\n시작 값과 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &end);
            printf("\n\nBFS 방식으로 경로 탐색\n");
            visitCount = 0;
            for (int i = 0; i < g->n; i++) {
                visited[i] = 0;
                parent[i] = -1;
            }
            bfsMatQueue(g, start, end); // bfs
            printf("\n방문한 노드의 총 횟수: %d\n", visitCount);
        }
        else if (num == 3) {
            break;
        }
    }

    free(g);
    return 0;
}
