from datetime import datetime
from pymongo import MongoClient

file = open('Software.txt', encoding="utf8").read()

reviews = []
for i, lines in enumerate(file.split('\n\n')):
    review = {}
    for j, line in enumerate(lines.split('\n')):
        if line == '':
            break
        elif j == 0:
            review['productId'] = line.split(': ')[1]
        elif j == 1:
            review['title'] = line.split(': ')[1]
        elif j == 2:
            price = line.split(': ')[1]
            review['price'] = None if price == "unknown" else float(price)
        elif j == 3:
            userId = line.split(': ')[1]
            review['userId'] = None if userId == "unknown" else userId
        elif j == 4:
            profileName = line.split(': ')[1]
            review['profileName'] = None if profileName == "unknown" else profileName
        elif j == 5:
            review['helpfulness'] = line.split(': ')[1]
        elif j == 6:
            review['score'] = float(line.split(': ')[1])
        elif j == 7:
            # , timezone.utc)  # .isoformat('T', 'auto') -> zapravo nije potrebno
            review['time'] = datetime.utcfromtimestamp(int(line.split(': ')[1]))
        elif j == 8:
            review['summary'] = line.split(': ')[1]
        elif j == 9:
            review['text'] = line.split(': ')[1]
    if len(review) > 0:
        reviews.append(review)

client = MongoClient('mongodb://root:rootnmbp@127.0.0.1')
db = client['labos']
collection = db['reviews']
collection.insert_many(reviews)

