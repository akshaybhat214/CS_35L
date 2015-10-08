#!/usr/bin/python

"""
Imitate all features of the command comm,
and add the additional feature of being able 
to compare unsorted files if the flag -u is 
activated.
"""

import random, sys, string, locale
from optparse import OptionParser

"""locale.setlocale(locale.LC_All, 'C')"""
locale.setlocale(locale.LC_ALL, '')

class getlines:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def getList(self):
        list1=list(self.lines)
        return list1

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

Output 3 columns for 1, 2 and matching entries."""
   
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", action="store_true",dest="suppress1"
                      , default=False)
    parser.add_option("-2", action="store_true",dest="suppress2"
                      , default=False)
    parser.add_option("-3", action="store_true",dest="suppress3"
                      , default=False)
    parser.add_option("-u", action="store_true",dest="canSort"
                      , default=False)

    options, args = parser.parse_args(sys.argv[1:])
    input_file1 = args[0]
    input_file2 = args[1]

    def printCols(str, col):
        if col==1:
            if options.suppress1==True:
                return
        elif col==2:
            if options.suppress2==True:
                return
            if options.suppress1==False:
                sys.stdout.write("\t")
        elif col==3:
            if options.suppress3==True:
                return
            if options.suppress1==False:
                sys.stdout.write("\t")
            if options.suppress2==False:
                sys.stdout.write("\t")

        sys.stdout.write(str)  

    if len(args) != 2:
        parser.error("wrong number of operands")

    try:
        if input_file1=="-":
            file1=list(sys.stdin.readlines())
        else:
            lines1=getlines(input_file1)
            file1=list(lines1.getList())

        if input_file2=="-":
            file2=list(sys.stdin.readlines())
        else:
            lines2=getlines(input_file2)
            file2=list(lines2.getList())
    except:
        parser.error("Incorrectly formatted files.")

    if options.canSort==False:
        if file1!= sorted(file1) or file2!=sorted(file2):
            parser.error("One or more files is not sorted")

    file1.sort()
    file2.sort()
    
    dict1={}
    dict2={}
    for i in file1:
        if i in dict1:
            dict1[i]+=1
        else:
            dict1[i]=1
    for j in file2:
        if j in dict2:
            dict2[j]+=1
        else:
            dict2[j]=1

    uniqueFile1=list(set(file1))
    uniqueFile2=list(set(file2))
    uniqueFile1.sort()
    uniqueFile2.sort()
    count1=len(uniqueFile1)
    count2=len(uniqueFile2)

    for k in uniqueFile1:
        firstCol=1
        thirdCol=0
        if k in dict2:
            thirdCol= min(dict1[k],dict2[k])
            firstCol= max(0,dict1[k]-dict2[k])
        else:
            firstCol=dict1[k]
        for i in range (0,firstCol):
            printCols(k,1)
        for j in range (0,thirdCol):
            printCols(k,3)

    for j in uniqueFile2:
        secondCol=0
        if j in dict1:
            secondCol= max(0,dict2[j]-dict1[j])
        else:
            secondCol=dict2[j]
        for a in range (0,secondCol):
            printCols(j,2)
            
if __name__ == "__main__":
    main()
