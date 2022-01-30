import numpy as np
from matplotlib import pyplot as plt
from app_perceptron_lib.dataset_generator import DatasetGenerator
from app_perceptron_lib.data_plotter import DataPlotter
from gi.repository import GLib


class Perceptron:

    def __init__(self, run_perceptron):
        self.run_perceptron = run_perceptron
        self.line = None

    def clear_line(self):
        self.line = None

    def train(self, train_set, plotter, callback, max_epochs=500,
              learning_rate=0.7):
        weights = np.array([np.random.uniform(-1, 1) for _ in range(3)])
        best_error = float('inf')
        data = [x[0] for x in train_set]
        labels = [x[1] for x in train_set]
        if max_epochs < 1:
            print('Warning: Max epochs must be greater than 1. Executing with one epoch')
        for epoch in range(1, max(2, max_epochs+1)):
            weights, epoch_error = self.run_perceptron(weights, data, labels, learning_rate)
            self.line = plotter.plot_decision_boundary(weights, self.line,
                    color='k', label='Trainning Model')
            if epoch_error < best_error:
                best_weights = weights
                best_epoch = epoch
                best_error = epoch_error
                if epoch_error == 0:
                    break
        self.best_weights = best_weights
        results =  best_weights, best_epoch, best_error
        GLib.idle_add(callback, results)

    def test(self, test_set):
        try:
            prediction_list = []
            test_errors = len(test_set)
            for entry in test_set:
                values, label = entry[0], entry[1]
                prediction = 1 if self.best_weights.dot(values) >= 0 else 0
                is_prediction_right = True if prediction == label else False
                test_errors -= is_prediction_right
                prediction_list.append((entry[0], entry[1],
                                        is_prediction_right))
            return prediction_list, test_errors
        except AttributeError:
            return [], 0
