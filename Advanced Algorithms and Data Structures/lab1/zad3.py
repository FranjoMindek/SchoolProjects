import numpy as np

if __name__ == '__main__':

    vector_a = np.array([[1], [3], [5]])
    vector_b = np.array([[2], [4], [6]])

    mat_mul = np.outer(vector_a, vector_b)
    print(mat_mul)
    print()

    vect_dot = np.dot(vector_a.transpose(), vector_b)
    print(vect_dot)
    print()

    mat_exp = mat_mul**2
    print(mat_exp)
    print()

    sub_mat = mat_mul[1:, 1:]
    print(sub_mat)
    print()
