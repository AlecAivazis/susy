file1 = set()
file2 = set()

for line in open("analysis/alec2.txt"):
    file1.add(line.strip())

for line in open("/home/users/cgeorge/for_ugrads/my_pred/alex.txt"):
    file2.add(line.strip())

print file1-file2
