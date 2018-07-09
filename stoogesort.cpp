/*
File: stoogesort.cpp
Description: This function takes an array/vector of integers, then sorts it
Name: Calista Wong
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


/* Code reference: https://www.sanfoundry.com/cplusplus-program-perform-stooge-sort/ */

void StoogeSort(int array[],int start, int end)
{
        if(end-start+1 > 2) //array's length is more than 2, so break it apart
        {
                int m = (end-start+1)/3; //represents the 1/3 mark point
                StoogeSort(array, start, end-m); //StoogeSort(A[0 ... m - 1])
                StoogeSort(array, start+m, end); //StoogeSort(A[n - m ... n - 1])
                StoogeSort(array, start, end-m); //Stoogesort(A[0 ... m - 1])

        }

        //check if need to swap
        if(array[end] < array[start])
        {
                int temp = array[start];
                array[start] = array[end];
                array[end] = temp;
        }
}


int main()
{
        ifstream infile;
        infile.open("data.txt");
        if (!infile)
                {
                        cout << "File not found." << endl;
                }
        //count how many lines and the highest number of elements
        string str;
        int numLine = 0;
        int highest = 0;
        while (getline(infile, str))
                        {
                                numLine++;

                                //determine highest number of integers
                                //store as string vector
                                vector<string> result;
                                istringstream iss(str);
                                for(string s; iss >> s;)
                                        result.push_back(s);
                                if (result.size() > highest)
                                        highest = result.size();
                        }

        //create 2D array based on number of lines and the highest number of elements
        int myArray [numLine][highest];
        //create another 2D array of bools
        bool boolArray [numLine][highest];

        //initialize boolArray with false
        for (int i=0; i<numLine; i++)
        {
                for (int j=0; j<highest; j++)
                {
                        boolArray[i][j] = false;
                }
        }
 	//rewind the file
        infile.clear(); //rewind file
        infile.seekg(0);

        vector <string> result;
        int line=0; //keeps track of which line

        ofstream outfile;
        outfile.open("stooge.out");

        while (getline(infile, str)) //find how many characters a line
        {
                //store as string vector
                vector<string> result;
                istringstream iss(str);
                for(string s; iss >> s;)
                        result.push_back(s);

                //dynamic array for number of vector elements
                int*temp = new int[result.size()];

                //convert string into integer and store in array
                for (int i=0; i<result.size(); i++)
                {
                        //convert string into integer
                        string myString = result[i];
                        stringstream geek(myString);
                        int x = 0;
                        geek >> x;

                        //store into array
                        temp[i] = x;
                }

                cout << "before sort: " << endl;
                for (int i=0; i<result.size(); i++)
                {
                        cout << temp[i] << " ";
                }

                int first = temp[0];
                //cout << "The first element: " << first << endl;

                cout << endl;
                //send to be sorted
                StoogeSort(temp, 0, result.size()-1);

                cout << "after sort: " << endl;
                for (int i=0; i<result.size(); i++)
                {
                        cout << temp[i] << " " ;
                }
                cout << endl;
                cout << endl;

                //only store the first x elements
                for (int i=0; i<first; i++)
                {
                        myArray[line][i] = temp[i];
                        boolArray[line][i] = true;
                }
                line++;

                //delete memory of dynamic array
                delete []temp;
               temp = NULL;
        }
 	//write to file
        for (int i=0; i<numLine; i++)
        {
                for (int j=0; j<highest; j++)
                {
                        if (boolArray[i][j] == true)
                                {
                                        outfile << myArray[i][j] << " ";
                                }
                }
                outfile << endl;
        }

        //close files
        outfile.close();
        infile.close();

        return 0;
}
