import numpy as np


class DatasetGenerator:

    def generate_dataset(self, size):
        self.set_random_target_line()
        self.dataset = []
        if size < 1:
            print('Warning: Dataset size must be greater than 1. Executing\
                    with one sample')
        for i in range(max(1, size)):
            x1, x2 = [np.random.uniform(-1, 1) for _ in range(2)]
            attrs = np.array([1, x1, x2])
            label = 1 if self.target_line.dot(attrs) >= 0 else 0
            self.dataset.append((attrs, label))

    def split_dataset(self, test_proportion=.3):
        dataset = np.array(self.dataset)
        test_set, train_set = [], []
        for label in (0, 1):
            label_set = dataset[dataset[:, 1] == label].tolist()
            test_size = round(test_proportion * len(label_set))
            test_set.extend(label_set[:test_size])
            train_set.extend(label_set[test_size:])
        np.random.shuffle(test_set)
        np.random.shuffle(train_set)
        return train_set, test_set

    def set_random_target_line(self):
        w1, w2 = [np.random.uniform(-1, 1) for _ in range(2)]
        # make bias close to 0 to force a fair class division
        b = np.random.uniform(-.15, .15)
        self.target_line = np.array([b, w1, w2])

    def get_split_dataset(self, size, test_proportion):
        self.generate_dataset(size)
        return self.split_dataset(test_proportion), self.target_line
