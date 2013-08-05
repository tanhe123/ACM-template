#define eps 1e-8
#define zero(x) (((x)>0?(x):-(x))<eps)
struct point{double x,y;};

//计算cross product (P1-P0)x(P2-P0)
double xmult(point p1,point p2,point p0){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
//graham算法顺时针构造包含所有共线点的凸包,O(nlogn)
point p1,p2;
int graham_cp(const void* a,const void* b){
    double ret=xmult(*((point*)a),*((point*)b),p1);
    return zero(ret)?(xmult(*((point*)a),*((point*)b),p2)>0?1:-1):(ret>0?1:-1);
}
void _graham(int n,point* p,int& s,point* ch){
    int i,k=0;
    for (p1=p2=p[0],i=1;i<n;p2.x+=p[i].x,p2.y+=p[i].y,i++)
        if (p1.y-p[i].y>eps||(zero(p1.y-p[i].y)&&p1.x>p[i].x))
            p1=p[k=i];
    p2.x/=n,p2.y/=n;
    p[k]=p[0],p[0]=p1;
    qsort(p+1,n-1,sizeof(point),graham_cp);
    for (ch[0]=p[0],ch[1]=p[1],ch[2]=p[2],s=i=3;i<n;ch[s++]=p[i++])
        for (;s>2&&xmult(ch[s-2],p[i],ch[s-1])<-eps;s--);
}

int wipesame_cp(const void *a, const void *b)
{
    if ((*(point *)a).y < (*(point *)b).y - eps) return -1;
    else if ((*(point *)a).y > (*(point *)b).y + eps) return 1;
    else if ((*(point *)a).x < (*(point *)b).x - eps) return -1;
    else if ((*(point *)a).x > (*(point *)b).x + eps) return 1;
    else return 0;
}

int _wipesame(point * p, int n)
{
    int i, k;
    qsort(p, n, sizeof(point), wipesame_cp);
    for (k=i=1;i<n;i++)
        if (wipesame_cp(p+i,p+i-1)!=0) p[k++]=p[i];
    return k;
}

//构造凸包接口函数,传入原始点集大小n,点集p(p原有顺序被打乱!)
//返回凸包大小,凸包的点在convex中
//参数maxsize为1包含共线点,为0不包含共线点,缺省为1
//参数clockwise为1顺时针构造,为0逆时针构造,缺省为1
//在输入仅有若干共线点时算法不稳定,可能有此类情况请另行处理!
int graham(int n,point* p,point* convex,int maxsize=1,int dir=1){
    point* temp=new point[n];
    int s,i;
    n = _wipesame(p,n);
    _graham(n,p,s,temp);
    for (convex[0]=temp[0],n=1,i=(dir?1:(s-1));dir?(i<s):i;i+=(dir?1:-1))
        if (maxsize||!zero(xmult(temp[i-1],temp[i],temp[(i+1)%s])))
            convex[n++]=temp[i];
    delete []temp;
    return n;
}
double area_polygon(int n,point* p)//多边形面积
{
    double s1=0,s2=0;
    int i;
    for (i=0; i<n; i++)
        s1+=p[(i+1)%n].y*p[i].x,s2+=p[(i+1)%n].y*p[(i+2)%n].x;
    return fabs(s1-s2)/2;
}
///多边形费马点，点集pt，大小n，传入ptres作为费马点这一点，返回值是所有点到费马点的距离
double fermat_point(point pt [], int n, point & ptres)
{
  point u, v;
	double step = 0.0, curlen, explen, minlen;
	int i, j, k, idx;
	bool flag;
	u.x = u.y = v.x = v.y = 0.0;
	for (i = 0; i < n; ++i)
	{
		step += fabs(pt[i].x) + fabs(pt[i].y);
		u.x += pt[i].x;
		u.y += pt[i].y;
	}
	u.x /= n;
	u.y /= n;
	flag = 0;
	while (step > 1e-10)
	{
		for (k = 0; k < 10; step /= 2, ++k)
			for (i = -1; i <= 1; ++i)
				for (j = -1; j <= 1; ++j)
				{
					v.x = u.x + step*i;
					v.y = u.y + step*j;
					curlen = explen = 0.0;
					for (idx = 0; idx < n; ++idx)
					{
						curlen += distance(u, pt[idx]);
						explen += distance(v, pt[idx]);
					}
					if (curlen > explen)
					{
						u = v;
						minlen = explen;
						flag = 1;
					}
				}
	}
	ptres = u;
	return flag ? minlen : curlen;
}
//RC算法求凸包直径（有问题）
int rotating_calipers(point *ch, int n)  
{  
    int q = 1, ans = 0;  
    ch[n] = ch[0];  
    for (int p = 0; p < n; p++)  
    {  
        while (xmult(ch[p + 1], ch[q + 1], ch[p]) > xmult(ch[p + 1], ch[q], ch[p]))  
            q = (q + 1)%n;  
        ans = max(ans, max(dist2(ch[p], ch[q]), dist2(ch[p + 1], ch[q + 1])));  
    }  
    return ans;  
}
