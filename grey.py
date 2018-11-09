from skimage import io,transform,color
import numpy as np

def convert_gray(f,**args):
    rgb=io.imread(f)
    gray=color.rgb2gray(rgb)
    dst=transform.resize(gray,(480,640))
    return dst
datapath='F:\\WorkStation\\call_gesture\\sample_net\\testing'
str=datapath+'/*.jpg'
coll = io.ImageCollection(str,load_func=convert_gray)
for i in range(len(coll)):
    io.imsave(r'F:\\WorkStation\\call_gesture\\sample_net\\testing\\' + np.str(i) + '.jpg',coll[i])