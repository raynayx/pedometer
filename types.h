#pragma once



struct COEFFICIENTS
{
    float alpha[3];
    float beta[3];
};
struct axes
{
    float x; 
    float y; 
    float z;
};
struct axesArr
{ 
    axes arr[50];
};

struct parsedAxesArr
{
    axes uArr[50];
    axes gArr[50];
};

struct oneDArr
{
    float oneDArr[50];
};