"""Gaussian fit demo.
Andriy Zatserklyaniy <zatserkl@fnal.gov> Feb 6, 2017
"""

import math
import random
import matplotlib.pyplot as plt
from collections import Counter

import numpy as np                      # arrays for fit
from scipy.optimize import curve_fit    # fitting routine

def flat_distribution(N=100):
    """plot distribution
    """
    
    random.seed(0)
    x = [random.random() for _ in range(N)]
    
    # print 'x:', x[:10]

flat_distribution(100)

def gauss_distribution(N=12, ngroups=1000):
    """plot distribution
    """

    print 'N =', N, 'ngroups =', ngroups
    
    random.seed(0)

    #
    # Produces normally distributed random numbers.
    # According the Central Limit Theorem, AVERAGE of large number N
    # of independent identically distributed numbers with mean=mean0 and sigma=sigma0
    # tend to be distributed normally with
    #
    # mean = mean0
    # sigma = sigma0 / sqrt(N)
    #
    # We will use flat distribution (0,1) with mean0 = 0.5 and sigma0 = 1/sqrt(12)
    #

    # list comprehension
    #                    using list comprehension.
    #
    # NB: the variable _ works fine for both.
    xgauss = [sum([random.random() for _ in range(N)])/N for _ in range(ngroups)]

    # print '_ =', _    # _ = 19 here

    # print '\nxgauss:', xgauss[:5]

    mean0  = 0.5
    sigma0 = 1/math.sqrt(12)
    
    # according to statistics:
    # mean  = mean0 = 0.5
    # sigma = sigma0 / sqrt(N)
    #
    mean  = mean0
    sigma = sigma0 / math.sqrt(N)

    print 'expected: mean =', mean, 'sigma =', sigma

    #
    # calculate sigma
    #
    
    variance = sum([(x-mean)**2 for x in xgauss]) / ngroups # use exact mean = 0.5
    sigma_calc = math.sqrt(variance)
    print 'sigma_calc =', sigma_calc

    mean_est = sum(xgauss) / ngroups
    variance_est = sum([(x-mean_est)**2 for x in xgauss]) / (ngroups-1) # use exact mean = 0.5
    sigma_calc_est = math.sqrt(variance_est)
    print 'mean_est =', mean_est, 'sigma_calc_est =', sigma_calc_est

    #########################
    # plot the distribution #
    #########################

    #-- plt.figure()                                        # create a new figure: do not need if use ax
    #
    # get subplot to use axis coordinate system
    #
    fig, ax = plt.subplots(1)

    #
    # plot the histogram
    #
    #-- ybins, xbins, patches = plt.hist(xgauss, bins=20)
    ybins, xbins, patches = ax.hist(xgauss, bins=20)
    # plt.show()                                        # we are in the middle of plot: do not apply plt.show()

    # print 'xbins:', xbins
    # print 'ybins:', ybins

    ################
    #              #
    # fit Gaussian #
    #              #
    ################

    #
    # NB: both parameter arguments (*par and A,mean,sigma) work w/o changes in the code that use the fun
    #
    #-- fun = lambda x, A, mean, sigma: A * np.exp(-0.5*((x-mean)/sigma)**2)    # separate arguments
    fun = lambda x, *par: par[0] * np.exp(-0.5*((x-par[1])/par[2])**2)          # *par: array-like

    ybins_arr = np.array(ybins)
    width = xbins[1] - xbins[0]
    xbins_arr = np.array(xbins[:len(ybins)] + width/2)  # evaluate in the bin center
    yerr_arr = np.sqrt(ybins_arr)
    
    # print 'len(xbins_arr) =', len(xbins_arr), 'len(ybins_arr) =', len(ybins_arr)
    # for i in range(len(xbins_arr)):
    #     print xbins_arr[i], ybins_arr[i]

    # print '\nthe same printout with one line'
    # print ''.format(xbins_arr_i, ybins_arr_i) for xbins_arr_i, ybins_arr_i in zip(xbins_arr, ybins_arr)
    
    ##############################
    # fit and get the parameters #
    ##############################

    # initial values of the fit parameters
    # NB: we already estimated mean and sigma

    A = max(ybins_arr)
    print 'A =', A

    popt0 = [A, mean, sigma]

    try:
        # popt, pcov = curve_fit(fun, xbins_arr, ybins_arr, popt0)               # equal weights
        popt, pcov = curve_fit(fun, xbins_arr, ybins_arr, popt0, yerr_arr, True) # absolute_sigma = True
    except RuntimeError as e:
        # print "Minimization failed: {0}: {1}".format(e.errno, e.stderror)
        print '***Exception RuntimeError:', e
        print 'Terminated'
        plt.show()      # plot whatever we have
        return

    print 'popt:', popt
    print 'pcov:\n', pcov

    # Parameters' errors
    perr = np.sqrt(np.diag(pcov))

    print 'Result: A =', popt[0], '+-', perr[0], 'Mean =', popt[1], '+-', perr[1], 'Sigma =', popt[2], '+-', perr[2]

    #####################
    # plot the function #
    #####################

    xfun = np.linspace(xbins_arr[0], xbins_arr[-1], 100) # 100 points
    ax.plot(xfun, fun(xfun, *popt), 'r-')                # NB: *popt

    #
    # get subplot to use axis coordinate system
    #
    #----------------fig, ax = plt.subplots(1)
    
    text = "A =\t%0.1f$\pm$%0.3g\nMean =\t%0.3g$\pm$%0.3g\nSigma =\t%0.3g$\pm$%0.3g" \
                % (popt[0], perr[0], popt[1], perr[1], popt[2], perr[2])
    
    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)    # bbox properties

    #-- plt.text(0.05, 0.95, text, transform=ax.transAxes, fontsize=14, va='top', bbox=props)
    ax.text(0.05, 0.95, text, transform=ax.transAxes, fontsize=14, va='top', bbox=props)

    plt.show()
    
# gauss_distribution(20, 1000)
gauss_distribution(12, 100000)
