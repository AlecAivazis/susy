# compareFiles.py - Alec Aivazis
# usage: python compareFiles.py
# description: This will compare filePath1 and filePath2 for a difference in lines 
#              and print it to the terminal. Since sets are used, the order of lines
#              doesn't matter. 

filePath1 = "eventList.txt"
filePath2 = "alex_all.txt"

# -----------------

set1 = set()
set2 = set()

# open filePath1 and add it to its set
for line in open(filePath1):
    set1.add(line.strip())

# open filePath1 and add it to its set
for line in open(filePath2):
    set2.add(line.strip())

# if set1 is bigger,
if len(set1) > len(set2):

    # diffSet must be "postive"
    diffSet = set1-set2
    # keep track of which one was bigger
    big = filePath1 

else: 
    # set 2 must have been bigger
    diffSet = set2-set1
    # so remember that
    big = filePath2
    
# make diffSet into a list so we can sort it for pretty output
diffSet = list(diffSet)

# check if the two sets were the same
if len(diffSet) == 0:
    print "They're the same (order doesn't matter)"

# if the difference is non zero, then iterate over the difference and print
else:
    # sort diffSet before we iterate
    for diff in sorted(diffSet):
        print str(diff)

    # print what file is bigger at the end
    print "bigger file: " + big
