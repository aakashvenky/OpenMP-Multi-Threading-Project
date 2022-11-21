/*
Author: Aakash Venkataraman
Class :  ECE6122 - A
Last Date Modified: 10-10-2022
Description:
Code takes file path of the file which contains matrix as input and outputs their prodcut in MatrixOut.txt
*/

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;
int main(int argc,char** argv)
{
if(argc<2 || argc >3)
{
// If command line arguments is less than 2, then file path is not mentioned.
fstream fprint;
fprint.open("MatrixOut.txt",ios::out);
cout<<"Invalid or Insufficient number of arguments";
fprint.close();
return 0;
}
if(argc == 2)
{
//When file path is mentioned, the matrix multiplication is done for the matrix present in the file located in mentioned location
double row, col,row1,col1;
string r, c , c1 , r1 , temp , temp1;
fstream fout; // fout file contains the matrix A and B and their sizes
fstream fprint; // fprint is used to print the product of matrixes.
fout.open(argv[1],ios::in);
fout>>r>>c;
row = stod(r);
col = stod(c);
int i, j , k;
vector<vector<double>>A;
A.resize(row, vector<double>(col));
for(int i = 0; i< row;i++)
{
for(int j = 0 ; j< col; j++)
{
  fout>>temp;
  A[i][j] = stod(temp);  
}
}
fout>>r1>>c1;
row1 = stod(r1);
col1 = stod(c1);
vector<vector<double>>B;
B.resize(row1, vector<double>(col1));
for(int i=0; i< row1; i++)
{ for(int j = 0 ; j < col1; j++)
{
  fout>>temp1;
  B[i][j] = stod(temp1);
}
}
vector<vector<double>> C;
C.resize(row,vector<double>(col1));
#pragma omp parallel for private(i,j,k) shared (A,B,C)
for (int i = 0 ; i < int(row);i++)
{ for(int j=0; j< int(col1);j++)
{  for(int k=0; k< int(col);k++)
 {  
    C[i][j] += A[i][k]*B[k][j]; 
 } 
}
}
fprint.open("MatrixOut.txt",ios::out);
fprint<<row<< " "<<col1<<endl;
for(int i = 0; i< row; i++)
{ for(int j=0; j<col1;j++)
{
fprint<<std::scientific;
fprint<< C[i][j] << " ";
}
fprint<<endl;
}
}
return 0;
}


