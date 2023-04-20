import numpy as np
import argparse
# import threading
# import time
# from copy import deepcopy
# import random



# class Neuron:
#     # def __init__(self, ulaz, funkcija=sigmoid) -> None:
#     #     self.tezine = np.random.normal(0, 0.01, ulaz+1) 
#     #     self.funkcija = funkcija
#         # for i in range(ulaz):
#         #     self.tezine.append(np.random.normal()
        
#     def random(self, ulaz, funkcija=sigmoid) -> None:
#         self.tezine = np.random.normal(0, 0.01, ulaz+1) 
#         self.funkcija = funkcija
        

#     def izlaz(self, ulaz) -> float:
#         return self.funkcija(np.dot(self.tezine[:-1], ulaz) + self.tezine[-1])
    

# class NeuronskaMreza:
#     # def __init__(self, slojevi: list) -> None:  # slojevi -> ulaz/sloj1/sloj2../izlaz
    
#     def random(self, slojevi: list) -> None:
#         self.slojevi = []
#         for i in range(1,len(slojevi)):
#             neuroni = []
#             for j in range(slojevi[i]):
#                 neuroni.append(Neuron())
#                 neuroni[j].random(slojevi[i-1])
#             self.slojevi.append(neuroni)
            
#     def print_arhitecture(self) -> None:
#         for i, sloj in enumerate(self.slojevi):
#             print("sloj", i+1)
#             for j, neuron in enumerate(sloj):
#                 print("neuron", j+1, "-> tezine", neuron.tezine[:-1], "bias", neuron.tezine[-1])
    
#     def izlaz(self, ulazi) -> float:
#         ulaz = ulazi
#         for i, sloj in enumerate(self.slojevi):
#             # print("sloj", i, "ulaz ->", ulaz)
#             temp = []
#             for neuron in sloj:
#                 izlaz = neuron.izlaz(ulaz)
#                 temp.append(izlaz)
#             ulaz = deepcopy(temp)
#         # print("izlaz ->", ulaz)
#         return ulaz[0]  # hardkodirano 1 izlaz
                
#     def greska(self, ulazi, izlazi) -> float:  # ulazi = lista ulaza koji sami mogu biti liste
#         greska = 0
#         for i in range(len(ulazi)):
#             izlaz = self.izlaz(ulazi[i])
#             greska += (izlazi[i] - izlaz)**2
#         greska = greska / len(ulazi)
        # return greska
# ulazi = [[1, 2, 3], [1, 2, 3]]
# izlazi = [1, 2]
# test = [3, 5, 5, 1]
# nm = NeuronskaMreza(test)
# nm.print_arhitecture()
# print(nm.greska(ulazi, izlazi))


# def proporcionalna_selekcija(kazne, ukupna_kazna):
#     izbor = np.random.rand()
#     trenutni = 0
#     for kazna in kazne:
#         trenutni += kazna[0]/ukupna_kazna
#         if trenutni > izbor:
#             return kazna[1]

# def krizaj(roditelj1: NeuronskaMreza, roditelj2: NeuronskaMreza, arhitektura):
#     dijete = NeuronskaMreza()
#     dijete.random(arhitektura)
#     for sloj in range(len(dijete.slojevi)):
#         for neuron in range(len(dijete.slojevi[sloj])):
#             dijete.slojevi[sloj][neuron].tezine = (roditelj1.slojevi[sloj][neuron].tezine + roditelj2.slojevi[sloj][neuron].tezine) / 2
#             # print(f"Rod1={roditelj1.slojevi[sloj][neuron].tezine}\nRod2={roditelj2.slojevi[sloj][neuron].tezine}\nDijete={dijete.slojevi[sloj][neuron].tezine}")
#     return dijete

# def mutiraj(vjerojatnost, skala, neuronska_mreza):
#     for sloj in range(len(neuronska_mreza.slojevi)):
#         for neuron in range(len(neuronska_mreza.slojevi[sloj])):
#             if np.random.rand() <= vjerojatnost:
#                 neuronska_mreza.slojevi[sloj][neuron].tezine += np.random.normal(0, skala)
#                 # print("mutirao")


# treniranje = "sine_train.txt"
# testiranje = "sine_test.txt"

# arhitektura = [5, 1]  # ucitati 

# ulazi = []
# izlazi = []

# with open(treniranje, "r") as treniranje_info:
#     header = treniranje_info.readline().split(",")
#     arhitektura.insert(0, len(header)-1)
#     data = treniranje_info.readlines()
#     for line in data:
#         brojevi = line.split(",")
#         ulazi.append(list(map(float, (brojevi[:-1]))))
#         izlazi.append(float(brojevi[-1]))
        
# ulazi = np.array(ulazi)
# izlazi = np.array(izlazi)
        
# velicina_populacije = 10
# elitizam = 2
# vjerojatnost_mutacije = 0.1
# skala_mutacije = 0.1
# iteracija = 10000

# neuronske_mreze = []
# # pocetna populacija
# for i in range(velicina_populacije):
#     neuronske_mreze.append(NeuronskaMreza())
#     neuronske_mreze[i].random(arhitektura)

# for i in range(iteracija+1):
#     nova_populacija = []
    
#     kazne = []
#     ukupna_kazna = 0
    
#     # izracunaj greske zbog elitizma i selekcije
#     for j in range(velicina_populacije):  # [(kazna0, nm0), (kazna1, nm1), ...]
#         greska = neuronske_mreze[j].greska(ulazi, izlazi)
#         ukupna_kazna += greska
#         kazne.append((greska, neuronske_mreze[j]))
#     kazne.sort(key = lambda x: x[0]) 
#     # dodaj elitizam najboljih u novu populaciju
#     for j in range(elitizam):
#         nova_populacija.append(kazne[j][1])
#     # 
#     while len(nova_populacija) < velicina_populacije:
#         roditelj1 = proporcionalna_selekcija(kazne, ukupna_kazna)
#         roditelj2 = proporcionalna_selekcija(kazne, ukupna_kazna)
#         dijete = krizaj(roditelj1, roditelj2, arhitektura) # dijete poprima srednje vrijednosti
#         mutiraj(vjerojatnost_mutacije, skala_mutacije, dijete)
#         nova_populacija.append(dijete)
            
#     neuronske_mreze = nova_populacija
    
#     # print("Interation", i)
#     if i % 2000 == 0:
#         print(f"[Train error @{i}]: {kazne[0]}")
def sigmoid(x):
    return 1/(1+np.exp(-x))

class NeuronskaMreza:
    def __init__(self, arhitektura: list, roditelj1 = None, roditelj2 = None) -> None:
        self.arhitektura = arhitektura
        granice_tezina = [0]
        for i in range(1, len(arhitektura)):
            granice_tezina.append((arhitektura[i-1]+1) * arhitektura[i] + granice_tezina[i-1])
        if roditelj1 is None or roditelj2 is None:
            self.tezine = np.random.normal(0, 0.01, granice_tezina[-1])
        else:
            self.tezine = (roditelj1.tezine + roditelj2.tezine)/2
        
        self.slojevi = [] 
        for i in range(1, len(arhitektura)):
            neuroni = []
            vel_ulaza = arhitektura[i-1]+1
            broj_neurona = arhitektura[i]
            
            for j in range(broj_neurona):  # 0 1 2 3 4
                poc = j * vel_ulaza + granice_tezina[i-1]
                neuroni.append(self.tezine[poc:poc+vel_ulaza])
                
            self.slojevi.append(neuroni)
            
    def test(self):
        print(self.tezine)
        for sloj in self.slojevi:
            print(sloj)
            for neuron in sloj:
                print(neuron, end='')
            print()
        

    def izlaz(self, ulaz) -> float:  # hardkodirano na 1 izlaz tipa float
        izlazi_sloja = ulaz
        for sloj in self.slojevi[:-1]:
            izlazi = []
            for neuron in sloj:
                izlazi.append(sigmoid(np.dot(neuron, izlazi_sloja)))
            izlazi.append(1.0)
            izlazi_sloja = izlazi
        izlaz = np.dot(self.slojevi[-1][0], izlazi_sloja)
        return izlaz  # izbaci izlaz dodan zbog bias (1.0) 
    
    def mutiraj(self, vjerojatnost, skala) -> None:
        # test = [0 if np.random.rand() < vjerojatnost else np.random.normal(0.0, skala) for i in range(len(self.tezine))]
        # print(test)
        mutacije = np.random.choice([0, np.random.normal(0.0, skala)], len(self.tezine), p=[1-vjerojatnost, vjerojatnost])
        self.tezine += mutacije

    def greska(self, ulazi, izlazi) -> float:
        greska = 0
        for i in range(len(ulazi)):
            izlaz = self.izlaz(ulazi[i])
            greska += (izlazi[i] - izlaz)**2
        greska = greska / len(ulazi)
        return greska
        

def proporcionalna_selekcija(dobrote, ukupna_dobrota):
    izbor = np.random.rand()
    trenutni = 0
    for dobrota in dobrote:
        trenutni += dobrota[0]/ukupna_dobrota
        if trenutni > izbor:
            return dobrota[1]
        
def dodaj_dobrotu(neuronska_mreza, dobrote, ulazi, izlazi):
    greska = neuronska_mreza.greska(ulazi, izlazi)
    dobrota = 1/greska
    dobrote.append((dobrota, neuronska_mreza))

parser = argparse.ArgumentParser(description='Configuration')
parser.add_argument('--train')
parser.add_argument('--test')
parser.add_argument('--nn')
parser.add_argument('--popsize')
parser.add_argument('--elitism')
parser.add_argument('--p')
parser.add_argument('--K')
parser.add_argument('--iter')
args = parser.parse_args()


treniranje = args.train
testiranje = args.test

arhitektura = []
if args.nn == "5s":
    arhitektura = [5, 1]  # ucitati 
elif args.nn == "20s":
    arhitektura = [20, 1]
elif args.nn == "5s5s":
    arhitektura = [5, 5, 1]

ulazi_treniranje = []
izlazi_treniranje = []

ulazi_testiranje = []
izlazi_testiranje = []

with open(treniranje, "r") as testiranje_info:
    header = testiranje_info.readline().split(",")
    arhitektura.insert(0, len(header)-1)
    data = testiranje_info.readlines()
    for line in data:
        brojevi = line.split(",")
        brojevi = list(map(float, brojevi))
        brojevi.insert(len(brojevi)-1, 1.0)

        ulazi_treniranje.append(brojevi[:-1])
        izlazi_treniranje.append(brojevi[-1])

with open(testiranje, "r") as testiranje_info:
    header = testiranje_info.readline()
    data = testiranje_info.readlines()
    for line in data:
        brojevi = line.split(",")
        brojevi = list(map(float, brojevi))
        brojevi.insert(len(brojevi)-1, 1.0)

        ulazi_testiranje.append(brojevi[:-1])
        izlazi_testiranje.append(brojevi[-1])
        
ulazi_treniranje = np.array(ulazi_treniranje)
izlazi_treniranje = np.array(izlazi_treniranje)

ulazi_testiranje = np.array(ulazi_testiranje)
izlazi_testiranje = np.array(izlazi_testiranje)

# print(ulazi_testiranje)
# print(izlazi_testiranje)
   
velicina_populacije = int(args.popsize)
elitizam = int(args.elitism)
vjerojatnost_mutacije = float(args.p)
skala_mutacije = float(args.K)
iteracija = int(args.iter)

neuronske_mreze = []
# pocetna populacija
for i in range(velicina_populacije):
    neuronske_mreze.append(NeuronskaMreza(arhitektura))

for i in range(1,iteracija+1):
    nova_populacija = []
    
    dobrote = []
    ukupna_dobrota = 0
    
    # izracunaj greske zbog elitizma i selekcije
    # time0 = time.time_ns()
    for j in range(velicina_populacije):  # [(kazna0, nm0), (kazna1, nm1), ...]
        dobrota = 1/neuronske_mreze[j].greska(ulazi_treniranje, izlazi_treniranje)
        ukupna_dobrota += dobrota
        dobrote.append((dobrota, neuronske_mreze[j]))

    # threads = []
    # for j in range(velicina_populacije):  # [(kazna0, nm0), (kazna1, nm1), ...]
    #     thread = threading.Thread(target=dodaj_dobrotu, args=(neuronske_mreze[j], dobrote, ulazi, izlazi))
    #     threads.append(thread)
    #     threads[j].start()
    # for thread in threads:
    #     thread.join() 
    # ukupna_dobrota = sum(x[0] for x in dobrote)  
        
    # time1 = time.time_ns()
    # print("Racunanje dobrote ", time1-time0)

    dobrote.sort(key = lambda x: x[0], reverse=True) 
    # dodaj elitizam najboljih u novu populaciju
    for j in range(elitizam):
        nova_populacija.append(dobrote[j][1])
    # krizaj
    while len(nova_populacija) < velicina_populacije:
        roditelj1 = proporcionalna_selekcija(dobrote, ukupna_dobrota)
        roditelj2 = proporcionalna_selekcija(dobrote, ukupna_dobrota)
        # print(roditelj1, roditelj2)
        dijete = NeuronskaMreza(arhitektura, roditelj1=roditelj1, roditelj2=roditelj2)# dijete poprima srednje vrijednosti
        dijete.mutiraj(vjerojatnost_mutacije, skala_mutacije)
        nova_populacija.append(dijete)
    neuronske_mreze = nova_populacija

    if i % 2000 == 0:
        print(f"[Train error @{i}]: {1/dobrote[0][0]}") 

min_greska = None
for j in range(velicina_populacije):  # [(kazna0, nm0), (kazna1, nm1), ...]
    greska = neuronske_mreze[j].greska(ulazi_testiranje, izlazi_testiranje)
    if min_greska is None or greska < min_greska:
        min_greska = greska
print(f"[Test error]: {min_greska}")
        
            

