import matplotlib.pyplot as plt
from collections import Counter

class Histo:
    debug = False
    counter = 0
    __privateGlobalNumber = 0   # can be accessed outside: Histo.__Histo__privateGlobalNumber, inside: self.__privateGlobalNumber

    def __init__(self, data, title):
        # NB: self.title available only after definition
        Histo.__privateGlobalNumber += 1
        Histo.counter += 1
        self.data = data
        self.title = title
        print 'Histo constructor for', self.title
        # print 'Histo.__privateGlobalNumber =', Histo.__privateGlobalNumber, 'is NOT the same as Histo._Histo__privateGlobalNumber =', Histo._Histo__privateGlobalNumber
        print 'Histo.__privateGlobalNumber =', Histo.__privateGlobalNumber

    def __del__(self):
        print 'Histo destructor for', self.title
        if Histo:
            Histo.__privateGlobalNumber -= 1
            Histo.counter -= 1
            # Histo._Histo__privateGlobalNumber -= 1    # access in this way will cause Exception AttributeError: "'NoneType' object has no attribute '_Histo__privateGlobalNumber'" in ...

    def prepare(self,nbins):
        """Creates a histogram
        """
        self.nbins = nbins
        self.__privateLocalNumber = nbins   # can be accessed from the instance histo as histo._Histo__privateLocalNumber

        data_min = min(self.data)
        data_max = max(self.data)
        if self.debug: print 'min =', data_min, 'max =', data_max
        range = data_max - data_min
        width = (data_max - data_min) / self.nbins
        if self.debug: print 'width =', width

        # for point in self.data:
        #     print point / width

        decile = lambda data_point, data_min, width: data_min + int((data_point-data_min)/width)*width
        # decile = lambda data_point, data_min, width: data_min + (data_point-data_min)/width*width    # funny w/o int for float self.data

        # if self.debug:
        #     print '\nprint val'
        #     for bin,point in enumerate(self.data):
        #         val = decile(point,data_min,width)
        #         print bin,val

        histogram = Counter(decile(point,data_min,width) for point in self.data)  # histogram is a dictionary

        ymin = min(histogram.values())
        if ymin > 0: ymin = 0                # for empty bins
        ymax = max(histogram.values())
        ymax += 0.10*(ymax - ymin)
        # if self.debug: print 'ymin =', ymin, 'ymax =', ymax

        # if self.debug:
        #     print '\nprint histogram'
        #     for tuple in histogram.items():      # tuple is a tuple in the dictionary histogram
        #         key,value = tuple
        #         print key, value

        # bin_width = int(0.80*width)       # separate bars
        bin_width = width                   # ROOT-like histogram without separations between the bars (a black line separates the bars)
        # if self.debug: print 'bin_width =', bin_width

        #
        #   the histogram
        #
        # plt.bar([x-bin_width/2 for x in histogram.keys()], histogram.values(), bin_width)     # if you'd like to shift the bars
        plt.bar(histogram.keys(), histogram.values(), bin_width)
        xmin = data_min
        xmax = data_max + bin_width
        plt.axis([xmin,xmax, ymin,ymax])
        # plt.show()

    def plot(self):
        plt.show()
        plt.title(self.title)

if __name__ == "__main__":

    # grades = [83,95,91,87,70,0,85,82,100,67,73,77,0]
    grades = [83.,95.,91.,87.,70.,0.,85.,82.,100.,67.,73.,77.,0.]       # float to test float data features
    
    #
    # This stuff works fine
    #
    # histo = Histo(grades,'10 bins histo')
    # histo.prepare(10)
    # histo.plot()
    # 
    # histo.prepare(8,'8 bins histo')
    # histo.plot()
    # 
    # histo.prepare(4,'4 bins histo')
    # histo.plot()
    
    #
    #   Add attribute
    #
    
    print '\nTurn Histo.debug = True for the first histogram created\n'
    Histo.debug = True
    
    histo10 = Histo(grades, 'histo for 10 bins')
    histo10.prepare(10)
    # histo10.remark = '10 bins'             # add a new attribute directly
    setattr(histo10, 'remark', '10 bins')    # add a new attribute with setattr
    
    print '\nhisto10._Histo__privateLocalNumber =', histo10._Histo__privateLocalNumber
    print '--> after histo10: Histo.counter =', Histo.counter
    
    # print '\nTurn Histo.debug = False for the rest of histograms\n'
    # Histo.debug = False
    
    histo8 = Histo(grades, 'histo for 8 bins')
    histo8.prepare(10)
    histo8.remark = '8 bins'                 # add a new attribute directly
    # setattr(histo8, 'remark', '8 bins')    # add a new attribute with setattr
    print '--> after histo8: Histo.counter =', Histo.counter
    
    histo4 = Histo(grades, 'histo for 4 bins')
    histo4.prepare(4)
    print '--> after histo4: Histo.counter =', Histo.counter
    
    print 'histo4._Histo__privateGlobalNumber =', histo4._Histo__privateGlobalNumber
    
    print '\nbefore creation of histogram list: Histo._Histo__privateGlobalNumber =', Histo._Histo__privateGlobalNumber
    
    histos = [histo10, histo8, histo4]
    
    print 'after creation of histogram list: Histo._Histo__privateGlobalNumber =', Histo._Histo__privateGlobalNumber
    
    print '\nattribute remark'
    for h in histos:
        # print getattr(h, 'remark')         # get the new attribute with getattr
        # print h.remark                       # get the new attribute directly
        if hasattr(h, 'remark'): print h.title, 'has a remark', h.remark
        else: print h.title, 'does not have an attribute remark'
    
    print '\ndelete histo8'
    histo8.__del__()
    
    print '\nlook at the second element of the array histos'
    print 'histos[1].title =', histos[1].title
    
    print '\nBye: going out of scope of main'
