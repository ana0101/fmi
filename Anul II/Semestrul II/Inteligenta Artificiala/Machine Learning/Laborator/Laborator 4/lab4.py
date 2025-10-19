import numpy as np
from sklearn import svm
from sklearn.metrics import accuracy_score
from sklearn.metrics import f1_score

train_data = np.load('data_lab5/data/training_sentences.npy', allow_pickle=True)
train_labels = np.load('data_lab5/data/training_labels.npy', allow_pickle=True)
test_data = np.load('data_lab5/data/test_sentences.npy', allow_pickle=True)
test_labels = np.load('data_lab5/data/test_labels.npy', allow_pickle=True)


# 1
def normalize_data(train_data, test_data, type=None):
    if type is None:
        return train_data, test_data

    elif type == 'standard':
        mean_train_data = np.mean(train_data, axis=0)
        std_train_data = np.std(train_data, axis=0)
        normalized_train_data = np.divide(np.subtract(train_data, mean_train_data), std_train_data)
        mean_test_data = np.mean(test_data, axis=0)
        std_test_data = np.std(test_data, axis=0)
        normalized_test_data = np.divide(np.subtract(test_data, mean_test_data), std_test_data)
        return normalized_train_data, normalized_test_data

    elif type == 'l1':
        train_norm = np.sum(np.abs(train_data), axis=0)
        normalized_train_data = np.divide(train_data, train_norm)
        test_norm = np.sum(np.abs(test_data), axis=0)
        normalized_test_data = np.divide(test_data, test_norm)
        return normalized_train_data, normalized_test_data

    elif type == 'l2':
        train_norm = np.sqrt(np.sum(np.square(train_data)))
        normalized_train_data = np.divide(train_data, train_norm)
        test_norm = np.sqrt(np.sum(np.square(test_data)))
        normalized_test_data = np.divide(test_data, test_norm)
        return normalized_train_data, normalized_test_data


# 2
class BagOfWords:
    def __init__(self):
        self.vocab = {}

    def build_vocabulary(self, data):
        idx = 0
        words = []
        for message in data:
            for word in message:
                if word not in self.vocab:
                    self.vocab[word] = idx
                    words.append(word)
                    idx += 1

    def get_features(self, data):
        features = np.zeros((len(data), len(self.vocab)))
        for i, message in enumerate(data):
            for word in message:
                if word in self.vocab:
                    features[i, self.vocab[word]] += 1
        return features

bag = BagOfWords()
bag.build_vocabulary(train_data)
train_features = bag.get_features(train_data)
test_features = bag.get_features(test_data)
normalized_train_features, normalized_test_features = normalize_data(train_features, test_features, 'l2')
print(len(bag.vocab))

# 6
svm_model = svm.SVC(kernel='linear', C=1)
svm_model.fit(normalized_train_features, train_labels)
test_predictions = svm_model.predict(normalized_test_features)
accuracy = accuracy_score(test_labels, test_predictions)
f1 = f1_score(test_labels, test_predictions)
print('Accuracy:', accuracy)
print('F1:', f1)

# 7
coefficients = svm_model.coef_
sorted_indices = np.argsort(coefficients)
print('Most negative words:')
for i in range(10):
    print(sorted_indices[i])

print('Most positive words:')
for i in range(10):
    print(sorted_indices[-i-1])