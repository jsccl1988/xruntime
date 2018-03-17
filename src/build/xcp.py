#!/usr/bin/python
import sys
import os
import shutil

def copy(src, target):
    print('[src   ]%s' % src)
    print('[target]%s' % target)

    if os.path.isdir(src):
        if os.path.exists(target):
            shutil.rmtree(target)

        print "[copy dir]: src:%s,dest:%s" % \
            (src, target)
        shutil.copytree(src, target)
    else:
        if os.path.isfile(src):
            print "[copy file]: src:%s,dest:%s" % \
                (src, target)            
            shutil.copy2(src, target)
        else:
            print "[ERROR] %s not exist" % (src)
            return -1

    return 0

if __name__ == '__main__':
    if len(sys.argv) < 3 :
        print('usage: copy.py [src] [target]')
        exit(-1)
        
    print('copy ...')
    src = sys.argv[1]
    target = sys.argv[2]

    copy(src, target)
