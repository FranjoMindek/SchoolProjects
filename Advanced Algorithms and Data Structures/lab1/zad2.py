
if __name__ == '__main__':

    person_data = {"Ana": 1995,
                   "Zoran": 1978,
                   "Lucija": 2001,
                   "Anja": 1997}
    print(person_data)

    for key in person_data:
        person_data[key] -= 1
    print(person_data)

    year_age = []
    for key, value in person_data.items():
        year_age.append((value, 2022-value))
    print(year_age)

