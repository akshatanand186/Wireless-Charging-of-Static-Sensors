import matplotlib.pyplot as plt
from datetime import datetime

with open("Statistics/finalstats_v1.txt", 'r') as file:
    n, gamma = map(float, file.readline().split())
    data = [list(map(float, line.split())) for line in file]

sensors = [int(row[0]) for row in data]
wcvs = [row[5] for row in data]

plt.subplot(2, 1, 1)
plt.plot(sensors, wcvs, marker='o', color='blue')

# Adding text to the plot
plt.xlabel('Number of Sensors')
plt.ylabel('Number of WCVs')
plt.title(f'Number of WCVs vs Number of Sensors with $\\gamma$ = {gamma}')

with open("Statistics/finalstats_v2.txt", 'r') as file:
    n, numberOfsensors = map(float, file.readline().split())
    data = [list(map(float, line.split())) for line in file]

gamma = [int(row[1]) for row in data]
wcvs = [row[5] for row in data]

plt.subplot(2, 1, 2)
plt.plot(gamma, wcvs, marker='s', color = 'red')


plt.ylabel('NumberofWCVs')
plt.xlabel('ChargingRange')
plt.title(f'ChargingRange vs NumberofWCVs with numberOfSensors = {numberOfsensors}')
plt.tight_layout()

now = datetime.now()
dt_string = now.strftime("%d-%m-%Y_%H-%M-%S")
plt.savefig('Statistics/Stats' + dt_string + '.png')
plt.show()

