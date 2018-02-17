# http://pymbook.readthedocs.io/en/latest/testing.html

import unittest
from factorial import fact, div

class TestFactorial(unittest.TestCase):
    """
    Our basic test class
    """

    def test_fact(self):
        """
        The actual test.
        Any method which starts with ``test_`` will considered as a test case.
        """
        res = fact(5)
        self.assertEqual(res, 120)      # test will be OK
        # self.assertEqual(res, 121)      # test will fail

    def test_error(self):
        """
        To test exception raise due to run time error
        """
        self.assertRaises(ZeroDivisionError, div, 0)

if __name__ == '__main__':
    unittest.main()
