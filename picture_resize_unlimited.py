from PIL import Image
import os.path
import glob

pathin = input("source Path(end with '/'):")  
pathout = input("out Path(end with '/'):")  

def convertjpg(jpgfile,outdir,width=640,height=480):
  img=Image.open(jpgfile)
  try:
    new_img=img.resize((width,height),Image.BILINEAR)  
    new_img.save(os.path.join(outdir,os.path.basename(jpgfile)))
  except Exception as e:
    print(e)

for jpgfile in glob.glob(path + '*.jpg'):
  convertjpg(jpgfile,pathout)
