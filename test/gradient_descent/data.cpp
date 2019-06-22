#include <bits/stdc++.h>
using namespace std;
typedef double db;
inline int gen(int l,int r){
	static random_device rand;
	return uniform_int_distribution<int>(l,r)(rand);
}
inline db gendb(db l,db r){
	static random_device rand;
	return uniform_real_distribution<db>(l,r)(rand);
}
db a[100];
int main(){
	int n=gen(1,10),m=gen(1,50);
	db mx=10,fl=0.4;
	cout<<n<<" "<<m<<endl;
	for(int i=0;i<=n;i++){
		a[i]=gendb(-mx,mx);
	}
	db fl_sum=0;
	for(int i=1;i<=m;i++){
		db f=a[0];
		for(int j=1;j<=n;j++){
			db v=gendb(-mx,mx);
			f+=v*a[j];
			cout<<v<<" ";
		}
		db v=gendb(-fl,fl);
		fl_sum+=v*v;
		cout<<f+v<<endl;
	}
	cerr<<"original:[";
	for(int i=1;i<=n;i++){
		cerr<<a[i]<<",";
	}
	cerr<<a[0]<<"]"<<endl;
	cerr<<"data mse:"<<fl_sum/m<<endl;
}
