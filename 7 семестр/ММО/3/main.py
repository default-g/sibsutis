import numpy as np
import sklearn as sk
from sklearn.impute import SimpleImputer
from sklearn.linear_model import Lars
from sklearn import model_selection
from sklearn import preprocessing


def testData(data):
    score = []
    iterations = 10
    for _ in range(iterations):
        x = data[:, :-1]
        y = data[:, -1]

        x_train, x_test, y_train, y_test = model_selection.train_test_split(x, y, test_size=0.3)

        imputer = SimpleImputer()

        imputer.fit(x_train)

        x_train = imputer.transform(x_train)
        x_train = preprocessing.normalize(x_train)

        x_test = imputer.transform(x_test)
        x_test = preprocessing.normalize(x_test)

        regressor = Lars()
        regressor.fit(x_train, y_train)

        y_predicted = regressor.predict(x_test)

        matches = 0
        for y_true, y_pred in zip(y_test, y_predicted):
            matches += (y_pred - 1 <= y_true <= y_pred + 1)
        matches /= len(y_test)

        score.append(matches)
    avg_score = 0
    for s in score:
        avg_score += s
    avg_score /= iterations

    return avg_score


def main():
    general_data = np.genfromtxt(
        'data.csv', delimiter=',', dtype='unicode', skip_header=True)

    classes = {
        "white": 0,
        "red": 1
    }
    for row in general_data:
        row[0] = classes[row[0]]
        for i, _ in enumerate(row):
            if row[i] == '':
                row[i] = np.NaN
    
    general_data = general_data.astype(float)

    red_wine_data = np.array([
        x for x in general_data if x[0] == classes["red"]
    ])

    white_wine_data = np.array([
        x for x in general_data if x[0] == classes["white"]
    ])

    print('General: %.2f%%' % (testData(general_data) * 100))
    print('Red: %.2f%%' % (testData(red_wine_data) * 100))
    print('White: %.2f%%' % (testData(white_wine_data) * 100))


if __name__ == "__main__":
    main()
