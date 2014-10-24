# -*- coding: utf-8 -*-
#!/usr/bin/python2
#
# Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
#

import sys
import scipy as sp
from scipy.fftpack import fft, fftfreq
import numpy as np
import matplotlib.pyplot as plt

def cos_sample():
    t = np.linspace(0, 120, 4000)
    x = np.cos(t)
    xn = x + np.random.randn(len(t)) * 0.1

    plt.figure('cos')
    plt.subplot(211)
    plt.plot(t, x)
    plt.subplot(212)
    FFT = abs(fft(x))
    freqs = fftfreq(x.size, t[1] - t[0])
    plt.plot(freqs, 20 * sp.log10(FFT), 'x')

    plt.figure('noised')
    plt.subplot(211)
    plt.plot(t, xn)
    plt.subplot(212)
    FFT = abs(fft(xn))
    freqs = fftfreq(xn.size, t[1] - t[0])
    plt.plot(freqs, 20 * sp.log10(FFT), 'x')

    plt.show()

if __name__=='__main__':
    if len(sys.argv) > 1:
        print sys.argv[1]

    cos_sample()
