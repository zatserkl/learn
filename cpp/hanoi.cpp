#include <iostream>
#include <cstdarg>
#include <stack>

using std::cout;      using std::endl;

// inline std::ostream& operator <<(std::ostream& os, const std::stack<int>& stack) {
//     // prints stack in reverse order
//     for (std::stack<int> copy=stack; copy.size(); copy.pop()) os << " " << copy.top();
//     return os;
// }

inline std::ostream& operator <<(std::ostream& os, const std::stack<int>& stack)
{
    // prints stack in direct order

    std::stack<int> copy = stack;       // create a copy of the const stack
    std::stack<int> reverse;

    while (copy.size()) {
        reverse.push(copy.top());
        copy.pop();
    }
    while (reverse.size()) {
        os << reverse.top();
        reverse.pop();
        if (reverse.size()) os << " ";
    }
    return os;
}

class HanoiTower {
friend std::ostream& operator<<(std::ostream&, const std::stack<int>&);
public:
    std::stack<int> tower1;
    std::stack<int> tower2;
    std::stack<int> tower3;
public:
    HanoiTower(int n=4) {
        for (int i=n; i>0; --i) tower1.push(i);
    }
    void MoveDisk(std::stack<int>& from, std::stack<int>& to)
    {
        // this function makes actual changes to the towers
        to.push(from.top());
        from.pop();
        Show();                         // show changes
    }
    void MoveTower(int n, std::stack<int>& from, std::stack<int>& to, std::stack<int>& buf)
    {
        cout<< "--" << n << "--" <<endl;
        if (n == 0) return;

        // if (n == 1) {
        //     // this is nothing but just optimization: save function call
        //     MoveDisk(from, to);      // make actual changes to the towers
        //     return;
        // }

        MoveTower(n-1, from, buf, to);
        MoveDisk(from, to);             // make actual changes to the towers
        MoveTower(n-1, buf, to, from);
    }
    void MoveTower() {
        MoveTower(tower1.size(), tower1, tower3, tower2);
    }
    void Show() const {
        cout<< "tower1:\t" << tower1 <<endl;
        cout<< "tower2:\t" << tower2 <<endl;
        cout<< "tower3:\t" << tower3 <<endl;
        cout<< "------------------" <<endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc == 1) {
        cout<< "Usage:\n" << argv[0] << " n" <<endl;
        return 0;
    }

    int n = atoi(argv[1]);

    HanoiTower hanoi(n);
    cout<< "-- Initial:" <<endl;
    hanoi.Show();
    cout<<endl;

    hanoi.MoveTower();

    cout<< "\n--- Final:" <<endl;
    hanoi.Show();

    return 0;
}
