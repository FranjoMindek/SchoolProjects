
def reverse_sort(names: list) -> list:
    copy: list = names.copy()
    copy.sort(reverse=True)
    return copy


if __name__ == '__main__':

    names = ["Ana", "Petar", "Ana", "Lucija", "Vanja", "Pavao", "Lucija"]
    names_desc = reverse_sort(names)
    selected_names = names_desc[:-1]
    unique_selected_names = set(selected_names)
    pass_names = []
    for name in unique_selected_names:
        pass_names.append(name + "-pass")
    print(names_desc)
    print(selected_names)
    print(unique_selected_names)
    print(pass_names)
