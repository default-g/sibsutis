import pandas as pd
import numpy as np
from sklearn.tree import DecisionTreeClassifier
from sklearn import tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.impute import SimpleImputer


data = pd.read_csv('heart_data.csv')

data = data.replace('?', np.nan)
data = data.astype(float)
# data = data.fillna(data.mean())

dropped_column = data.drop('goal', axis=1)
imputer = SimpleImputer()
imputer.fit(dropped_column)

X = imputer.transform(dropped_column)
y = data['goal']

max_depths = [i for i in range(2, 17, 2)]
max_leaf_nodes = [i for i in range(2, 17, 2)]

max_accuracy_data = {
    'accuracy': 0,
    'max_depth': 0,
    'max_leaf_nodes': 0
}

scores = []

for i in range(10):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)

    for max_depth in max_depths:
        for max_leaf_node in max_leaf_nodes:
            clf = DecisionTreeClassifier(max_depth=max_depth, max_leaf_nodes=max_leaf_node)
            clf.fit(X_train, y_train)
            y_pred = clf.predict(X_test)

            accuracy = accuracy_score(y_test, y_pred)
            if accuracy > max_accuracy_data['accuracy']:
                max_accuracy_data['accuracy'] = accuracy
                max_accuracy_data['max_depth'] = max_depth
                max_accuracy_data['max_leaf_nodes'] = max_leaf_node
            scores.append({'Split': i, 'Max Depth': max_depth, 'Max Leaf Nodes': max_leaf_node, 'Accuracy': accuracy})


table = pd.DataFrame(scores)
table = table.groupby(['Max Depth', 'Max Leaf Nodes']).mean()
table = table[['Accuracy']]
table = table.unstack()
table.columns = table.columns.droplevel()
table.index.name = 'Max Depth'
print(table)

print('Max Accuracy: ', max_accuracy_data['accuracy'])
print('Max Depth: ', max_accuracy_data['max_depth'])
print('Max Leaf Nodes: ', max_accuracy_data['max_leaf_nodes'])


