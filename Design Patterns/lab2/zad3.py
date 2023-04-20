def mymax(iterable, key=lambda x: x):
    max_x=max_key=None
    first = True
    
    for x in iterable:
        if first:
            max_x = x
            max_key = key(x)
            first = False
        if key(x) > max_key:
            max_x = x
            max_key = key(x)
            
    return max_x


maxint = mymax([1, 3, 5, 7, 4, 6, 9, 2, 0])
maxchar = mymax("Suncana strana ulice")
maxstring = mymax([
  "Gle", "malu", "vocku", "poslije", "kise",
  "Puna", "je", "kapi", "pa", "ih", "njise"])
D = {'burek':8, 'buhtla':5, 'zlatno-pecivo':55}
maxdict = mymax(D, D.get)

person1 = ("Franjo", "Mindek")
person2 = ("Alen", "Bazant")
person3 = ("Ivan", "Horvat")
person4 = ("Zvonimir", "Kovacic")
person4 = ("Branimir", "Zgodan")

people = [person1, person2, person3, person4]

lastperson = mymax(people, lambda x: x[::-1]) # prezime pa ime, pretpostavljam da se tako mislilo

print(maxint, maxchar, maxstring, maxdict, lastperson)

