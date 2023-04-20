from cmath import log
import sys
import csv


class ID3:
    def __init__(self, max_depth=99999):
        self.max_depth = max_depth
        self.train_rows = None
        self.attribute_values = None
        self.head = None
        self.outcome = None
    
    def fit(self, train_data, attributes):  # prima parsirani dataset za traniranje
        self.train_rows = len(train_data)
        self.attribute_values = attributes
        self.outcome = list(attributes)[-1]
        print('In CustomIG less is better')
        self.head = self.id3(train_data, train_data, list(attributes)[:-1])

        # branches printing pomocu BFS
        print('[BRANCHES]:')
        queue = list()
        for subtree in self.head.subtrees:
            queue.append(subtree[0])
        while queue:
            s = queue.pop(0)
            if type(s) is Leaf:
                print(s.path)
            if type(s) is Node:
                for subtree in s.subtrees:
                    queue.append(subtree[0])

    def id3(self, data, parent_data, attributes, depth=1, path=''):
        if len(data) == 0 or depth == 0:
            # value je onaj value od outcome koji je najbrojniji od parent_data
            value = self.most_common_outcome(parent_data)
            path = path + value
            return Leaf(value, path)
        # value je onaj koji je najbrojniji od data
        value = self.most_common_outcome(data)
        most_common_outcome_data = [row for row in data if row[self.outcome] == value]
        if len(attributes) == 0 or data == most_common_outcome_data or depth > self.max_depth: # ili data je jednak data kada gledamo samo values koje su najbrojnije (npr. preostalo je 5 yes i 0 no -> znaci mora biti leaf sa yes)
            path = path + value
            return Leaf(value, path)
        
        x = self.most_discriminant_attribute(data, attributes)
        subtrees = []
        
        for attribute_value in self.attribute_values[x]:
            new_data = [row for row in data if row[x] == attribute_value]
            new_attributes = attributes.copy()
            new_attributes.remove(x)
            node = self.id3(new_data , data, new_attributes, depth+1, path + f'{depth}:{x}={attribute_value} ')
            subtrees.append((node, attribute_value))
        return Node(value, subtrees, depth, x)
    
    def predict(self, test_data):  # proci kroz stablo da vidimo koji je rezultat
        predictions = []
        correct = 0
        sorted_outcome_values = sorted(list(self.attribute_values.get(self.outcome)))
        outcome_values_values = {}
        for i, x in enumerate(sorted_outcome_values):
            outcome_values_values[x] = i
        confusion_matrix = [0] * len(sorted_outcome_values)*len(sorted_outcome_values)
        # print(outcome_values_values)
        print('[PREDICTIONS]:', end='')
        for row in test_data:
            obj = self.head
            while type(obj) is not Leaf:
                attribute_value = row.get(obj.attribute)
                if attribute_value not in self.attribute_values.get(obj.attribute):
                    break
                for subtree in obj.subtrees:
                    if subtree[1] == attribute_value:
                        obj = subtree[0]
                        break
            confusion_matrix[outcome_values_values.get(row.get(self.outcome)) * len(
                outcome_values_values) + outcome_values_values.get(obj.value)] += 1
            predictions.append(obj.value)
            if obj.value == row.get(self.outcome):
                correct += 1
            print(' ' + obj.value, end='')
        print()
        print('[ACCURACY]: ', end='')
        print(format(correct/len(test_data), ".5f"))
        print('[CONFUSION_MATRIX]:')
        for i, number in enumerate(confusion_matrix):
            if i % len(outcome_values_values) == len(outcome_values_values)-1:
                print(number)
            else:
                print(number, end=' ')
        # print(confusion_matrix)
        return predictions

    def most_discriminant_attribute(self, data, attributes):
        attribute_outcomes = {}
        total = len(data)
        for attribute in attributes: # za svaki atribut
            specific_outcomes = dict()
            for attribute_value in self.attribute_values[attribute]: # za sve dosad vidjene vrijednosti tog atributa
                specific_outcomes[attribute_value] = list()
                specific_outcomes[attribute_value].append(dict())
                specific_outcomes[attribute_value].append(0)
            for row in data:
                specific_outcomes[row[attribute]][1] += 1
                if specific_outcomes[row[attribute]][0].get(row[self.outcome]) is not None:
                    specific_outcomes[row[attribute]][0][row[self.outcome]] += 1
                else:
                    specific_outcomes[row[attribute]][0][row[self.outcome]] = 1
            attribute_outcomes[attribute] = specific_outcomes
        print(attribute_outcomes)
        most_discriminant = ''
        max_ig = 9999999
        for attribute, outcomes in attribute_outcomes.items():
            information_gain = 0.0
            for outcome in outcomes.values():
                child_entropy = 0.0
                for value in outcome[0].values():
                    child_entropy -= value/outcome[1] * log(value/outcome[1], 2)
                information_gain += outcome[1]/total * child_entropy
            information_gain = round(information_gain.real, 5)
            print(f'CustomIG({attribute}) = {information_gain}', end=' ')
            if information_gain < max_ig or information_gain <= max_ig and attribute < most_discriminant:
                max_ig = information_gain
                most_discriminant = attribute
        print()
        return most_discriminant
 
    def most_common_outcome(self, data):
        values = {}
        for row in data:
            value = row.get(self.outcome)
            if values.get(value) is None:
                values[value] = 1
            else:
                values[value] += 1
        values = dict(sorted(values.items()))
        return max(values, key=values.get)
            

class Node:
    def __init__(self, value, subtrees, depth, attribute):
        self.value = value
        self.depth = depth
        self.subtrees = subtrees
        self.attribute = attribute
        

class Leaf:
    def __init__(self, value, path):
        self.value = value
        self.path = path


if len(sys.argv) >= 4:
    model = ID3(int(sys.argv[3]))
else:
    model = ID3()

train_data = []
attribute_values = {}   # key = naziv atributa, value = sve moguce vrijednosti atributa (set)
with open(sys.argv[1], newline='') as train_dataset_csv:
    train_dataset = csv.DictReader(train_dataset_csv)  # zasebni ulazi kao dictionary
    for row in train_dataset:
        # print(row)
        train_data.append(row)
        for key, value in row.items():
            if key in attribute_values:
                attribute_values[key].add(value)
            else:
                attribute_values[key] = {value}
# attribute_values = dict(sorted(attribute_values.items()))
model.fit(train_data, attribute_values)

test_data = []
with open(sys.argv[2], newline='') as test_dataset_csv:
    test_dataset = csv.DictReader(test_dataset_csv)
    for row in test_dataset:
        test_data.append(row)

predictions = model.predict(test_data)



