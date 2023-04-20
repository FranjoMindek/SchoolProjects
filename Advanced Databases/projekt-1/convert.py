import pandas as pd

df = pd.read_csv('Musical_instruments_reviews.csv')
df = df[['summary', 'reviewText']]
df.to_csv('converted.csv', index=False)