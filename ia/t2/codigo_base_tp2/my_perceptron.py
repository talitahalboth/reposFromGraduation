import numpy as np

def run_perceptron(weights, data, labels, learning_rate=1):
    epoch_error = 0
    # Para cada instancia e label
    for x, y in zip(data, labels):
	# IMPLEMENTE AQUI A ATUALIZACAO DOS PESOS
        dotProduct = np.dot(weights, x)
        position = 1
        # <= 0 : is in lower
        if (dotProduct <= 0):
            position = 0
        # if the position it found is different than the label, fix weight
        if (position != y):
            # if is in upper and should be lower
            if position == 1:
                d = -1
            # other way around
            else:
                d = 1
            # update weights based on d and learning rate
            weights = weights + (x*learning_rate*d)
            epoch_error+=1

    return weights, epoch_error

