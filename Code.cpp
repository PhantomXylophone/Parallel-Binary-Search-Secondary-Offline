#include<bits/stdc++.h>
using namespace std;
int root,cnt,x,y,k,n,m,len,pos,p,ans[300005],tree[300005],maxn,a[300005],od,newid[300005],idcnt,idx,tot,qcnt;
struct order{
    int x,y,k,op,id;
}q[300005],q1[300005],q2[300005];
void add(int x,int y){for(;x<=tot;x+=x&(-x))tree[x]+=y;}
int sum(int x){
    int ans=0;
    for(;x;x-=x&(-x))ans+=tree[x];
    return ans;
}
struct node{int ls,rs,pri,sz,rk,val,ext=1;}t[300005];
void update(int u){t[u].sz=t[t[u].ls].sz+t[t[u].rs].sz+t[u].ext;}
int newnode(int c,int val){t[++cnt]={0,0,rand(),1,c,val,1};return cnt;}
void split(int u,int x,int &L,int &R){
    if(!u){L=R=0;return;}
    if(t[t[u].ls].sz+t[u].ext<=x)L=u,split(t[u].rs,x-t[t[u].ls].sz-t[u].ext,t[u].rs,R);
    else R=u,split(t[u].ls,x,L,t[u].ls);
    update(u);
}
int merge(int x,int y){
    if(!x||!y)return x|y;
    if(t[x].pri>t[y].pri){t[x].rs=merge(t[x].rs,y),update(x);return x;}
    else{t[y].ls=merge(x,t[y].ls),update(y);return y;}
}
void del(int u,int x){
    t[u].sz--;
    if(t[t[u].ls].sz+t[u].ext==x)t[u].ext=0;
    else if(t[t[u].ls].sz+t[u].ext<x)del(t[u].rs,x-t[t[u].ls].sz-t[u].ext);
    else del(t[u].ls,x);
    update(u);
}
int find(int u,int x){
    if(t[t[u].ls].sz+t[u].ext==x)return u;
    else if(t[t[u].ls].sz+t[u].ext<x)return find(t[u].rs,x-t[t[u].ls].sz-t[u].ext);
    return find(t[u].ls,x);
}
void inorder(int u){
    if(!u)return;
    inorder(t[u].ls),newid[t[u].rk]=++tot,cout<<t[u].val<<" ";inorder(t[u].rs);
}
void solve(int l,int r,int ql,int qr){
    if(l>r||ql>qr)return;
    int cnt1=0,cnt2=0,mid=l+r>>1;
    if(l==r){
        for(int i=ql;i<=qr;++i)
            if(q[i].op==1)
                ans[q[i].id]=l;
        return;
    }
    bool b1=0,b2=0;
    for(int i=ql;i<=qr;++i){
        if(q[i].op==1){
            int t=sum(q[i].y)-sum(q[i].x-1);
            if(q[i].k<=t)
                q1[++cnt1]=q[i],b1=1;
            else q[i].k-=t,q2[++cnt2]=q[i],b2=1;
        }
        else{
            if(q[i].y<=mid)
                add(q[i].x,q[i].k),q1[++cnt1]=q[i];
            else q2[++cnt2]=q[i];
        }
    }
    for(int i=1;i<=cnt1;++i)
        if(q1[i].op!=1)
            add(q1[i].x,-q1[i].k);
    for(int i=1;i<=cnt1;++i)q[ql+i-1]=q1[i];
    for(int i=1;i<=cnt2;++i)q[ql+cnt1+i-1]=q2[i];
    if(b1)solve(l,mid,ql,ql+cnt1-1);
    if(b2)solve(mid+1,r,ql+cnt1,qr);
}
int read(){
    int x=0,f=1,ch=getchar_unlocked();
    for(;!isdigit(ch);ch=getchar_unlocked())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar_unlocked())x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
void write(int x){
    if(x<0)putchar_unlocked('-'),x=-x;
    if(x>=10)write(x/10);
    putchar_unlocked(x%10+'0');
}
signed main(){
    srand(time(0));
    n=read(),m=read();
    for(int i=1;i<=n;++i)q[++idx]={i,read(),1,2,0},root=merge(root,newnode(++idcnt,q[idx].y)),maxn=max(maxn,q[i].y);
    for(int i=1;i<=m;++i){
        od=read(),x=read();
        if(od==1)y=read(),q[++idx]={find(root,x),find(root,y),read(),1,++qcnt};
        else if(od==2){
            y=read();
            maxn=max(maxn,y);
            int L,R,P=newnode(++idcnt,y);
            ++idx,q[idx]={P,y,1,2,0};
            split(root,x,L,R);
            root=merge(merge(L,P),R);
        }
        else {int tmp=find(root,x);++idx,q[idx]={tmp,t[tmp].val,-1,0,0},del(root,x);}
    }
    inorder(root);cout<<endl;
    for(int i=1;i<=idx;++i){
        q[i].x=newid[q[i].x];
        if(q[i].op==1)q[i].y=newid[q[i].y];
        cout<<q[i].op<<" "<<q[i].x<<" "<<q[i].y<<" "<<q[i].k<<endl;
    }
    solve(1,maxn,1,idx);
    for(int i=1;i<=qcnt;++i)write(ans[i]),putchar_unlocked('\n');
    return 0;
}
