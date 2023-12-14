import matplotlib.pyplot as plt 
time_flams = [345.8, 392.48, 418.348, 436.235, 452.423, 473.842, 488.584, 504.358, 526.136, 553.014, 577.601, 621.597, 650.464, 666.339, 682.214]

time_lights = [370.9, 588.99, 772.399, 942.64, 1135.56, 1308.96, 1574.5, 1815.35, 2040.43, 2273.54]

sizes_flam = [i for i in range(1, 16)]
sizes_lights = [i for i in range(1, 11)]

print("Фламинго")
for num in sizes_flam:
    print(" %4d & %.2f \\\\ \n \\hline" %(num, time_flams[num - 1]))
    
print("Источники света")
for num in sizes_lights:
    print(" %4d & %.2f \\\\ \n \\hline" %(num, time_lights[num - 1]))



fig1 = plt.figure(figsize=(10, 7))
plot = fig1.add_subplot()
plot.plot(sizes_flam, time_flams)

plt.legend()
plt.grid()
plt.title("Временные характеристики")
plt.ylabel("Затраченное время (мс)")
plt.xlabel("Количество фламинго")

plt.show()


fig2 = plt.figure(figsize=(10, 7))
plot = fig2.add_subplot()
plot.plot(sizes_lights, time_lights)


plt.legend()
plt.grid()
plt.title("Временные характеристики")
plt.ylabel("Затраченное время (мс)")
plt.xlabel("Количество источников света")

plt.show()
