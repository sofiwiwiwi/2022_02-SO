n_size = int(input())
m_size = int(input())

cont = 0
for i in range(n_size):
    for j in range(0,n_size, m_size):
        matrix = [[0 for i in range(n_size)] for j in range(n_size)]
        for k in range(m_size):
            matrix[i][j + k] = 1
        to_write = ""
        for i in range(len(matrix)):
            to_write += " ".join("".join(str(matrix[i]).split(" ")).split(","))
            if(i != n_size - 1):
                to_write += ","
        file_test = open(f'test_{n_size}_{cont}.txt', "w")
        file_test.write(f'{n_size}\n{m_size}\n{to_write}')
        file_test.close()
        cont+= 1
        for k in range(m_size):
            matrix[i][j + k] = 0