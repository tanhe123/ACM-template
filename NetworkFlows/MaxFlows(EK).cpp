//最大流的EK算法，建立图并以map1邻接矩阵传入，map[i][j]代表i点到j点的路径容量
//一共有1~n共n个点，留出0号点和n+1号点用来虚拟超级源点和超级汇点，用来处理多源点和多汇点问题
//模板中已使用超级源点和超级汇点，如果不需要请修改
//返回值ans是最大流量
const int inf = 1<<30;  
const int M =105;  //点的最大个数
int map1[M][M],pre[M],vis[M],n;  
int EK()  
{  
    int i,ans=0,now,min1;  
    queue <int> q;  
    while(1)  //每循环一次找一次增广路  
    {  
        memset(pre,-1,sizeof(pre));  //记录增广路路径
        memset(vis,0,sizeof(vis));  
        while(!q.empty())  
        {  
            q.pop();  
        }  
        q.push(0);  //单源点这里需要将0修改成1
        vis[0]=1;  //单源点这里需要将0修改成1
        while(!q.empty())  
        {  
            now=q.front();  
            q.pop();  
            if(now==n+1) //已经搜索到超级汇点  跳出循环  
            {  
                break;  
            }  
            for(i=0;i<=n+1;i++)  //单汇点这里需要将n+1修改成n
            {  
                if(!vis[i]&&map1[now][i]>0)//如果节点i没被搜索过且节点now到节点i残余流量大于0  
                {  
                    pre[i]=now; //记录i的前驱节点是now  
                    vis[i]=1;  //标记i点已经被访问过  
                    q.push(i);  //把i点放入队列进行下一次BFS  
                }  
            }  
        }  
        if(!vis[n+1])  //单汇点这里需要将n+1修改成n
        {  
            break;  //如果BFS完毕没有搜到到节点n+1的增广路，就已经找到最大流  跳出  
        }  
        min1=inf;  
        for(i=n+1;i!=0;i=pre[i])  //单汇点这里需要将n+1修改成n
        {  
            if(map1[pre[i]][i]<min1)  //寻找整个增广路上的残余流量的最小值，此为整个增广路的流量  
            {  
                min1=map1[pre[i]][i];  
            }  
        }  
        ans+=min1;  
        for(i=n+1;i!=0;i=pre[i])  //单汇点这里需要将n+1修改成n
        {  
            map1[pre[i]][i]-=min1;//残余流量减少  
            map1[i][pre[i]]+=min1;//已使用流量增加  
        }  
    }  
    return ans;  
}  
