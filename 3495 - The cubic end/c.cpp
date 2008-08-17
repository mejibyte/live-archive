
//Robado de http://www.acmgnyr.org/year2005/problems.shtml

/*
 * 2005 ACM Greater New York Regional Collegiate Programming Contest
 * Problem C -- Cubic End
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * FindCubeRoot below, the core of the whole thing works as follows:
 * to start, we use the facts that 1^3 = 1, 3^3 = 27, 7^3 = 343
 * and 9^3 = 729 to choose the appropriate least significant digit c0
 * then
 * assuming result c has digits up to 10^(k-1) so c^3 matches the
 * desired value up to k-1 digit, consider (c + d*10^k)^3 with 0<= d <= 9
 * = c^3 + 3*(c^2)*d*10^k + 3*c*(d^2)*10^(2k) + (d^3)*10^(3k)
 * the only terms that can affect digit k of the cube are the k-th
 * digit of c^3 (= y) and 3*(c^2)*d (mod 10) = 3*c0*c0*d (mod 10)
 * where c0 is the least significant digit of c
 * if Dk is the desired kth digit, we need Dk = y + 3*c0*c0*d (mod 10)
 * so d = (Dk - y)/(3*c0*c0) (mod 10)
 * since 3 and c0 are relatively prime to 10, we can solve this
 * (3*1*1) * 7 = 21 = 1 (mod 10)
 * (3*3*3) * 3 = 81 = 1 (mod 10)
 * (3*7*7) * 3 = 441 = 1 (mod 10)
 * (3*9*9) * 7 = 1701 = 1 (mod 10)
 * gives reciprocals (mod 10)
 */

#define MAX_DIGITS      10
char desired[MAX_DIGITS];
char result[MAX_DIGITS];
char resCubed[MAX_DIGITS];
char resSquared[MAX_DIGITS];

char inbuf[256];

// multiply nDig1 decimal digits of pFact1 by nDig2 decimal digits
// of pFact2 into decimal digits of pRes, return number of digits in pRes
// up to MAX_DIGITS
// if val = carry_from_prev_digit + SUM[i=0..k](pFact1[i] * pFact2[k-i])
// result digit k = val % 10 and carry to next digit = val/10
// once k is > min(nDig1, nDig2) pFact1[i] or [Fact2[k-i] may be off the
// end of the number (and thus 0)
int
MulDecimal(char *pFact1, char *pFact2, char *pRes, int nDig1, int nDig2)
{
        int sum, carry, digit, start, end, i;
        carry = 0;
        for(digit = 0; digit < MAX_DIGITS ; digit++)
        {
                // want sum 0 .. digit(fact1[i] * fact2[digit -i])
                // but need to limit if we run out of digits
                sum = carry;    // from previous digit
                start = 0;
                if(digit > nDig2)
                {       // if i < start, pFact2[k-i] is off the end (= 0)
                        start = digit - nDig2;
                }
                end = digit;
                if(digit > nDig1)
                {       // if i > end, pFact1[i] is off the end (= 0)
                        end = nDig1;
                }
                for(i = start; i <= end ; i++)
                {
                        sum += pFact1[i] * pFact2[digit - i];
                }
                pRes[digit] = sum % 10;
                carry = sum /10;
        }
        for(i = MAX_DIGITS - 1; i >= 0 ; i--)
        {
                if(pRes[i] != 0)
                {
                        return (i+1);
                }
        }
        return 0;
}

// find up to MAX_DIGITS of (nSrcDig of) pSrc cubed into pCube
int
FindCube(char *pSrc, int nSrcDig, char *pCube)
{
        char square[MAX_DIGITS];
        int nSqDig, nCubeDig;
        nSqDig = MulDecimal(pSrc, pSrc, &(square[0]), nSrcDig, nSrcDig);
        nCubeDig = MulDecimal(pSrc, &(square[0]), pCube, nSrcDig, nSqDig);
        return nCubeDig;
}

// return the least significant digit at which pNum1 and pNum2 differ
int
FindFirstDiff(char *pNum1, char *pNum2)
{
        int i;
        for(i= 0; i < MAX_DIGITS ; i++)
        {
                if(pNum1[i] != pNum2[i])
                {
                        return i;
                }
        }
        return MAX_DIGITS;
}

// read digits from pBuf, put least significant in pNum[0] etc
int
ReadNumber(char *pBuf, char *pNum)
{
        int i, first, last, j;
        i = 0;
        first = last = -1;
        while(pBuf[i] != 0)
        {
                if(::isdigit(pBuf[i]))
                {
                        if(first < 0)
                        {
                                first = i;
                        }
                        last = i;
                }
                else if(first > 0)
                {       // seen a digit and this is not , past the end
                        break;
                }
                i++;
        }
        if(first < 0)
        {
                return -1;
        }
        if((last - first+ 1) > MAX_DIGITS)
        {
                return -2;
        }
        ::memset(pNum,0, MAX_DIGITS);
        for(i= last, j = 0; i >= first ; i--, j++)
        {
                pNum[j] = (pBuf[i] - '0');
        }
        return (last - first + 1);
}

// write out nDigits from pNum (most significant digit first) followed by CR
void
WriteNumber(char *pNum, int nDigits)
{
        int i;
        for(i = nDigits - 1; i >= 0 ; i--)
        {
                putchar(pNum[i] + '0');
        }
        putchar('\n');
}

// put in pRes, least sig digit first a decimal number
// of at most nDesDigits such that the last nDesDigits of
// result^3 = pDes digits
int
FindCubeRoot(char *pDes, char *pRes, int nDesDigits)
{
        int nResDigits, firstDiffInd, recip, diff;
        ::memset(pRes,0, MAX_DIGITS);
        // get least significant digit of result and reciprocal (mod 10) of 3*c0*c0
        if(pDes[0] == 1)
        {
                pRes[0] = 1;
                recip = 7;
        }
        else if(pDes[0] == 3)
        {
                pRes[0] = 7;
                recip = 3;
        }
        else if(pDes[0] == 7)
        {
                pRes[0] = 3;
                recip = 3;
        }
        else if(pDes[0] == 9)
        {
                pRes[0] = 9;
                recip = 7;
        }
        else
        {       // bad input LSD
                return -1;      // caller should check
        }
        nResDigits = 1;
        FindCube(pRes, nResDigits, &(resCubed[0]));
        firstDiffInd = FindFirstDiff(pDes, &(resCubed[0]));
        while(firstDiffInd < nDesDigits)
        {
                diff = pDes[firstDiffInd] - resCubed[firstDiffInd];
                if(diff < 0)
                {
                        diff += 10;
                }
                diff *= recip;
                pRes[firstDiffInd] = diff % 10;
                nResDigits = firstDiffInd + 1;
                FindCube(pRes, nResDigits, &(resCubed[0]));
                firstDiffInd = FindFirstDiff(pDes, &(resCubed[0]));
        }
        return nResDigits;
}

int
main(int argc, char **argv)
{
        int nProb, probNum, digCnt, resCnt;

        if(fgets(&(inbuf[0]), 255, stdin) == NULL)
        {
                fprintf(stderr, "Read failed on problem count\n");
                return -1;
        }
        if(sscanf(&(inbuf[0]), "%d", &nProb) != 1)
        {
                fprintf(stderr, "Scan failed on problem count\n");
                return -2;
        }
        for(probNum = 1; probNum <= nProb ; probNum++)
        {
                if(fgets(&(inbuf[0]), 255, stdin) == NULL)
                {
                        fprintf(stderr, "Read failed on problem %d data\n", probNum);
                        return -3;
                }
                digCnt = ReadNumber(&(inbuf[0]), &(desired[0]));
                if(digCnt == -1)
                {
                        fprintf(stderr, "No digits problem %d \n", probNum);
                        return -4;
                }
                if(digCnt == -2)
                {
                        fprintf(stderr, "Too many digits problem %d \n", probNum);
                        return -5;
                }
                if(((desired[0] & 1) == 0) || (desired[0] == 5))
                {
                        fprintf(stderr, "Least digit not 1, 3, 7, or 9 problem %d \n", probNum);
                        return -6;
                }
                resCnt = FindCubeRoot(&(desired[0]), &(result[0]), digCnt);
                WriteNumber(&(result[0]), resCnt);
        }
        return 0;
}
