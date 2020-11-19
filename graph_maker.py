import pandas as pd
import sys
import argparse
from matplotlib import pyplot as plt
from pathlib import Path


# parser = argparse.ArgumentParser(description='Choose tree to process.')
# parser.add_argument('strings', metavar='tree name', type=str, nargs='+',
#                     help='an integer for the accumulator')
# parser.add_argument('--sum', dest='accumulate', action='store_const',
#                     const=sum, default=max,
#                     help='sum the integers (default: find the max)')
#
# args = parser.parse_args()
# print(args.strings)

path = "graphs"
if len(sys.argv) > 1:
    path += sys.argv[1]


pd.read_csv('data.csv')
Path(path).mkdir(parents=True, exist_ok=True)

y = pd.read_csv('data.csv').elapsed_find_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Find time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(path + '/find_time.pdf')

y = pd.read_csv('data.csv').elapsed_insert_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Insert time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(f'{path}/insert_time.pdf')

y = pd.read_csv('data.csv').elapsed_delete_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle('Delete time')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(f'{path}/delete_time.pdf')
