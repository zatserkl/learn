// Andriy Zatserklyaniy <zatserkl@ucsc.edu> Nov 9, 2016

/*
clang++ -Wall input.cpp
*/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using std::cout;    using std::endl;

/*
time, id1, id2, amount, message
2016-11-02 09:38:53, 49466, 6989, 23.74, 🦄 
2016-11-02 09:38:53, 52349, 8552, 37.10, Pitcher 
2016-11-02 09:38:53, 32639, 2562, 18.68, 🚕 
2016-11-02 09:38:53, 15381, 13167, 20.92, For your wife. 
*/

struct Payment {
    // record in the input
    char date[16];  // no fine tuning for now
    char time[16];
    int id1;
    int id2;
    double amount;
    // ignore the message
};

void input(const char* ifname="paymo_input/batch_payment.csv")
{
    std::ifstream ifile(ifname);
    if (!ifile) {
        cout<< "Could not find input file " << ifname <<endl;
        return;
    }

    // FYI: wc paymo_input/batch_payment.csv
    // 3938361 27825699 220149304 paymo_input/batch_payment.csv
    // wc paymo_input/stream_payment.csv 
    // 3000001 21206663 168199872 paymo_input/stream_payment.csv

    const int nlines_max = 8000000;     // practical limit

    std::string line;

    // read header
    std::getline(ifile, line);
    cout<< line <<endl;

    // process the first lines

    int nlines = 10;

    std::vector<Payment> vpayments(nlines_max);

    std::map<int, int> map_freq_id1;
    std::map<int, int> map_freq_id2;

    for (int iline=0; std::getline(ifile, line); ++iline) {
        //
        // simplifications because we process just one dataset provided
        // 1) assume the same format for all records
        // 2) no out-of-range check for vector
        //

        // if (iline > nlines) break;

        Payment& payment = vpayments.at(iline);     // reference to the current elements. By the product checks range. 

        sscanf(line.c_str(), "%s %s %d, %d, %lf", payment.date, payment.time, &payment.id1, &payment.id2, &payment.amount);
        if (iline < nlines) cout<< payment.date << " " << payment.time << " " << payment.id1 << ", " << payment.id2 << ", " << payment.amount <<endl;

        ++map_freq_id1[payment.id1];
        ++map_freq_id2[payment.id2];
    }

    cout<< "map_freq_id1.begin()->first = " << map_freq_id1.begin()->first <<endl;
    cout<< "map_freq_id1.rbegin()->first = " << map_freq_id1.rbegin()->first <<endl;
    cout<< "map_freq_id2.begin()->first = " << map_freq_id2.begin()->first <<endl;
    cout<< "map_freq_id2.rbegin()->first = " << map_freq_id2.rbegin()->first <<endl;
    cout<<endl;

    int nprint = 20;

    cout<< "id1 frequency" <<endl;
    std::map<int,int>::const_iterator itmax1 = map_freq_id1.begin();
    int max1 = itmax1->second;
    std::map<int,int>::const_iterator itmin1 = map_freq_id1.begin();
    int min1 = itmin1->second;
    for (std::map<int,int>::const_iterator it=map_freq_id1.begin(); it!=map_freq_id1.end(); ++it) {
        if (it->second > max1) {
            max1 = it->second;
            itmax1 = it;
        }
        if (it->second < min1) {
            min1 = it->second;
            itmin1 = it;
        }
        // if (std::distance<std::map<int,int>::const_iterator>(map_freq_id1.begin(), it) < nprint) cout<< it->first << "\t " << it->second <<endl;
        int icurr = std::distance<std::map<int,int>::const_iterator>(map_freq_id1.begin(), it);
        if (icurr < nprint) cout<< it->first << "\t " << it->second <<endl;
        if (icurr > 0 && icurr % 10000 == 0) cout<< "processing icurr = " << icurr <<endl;
    }

    cout<< "id2 frequency" <<endl;
    std::map<int,int>::const_iterator itmax2 = map_freq_id2.begin();
    int max2 = itmax2->second;
    std::map<int,int>::const_iterator itmin2 = map_freq_id2.begin();
    int min2 = itmin2->second;
    for (std::map<int,int>::const_iterator it=map_freq_id2.begin(); it!=map_freq_id2.end(); ++it) {
        if (it->second > max2) {
            max2 = it->second;
            itmax2 = it;
        }
        if (it->second < min2) {
            min2 = it->second;
            itmin2 = it;
        }
        // if (std::distance<std::map<int,int>::const_iterator>(map_freq_id2.begin(), it) < nprint) cout<< it->first << "\t " << it->second <<endl;
        int icurr = std::distance<std::map<int,int>::const_iterator>(map_freq_id2.begin(), it);
        if (icurr < nprint) cout<< it->first << "\t " << it->second <<endl;
        if (icurr > 0 && icurr % 10000 == 0) cout<< "processing icurr = " << icurr <<endl;
    }

    cout<< "map_freq_id1.size() = " << map_freq_id1.size() <<endl;
    cout<< "map_freq_id2.size() = " << map_freq_id2.size() <<endl;
    cout<< "id1 = " << itmax1->first << " paid in the maximum number of transactions " << itmax1->second <<endl;
    cout<< "id2 = " << itmax2->first << " received the maximum number of payments " << itmax2->second <<endl;
    cout<< "id1 = " << itmin1->first << " paid in the minimum number of transactions " << itmin1->second <<endl;
    cout<< "id2 = " << itmin2->first << " received the minimum number of payments " << itmin2->second <<endl;
}

int main() {
    input();
    return 0;
}

/*
graph-book$ clang++ -Wall input.cpp 
graph-book$ ./a.out 
time, id1, id2, amount, message
2016-11-02 09:38:53, 49466, 6989, 23.74
2016-11-02 09:38:53, 52349, 8552, 37.1
2016-11-02 09:38:53, 32639, 2562, 18.68
2016-11-02 09:38:53, 15381, 13167, 20.92
2016-11-02 09:38:53, 17052, 6289, 39.09
2016-11-02 09:38:53, 54008, 15138, 21.74
2016-11-02 09:38:53, 74050, 45140, 36.92
2016-11-02 09:38:53, 46702, 8034, 32.07
2016-11-02 09:38:53, 41480, 22688, 3.19
2016-11-02 09:38:53, 47846, 6067, 14.96
map_freq_id1.begin()->first = 0
map_freq_id1.rbegin()->first = 77359
map_freq_id2.begin()->first = 0
map_freq_id2.rbegin()->first = 77359

id1 frequency
0	 242
1	 230
2	 93
3	 160
4	 144
5	 44
6	 158
7	 60
8	 368
9	 35
10	 94
11	 79
12	 111
13	 134
14	 203
15	 626
16	 47
17	 215
18	 52
19	 145
processing icurr = 10000
processing icurr = 20000
processing icurr = 30000
processing icurr = 40000
processing icurr = 50000
processing icurr = 60000
processing icurr = 70000
id2 frequency
0	 1023
1	 459
2	 108
3	 323
4	 302
5	 15
6	 312
7	 84
8	 1104
9	 42
10	 163
11	 143
12	 290
13	 327
14	 821
15	 3098
16	 57
17	 577
18	 112
19	 305
processing icurr = 10000
processing icurr = 20000
processing icurr = 30000
processing icurr = 40000
processing icurr = 50000
processing icurr = 60000
processing icurr = 70000
map_freq_id1.size() = 77360
map_freq_id2.size() = 77360
id1 = 2481 paid in the maximum number of transactions 2576
id2 = 34 received the maximum number of payments 18480
id1 = 67213 paid in the minimum number of transactions 13
id2 = 28 received the minimum number of payments 1
graph-book$ 
*/
