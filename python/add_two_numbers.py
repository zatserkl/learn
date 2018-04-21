import sys


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class LinkedList:
    """ Helper class for this problem.
    Just add_node and show.
    """
    def __init__(self, head):
        self.head = head

    def add_node(self, x):
        node = ListNode(x)
        node.next = self.head
        self.head = node

    @staticmethod   # static: added to this class just for convenience
    def show(head):
        node = head
        while node:
            print(node.val, end='')
            node = node.next
        print()

    @staticmethod   # static: does not depend on class variables
    def inverse(head):
        """ Returns inversed list.
        """
        # insert in the head
        head_out = None
        node = head
        while node:
            node_out = ListNode(node.val)   # create new node
            node_out.next = head_out
            head_out = node_out
            node = node.next
        return head_out


class Solution:
    def addTwoNumbers_submitted(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """

        head = None
        last = head     # last node in the linked list

        res = 0

        while l1 or l2:
            n1 = 0
            n2 = 0

            if l1:
                n1 = l1.val
            if l2:
                n2 = l2.val

            sum = n1 + n2 + res     # sum of two one-digit numbers

            mod = sum % 10
            res = 0
            if sum > 9:
                res = 1

            node = ListNode(mod)
            if head is None:
                head = node
            else:
                last.next = node
            last = node

            if l1:
                l1 = l1.next
            if l2:
                l2 = l2.next

        if res > 0:
            node = ListNode(res)
            if head is None:
                head = node
            else:
                last.next = node
            last = node             # don't need last anymore actually

        return head
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """

        head = None
        last = head     # last node in the linked list

        res = 0

        while l1 or l2:
            n1 = 0
            n2 = 0

            if l1:
                n1 = l1.val
            if l2:
                n2 = l2.val

            sum = n1 + n2 + res     # sum of two one-digit numbers

            mod = sum % 10
            res = 0
            if sum > 9:
                res = 1

            node = ListNode(mod)    # add this node to the tail
            if head is None:
                head = node
            else:
                last.next = node
            last = node

            if l1:
                l1 = l1.next
            if l2:
                l2 = l2.next

        if res > 0:
            node = ListNode(res)
            if head is None:
                head = node
            else:
                last.next = node
            last = node             # don't need last anymore actually

        return head


def store_number_old(n):
    """ Stores int number in linked list as ones-tens-hundreds
    """

    n_orig = n

    # store in list ones - tens - hundreds
    digit_list = [n % 10]   # needed for n = 0
    n = n // 10
    while n:
        res = n % 10
        digit_list.append(res)
        n = n // 10

    print("store_number:", n_orig, "in inverse order of digits =", digit_list)

    # convert to linked list hundreds-tens-ones
    head = None
    for digit in digit_list:
        node = ListNode(digit)
        node.next = head
        head = node

    return node


def store_number(n):
    """ Stores int number in linked list as ones-tens-hundreds
    """

    n_orig = n

    # store in list ones - tens - hundreds
    digit_list = [n % 10]   # needed for n = 0
    n = n // 10
    while n:
        res = n % 10
        digit_list.append(res)
        n //= 10

    print("store_number:", n_orig, "in inverse order of digits =", digit_list)

    # convert to linked list hundreds-tens-ones
    head = None
    for digit in reversed(digit_list):
        node = ListNode(digit)
        node.next = head
        head = node

    return node


def main(n1=342, n2=465):
    # # test store_number
    # number = 342
    # ltest = store_number(number)
    # print("representation of number (in inverse order)", number)
    # LinkedList.show(ltest)

    # put number 342 into l1 (in revese order)

    # l1 = None
    #
    # node = ListNode(3)  # hundreds
    # node.next = l1                    # done in constructor actually
    # l1 = node
    #
    # node = ListNode(4)  # tens
    # node.next = l1
    # l1 = node
    #
    # node = ListNode(2)  # ones
    # node.next = l1
    # l1 = node

    l1 = store_number(n1)

    # show content
    print("the 1st number", n1, "in linked list representation:")
    LinkedList.show(l1)

    print("create inverse list to l1")
    l1_inv = LinkedList.inverse(l1)
    print("inverse list")
    LinkedList.show(l1_inv)

    # put number 465 into l1 (in revese order)

    # node = ListNode(4)  # hundreds
    # l2 = node
    #
    # node = ListNode(6)  # tens
    # node.next = l2
    # l2 = node
    #
    # node = ListNode(5)  # ones
    # node.next = l2
    # l2 = node

    # n2 = 465
    l2 = store_number(n2)

    # show content
    print("the 2nd number", n2, "in linked list representation:")
    LinkedList.show(l2)

    solution = Solution()
    lsum = solution.addTwoNumbers(l1, l2)

    print("sum:")
    LinkedList.show(lsum)

    print("actual sum", n1, "+", n2, "=", n1 + n2)


if __name__ == "__main__":
    n1 = 342
    n2 = 465
    if len(sys.argv) > 2:
        n1 = int(sys.argv[1])
        n2 = int(sys.argv[2])
    main(n1, n2)
