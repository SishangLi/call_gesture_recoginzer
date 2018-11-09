import os
path = input("Path(end with '/'):")      

f = os.listdir(path)

sec = 1		
num = 47   #要从几开始命名，设置这里

for i in f:
    picture = path+f[sec-1]
    if num < 10:
        newname = path+'00'+str(num)+'.JPG'
    elif 9 < num < 100:
        newname = path+'0'+str(num)+'.JPG'
    elif num > 99:
        newname = path+''+str(num)+'.JPG'
    
    os.rename(picture,newname)
	
    print(picture,'======>',newname)
    
    num+=1
    sec+=1