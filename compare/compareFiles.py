file1 = set()
file2 = set()

f1 = open('alex.txt')
for line in f1:
    file1.add(line.strip())

f2 = open('ours.txt')
for line in f2:
    file2.add(line.strip())

if len(file1) > len(file2):
    difference = list(file1-file2)
else:
    difference = list(file2-file1)

for item in difference:
    print item

