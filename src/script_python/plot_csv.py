import csv
import sys
import numpy as np
import matplotlib.pyplot as plt

import plotly.plotly as py
import plotly.graph_objs as go
import scipy
from scipy import signal
import math




def plot_double_graph(args):
    filename = args[0]
    data1 = np.genfromtxt(filename, delimiter=',')

    color = 'tab:red'
    fig, ax1 = plt.subplots()    
    ax1.set_xlabel('#hand')
    ax1.set_ylabel('fist file', color=color)
    
    if len(args) > 1:
        filename = args[1]
        data2 = np.genfromtxt(filename, delimiter=',')
        # data2 = signal.savgol_filter(data2, math.ceil(data2.shape[0]/50), 2)

        size_max = min(data1.shape[0], data2.shape[0])

        data1 = data1[0:size_max]
        data2 = data2[0:size_max]

        ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis

        color = 'tab:blue'
        ax2.set_ylabel('second file', color=color)  # we already handled the x-label with ax1
        ax2.plot(data2, color=color)
        ax2.tick_params(axis='y', labelcolor=color)

    color = 'tab:red'
    ax1.plot(data1, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    

    fig.tight_layout()  # otherwise the right y-label is slightly clipped
    plt.show()


def plot_smooth_graph(args):
    filename = args[0]
    data1 = np.genfromtxt(filename, delimiter=',')
    trace = go.Scatter(
    y = signal.savgol_filter(data1, math.ceil(data1.shape[0]/50), 2),
    mode='line'
    )
    data = [trace]
    py.iplot(data, filename='basic-line')



def main(argv):    
    plot_double_graph(argv)
    # plot_graph(argv)


if __name__ == "__main__":
    main(sys.argv[1:])


