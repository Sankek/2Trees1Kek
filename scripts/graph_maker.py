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

save_path = "data/graphs"
data_path = "data/data.csv"
title = ''
if len(sys.argv) > 1:
    name = sys.argv[1]
    save_path += "/" + name
    data_path = "data/" + name + ".csv"
    title = name


df = pd.read_csv(data_path)
Path(save_path).mkdir(parents=True, exist_ok=True)

y = df.elapsed_find_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle(f'Find time {title}')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(save_path + '/find_time.pdf')

y = df.elapsed_insert_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle(f'Insert time {title}')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(f'{save_path}/insert_time.pdf')

y = df.elapsed_delete_time
x = [10 ** i for i in range(len(y))]
fig, axs = plt.subplots(1, 2, figsize=(15, 4))
fig.suptitle(f'Delete time {title}')
axs[0].plot(y)
axs[1].plot(x, y)
plt.savefig(f'{save_path}/delete_time.pdf')
