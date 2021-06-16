import matplotlib.pyplot as plt
import numpy as np
import csv
import scipy.optimize as opt

reader = csv.reader(open("output_times.csv", "r"), delimiter=",")
x = list(reader)
matrix = np.array(x).astype("float")

# Submatrix
#matrix = np.transpose(matrix)
n_sizes = matrix[0]
sparse_matrix = matrix[1:4, :]
dense_matrix = matrix[4:7, :]

#sparse_matrix[:, 1] = 1
mean_sparse = sparse_matrix.mean(0)
std_sparse = sparse_matrix.std(0)

mean_dense = dense_matrix.mean(0)
std_dense = dense_matrix.std(0)


# Print array
#np.set_printoptions(formatter={'float': lambda x: "{0:0.2f}".format(x)})
#print(n_sizes)


# Plot dense
plt.errorbar(n_sizes, mean_dense, std_dense, color="blue", label='Denso')

linear_model = np.polyfit(n_sizes, mean_dense, 1)
linear_model_fn = np.poly1d(linear_model)
x_s = np.arange(0, n_sizes[-1])
plt.plot(x_s, linear_model_fn(x_s), color="blue", label="Denso (aprox.)", linestyle='dotted')

# Plot sparse
plt.errorbar(n_sizes, mean_sparse,std_sparse, color="orange", label='Esparso')

linear_model = np.polyfit(n_sizes, mean_sparse, 1)
linear_model_fn = np.poly1d(linear_model)
x_s = np.arange(0, n_sizes[-1])
plt.plot(x_s, linear_model_fn(x_s), color="orange", label="Esparso (aprox.)", linestyle='dotted')

# Plot final config
plt.xlabel('Tamanho da entrada (n)')
plt.ylabel('Tempo de processamento (s)')
plt.title('Graph Drawing Algorithm')
plt.grid(linestyle = '--')
plt.legend()
plt.show()