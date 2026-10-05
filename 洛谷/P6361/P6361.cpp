// Source: https://www.luogu.com.cn/article/dhmaeuag
#include<stdio.h>
#include<string.h>
#include<random>
typedef unsigned int word;
const word mod=1e9+7;
struct matrix{//矩阵
	word num[4];
	inline matrix(){}
	inline matrix(word a,word b,word c,word d){
		num[0]=a,num[1]=b,num[2]=c,num[3]=d;}
	#define mul(a,b) (1ull*num[a]*p.num[b])
	#define plus(a,b,c,d) (mul(a,b)+mul(c,d))%mod
	inline matrix operator()(const matrix &p)const{
		return matrix(
			plus(0,0,1,2),plus(0,1,1,3),
			plus(2,0,3,2),plus(2,1,3,3));}
	#undef mul
	#undef plus
}const I(1,0,0,1);
struct READ{//快读快写
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(type &num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
std::mt19937 RAND(std::random_device{}());
struct treap{
	treap *l,*r;
	word f,cnt,end,blc;
	//f 第一个 1 的位置
	//cnt 1 的个数
	//end 最后一个 1 的位置
	matrix val,sum;
	//val 当前连续段的转移矩阵之积
	//sum 整棵平衡树的转移矩阵之积
	inline treap(){blc=RAND();}
	inline void calc(const word d){//计算转移矩阵 (a_i-a_{i-1}=d)
		end=f? f+((cnt-1)<<1):0;
		sum=val=matrix(
			(1ull*(cnt-1)*((d-1)/2)+1)%mod,
			(1ull*(cnt-1)*(d/2)+1)%mod,
			(d-1)/2,d/2);
	}
	inline void pushup(){
		sum=val;
		if(l) sum=sum(l->sum);
		if(r) sum=r->sum(sum),end=r->end;
		else end=f? f+((cnt-1)<<1):0;
	}
}p[1u<<17];
inline treap* merge(treap *l,treap *r){
	if(l==0) return r;
	if(r==0) return l;
	if(l->blc<=r->blc){
		l->sum=r->sum(l->sum);
		l->end=r->end;
		return l->r=merge(l->r,r),l;
	}
	r->sum=r->sum(l->sum);
	return r->l=merge(l,r->l),r;
}
inline treap* split(treap *&rt,word size){
	//分离 f>size 的连续段
	if(rt==0) return 0;
	treap *out=0;
	if(size<rt->f){
		out=split(rt->l,size);
		treap *swap=rt->l;
		rt->l=out,out=swap;
		swap=rt,rt=out,out=swap;
		return out->pushup(),out;
	}
	if(size==rt->f) out=rt->r,rt->r=0;
	else out=split(rt->r,size);
	return rt->pushup(),out;
}
inline treap* splitend(treap *&rt){
	if(rt->r){
		treap *out=splitend(rt->r);
		return rt->pushup(),out;
	}
	treap *out=rt;
	rt=rt->l,out->l=0;
	return out->pushup(),out;
}
inline treap* splitbegin(treap *&rt){
	if(rt->l){
		treap *out=splitbegin(rt->l);
		return rt->pushup(),out;
	}
	treap *out=rt;
	rt=rt->r,out->r=0;
	return out->pushup(),out;
}
word n,psiz;
treap *rt=p,*mid,*right;
inline void getend(){//讨论 mid 与后继的拼接情况
	treap *mid_=right;
	right=split(mid_,mid->f+(mid->cnt<<1));
	if(mid_) mid->cnt+=mid_->cnt;
	mid->calc(mid->f-rt->end);
	if(right){
		treap *nxt=splitbegin(right);
		nxt->calc(nxt->f-mid->end);
		mid=merge(mid,nxt);
	}
	rt=merge(merge(rt,mid),right);
}
inline void insert(word val){
	mid=split(rt,val);
	right=split(mid,val+1);
	if(mid) mid->f=mid->end+1,mid->cnt=1;//在连续段的最前面
	else if((rt==p&&rt->r==0)||val>rt->end+2)//没有插入到已有的连续段中
		mid=p+(++psiz),mid->f=val,mid->cnt=1;
	else if(mid=splitend(rt),val==mid->end+2) ++mid->cnt;
		//拼接到连续段的末尾
	else if((val-mid->f)&1){//破坏了不相邻的性质
		if(val!=mid->end+1){//在连续段中间
			mid->cnt=(val+1-mid->f)/2;
			val=mid->end+1;
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}else if(++val,mid->cnt!=1){//在连续段末尾
			--mid->cnt,mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}
		mid=right,right=split(mid,val+1);
		if(mid) mid->f=mid->end+1;
		else mid=p+(++psiz),mid->f=val;
		mid->cnt=1;
	}else if(val==mid->end){//破坏了不相接的性质（在连续段末尾）
		if(mid->f!=1&&mid->f!=2)
			return val=mid->f-2,++mid->f,getend(),insert(val);
		//开头不为 1 或 2 的情况
		if(mid->f==1) ++mid->f;
		else --mid->f,++mid->cnt;
		//开头为 1 或 2 的情况
	}else{//破坏了不相接的性质（在连续段中间）
		treap *nxt=p+(++psiz);
		nxt->f=mid->end+1,nxt->cnt=1;
		mid->cnt=(val-mid->f)/2;
		if(mid->f!=1&&mid->f!=2){
			if(val=mid->f-2,++mid->f,mid->cnt){
				mid->calc(mid->f-rt->end);
				rt=merge(rt,mid);
			}
			return mid=nxt,getend(),insert(val);
		}
		//开头不为 1 或 2 的情况
		if(mid->f==2){
			--mid->f,++mid->cnt;
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}else if(++mid->f,mid->cnt){
			mid->calc(mid->f-rt->end);
			rt=merge(rt,mid);
		}
		mid=nxt;
		//开头为 1 或 2 的情况
	}
	getend();
}
int main(){
	cin>>n;
	rt->f=0,rt->cnt=1,rt->end=0;
	rt->val=rt->sum=I;
	for(word val;n;--n){
		cin>>val,insert(val);
		printf("%u\n",(rt->sum.num[0]+rt->sum.num[2])%mod);
	}
	return 0;
}
