import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

with open("DelanuayTriangleWithSLs\DelaunayTriangle.txt", "r") as file:
    lines = file.readlines()

n = int(lines[0])

triangles = []
line_number = 1
for _ in range(n):
    triangle = []
    for _ in range(3):
        x, y = map(float, lines[line_number].split())
        triangle.append((x, y))
        line_number += 1
    triangles.append(triangle)

m = int(lines[line_number])
line_number += 1

SoujournLocations = []
for _ in range(m):
    x, y = map(float, lines[line_number].split())
    SoujournLocations.append((x, y))
    line_number += 1


x = int(lines[line_number])
line_number += 1

StaticSensors = []
for _ in range(x):
    x, y = map(float, lines[line_number].split())
    StaticSensors.append((x, y))
    line_number += 1





with open("WCVsPathTracing\WCV.txt", "r") as file:
    lines = file.readlines()


base_station = list(map(float, lines[0].split()))
base_x, base_y = base_station

N = int(lines[1])

fig = plt.figure(figsize=(12, 6))

plt.plot(base_x, base_y, 'go', markersize=10, label="Base Station")

all_x_points, all_y_points = [], []

line_number = 2
i = 0
path_colors = ['b-', 'm-', 'y-', 'k-']
for _ in range(N):

    M = int(lines[line_number])
    line_number += 1


    vehicle_x_points, vehicle_y_points = [], []
    for _ in range(M):
        x, y = map(float, lines[line_number].split())
        vehicle_x_points.append(x)
        vehicle_y_points.append(y)
        all_x_points.append(x)
        all_y_points.append(y)
        line_number += 1

    plt.plot(vehicle_x_points, vehicle_y_points, path_colors[i%4], label=f"Vehicle Path {i}")
    i += 1
    Z = int(lines[line_number])
    line_number += 1

    line_number += 1

for triangle in triangles:
    triangle.append(triangle[0])  # Close the triangle by adding the first point to the end
    x, y = zip(*triangle)
    plt.plot(x, y, 'c--', alpha = 0.3)

x, y = zip(*SoujournLocations)
plt.plot(x, y, 'g+',markersize=10,label="Soujourn Locations")

x, y = zip(*StaticSensors)
plt.plot(x, y, 'ro',markersize=3,label="Static Sensors")

# Determine the axis limits based on all visited SoujournLocations
plt.xlim(-25, 25)
plt.ylim(-5, 10)

plt.xlabel("X")
plt.ylabel("Y")
plt.title("Base Station, Vehicle Paths, Triangles, and Points")
plt.legend()
plt.grid(True)

plt.show()

now = datetime.now()
dt_string = now.strftime("%d-%m-%Y_%H-%M-%S")
fig.savefig('OutputImage/WCVTrace' + dt_string + '.png')