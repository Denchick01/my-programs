#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

void Test ();
void EnterParam (double par[]);
void OutResult (int nRoots, double x1, double x2);
int CheckParam (double a, double b, double c, double d);
int SqEquation (double a, double b, double c, double* x1, double* x2);
bool IsZero (double z);

//!@const SQEQ_INF is infinity
//!@const EPSILON is error of computing the type of double
const int SQEQ_INF = -1;
const double EPSILON = 2e-5;

int main ()
{
    while (true)
    {
        Test ();

        //double par[2], x1 = 0, x2 = 0;
        //EnterParam (par);

        //int nRoots = SqEquation (par[0], par[1], par[2], &x1, &x2);
        //OutResult (nRoots, x1, x2);
    }
}

//! @function SqEquation
//! Calculation of the discriminant
//! @param a a - coefficient
//! @param b b - coefficient
//! @param c c - coefficient
//! @param d d - discriminant
//! @return returns the number of roots
int SqEquation (double a, double b, double c, double* x1, double* x2)
{
    assert (x1 != NULL); assert (x2 != NULL);
    assert (x1 != x2);

    double d = (b * b - 4 * a * c);
    *x1 = (- b - sqrt (d)) / 2 / a;
    *x2 = (- b + sqrt (d)) / 2 / a;

    return CheckParam (a,b,c,d);
}

//! @function IsZero
//! Check  coefficient is zero or not
//! @param one of coefficients
//! @return true if coefficient is zero or false if coefficient is not zero
bool IsZero (double par)
{
    return fabs (par) < EPSILON;
}

//! @function CheckParam
//! Determines the number of roots
//! @param a a - coefficient
//! @param b b - coefficient
//! @param c c - coefficient
//! @param d d - discriminant
//! @return returns the number of roots
int CheckParam (double a, double b, double c, double d)
{
    if (IsZero (a))
        return SQEQ_INF;

    else if (d < 0)
        return 0;

    else if (IsZero (b) && IsZero (c))
        return 1;

    else
        return 2;
}

//! @function OutResult
//! Outputs the result
//! @param nRoots nRoots - number of roots
//! @param x1 x1 - variable
//! @param x2 x2 - variable
void OutResult (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case SQEQ_INF:
            printf ("the number of real roots = 0, incorrect variable a\n");
            break;

        case 0:
            printf ("the number of real roots = 0, imaginary roots\n");
            break;

        case 1:
            printf ("the number of real roots = 1\n x = %lg\n", x2);
            break;

        case 2:
            printf ("the number of real roots = 2\n x1 = %lg ; x2 = %lg\n", x1, x2);
            break;
    }
}

//! @function EnterParam
//! Reads a stream of input data
//! @param par[] par[] - array of coefficients
void EnterParam (double par[])
{
    char npar[] = "abc";
    int i=0;

    while (i <= 2)
    {
        printf ("Please enter coefficient %c = ", npar[i]);
        scanf ("%lg", &par[i++]);
    }
}


//! @function Test
void Test ()
{
    double x1 = 0;
    double x2 = 0;
    double arga[5] = {0,1,1,4.6,2.3};
    double argb[5] = {1,4.5,3,0,5};
    double argc[5] = {2,2,7.7,0,2};
    for (int i=0; i <= 4; i++)
    {
        printf ("a = %2.1f b = %2.1f c = %2.1f  ",arga[i], argb[i], argc[i]);
        int nRoots = SqEquation (arga[i], argb[i], argc[i], &x1, &x2);
        OutResult (nRoots, x1, x2);
    }
    system("PAUSE");
}

