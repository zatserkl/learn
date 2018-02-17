# import pandas
#-- from pandas import *            # to use DataFrame
from pandas import DataFrame

# conda install matplotlib
import matplotlib
#Enable inline plotting
#--AZ %matplotlib inline

def main():	
	baby_name = ['Alice','Charles','Diane','Edward']
	number_births = [96, 155, 66, 272]
	dataset = list(zip(baby_name,number_births))
	df = DataFrame(data = dataset, columns=['Name', 'Number'])
	# df['Number'].plot()
	df.plot('Name', 'Number', kind='bar')
        matplotlib.pyplot.show()        #--AZ to use the system python

if __name__ == "__main__":
    main()
