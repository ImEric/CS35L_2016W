#!/usr/bin/python

import random, sys
from optparse import OptionParser

class comm:
	def __init__(self, filename_1, filename_2):
		if filename_1 == "-":
			f1 = sys.stdin
		else:
			f1 = open(filename_1, 'r')
		self.lines1 = f1.readlines()
		f1.close()

		if filename_2 == "-":
			f2 = sys.stdin
		else:
			f2 = open(filename_2, 'r')
		self.lines2 = f2.readlines()
		f2.close()

	def orderedcomm(self, sp1, sp2, sp3):
		output = ""
		ph = "        "
		file1, file2 = self.lines1, self.lines2
		len1, len2 = len(file1), len(file2)
		i,j = 0,0

		if sp1 and sp2 and sp3:
			return output

		if '\n' not in file1[len1-1]:
			file1[len1-1] += '\n'
		if '\n' not in file2[len2-1]:
			file2[len2-1] += '\n'

		while i < len1 and j < len2:
			#unique in 1
			if file1[i] < file2[j]:
				#check if -1
				if not sp1:
					output += file1[i]
				i += 1
			#unique in 2
			elif file1[i] > file2[j]:
				#check if -2
				if not sp2:
					if sp1:
						output += file2[j]
					else:
						output += ph + file2[j]
				j += 1
			#both in 1 & 2
			else:
				#check if -3
				if not sp3:
					if sp1 and sp2:
						output += file1[i]
					elif sp1 or sp2:
						output += ph + file1[i]
					else:
						output += ph + ph + file1[i]
				i += 1
				j += 1
		#check for remaining list
		if i < len1 and not sp1:
			for m in range(i, len1):
				output += file1[m]

		if j < len2 and not sp2:
			for n in range(j, len2):
				if sp1:
					output += file2[n]
				else:
					output += ph + file2[n]
		return output


	def unorderedcomm(self, sp1, sp2, sp3):
		output = ""
		ph = "        "
		file1, file2 = self.lines1, self.lines2

		if sp1 and sp2 and sp3:
			return output

		#add a newline to end of file if not there already
		if '\n' not in file1[len(file1)-1]:
			file1[len(file1)-1] += '\n'
		if '\n' not in file2[len(file2)-1]:
			file2[len(file2)-1] += '\n'

		#go through file1 first
		for i in range(len(file1)):
			found = False
			#search through file2
			for j in range(len(file2)):
				#if found in file2
				if file1[i] == file2[j]:
					if not sp3:
						if sp1 and sp2:
							output += file1[i]
						elif sp1 or sp2:
							output += ph + file1[i]
						else:
							output +=\
							 ph + ph + file1[i]
					#pop the element from file2
					file2.pop(j)
					found = True
					#skip the rest of file2
					break
					
			#if not found in file2, add to col1
			if not found and not sp1:
				output += file1[i]

		#add unpoped elements in file2 to col2
		if not sp2:
			for k in range(len(file2)):
				if sp1:
					output += file2[k]
				else:
					output += ph + file2[k]
		return output



	def checkifsorted(self):
		file1, file2 = self.lines1, self.lines2
		for i in range(len(file1) - 1):
			if file1[i] > file1[i+1]:
				return False

		for j in range(len(file2) - 1):
			if file2[j] > file2[j+1]:
				return False
		return True

def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

Read FILE1 and FILE2 and produce three text columns as output: 
lines only in file1, lines only in file2, and lines in both files."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", "--suppress1",
                      action="store_true", dest="suppress1", default=False,
                      help="Suppress the output column unique to FILE1.")

    parser.add_option("-2", "--suppress2",
                      action="store_true", dest="suppress2", default=False,
                      help="Suppress the output column unique to FILE2.")

    parser.add_option("-3", "--suppress3",
                      action="store_true", dest="suppress3", default=False,
                      help="Suppress the output column appear in both files.")

    parser.add_option("-u", "--unordered",
                      action="store_true", dest="unordered", default=False,
                      help="Comparing unordered files")

    options, args = parser.parse_args(sys.argv[1:])

    sp1 = options.suppress1
    sp2 = options.suppress2
    sp3 = options.suppress3

    if len(args) != 2:
    	parser.error("Wrong number of input files.")

    try:
    	generator = comm(args[0],args[1])

    	if options.unordered:
    		sys.stdout.write(\
    			generator.unorderedcomm(sp1,sp2,sp3))
    	else:
    		if(generator.checkifsorted()):
    			sys.stdout.write(\
    				generator.orderedcomm(sp1,sp2,sp3))
    		else:
    			# if -u is not specified and the files are not sorted
    			parser.error("File not ordered")

    except IOError as err:
        errno, strerror = err.args
        parser.error("I/O error({0}): {1}".format(errno, strerror))


if __name__ == "__main__":
	main()




