#include <iostream>
#include <vector>

using std::cout;    using std::endl;

typedef int data_type;

// data_type binary_search(data_type element, const std::vector<data_type>& vec,
//                         int low, int high)
// {
//     // working but a bit complecated algorithm
//
//     if (element == vec[low]) return low;
//     if (element == vec[high]) return high;
// 
//     if (high == low + 1) return -1;
//     if (element < vec[low] && element > vec[high]) return -1;
// 
//     int mid = low + (high - low) / 2;     // mid always lower than high
//     if (element < vec[mid]) {
//         high = mid;
//     }
//     else {
//         low = mid;
//     }
//     return binary_search(element, vec, low, high);
// }

data_type binary_search(data_type element, const std::vector<data_type>& vec,
                        int low, int high)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;     // mid always lower than high
        if (element == vec[mid]) return mid;

        // We checked for mid.
        // If element is absent the expressions mid-1 and mid+1 in calls below
        // will make low > high

        if (element < vec[mid]) {
            return binary_search(element, vec, low, mid-1);     // NB: mid-1
        }
        else {
            return binary_search(element, vec, mid+1, high);    // NB: mid+1
        }
    }

    // if we are here, the element was not found
    cout<< "binary_search: element " << element << " was not found" 
        << " low = " << low << " high = " << high <<endl;
    return -1;
}

data_type binary_search(data_type element, const std::vector<data_type>& vec)
{
    int low = 0;
    int high = vec.size() - 1;
    return binary_search(element, vec, low, high);
}

void test(data_type element, const std::vector<data_type>& vec)
{
    int index = binary_search(element, vec);
    cout<< "index of " << element << " is " << index <<endl;
}

int main()
{
    std::vector<data_type> vec = {10, 11, 12, 20, 25, 30, 35, 40, 45};
    for (auto val: vec) {cout<< val << " ";}
    cout<<endl;

    // data_type element = vec[1];                  // ok: element w/ index 1
    // data_type element = vec[0];                  // ok: first element
    // data_type element = vec[vec.size() - 1];     // ok: last element
    // data_type element = 22;                      // ok: non-existing element

    test(vec[2], vec);
    test(vec[0], vec);
    test(vec[vec.size()-1], vec);
    test(1, vec);
    test(99, vec);
    test(22, vec);
}
