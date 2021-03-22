#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>


int N = 4000;
using namespace std;

string String() {
    auto randchar = []() -> char
    {
        const char charset[] = "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        random_device rd;
        return charset[ rd() % max_index ];
    };
    string str(5,0);
    generate_n( str.begin(), 5, randchar );
    return str;
}

void collision(vector <unsigned int> hashes)
{
            string File_ = "out2.dat";
    ofstream out(File_);

    if (!out.is_open()) {
        cerr << "Can not open: " << File_ << endl;
        exit(EXIT_FAILURE);
    }

    for (unsigned int k = 1; k < N; k++) {
        vector <unsigned int> dub;
        int count = 0;

        for (int i = 0; i < k - 1; i++) {
            bool fl = true;

            for (int j = 0; j < dub.size(); j++) {
                if (dub[j] == hashes[i]) {
                    fl = false;
                    break;
                }
            }

            if (fl == true) {
                dub.push_back(hashes[i]);

                for (int j = i + 1; j < k; j++) {
                    if (hashes[j] == hashes[i]) {
                        count++;
                    }
                }
            }
        }
        out<< k + 1 << "\t" << count << "\n";
    }

    out.close();
}

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a = a * b;
    }
    return hash%1000000;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash%1000000;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits =
        (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash%1000000;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash%1000000;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }
    return hash%1000000;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash%1000000;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash%1000000;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = length;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash%1000000;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash%1000000;
}


int main()
{
    vector <string> strings(N);
    for (auto j = 0; j < strings.size(); j++)
    {
        for (auto i = 0; i < 3; i++)
        {
            strings[j] = String();
        }
    }

    vector <unsigned int> hashes(N);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //   hashes[j] = RSHash(strings[j].c_str(), N);
    // }
    // collision(hashes);
    
    // for (auto j = 0; j < strings.size(); j++)
    // {
    //    hashes[j] = JSHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    for (size_t j = 0; j < strings.size(); j++)
    {
       hashes[j] = PJWHash(strings[j].c_str(), N);
    }
    collision(hashes);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //    hashes[j] = ELFHash(strings[j].c_str(), N);
    // }
    // collision(hashes);     

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //    hashes[j] = BKDRHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //    hashes[j] = SDBMHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //   hashes[j] = DJBHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //   hashes[j] = DEKHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    // for (size_t j = 0; j < strings.size(); j++)
    // {
    //     hashes[j] = APHash(strings[j].c_str(), N);
    // }
    // collision(hashes);

    return 0;
}