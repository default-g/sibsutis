import math
import csv
import random
from tabulate import tabulate


def euclidean_distance(point1, point2):
    """Вычисление евклидова расстояния между двумя точками"""
    distance = 0.0
    for i in range(len(point1)):
        distance += (point1[i] - point2[i]) ** 2
    return math.sqrt(distance)


def kfold_split(data, k):
    """Скользящий контроль"""
    fold_size = len(data) // k
    remainder = len(data) % k
    indices = list(range(len(data)))
    folds = []

    start = 0
    for i in range(k):
        fold_indices = indices[start:start+fold_size]
        start += fold_size

        if i < remainder:
            fold_indices.append(indices[start])
            start += 1

        train_indices = [idx for idx in indices if idx not in fold_indices]
        folds.append((train_indices, fold_indices))

    min_fold_size = min(len(train_indices) for train_indices, _ in folds)
    q = 1 / min_fold_size  # Calculate q as the inverse of the minimum fold size

    return folds, q


def k_nearest_neighbors(X_train, y_train, x_test, k):
    """Алгоритм k-ближайших соседей с весовой функцией"""
    distances = []
    for i in range(len(X_train)):
        dist = euclidean_distance(X_train[i], x_test)
        distances.append((dist, y_train[i]))
    distances.sort(key=lambda x: x[0])  # Сортировка по расстоянию
    neighbors = distances[:k]  # k ближайших соседей

    # Определение параметра q
    folds, q = kfold_split(X_train, k)

    # Весовая функция - обратная пропорциональность расстоянию
    weights = [q ** neighbor[0] for neighbor in neighbors]

    labels = [neighbor[1] for neighbor in neighbors]  # Метки классов соседей
    weighted_votes = {}

    # Учет весов при голосовании
    for i in range(k):
        label = labels[i]
        if label not in weighted_votes:
            weighted_votes[label] = 0
        weighted_votes[label] += weights[i]

    # Определение наиболее часто встречающейся метки класса
    majority_vote = max(weighted_votes, key=weighted_votes.get)

    return majority_vote


if __name__ == '__main__':
    data = []
    with open('data.csv', 'r') as file:
        reader = csv.reader(file)
        for row in list(reader)[1:]:
            data.append(row)
    the_1s = []
    the_0s = []
    k = 3
    for row in data:
        if row[2] == '1':
            the_1s.append(row)
        else:
            the_0s.append(row)
    statistics = []
    for i in range(10):
        random.shuffle(the_0s)
        random.shuffle(the_1s)
        target_count = min(len(the_0s), len(the_1s)) // 3
        parts = []
        parts.append(the_0s[:target_count] + the_1s[:target_count])
        parts.append(the_0s[target_count:2*target_count] + the_1s[target_count:2*target_count])
        parts.append(the_0s[2*target_count:] + the_1s[2*target_count:])

        X_train = []
        y_train = []
        for item in parts[0] + parts[1]:
            X_train.append([float(item[0]), float(item[1])])
            y_train.append(float(item[2]))
        statistic = {
            'right': 0,
            'wrong': 0,
        }
        for item in parts[2]:
            prediction = k_nearest_neighbors(X_train, y_train, [float(item[0]), float(item[1])], k)
            if prediction == float(item[2]):
                statistic['right'] += 1
            else:
                statistic['wrong'] += 1
        row = [[
            statistic['right'], statistic['wrong'], (statistic['right'] / (statistic['right'] + statistic['wrong'])) * 100
        ]]
        header = ['Right', 'Wrong', '%' ]
        print(tabulate(row, header, tablefmt='grid'))
