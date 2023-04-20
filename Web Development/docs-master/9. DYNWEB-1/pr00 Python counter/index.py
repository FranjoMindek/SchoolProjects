from datetime import date
today = date.today()
fc = today.strftime('%Y%m%d') + ".counter"
num = 0
try:
    #trying to open a file in read mode
    f = open(fc, "rt")
    num = int(f.readline())
    f.close()
except IOError:
    pass
except:
    print("Other error")

num = num + 1

f = open(fc, "wt")
f.write(str(num) + "\n")
f.close()

print ("Ova stranica je posjecena " + str(num) + " puta.")
