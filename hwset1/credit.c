#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long cnum;
    
    // Initialize bounds for card numbers
    long long amex_low1 = 340000000000000; // least 15 digit number starting with 34
    long long amex_top1 = 349999999999999; // greatest 15 digit number starting with 34
    long long amex_low2 = 370000000000000; // least 15 digit number starting with 37
    long long amex_top2 = 379999999999999; // greatest 15 digit number starting with 37
    long long mc_low = 5100000000000000; // least 16 digit number starting with 51
    long long mc_top = 5599999999999999; // greatest 16 digit number starting with 55
    long long v_low1 = 4000000000000; // least 13 digit number starting with 4
    long long v_top1 = 4999999999999; // greatest 13 digit number starting with 4
    long long v_low2 = 4000000000000000; // least 16 digit number starting with 4
    long long v_top2 = 4999999999999999; // greatest 16 digit number starting with 4
    
/**
 * Gets the card number from the user
 * Based off source code from lecture 2, function-1.c, for GetPositiveInt()
 **/
    do
    {
        printf("Number: ");
        cnum = GetLongLong();
    }
    /**
    // Set up to only accept numbers that are in the ranges of AMEX, VISA, or MASTERCARD
    // but CS50 check wants INVALID for other numbers instead of asking for a Number
    while ( (cnum<v_low1) || 
            ((cnum>v_top1) && (cnum<amex_low1)) || 
            ((cnum>amex_top1) && (cnum<amex_low2)) ||
            ((cnum>amex_top2) && (cnum<v_low2)) || 
            ((cnum>v_top2) && (cnum<mc_low)) || 
            (cnum>mc_top) );
    **/
    while(cnum<0);
    
/** Implement checksum **/
    long long temp_cnum = cnum; // a copy of cnum to edit
    int digit; // a variable to look at each digit of cnum
    int sum_mult = 0; // the sum of the digits that were multiplied by 2
    int sum_not_mult = 0; // the sum of the digits that weren't multiplied by 2
    for (int ii = 1; temp_cnum > 0; ii++)
    {
        /** Look at each digit, code for separating digits is from:
         *  stackoverflow.com/questions/9302681/c-how-to-break-apart-a-multi-digit-number-into-separate-variables
         *  "C: how to break apart a multi digit number into separate variables"
         **/
        digit = temp_cnum % 10;
        temp_cnum /= 10;
        
        if (ii%2 == 0)
        {
            int product = digit * 2;
            
            /** Look at each digit of the product, code for separating digits is from:
            *  stackoverflow.com/questions/9302681/c-how-to-break-apart-a-multi-digit-number-into-separate-variables
            *  "C: how to break apart a multi digit number into separate variables"
            **/
            while(product > 0)
            {
                sum_mult += product % 10;
                product /= 10;
            }
            
            
        }else{
            sum_not_mult += digit;
        }
    }
    int final_sum = sum_mult + sum_not_mult;
    int last_digit = final_sum % 10;
    
            
    if (last_digit != 0){  // if the last_digit == 0, the number is valid
        printf("INVALID\n");
    } else if (((cnum>=amex_low1) && (cnum<=amex_top1)) || 
               ((cnum>=amex_low2) && (cnum<=amex_top2))) 
    {
        printf("AMEX\n");
    } else if ((cnum>=mc_low) && (cnum<=mc_top)) {
         printf("MASTERCARD\n");
    } else if (((cnum>=v_low1) && (cnum<=v_top1)) ||
                   ((cnum>=v_low2) && (cnum<=v_top2)))
    {
        printf("VISA\n");
    }else{
        printf("INVALID\n");
    }
        
    
    return 0;
    
}