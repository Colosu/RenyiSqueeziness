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
    Pearson50file = "./Pearson50.txt"
    Spearman50file = "./Spearman50.txt"
    Correlationfile = "./Correlation.png"
    
    AlphaFile = open(Alphafile, "r")
    Pearson50File = open(Pearson50file, "r")
    Spearman50File = open(Spearman50file, "r")
    
    
    Alpha = []
    for line in AlphaFile:
        Alpha.append(float(line))
    Pearson50 = []
    for line in Pearson50File:
        Pearson50.append(float(line))
    Spearman50 = []
    for line in Spearman50File:
        Spearman50.append(float(line))
    
    AlphaFile.close()
    Pearson50File.close()
    Spearman50File.close()
    
    intP50 = interp1d(Alpha, Pearson50, kind='quadratic')
    intS50 = interp1d(Alpha, Spearman50, kind='quadratic')
    grid = np.linspace(0, 11, num=101, endpoint=True)
    
    # plot patterns
    fig1 = '\u03B1 vs Correlation'
    plt.figure(fig1)
    plt.title(fig1)
    plt.xlabel("\u03B1")
    plt.ylabel("Correlation")
    #plt.xlim(-0.1,1.1)
    #plt.ylim(-0.1,2)
    #plt.plot(Alpha, Pearson10)
    plt.plot(grid, intP50(grid), grid, intS50(grid))
    plt.legend(["Pearson", "Spearman"])
    plt.savefig(Correlationfile)
    plt.clf()