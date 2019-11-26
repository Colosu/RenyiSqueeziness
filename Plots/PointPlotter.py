#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Apr 24 09:14:54 2018

@author: colosu
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

for J in range(50):
    Alphafile = "./Alpha.txt"
    Pearson10file = "./Pearson10.txt"
    Spearman10file = "./Spearman10.txt"
    Pearson20file = "./Pearson20.txt"
    Spearman20file = "./Spearman20.txt"
    Pearson30file = "./Pearson30.txt"
    Spearman30file = "./Spearman30.txt"
    Pearson40file = "./Pearson40.txt"
    Spearman40file = "./Spearman40.txt"
    Pearson50file = "./Pearson50.txt"
    Spearman50file = "./Spearman50.txt"
    Pearson60file = "./Pearson60.txt"
    Spearman60file = "./Spearman60.txt"
    Pearson70file = "./Pearson70.txt"
    Spearman70file = "./Spearman70.txt"
    Pearsonfile = "./Pearson.png"
    Spearmanfile = "./Spearman.png"
    
    AlphaFile = open(Alphafile, "r")
    Pearson10File = open(Pearson10file, "r")
    Spearman10File = open(Spearman10file, "r")
    Pearson20File = open(Pearson20file, "r")
    Spearman20File = open(Spearman20file, "r")
    Pearson30File = open(Pearson30file, "r")
    Spearman30File = open(Spearman30file, "r")
    Pearson40File = open(Pearson40file, "r")
    Spearman40File = open(Spearman40file, "r")
    Pearson50File = open(Pearson50file, "r")
    Spearman50File = open(Spearman50file, "r")
    Pearson60File = open(Pearson60file, "r")
    Spearman60File = open(Spearman60file, "r")
    Pearson70File = open(Pearson70file, "r")
    Spearman70File = open(Spearman70file, "r")
    
    
    Alpha = []
    for line in AlphaFile:
        Alpha.append(float(line))
    Pearson10 = []
    for line in Pearson10File:
        Pearson10.append(float(line))
    Spearman10 = []
    for line in Spearman10File:
        Spearman10.append(float(line))
    Pearson20 = []
    for line in Pearson20File:
        Pearson20.append(float(line))
    Spearman20 = []
    for line in Spearman20File:
        Spearman20.append(float(line))
    Pearson30 = []
    for line in Pearson30File:
        Pearson30.append(float(line))
    Spearman30 = []
    for line in Spearman30File:
        Spearman30.append(float(line))
    Pearson40 = []
    for line in Pearson40File:
        Pearson40.append(float(line))
    Spearman40 = []
    for line in Spearman40File:
        Spearman40.append(float(line))
    Pearson50 = []
    for line in Pearson50File:
        Pearson50.append(float(line))
    Spearman50 = []
    for line in Spearman50File:
        Spearman50.append(float(line))
    Pearson60 = []
    for line in Pearson60File:
        Pearson60.append(float(line))
    Spearman60 = []
    for line in Spearman60File:
        Spearman60.append(float(line))
    Pearson70 = []
    for line in Pearson70File:
        Pearson70.append(float(line))
    Spearman70 = []
    for line in Spearman70File:
        Spearman70.append(float(line))
    
    AlphaFile.close()
    Pearson10File.close()
    Spearman10File.close()
    Pearson20File.close()
    Spearman20File.close()
    Pearson30File.close()
    Spearman30File.close()
    Pearson40File.close()
    Spearman40File.close()
    Pearson50File.close()
    Spearman50File.close()
    Pearson60File.close()
    Spearman60File.close()
    Pearson70File.close()
    Spearman70File.close()
    
    intP10 = interp1d(Alpha, Pearson10, kind='cubic')
    intS10 = interp1d(Alpha, Spearman10, kind='cubic')
    intP20 = interp1d(Alpha, Pearson20, kind='cubic')
    intS20 = interp1d(Alpha, Spearman20, kind='cubic')
    intP30 = interp1d(Alpha, Pearson30, kind='cubic')
    intS30 = interp1d(Alpha, Spearman30, kind='cubic')
    intP40 = interp1d(Alpha, Pearson40, kind='cubic')
    intS40 = interp1d(Alpha, Spearman40, kind='cubic')
    intP50 = interp1d(Alpha, Pearson50, kind='cubic')
    intS50 = interp1d(Alpha, Spearman50, kind='cubic')
    intP60 = interp1d(Alpha, Pearson60, kind='cubic')
    intS60 = interp1d(Alpha, Spearman60, kind='cubic')
    intP70 = interp1d(Alpha, Pearson70, kind='cubic')
    intS70 = interp1d(Alpha, Spearman70, kind='cubic')
    grid = np.linspace(0, 101, num=1001, endpoint=True)
    
    # plot patterns
    fig1 = '\u03B1 vs Pearson'
    plt.figure(fig1)
    plt.title(fig1)
    plt.xlabel("\u03B1")
    plt.ylabel("Pearson")
    #plt.xlim(-0.1,1.1)
    #plt.ylim(-0.1,2)
    #plt.plot(Alpha, Pearson10)
    plt.plot(grid, intP10(grid), grid, intP20(grid), grid, intP30(grid), grid, intP40(grid), grid, intP50(grid), grid, intP60(grid), grid, intP70(grid))
    plt.legend(["10", "20", "30", "40", "50", "60", "70"])
    plt.savefig(Pearsonfile)
    plt.clf()
    
    fig2 = '\u03B1 vs Spearman'
    plt.figure(fig2)
    plt.title(fig2)
    plt.xlabel("\u03B1")
    plt.ylabel("Spearman")
    #plt.xlim(-0.1,1.1)
    #plt.ylim(-0.1,1.1)
    #plt.plot(Alpha, Spearman10)
    plt.plot(grid, intS10(grid), grid, intS20(grid), grid, intS30(grid), grid, intS40(grid), grid, intS50(grid), grid, intS60(grid), grid, intS70(grid))
    plt.legend(["10", "20", "30", "40", "50", "60", "70"])
    plt.savefig(Spearmanfile)
    plt.clf()