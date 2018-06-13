import matplotlib.pyplot as plt


#with open('point_cloud_terminal.dat') as f:
with open('point_cloud.dat') as f:
    lines = f.readlines()
    x = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

plt.scatter(x, y)
plt.show()
#plt.savefig('qt.png')
