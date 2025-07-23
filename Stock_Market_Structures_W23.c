#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

struct stock_price_and_size
{
    float open;
    float close;
    float high;
    float low;
    float volume;
};

struct stock_price_and_size sps[10][30];

void day_date_calender()
{
    char *date[30];
    date[0] = "1st Sept.";
    date[1] = "4th Sept.";
    date[2] = "5th Sept.";
    date[3] = "6th Sept.";
    date[4] = "7th Sept.";
    date[5] = "8th Sept.";
    date[6] = "11th Sept.";
    date[7] = "12th Sept.";
    date[8] = "13th Sept.";
    date[9] = "14th Sept.";
    date[10] = "15th Sept.";
    date[11] = "18th Sept.";
    date[12] = "20th Sept.";
    date[13] = "21st Sept.";
    date[14] = "22nd Sept.";
    date[15] = "25th Sept.";
    date[16] = "26th Sept.";
    date[17] = "27th Sept.";
    date[18] = "28th Sept.";
    date[19] = "29th Sept.";
    date[20] = "3rd Oct.";
    date[21] = "4th Oct.";
    date[22] = "5th Oct.";
    date[23] = "6th Oct.";
    date[24] = "9th Oct.";
    date[25] = "10th Oct.";
    date[26] = "11th Oct.";
    date[27] = "12th Oct.";
    date[28] = "13th Oct.";
    date[29] = "16th Oct.";

    printf("The Calender for the stock market is as follows...\n");
    Sleep(2000);
    for (int i=0;i<30;i++) printf("Day %d is %s \n",i,date[i]);
} 

void initializing_data()
{
    /*  The data listed below is of 10 stock for 30 market days (excluding the off days i.e. weekends and other holidays) ranging from
        1st Sept. to 16th Oct. */

    printf("Reinitializing Data...\n");
    FILE *ptr = NULL;
    char str[20];

    ptr = fopen("stocks_data.txt","r");

    for (int index=0;index<10;index++)
    {
        for (int date=0;date<30;date++)
        {   
            fscanf(ptr,"%s",str);
            sps[index][date].open = atof(str);

            fscanf(ptr,"%s",str);
            sps[index][date].high = atof(str);

            fscanf(ptr,"%s",str);
            sps[index][date].low = atof(str);

            fscanf(ptr,"%s",str);
            sps[index][date].close = atof(str);

            fscanf(ptr,"%s",str);
            sps[index][date].volume = atof(str);
        }
    }
    fclose(ptr);
    printf("The data is ready now\n");
}

char* index_to_name(int index)
{
    char *s;
    if (index==0) s = "HDFC";
    else if (index==1) s="AXIS BANK";
    else if (index==2) s="BAJAJ AUTO";
    else if (index==3) s="TATAMOTORS";
    else if (index==4) s="MARUTI";
    else if (index==5) s="RELIANCE";
    else if (index==6) s="TITAN";
    else if (index==7) s="TCS";
    else if (index==8) s="INFY";
    else if (index==9) s="WIPRO";

    return s; 
}

void swap_int(int*num1,int*num2)
{
    int temp;
    temp=*num1;
    *num1=*num2;
    *num2=temp;
}

void per_change()
{
    float pc;       
    int j;
    int open_start,close_end;

    printf("Enter start day:\n");
    scanf("%d",&open_start);

    printf("Enter end day:\n");
    scanf("%d",&close_end);

    if (open_start<1 || close_end<1 || open_start>30 || close_end>30 || open_start>close_end) printf("Invalid input\n");
    else
    {
        for(j=0; j<10; j++)
        {
            float max=sps[j][close_end-1].close;
            float min=sps[j][open_start-1].open;
            pc=((max-min)/min)*100;
            printf("\n\nPercentage Change in the stock %s is %0.2f %%",index_to_name(j), pc);
        }
    }
}

void sorting_for_vol_and_cp()
{
    int date;

    printf("\nEnter the day for sorting\n");
    scanf("%d",&date);

    if (date<1 || date>30) printf("\nInvalid Input");
    else
    {
        int sorted_list[10];
        for (int i=0 ; i<10 ; i++) sorted_list[i]=i;
        // insertion sort in increasing order
        for (int i=0;i<10;i++)
        {
            int min_index,initial_index,swap_index;

            initial_index=sorted_list[i];

            min_index=initial_index;
            for(int j=i+1;j<10;j++)
            {
                int check_index;
                check_index=sorted_list[j];
                if (sps[min_index][date-1].volume > sps[check_index][date-1].volume) 
                {
                    min_index=check_index;
                    swap_index=j;   
                }

                else if (sps[min_index][date-1].volume == sps[check_index][date-1].volume)
                {
                    if (sps[min_index][date-1].close > sps[check_index][date-1].close) min_index=j;
                }
            }
            if (i!=min_index) swap_int(&sorted_list[swap_index],&sorted_list[i]);
        }
        printf("\n\nThe sorted data is as folllows\n\n");
        for (int i=0;i<10;i++) printf("%s %0.2f \n",index_to_name(sorted_list[i]),sps[sorted_list[i]][date-1].volume);
    }
}

void profit_loss()
{
    printf ("\n\nWe have data from date 1 to date 30 ");
    
    int buy_date,sell_date;

    printf("\nEnter the buying day\n");
    scanf("%d",&buy_date);

    printf("\nEnter the selling day\n");
    scanf("%d",&sell_date);

    if ((buy_date<1) || (buy_date>30) || (sell_date<1) || (sell_date>30)) printf("INVALID INPUT");
    else
    {
        //Assuming stock to be bought for low price and sold for high price
        for (int index=0;index<10;index++)
        {
            float pp,sp,result;          //purchase price and sell price

            pp=(sps[index][buy_date-1].open * sps[index][buy_date-1].volume);
            sp=(sps[index][sell_date-1].close * sps[index][sell_date-1].volume);
            result = sp-pp;

            if (result==0) printf("Neither profit nor loss for stock %s\n",index_to_name(index));
            else if (result>0)
            {
                result = 100*result/pp;
                printf("For stock %s , %0.2f%% profit\n",index_to_name(index),result);
            }

            else 
            {
                result = -100*result/pp;
                printf("For stock %s , %0.2f%% loss\n",index_to_name(index),result);
            }

            printf("\n\n");
        }
    }
}

void highest_perf()
{
    float gain, max=0;
    int j, high_index;

    int open_start,close_end;

    printf("Enter start day:\n");
    scanf("%d",&open_start);

    printf("Enter end day:\n");
    scanf("%d",&close_end);

    if (open_start<1 || close_end<1 || open_start>30 || close_end>30 || open_start>close_end) printf("Invalid input\n");
    else
    {

        for(j=0; j<10; j++)
        {
            float a=sps[j][close_end].close;
            float b=sps[j][open_start].open;

            gain=((a-b)/b)*100;
            if(gain>max)
            {
                max=gain;
                high_index=j;
            }
        }
        printf("\n\nThe highest performing stock is %s stock", index_to_name(high_index));
    }
}

void lowest_perf()
{
    float gain, min=0;
    int j, low_index;
    int open_start,close_end;

    printf("Enter start day:\n");
    scanf("%d",&open_start);

    printf("Enter end day:\n");
    scanf("%d",&close_end);

    if (open_start<1 || close_end<1 || open_start>30 || close_end>30 || open_start>close_end) printf("Invalid input\n");
    else
    {
        for(j=0; j<10; j++)
        {
            float a=sps[j][close_end].close;
            float b=sps[j][open_start].open;

            gain=((a-b)/b)*100;
            if(gain<min)
            {
                min=gain;
                low_index=j;
            }
        }
        printf("\n\nThe lowest performing stock is %s stock", index_to_name(low_index));
    }
}

void overall_performance()
{
    float performance[10];
    int performance_ptr[10];

    int start_date,end_date;

    printf("\nEnter the start day\n");
    scanf("%d",&start_date);

    printf("Enter the end day\n");
    scanf("%d",&end_date);

    if (start_date<1 || end_date<1 || start_date>30 || end_date>30 || start_date>end_date) printf("\nInvalid input");
    else
    {
        if (start_date==1) start_date=2; 
        for (int index=0;index<10;index++)
        {
            performance_ptr[index]=index;
            float sum=0;
            float change,prev_val,current_val;

            for(int date=start_date-1;date<end_date;date++)
            {
                current_val=sps[index][date].open;
                prev_val=sps[index][date-1].open;
                change=current_val-prev_val;
                sum = sum + change/prev_val * 100 * sps[index][date].volume;
            }
            performance[index]=sum;
        }

        //Selection sort
        for (int i=0;i<10;i++)
        {   
            int min_value_index,swap_index;
            min_value_index=performance_ptr[i];
            swap_index=i;

            for (int j=i+1;j<10;j++)
            {
                if(performance[min_value_index] > performance[performance_ptr[j]]) 
                {   
                    min_value_index=performance_ptr[j];
                    swap_index=j;
                }
            }

            if (swap_index!=i)
            {
                swap_int(&performance_ptr[swap_index],&performance_ptr[i]);
            }
            
        }
        for (int i=0;i<10;i++) printf("%s %0.2f\n",index_to_name(performance_ptr[i]),performance[performance_ptr[i]]);
    }
}

void average_of_average()
{

    int i,j;
    float sum_price=0,open,vol,sum_open_vol=0 ,weighted_average=0,sum_weighted_avg=0, avg_of_avg=0;
    int start_date,end_date;

    printf("Enter start day:\n");
    scanf("%d",&start_date);

    printf("Enter end day:\n");
    scanf("%d",&end_date);

    //Weighted mean = summ fixi / summ fi   fi=open_price xi=volume

    if (start_date<1 || end_date<1 || start_date>30 || end_date>30 || start_date>end_date) printf("Invalid input\n");
    else
    for(j=0; j<10; j++)
    {
        for(i=start_date-1; i<=end_date-1; i++)
        {
            open=sps[j][i].open;
            sum_price=sum_price + open;
            vol=sps[j][i].volume;
            sum_open_vol=open*vol + sum_open_vol;
        }
        weighted_average=sum_open_vol/sum_price;
        sum_weighted_avg=sum_weighted_avg+weighted_average;
    }
    avg_of_avg=sum_weighted_avg/10;
    printf("average of average is %0.2f", avg_of_avg);
}

void show_menu()
{
    int n=0;
    while (n!=8)
    {
        Sleep (1000);
        printf("\n\n1.To find percent change in price of a stock\n");
        printf("2.To stock given stock for a particular day volume wise then close price wise\n");
        printf("3.To find profit or loss for given buy and sell date\n");
        printf("4.To find Highest performing stock for a specified duration\n");
        printf("5.To find Lowest performing stock for a specified duration\n");
        printf("6.List stocks in increasing order of their overall performance\n");
        printf("7.To find average value of all stocks\n");
        printf("8.EXIT\n\n\n");
    
        Sleep(1000);

        printf("Which function would you like to access?\n");
        scanf("%d",&n);

        if (n==1) per_change();
        else if (n==2) sorting_for_vol_and_cp();
        else if (n==3) profit_loss();
        else if (n==4) highest_perf();
        else if (n==5) lowest_perf();
        else if (n==6) overall_performance();
        else if (n==7) average_of_average();
        else if (n==8) printf("Thank you");
        else printf("Wrong input! Please try again\n");
    } 
}

void main()
{
    day_date_calender();
    initializing_data();
    show_menu();
}