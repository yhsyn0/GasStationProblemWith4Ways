#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h> 

#define INF INT_MAX

using namespace std;
using namespace std::chrono;


//double mList[] = {35, 74, 75, 98, 126, 148, 165, 196, 212, 251, 287};
//double pList[] = {50, 1.4, 100, 68, 47, 75, 56, 21, 40, 55, 36};
//double mList[] = {26, 74, 100, 134, 160};
//double pList[] = {20, 21, 35, 42, 55};
//double mList[]={0.0, 29.5, 56, 114.5, 167, 227.5, 249, 281.8, 335, 372.4, 396, 451.6}; 
//double pList[]={0.0, 16.1, 17.8, 13.4, 18.7, 11.4, 18.8, 14.3, 6.6, 10.7, 12.4, 12.8};

//double mList[100] = {22,32,67,122,181,189,202,204,220,270,275,301,308,322,344,425,434,477,478,495,500,559,578,588,594,595,604,613,616,662,667,688,700,705,753,758,773,796,812,824,829,840,846,857,887,935,979,1019,1033,1042,1044,1153,1171,1177,1181,1222,1232,1259,1261,1301,1306,1307,1316,1321,1340,1347,1352,1362,1391,1394,1403,1413,1464,1535,1539,1587,1618,1631,1656,1673,1690,1700,1709,1774,1777,1782,1784,1793,1794,1818,1845,1857,1862,1873,1875,1878,1893,1916,1931,1969};
//double pList[100] = {23,54,197,55,199,186,98,152,160,107,118,83,11,144,51,90,174,114,129,5,104,173,155,157,140,148,156,74,136,142,109,20,126,56,172,100,38,115,149,125,137,71,34,151,46,66,9,93,57,139,2,179,29,123,181,63,77,95,43,159,188,89,21,48,130,91,76,52,108,146,105,135,8,32,96,15,68,84,120,61,81,171,191,39,133,82,47,127,79,143,198,169,94,138,165,166,27,78,80,31};
// 100'lük için k 50, f 200, ending 200

//double mList[50] = {19,26,30,58,93,94,138,145,150,153,205,213,227,256,257,264,287,293,312,316,339,372,393,423,438,461,532,553,555,556,563,584,616,621,631,638,659,674,689,692,706,729,734,735,739,788,812,871,894,965};
//double pList[50] = {93,37,100,84,30,14,37,69,80,28,74,17,90,73,26,40,30,68,39,16,11,10,64,47,17,48,87,31,94,93,22,8,42,65,47,93,70,73,69,51,62,10,84,78,97,22,92,74,52,100};
// 50'lik için k 50, f 100, ending 1000

double mList[25] = {19,26,30,58,93,94,138,145,150,153,205,213,227,256,257,264,287,293,312,316,339,372,393,423,461};
double pList[25] = {93,37,100,84,30,14,37,69,80,28,74,17,90,73,26,40,30,68,39,16,11,10,64,47,17};
// 25'lik için k 25, f 75, ending 500

//double mList[] = {0.0, 5.0, 9.0, 13.0, 16.0, 20.0, 22.0, 26.0};
//double pList[] = {0.0, 1.0, 2.0, 3.0, 1.0, 2.0, 1.0, 3.0};
//double mList[] = {0.0 ,40.0, 74.0, 100.0, 134.0, 160.0};
//double pList[] = {0.0 ,20.0, 80.0, 35.0, 42.0, 55.0};
int length = sizeof(mList) / sizeof(*mList);
double k = 25.0; // Not bu kısım diziye uygun olarak her değiştirmede güncellenmesi gerekir.
double f = 75.0;
double ending = 500.0;



void combinationUtil(double arr[], double data[],  
                    int start, int end,  
                    int index, int r, vector < vector < int > >&stations);

void allCombs(double arr[], int n, int r, vector < vector < int > > &stations);

void bf()
{
    double pMin = INT_MAX;// Sonradan dönüşeceği için böyle bıraktım.

    vector < vector < int > > all;
    vector < double > prices;

    for(int r = 0; r <= length; r++)
        allCombs(mList, length, r, all);

    for(unsigned int i = 0; i < all.size() - 1; i++)
    {
        double price = 0.0;

        for(unsigned int j = 0; j < all[i].size(); j++)
        {
            price += pList[all[i][j]];
        }
        prices.push_back(price);
    }

    int iob = -1;

    for(unsigned int i = 0; i < all.size() - 1; i++)
    {
        int control = 0;

        if((mList[all[i][all[i].size() - 1]] + f) >= ending && mList[all[i][0]] >= k && mList[all[i][0]] <= f)
        {
            for(int j = all[i].size() - 1; j > 0; j--)
            {
                if(mList[all[i][j]] - mList[all[i][j-1]] > f || mList[all[i][j]] - mList[all[i][j-1]] < k)
                    control = 1;
            }

            if(control != 1 && prices[i] < pMin)
            {
                iob = i;
                pMin = prices[i];
            }
        }
    }

    if(iob == -1)
    {
        cout << "Verilen kısıta uygun olan bir rota bulunamamıştır." << endl;
        exit(-1);
    }

    cout << "Durulan İstasyonlar ve Benzin Maliyetleri" << endl;

    for(unsigned i = 0; i < all[iob].size(); i++)
    {
        cout << all[iob][i] << " " << pList[all[iob][i]] << endl;
    }

    cout <<  "Toplam Maliyet : " << pMin << endl;
}



void greedy()
{
    double price = 0;

    vector <int> stations;
    vector <double> prices;
    int currStation = -1;
    double km = 0.0;

    while(km+f < ending)
    {  
        double temp = -1.0;

        for(int i = currStation + 1; i < length; i++)
        {   
            if(temp == -1 && mList[i] <= km+f && mList[i] >= km+k)
            {
                currStation = i;
                temp = (mList[i]-km)/pList[i];
            }

            else if(temp != -1 && mList[i] <= km+f && mList[i] >= km+k && 
                ((mList[i] - km)/pList[i]) > temp)
            {
                currStation = i;
                temp = pList[i];
            }
            
            if(mList[i] > km+f)
                break;
        }

        if(currStation == -1 || mList[currStation] < km+k)
        {
            cout << "Verilen kısıta uygun olarak yeni istasyona gidilememiştir." << endl;
            exit(-1);
        }

        stations.push_back(currStation);
        prices.push_back(pList[currStation]);
        price += pList[currStation];
        km = mList[currStation];
    } 
    
    cout << "Durulan İstasyonlar ve Benzin Maliyetleri" << endl;

    for(unsigned i = 0; i < stations.size(); i++)
    {
        cout << stations[i] << " " << prices[i] << " " << endl;
    }

    cout << "Toplam Maliyet : " << price << endl;
}



void subDC(int currStation, vector <int> &stations, vector <double> &prices);

void dc() // Decrease&Conquer
{
    vector <int> stations;
    vector <double> prices;
    double price = 0;

    subDC(-1, stations, prices);

    cout << "Durulan İstasyonlar ve Benzin Maliyetleri" << endl;

    for(unsigned i = 0; i < stations.size(); i++)
    {
        cout << stations[i] << " " << prices[i] << " " << endl;
        price += prices[i];
    }

    cout << "Toplam Maliyet : " << price << endl;
}

void findPaths(vector <int> &source, vector <int> &dest, 
                vector < vector < int > > &stations, 
                vector <int> &temp, int index);

void dp()
{
    vector <int> source;
    vector <int> dest;

    double arr[length+1][length+1];
    fill_n(&arr[0][0], sizeof(arr)/sizeof(**arr), 0);

    for(int i = 0; i < length+1; i++)
    {
        for(int j = i+1; j < length+1; j++)
        {
            if(mList[j] - mList[i] <= f && mList[j] - mList[i] >= k)
            {   
                arr[j][i] = pList[j];
                source.push_back(i);
                dest.push_back(j);
            }
        }
    }
  
    vector < vector < int > > stations;
    
    for(unsigned i = 0; i < source.size(); i++)
    {
        vector <int> temp;
        if(mList[source[i]] - f <= 0)
        {
            temp.push_back(source[i]);
            temp.push_back(dest[i]);

            findPaths(source, dest, stations, temp, i);
        }
    }

    double minPrice = INT_MAX;
    int minIndex = -1;

    for(unsigned i = 0; i < stations.size(); i++)
    {   
        double temp = pList[stations[i][0]];
        int control = 0;

        if(mList[stations[i][0]] < k)
            control = 1;

        for(unsigned j = stations[i].size() - 1; j > 0; j--)
        {
            if(mList[stations[i][j]] - mList[stations[i][j-1]] < k)
                control = 1;
            temp += pList[stations[i][j]];
        }

        if(control != 1 && temp < minPrice)
        {
            minPrice = temp;
            minIndex = i;
        }
    }
 
    cout << "Durulan İstasyonlar ve Benzin Maliyetleri" << endl;

    for(unsigned i = 0; i < stations[minIndex].size(); i++)
        cout << stations[minIndex][i] << " " << pList[stations[minIndex][i]] << endl;

    cout << "Toplam Maliyet : " << minPrice << endl;
}


int main()
{ /*
    auto start0 = high_resolution_clock::now();
    bf();
    auto stop0 = high_resolution_clock::now();
    auto duration0 = duration_cast<microseconds>(stop0 - start0);
    cout << "Brute Force : " << duration0.count() << " microsecond " << endl << endl;

    auto start1 = high_resolution_clock::now();
    greedy();
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout << "Greedy : " << duration1.count() << " microsecond " << endl << endl;

    auto start2 = high_resolution_clock::now();
    dc();
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout << "Decrease&Conquer : " << duration2.count() << " microsecond " << endl << endl;*/

    auto start3 = high_resolution_clock::now();
    dp();
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout << "Dynamic Programming : " << duration3.count() << " microsecond " << endl << endl;

    return 0;
}


// https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
// Aşağıdaki kombinasyon bulma ile ilgili kodları yukarıda belirtilen linkteki adresten aldım ve kendime göre uyarladım.
// _____________________________________________________________________________________________________________________

void combinationUtil(double arr[], double data[],  
                    int start, int end,  
                    int index, int r, vector < vector < int> >&stations)  
{  
    if (index == r)  
    {  
        for (int j = 0; j < r; j++) 
            stations[stations.size() - 1].push_back(data[j]);
           
        stations.push_back(vector <int>());

        return;  
    }  
  
    for (int i = start; i <= end &&  
        end - i + 1 >= r - index; i++)  
    {  
        data[index] = i;  
        combinationUtil(arr, data, i+1,  
                        end, index+1, r, stations);  
    }  
}
  
void allCombs(double arr[], int n, int r, vector < vector < int > > &stations)  
{  
    double data[r];  

    combinationUtil(arr, data, 0, n-1, 0, r, stations);  
}
// _____________________________________________________________________________________________________________________

void subDC(int currStation, vector <int> &stations, vector <double> &prices)
{
    double km;
    int newIndex = -1;
    if(currStation == -1)
        km = 0;
    else
        km = mList[currStation];

    if(km+f < ending)
    {
        double temp = -1.0;

        for(int i = currStation + 1; i < length; i++)
        {
            if(temp == -1 && mList[i] <= km+f && mList[i] >= km+k)
            {
                newIndex = i;
                temp = (mList[i]-km)/pList[i];
            }

            else if(temp != -1 && mList[i] <= km+f && mList[i] >= km+k && 
                ((mList[i]-km)/pList[i]) > temp)
            {
                newIndex = i;
                temp = pList[i];
            }
            
            if(mList[i] > km+f)
                break;
        }

        if(newIndex == -1 || mList[newIndex] < km+k)
        {
            cout << "Verilen kısıta uygun olarak yeni istasyona gidilememiştir." << endl;
            exit(-1);
        }

        stations.push_back(newIndex);
        prices.push_back(pList[newIndex]);

        subDC(newIndex, stations, prices);
    }

    else
        return;   
}

void findPaths(vector <int> &source, vector <int> &dest, 
                vector < vector < int > > &stations, vector <int> &temp, int index)
{
    if(mList[temp[temp.size()-1]] + f >= ending)
    {
        stations.push_back(temp);
        return;
    }

    vector <int> vec;
    vec.insert(vec.end(), temp.begin(), temp.end());

    if(vec[vec.size()-1] != dest[index])
        vec.push_back(dest[index]);

    for(unsigned i = index; i < source.size(); i++)
    {
        if(temp[temp.size() - 1] == source[i])
        {
            findPaths(source, dest, stations, vec, i);
        }
    }
}