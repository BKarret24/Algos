import matplotlib.pyplot as plt
import csv


def read_csv(filename):
    Ns = []
    S = []
    err = []
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            N = int(row[0])
            est = float(row[1])
            e = float(row[2])
            Ns.append(N)
            S.append(est)
            err.append(e)
    return Ns, S, err

Ns_wide, S_wide, err_wide = read_csv("wide_results.csv")
Ns_tight, S_tight, err_tight = read_csv("tight_results.csv")

plt.figure(figsize=(10, 6))
plt.plot(Ns_wide, S_wide, label="Широкий прямоугольник", color="orange")
plt.plot(Ns_tight, S_tight, label="Узкий прямоугольник", color="blue")
plt.xlabel("N")
plt.ylabel("Оценка площади")
plt.title("Зависимость оценки площади от N")
plt.grid(True)
plt.legend()
plt.savefig("area_vs_N.png", dpi=200)
plt.close()

plt.figure(figsize=(10, 6))
plt.plot(Ns_wide, err_wide, label="Широкий прямоугольник", color="orange")
plt.plot(Ns_tight, err_tight, label="Узкий прямоугольник", color="blue")
plt.xlabel("N")
plt.ylabel("Относительная ошибка")
plt.title("Относительная ошибка Монте-Карло")
plt.grid(True)
plt.legend()
plt.savefig("error_vs_N.png", dpi=200)
plt.close()



