from mpl_toolkits.mplot3d import Axes3D  # Needed even if unused
import matplotlib.pyplot as plt

# Define points
points = [
    (0, 0, 0),
    (1, 0, 0),
    (0, 1, 0),
    # (0,0, 2),
    (-1, 1, 1)
]

# Unpack points
xs, ys, zs = zip(*points)

# Plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Draw line segments between each pair of points
for i in range(len(points)):
    for j in range(i + 1, len(points)):
        x_pair = [points[i][0], points[j][0]]
        y_pair = [points[i][1], points[j][1]]
        z_pair = [points[i][2], points[j][2]]
        ax.plot(x_pair, y_pair, z_pair, color='b', alpha=0.5)

ax.scatter(xs, ys, zs, c='r', marker='o')

# Label axes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

# Define points
points = [
    (0, 0, 0),
    (1, 0, 0),
    (0, 1, 0),
    (0,0, 2),
    (-1, 1, 1)
]

# Unpack points
xs, ys, zs = zip(*points)

# Plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Draw line segments between each pair of points
for i in range(len(points)):
    for j in range(i + 1, len(points)):
        x_pair = [points[i][0], points[j][0]]
        y_pair = [points[i][1], points[j][1]]
        z_pair = [points[i][2], points[j][2]]
        ax.plot(x_pair, y_pair, z_pair, color='b', alpha=0.5)

ax.scatter(xs, ys, zs, c='r', marker='o')

# Label axes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()