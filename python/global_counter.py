# https://www.python-course.eu/python3_class_and_instance_attributes.php
# modified by Andriy Zatserklyaniy <zatserkl@gmail.com> Aug 2, 2018

class C: 

    counter = 0

    def __init__(self): 
        type(self).counter += 1
        # print('__init__: type(self).counter =', type(self).counter)
        print('__init__: C.counter =', C.counter)  # less fancy

    def __del__(self):
        type(self).counter -= 1
        print('__del__: C.counter =', C.counter)

def main():
    x = C()
    # print("Number of instances: : " + str(C.counter))
    y = C()
    # print("Number of instances: : " + str(C.counter))
    del x
    # print("Number of instances: : " + str(C.counter))

    #############################################################
    #
    # I commented out the line 'del y' below, but
    # you will see the message from __del__ anyway
    # because the object will be deleted by the garbage collector
    #
    #############################################################

    print('\nafter explicit "del x"')
    print('"del y" is commented out\n')

    # del y
    # # print("Number of instances: : " + str(C.counter))

if __name__ == "__main__":

    main()
    print('\nafter main(), when its variables went out of scope')
