import pandas as pd
from matplotlib import pyplot as plt

pd.read_csv('data.csv')

y = pd.read_csv('data.csv').elapsed_find_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Find time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig('find_time.pdf')

y = pd.read_csv('data.csv').elapsed_insert_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Insert time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig('insert_time.pdf')

y = pd.read_csv('data.csv').elapsed_delete_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Delete time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig('delete_time.pdf')
