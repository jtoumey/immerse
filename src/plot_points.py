import matplotlib.pyplot as plt


#with open('point_cloud_terminal.dat') as f:
#with open('point_cloud.dat') as f:
#with open('pc_insert.dat') as f:
with open('pc_refinePoint.dat') as f:
    lines = f.readlines()
    x = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

plt.ylim(0, 5)
plt.xlim(0, 6)
plt.scatter(x, y)
plt.show()
#plt.savefig('qt.png')
