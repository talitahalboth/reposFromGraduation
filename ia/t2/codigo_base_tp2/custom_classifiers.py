import numpy as np
from my_perceptron import run_perceptron
from sklearn import datasets

from sklearn.model_selection import train_test_split
from sklearn.datasets import make_classification
from sklearn import preprocessing

import matplotlib.pyplot as plt

from sklearn.manifold import TSNE

# from sklearn.datasets.samples_generator import make_blobs

from sklearn.utils import shuffle



class PerceptronClassifier():
    def __init__(self, learning_rate=0.001, max_iter=200, verbose=0, random_state=0):
        self.learning_rate = learning_rate
        self.max_iter = max_iter
        self.weights = None
        self.verbose = verbose
        self.random_state = random_state

    def fit(self, train_x, train_y):
        random_state_bkp = np.random.get_state()
        np.random.seed(self.random_state)
        train_x = np.array(train_x)
        total_instances, total_dim = train_x.shape
        train_x = np.append(np.ones((total_instances,1)), train_x, axis=1)

        train_y = np.array(train_y)

        train_x, train_y = shuffle(train_x, train_y, random_state=self.random_state)


        # Random Uniform Initialization
        weights = np.array([np.random.uniform(-1, 1)
                                 for _ in range(total_dim+1)])
        self.train_x = train_x
        self.train_y = train_y


        best_error = float('inf')

        if self.verbose >= 1:
            print("Training perceptron classifier")

        for epoch in range(self.max_iter):

            # Run kernel implemented by student
            weights, epoch_error = run_perceptron(weights, train_x,
                                                       train_y, self.learning_rate)


            if self.verbose >= 2 and (epoch % (self.max_iter/10) == 0):
                print("Error at epoch {}:\t{}".format(epoch, epoch_error))

            # If a better solution was founded, save it
            if epoch_error < best_error:
                best_weights = weights
                best_error = epoch_error
                if epoch_error == 0:
                    if self.verbose >= 1:
                        print("Error 0 at epoch {}. Exiting training.".format(epoch))
                    break
        self.weights = weights
        self.best_weights = best_weights
        
        np.random.set_state(random_state_bkp)

    def predict(self,test_x):
        test_x = np.array(test_x)
        total_instances, total_dim = test_x.shape
        test_x = np.append(np.ones((total_instances,1)), test_x, axis=1)

        # Verify what is the side of hyperplane that each point is
        # Then, use this information to predict a label
        pred = np.array([
            1 if self.best_weights.dot(x) >= 0 else 0
            for x in test_x
        ])

        return pred

    def score(self, test_x, test_y, metric="accuracy"):
        if not metric in ["accuracy"]:
            print("Invalid metric")

        pred = self.predict(test_x)
        return np.sum(test_y == pred)/len(test_x)


def generate_xor_problem(cluster_size=1000, random_state=-1):
    random_state_bkp = np.random.get_state()
    if random_state != -1:
        np.random.seed(random_state)
    
    dataX = np.random.random((cluster_size*4, 2))
    dataY = np.zeros(cluster_size*4)

    dataX[cluster_size*3:, 0] += 2
    dataX[cluster_size*3:, 1] += 2

    dataX[cluster_size:cluster_size*2, 0] += 2
    dataX[cluster_size*2:cluster_size*3, 1] += 2

    dataY[cluster_size:cluster_size*2,] = 1
    dataY[cluster_size*2:cluster_size*3] = 1

    np.random.set_state(random_state_bkp)
    return dataX, dataY

def plot_binary_2d_dataset(trainX, testX, trainY, testY, title=""):
    random_state_bkp = np.random.get_state()
    testX = np.array(testX)
    trainX = np.array(trainX)
    if len(trainX) > 0 and trainX.shape[1] > 2:
        merged = np.concatenate((trainX, testX.reshape((-1,trainX.shape[1]))),axis=0)
        merged_2d = TSNE(n_components=2, verbose=0, random_state=0).fit_transform(merged)
        trainX = merged_2d[:len(trainX)]
        testX = merged_2d[len(trainX):]

    if len(trainX) > 0:
        plt.scatter(trainX[:,0], trainX[:,1], c=trainY)
    if len(testX) > 0:
        plt.scatter(testX[:,0], testX[:,1], c=testY, marker="*")

    plt.title(title)
    plt.show()
    np.random.set_state(random_state_bkp)


def load_binary_xor_dataset(test_size=0.25, cluster_size=1000, random_state=-1):
    dataX, dataY = generate_xor_problem(cluster_size=cluster_size, random_state=random_state)

    trainX, testX, trainY, testY = train_test_split(dataX, dataY,
                                           test_size=test_size,
                                           random_state=0)

    return trainX, testX, trainY, testY

def load_binary_iris_dataset(classes_values=(1,2), test_size=0.25):
    iris = datasets.load_iris()
    dataY = iris.target

    # Filter dataset (ignore one of the three classes)
    fill = np.logical_or(dataY == classes_values[0], dataY == classes_values[1])
    dataX = iris.data[fill]  # we only take the first two features.
    dataY = dataY[fill]

    # Convert the labels to binary labels (0 or 1)
    le = preprocessing.LabelEncoder()
    dataY = le.fit_transform(dataY)

    trainX, testX, trainY, testY = train_test_split(dataX, dataY,
                                           test_size=test_size,
                                           random_state=0)

    return trainX, testX, trainY, testY

def load_binary_random_dataset(test_size=0.25, n_samples=1000, n_features=100):
    clusters = 10

    dataX, dataY = make_classification(n_samples=n_samples,
                                       n_features=n_features,
                                       n_clusters_per_class=1,
                                       n_redundant=0,
                                       n_classes=clusters,
                                       class_sep=1.5,
                                       n_informative=1+np.log2(clusters).astype(np.int))

    fill1 = dataY < clusters/2
    fill2 = fill1 == False
    dataY[fill1] = 0
    dataY[fill2] = 1


    trainX, testX, trainY, testY = train_test_split(dataX, dataY,
                                           test_size=test_size,
                                           random_state=0)



    return trainX, testX, trainY, testY
