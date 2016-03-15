#!usr/bin/python
#coding = utf-8
import sys
import os

def md5check(fileA, fileB):
#	print "Here check the two file.\n\n\n\n"
	os.system("sudo md5sum %s > sumA " % fileA)
	os.system("sudo md5sum %s > sumB" % fileB)
	fpA = open("sumA", "r")
	fpB = open("sumB", "r")
	strA = fpA.readline()
	strB = fpB.readline()
	for i in range(0, 32):
		if strA[i] == strB[i]:
			continue
		print "\n\nChecking Error! They are not the same.\n\n"
		os.system("sudo rm sumA sumB")
		return 0
	print "\n\nChecking finished. They are the same.\n\n"
	os.system("sudo rm sumA sumB")
	fpA.close()
	fpB.close()
	return 1

md5check(sys.argv[1],sys.argv[2])

