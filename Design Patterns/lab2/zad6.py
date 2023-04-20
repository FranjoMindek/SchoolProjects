from string import ascii_uppercase


class Sheet:
  def __init__(self, width, height):
    if width > 26:
      self.width = 26
    else:
      self.width = width
    self.height = height
    #self.cells = [Cell(self)] * self.width * self.height
    self.name_dict = {}
    self.ref_list = [[None for i in range(self.height)] for i in range(self.width)]
    for w in range(self.width):
      for h in range(self.height):
        name = ascii_uppercase[w] + str(h+1)
        self.name_dict[name] = (w, h)

  def set(self, name, exp):
    (w, h) = self.name_dict.get(name)
    self.ref_list[w][h] = Cell(self, name, exp)

  def call(self, name):
    (w, h) = self.name_dict.get(name)
    return self.ref_list[w][h]

  def print(self):
    print('==================================')
    for cells in self.ref_list:
      for cell in cells:
        if cell is not None:
          print(cell)
    print('==================================')

  def getrefs(self, cell):
    if cell.exp.isdigit():
      return None
    refs = list(map(lambda name: self.call(name), cell.exp.split("+")))
    return refs

  def evaluate(self, cell, already_evaluated):
    refs = self.getrefs(cell)
    if refs is None:
      cell.value = int(cell.exp)
      return
    value = 0
    if not set(refs).isdisjoint(already_evaluated):
      raise RuntimeError("Dependency loop")
    already_evaluated.append(cell)
    for ref in refs:
      already_evaluated_copy = already_evaluated[:] # Python sve radi s referencama
      self.evaluate(ref, already_evaluated_copy)    # pa bi u slučaju A4+A4+A4 program bacio Dependency loop error
      value += ref.value                            # iako on zapravo ne postoji
    cell.value = value                              # stoga šaljemo referencu na duplikat objekta


class Cell:
  def __init__(self, sheet, name, exp):
    self.sheet = sheet
    self.exp = exp
    self.name = name
    self.sheet.evaluate(self, [])
  def __str__(self):
    return f'Cell {self.name} of expresssion {self.exp} is {self.value}'
  def __eq__(self, other):
    return self.name == other.name
  def __hash__(self):
    return hash(self.name)


s=Sheet(5,5)

s.set('A1','2')
s.set('A2','5')
s.set('A3','A1+A2')
s.print()

s.set('A1','4')
s.set('A4','A1+A3')
s.print()

try:
  s.set('A1','A3')
except RuntimeError as e:
  print("Caught exception:",e)
s.print()

s.set('B1', 'A4+A4+A4')
s.print()