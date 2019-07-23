#include <iostream>
#include <cstring>
#include <cmath>
#include "point.h"
#include "pc.h"
using namespace std;

/*以下函数中，形如 
int g=0;
int len=c.length();
for(int i=0;i<len;i++)
    if(c[i]==' '){
        g=i;
        break;
    }
pois[num].name=c.substr(0,g);
c=c.erase(0,g+1);
的代码，其含义基本为在字符串c中截取出第一个空格之前的一段，记录后在c中删掉该段及空格 */ 
        
        
int pc::ifexist(string &nam){ 
    for(int i=num-1;i>=0;i--){
        if(!strcmp(nam.c_str(),pois[i].name.c_str()))
            return i;
    }
    return -1;
}

void pc::ori(){
    int n;
    cin >> n;
    char b[1000];
    for(int i=-1;i<n;i++){
        cin.getline(b,1000);
        if(i==-1)continue;
        string a=b;
        pois[i].set(a);
        pois[i].ifori=1;
    }//基础结点 
    int m;
    cin >> m;
    num=n-1;
    for(num;num<m+n;num++){
        cin.getline(b,1000);
        if(num==n-1)continue;
        pois[num].type="P";
        string c=b;
        int g=0;
        int len=c.length();
        for(int i=0;i<len;i++)
            if(c[i]==' '){
                g=i;
                break;
            }
        pois[num].name=c.substr(0,g);//记录名称 
        c=c.erase(0,g+3);
        g=0;
        len=c.length();
        for(int i=0;i<len;i++)
            if(c[i]==' '){
                g=i;
                break;
            }
        string tmp=c.substr(0,g);
        c=c.erase(0,g+1);
        if(ifexist(tmp)!=-1){//if等号后第一段字符为结点 
            pois[num].source[0]=ifexist(tmp);
            g=0;
            len=c.length();
            for(int i=0;i<len;i++)
                if(c[i]==' '){
                    g=i;
                    break;
                }
            string tmp1=c.substr(0,g);
            c=c.erase(0,g+1);
            pois[num].getway=tmp1;
            pois[num].source[1]=ifexist(c);
        }
        else{//if等号后第一段字符为运算 
        	pois[num].getway=tmp;
        	g=0;
            len=c.length();
            for(int i=0;i<len;i++)
                if(c[i]==' '){
                    g=i;
                    break;
                }
            if(g==0)pois[num].source[0]=ifexist(c); 
            else{//COND
            	string tmp2=c.substr(0,g);
            	pois[num].source[0]=ifexist(tmp2);
            	c=c.erase(0,g+1);
            	g=0;
            	len=c.length();
            	for(int i=0;i<len;i++)
                	if(c[i]==' '){
                	    g=i;
                	    break;
                	}
        		string tmp3=c.substr(0,g);
            	pois[num].source[1]=ifexist(tmp3);
        		c=c.erase(0,g+1);
        		pois[num].source[2]=ifexist(c);
			}
        } 
    }//衍生结点
    return;
}

void pc::operate(){
	int k;
	cin >> k;
    char b[1000];
    for(int i=-1;i<k;i++){
        cin.getline(b,1000);
        if(i==-1)continue;
        string c=b;
    	int g=0;
    	int len=c.length();
    	for(int i=0;i<len;i++)
        	if(c[i]==' '){
            	g=i;
            	break;
        	}
    	string tmp2=c.substr(0,g);
    	c=c.erase(0,g+1);
    	if(tmp2=="EVAL")eval(c);
    	if(tmp2=="SETANSWER")setanswer(c);
    	if(tmp2=="SETCONSTANT")setconstant(c);
    	opnum++;
	}
}

float pc::getval(int pos){
	if(errornum==1)return errornum;//错误终止 
    if(pois[pos].ifcal){
        return pois[pos].value;}//被计算过终止 
    else{
        if(pois[pos].ifori==1){
            cout<<"ERROR: Placeholder missing"<<endl;
            errornum=1;
            return 1;
        }//使用时未被赋值却被定义 
        pois[pos].ifcal=1;
        if(pois[pos].getway=="+")
            pois[pos].value=getval(pois[pos].source[0])
             +getval(pois[pos].source[1]);
        if(pois[pos].getway=="-")
            pois[pos].value=getval(pois[pos].source[0])
             -getval(pois[pos].source[1]);
        if(pois[pos].getway=="*")
            pois[pos].value=getval(pois[pos].source[0])
             *getval(pois[pos].source[1]);
        if(pois[pos].getway=="/"){
            if(getval(pois[pos].source[1])==0){
                cout<<"ERROR: Division by zero"<<endl;
                errornum=1;
                return 1;
            }
            pois[pos].value=getval(pois[pos].source[0])
             /getval(pois[pos].source[1]);
		}
        if(pois[pos].getway=="SIN")
            pois[pos].value=sin(getval(pois[pos].source[0]));
        if(pois[pos].getway=="LOG"){
            if(getval(pois[pos].source[0])<=0){
                cout<<"ERROR: LOG operator's input must be positive"<<endl;
                errornum=1;
                return 1;
            }
            pois[pos].value=log(getval(pois[pos].source[0]));
        }
        if(pois[pos].getway=="EXP")
            pois[pos].value=exp(getval(pois[pos].source[0]));
        if(pois[pos].getway=="SIGMOID")
            pois[pos].value=1/(1+exp(-getval(pois[pos].source[0])));
        if(pois[pos].getway=="TANH")
            pois[pos].value=
            (exp(getval(pois[pos].source[0]))
             -exp(-getval(pois[pos].source[0])))/
            (exp(getval(pois[pos].source[0]))
             +exp(-getval(pois[pos].source[0])));
        if(pois[pos].getway==">")
            pois[pos].value=getval(pois[pos].source[0])
            >getval(pois[pos].source[1]);
        if(pois[pos].getway=="<")
            pois[pos].value=getval(pois[pos].source[0])
            <getval(pois[pos].source[1]);
        if(pois[pos].getway==">=")
            pois[pos].value=getval(pois[pos].source[0])
            >=getval(pois[pos].source[1]);
        if(pois[pos].getway=="<=")
            pois[pos].value=getval(pois[pos].source[0])
            <=getval(pois[pos].source[1]);
        if(pois[pos].getway=="==")
            pois[pos].value=getval(pois[pos].source[0])
            ==getval(pois[pos].source[1]);
        if(pois[pos].getway=="PRINT"){
            pois[pos].value=getval(pois[pos].source[0]);
            cout<<"PRINT operator: "<<pois[pois[pos].source[0]].name
                <<" = "<<pois[pos].value<<endl;
		}
		if(pois[pos].getway=="COND"){
			float Bool=getval(pois[pos].source[0]);
			if(Bool>0)
			pois[pos].value=getval(pois[pos].source[1]);
			else 
			pois[pos].value=getval(pois[pos].source[2]);
		}
    }
    return pois[pos].value;
}

void pc::eval(string c){
	int g1=0;
	int len=c.length();
    for(int i=0;i<len;i++)
    	if(c[i]==' '){
            g1=i;
        	break;
		}
	string target=c;	
	if(g1!=0){//有赋值的需要 
		target=c.substr(0,g1);
    	c=c.erase(0,g1+1);
    	g1=0;
		len=c.length();
    	for(int i=0;i<len;i++)
    		if(c[i]==' '){
        	    g1=i;
        		break;
			}
		if(g1!=0){//需赋值个数不为0 
			int setnum=stoi(c.substr(0,g1));
		    c=c.erase(0,g1+1);
	    	for(int l=0;l<setnum;l++){
		    	g1=0;
				len=c.length();
		    	for(int i=0;i<len;i++)
		    	if(c[i]==' '){
		            g1=i;
		        	break;
				}
				string setname=c.substr(0,g1);
				c=c.erase(0,g1+1);
				g1=0;
				len=c.length();
		  	 	for(int i=0;i<len;i++)
		  	 	if(c[i]==' '){
		  	      g1=i;
		  	     	break;
				}
				string setvalue=c.substr(0,g1);
				if(g1==0)setvalue=c;
				c=c.erase(0,g1+1);
				pois[ifexist(setname)].value=atof(setvalue.c_str());//赋值 
				pois[ifexist(setname)].ifcal=1;
			}
		}
	}
	result[opnum]=getval(ifexist(target));//计算 
	if(errornum==0){
		cout << result[opnum]<<endl;
	}
	else errornum=0;
	for(int j=0;j<num;j++){
        if(pois[j].type=="P"){
            pois[j].value=0;
            pois[j].ifcal=0;
        }
    }//P型结点数值归0 
}

void pc::setconstant(string c){
	int g1=0;
	int len=c.length();
    for(int i=0;i<len;i++)
    if(c[i]==' '){
        g1=i;
        break;
	}
	string setname=c.substr(0,g1);
	string setvalue=c.erase(0,g1+1);
	pois[ifexist(setname)].value=atof(setvalue.c_str());
}

void pc::setanswer(string c){
	int g1=0;
	int len=c.length();
    for(int i=0;i<len;i++)
    if(c[i]==' '){
        g1=i;
        break;
	}
	string setname=c.substr(0,g1);
	string setvalue=c.erase(0,g1+1); 
	pois[ifexist(setname)].value=result[stoi(setvalue.c_str())-1];
}
