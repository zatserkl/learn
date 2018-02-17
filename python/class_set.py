class Set:
    """Implementation of set using list
    """
    def __init__(self, list_init=None):
        """constructor"""
        self.list = []
        if list_init is not None:
            for element in list_init:
                self.list.append(element)

"""From http://stackoverflow.com/questions/1436703/difference-between-str-and-repr-in-python

So, my advice: focus on making __str__ reasonably human-readable, 
and __repr__ as unambiguous as you possibly can, 
even if that interferes with the fuzzy unattainable goal of making __repr__'s 
returned value acceptable as input to __eval__!
"""

    def __repr__(self):
        """string representation of the Set object
        It will be printed in IPython if you type object name followed by <CR>
        """
        return str(self.list)

    def __str__(self):
        """string representation of the Set object
        It will be printed in IPython if you type object name followed by <CR>
        """
        return 'list: ' + str(self.list)

    def contains(self, element):
        return element in self.list

    def add(self, element):
        if element not in self.list:
            self.list.append(element)

    def remove(self, element):
        if element in self.list:
            self.list.remove(element)
