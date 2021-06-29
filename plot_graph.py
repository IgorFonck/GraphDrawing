import matplotlib.pyplot as plt
import numpy as np
import csv
import scipy.optimize as opt


def funcao_linear(n, cpu):
    """
    Aproximação linear
    :param n: tamanho da instância
    :param cpu: fator de conversão para tempo de CPU
    :return: aproximação
    """
    return n * cpu


# Read CVS
reader = csv.reader(open("output_times.csv", "r"), delimiter=",")
x = list(reader)
matrix = np.array(x).astype("float")

# Submatrix
n_sizes = np.int64(matrix[0])
sparse_matrix = matrix[1:4, :]
dense_matrix = matrix[4:7, :]

# Sparse mean and standard deviation
mean_sparse = sparse_matrix.mean(0)
std_sparse = sparse_matrix.std(0)

# Dense mean and standard deviation
mean_dense = dense_matrix.mean(0)
std_dense = dense_matrix.std(0)

# Print array
'''np.set_printoptions(formatter={'float': lambda x: "{0:0.2f}".format(x)})
print(n_sizes)'''

# Plot dense
plt.errorbar(n_sizes, mean_dense, std_dense, color="blue", label='Denso medido', linestyle='', fmt=".")

# Aprox. dense
range_multiplier = 1
parametros, pcov = opt.curve_fit(funcao_linear, xdata=n_sizes, ydata=mean_dense)
tamanhos_aproximados = range(n_sizes[-1] * range_multiplier)
aproximados = [funcao_linear(x, *parametros) for x in tamanhos_aproximados]
plt.plot(tamanhos_aproximados, aproximados, label="Denso (aprox.)", color="#7373ff", linestyle="dotted")

# Plot sparse
plt.errorbar(n_sizes, mean_sparse,std_sparse, color="red", label='Esparso medido', linestyle='', fmt="^")

# Aprox. sparse
parametros, pcov = opt.curve_fit(funcao_linear, xdata=n_sizes, ydata=mean_sparse)
tamanhos_aproximados = range(n_sizes[-1] * range_multiplier)
aproximados = [funcao_linear(x, *parametros) for x in tamanhos_aproximados]
plt.plot(tamanhos_aproximados, aproximados, label="Esparso (aprox.)", color="#ff7373", linestyle="dotted")

# Plot final config
plt.xlabel('Tamanho da entrada (n)')
plt.ylabel('Tempo de processamento (s)')
plt.title('Graph Drawing Algorithm - Igor O. Fonseca')
#plt.grid(linestyle = '--')
plt.legend()
plt.show()