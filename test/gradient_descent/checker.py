import numpy as np

def get_int_list():
    return [int(x) for x in input().split()]

def get_db_list():
    return [float(x) for x in input().split()]

n,point_cnt=get_int_list()

X=[]
y=[]

for i in range(point_cnt):
    arr=get_db_list()
    tmp=arr[:-1]
    tmp.append(1)
    X.append(tmp)
    y.append([arr[-1]])

X=np.array(X)
y=np.array(y)

b,residuals,tmp,tmp=np.linalg.lstsq(X,y,rcond=-1)
mse_std=np.mean(np.square(np.matmul(X,b)-y))
#print('python:',b)
#print('python mse:',mse_std)

import sys
with open(sys.argv[1],'r') as f:
    c=[[float(x)] for x in f.readline().split()]

c=np.array(c)
mse_out=np.mean(np.square(np.matmul(X,c)-y))

err=np.abs(mse_std-mse_out)
if err<1e-3:
    print('mse_std',mse_std,'mse_out',mse_out,'ok')
else:
    print('mse_std',mse_std,'mse_out',mse_out,'not ok!!!!!')
    exit(1)
