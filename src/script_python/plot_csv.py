import csv
import sys
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import plotly.plotly as py
import plotly.graph_objs as go
import scipy
import math
import time
from numpy import genfromtxt

def test():
    mycolumns = ['A', 'B']
    df = pd.DataFrame(columns=mycolumns)
    rows = [[1,2],[3,4],[5,6]]
    for row in rows:
        df.loc[len(df)] = row
    print(df)

def interactive_graphs():
    list_graph = [
        "graph1",
        "graph2"
    ]
    foldername = "./"
    filename = os.path.join(foldername, "data.csv")
    print(filename)
    create_data(filename, list_graph)
    fig, axs = plt.subplots(len(list_graph))
    plt.ion()    
    N = 1
    while True:
        print(N)
        N += 1
        add_data_to_graph(filename, list_graph)
        plot_graphs(filename, list_graph)

def plot_graphs(filename, list_graph):#, fig_, axs):
    data = pd.read_csv(filename)
    print(data)
    graphs_to_plot = {}
    for graph in list_graph:
        data_graph = data[graph]
        graphs_to_plot[graph] = data_graph    
    pl_x = 0
    fig, axs = plt.subplots(len(list_graph))
    plt.ion()
    for key in graphs_to_plot:
        axs[pl_x].plot(graphs_to_plot[key])
        pl_x += 1
    plt.show()
    plt.pause(2)
    plt.close(fig)

def create_data(filename, list_graph):
    data_df = pd.DataFrame(columns = list_graph)
    data = [[2, 4], [6, 8]]
    for row in data:
        data_df.loc[len(data_df)] = row
    data_df.to_csv(filename)    

def add_data_to_graph(filename, list_graph):
    data = pd.read_csv(filename, usecols = list_graph)
    data.loc[len(data) ] = [np.random.randn(), np.random.randn()]
    data.to_csv(filename)

def plot_csv_list(foldername, csv_list):
    pl_x = 0
    fig, axs = plt.subplots(len(csv_list))
    plt.ion()
    for graph in csv_list:
        filename = foldername + "/" + graph + ".csv"
        axs[pl_x].plot(get_csv_data(filename))
        pl_x += 1
    plt.show()
    plt.pause(2.5)
    plt.close(fig)
    
def get_csv_data(filename):    
    my_data = genfromtxt(filename, delimiter=',')
    return my_data


def main(argv):    
    csv_list = [
        "river_aggression_proba",
        "bankroll"
    ]
    # while True:
    plot_csv_list(argv[0], csv_list)
    # interactive_graphs()


if __name__ == "__main__":
    main(sys.argv[1:])


