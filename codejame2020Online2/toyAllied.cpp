#include <iostream>
#include <vector>
#include <fstream>
#include <list>
using namespace std;

#define MAX__M_N 300000
#define MAX_T 10
int idx[MAX__M_N]; //actually this is the store matrix of number of edge of a vertex
typedef long long int llint;

void initIdx()
{
    for (int i = 0; i < MAX__M_N; i++)
    {
        idx[i] = 0;
    }
}
int getCurrentIdx(const int idxCur)
{
    int ret = 0;
    for (int i = 1; i <= idxCur; i++)
    {
        ret += idx[i];
    }
    return ret;
}
int getCurrentIdxFrom(const int idxCur)
{
    int ret = 0;
    for (int i = 1; i < idxCur; i++)
    {
        ret += idx[i];
    }
    return ret;
}
void initEdgeFromInputMatrix(vector<llint> &edgeList, int **inputMatrix, int numberOfNotPair)
{
    initIdx();
    vector<llint>::iterator it_EdgeList;
    for (int i = 0; i < numberOfNotPair; i++)
    {
        int idx_add = getCurrentIdx(inputMatrix[i][0]);
        // cout << inputMatrix[i][0]<< " "<<idx_add<< endl;
        idx[inputMatrix[i][0]] += 1;

        edgeList.insert(edgeList.begin() + idx_add, inputMatrix[i][1]);
    }
}
void printEdgeList(vector<llint> edgeList, int numberOfvertex)
{
    int start = 0;
    int preIdx = 0;
    for (int i = 1; i <= numberOfvertex; i++)
    {
        if (i == 1)
            start = 0;
        else
        {
            start += idx[i - 1];
        }
        cout << "i=" << i << endl;
        for (int j = start; j < start + idx[i]; j++)
        {
            cout << edgeList.at(j) << " ";
        }
        cout << endl;
    }
    cout << "IN edge list hoan thanh" << endl;
}
void duyetDFS(bool visited[], const vector<llint> edgeList, int v)
{
    list<int> stack;
    stack.push_back(v);
    cout << "da toi tham " << v << endl;
    visited[v]=1;
    while (!stack.empty())
    {
        int vertex_x = stack.back();
        stack.pop_back();
        int idxcurrent = getCurrentIdx(vertex_x);
        int idxFrom = getCurrentIdxFrom(vertex_x);
        // cout << "idxFrom="<<idxFrom<<endl;
        // cout << "idxcurrent="<<idxcurrent<<endl;

        for (int i = idxFrom; i < idxcurrent; i++)
        {
            int nextVertx = edgeList.at(i);
            // cout << nextVertx<<" da chua toi "<<visited[nextVertx]<<endl;
            if (visited[nextVertx]==0)
            {
                visited[nextVertx]=1;
                cout << "da toi tham " << nextVertx << endl;
                // stack.push_back(vertex_x);
                stack.push_back(nextVertx);
            }
            else {
                // cout << "khong  toi tham " << nextVertx << endl;

            }
        }
    }
}
void duyetBFS(bool visited[], const vector<llint> edgeList, int v)
{
    list<int> queue;
    queue.push_back(v);
    cout << "da toi tham " << v << endl;
    visited[v]=1;
    while (!queue.empty())
    {
        int vertex_x = queue.front();
        queue.pop_front();
        int idxcurrent = getCurrentIdx(vertex_x);
        int idxFrom = getCurrentIdxFrom(vertex_x);
        // cout << "idxFrom="<<idxFrom<<endl;
        // cout << "idxcurrent="<<idxcurrent<<endl;

        for (int i = idxFrom; i < idxcurrent; i++)
        {
            int nextVertx = edgeList.at(i);
            // cout << nextVertx<<" da toi chua "<<visited[nextVertx]<<endl;
            if (visited[nextVertx]==0)
            {
                visited[nextVertx]=1;
                cout << "da toi tham " << nextVertx << endl;
                queue.push_back(vertex_x);
                queue.push_back(nextVertx);
            }
            else {
                // cout << "khong  toi tham " << nextVertx << endl;
            }
        }
    }
}
int main()
{
    vector<llint> edgeList;
    fstream f;
    f.open("./test.txt");
    int numberOfvertex;
    f >> numberOfvertex;
    int numberOfUnpair;
    f >> numberOfUnpair;
    bool *visisted=new bool[numberOfvertex+1];
    int **inputMatrix = new int *[numberOfUnpair];
    for (int i = 0; i < numberOfUnpair; i++)
    {
        int *edge = new int[2];
        f >> edge[0];
        f >> edge[1];
        inputMatrix[i] = edge;
    }
    initEdgeFromInputMatrix(edgeList, inputMatrix, numberOfUnpair);
    printEdgeList(edgeList, numberOfvertex);

    cout << "index " << endl;
    for (int i = 1; i <= numberOfvertex; i++)
    {
        visisted[i]=false;
    }

    duyetBFS(visisted,edgeList,1);
      for (int i = 1; i <= numberOfvertex+1; i++)
    {
        visisted[i]=false;
    }
    cout <<"------------------------------"<<endl;
    printEdgeList(edgeList, numberOfvertex);
    cout <<"------------------------------"<<endl;


    duyetDFS(visisted,edgeList,1);

    cout << endl;
}