#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "funcs.h"


char* int_to_month(int mm){
    switch (mm)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April ";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    
    default:
        return "Not a Month";
    }
}

int month_to_days(int mm){
    if      (mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12)
        return 31;
    else if (mm==4||mm==6||mm==9||mm==11)
        return 30;
    else
        return 28;
}

void date_to_temp_bin(date date,char *filename){
    FILE    *f;
    int days,
        i;
    float d;

    days=0;
    for(i=1;i<date.mm;i++){
        days+= month_to_days(i);
    }
    days+=date.dd;

    f = fopen(filename,"rb");
    if(f==NULL){
        fclose(f);
        printf("Error: %s",strerror(errno));
        return;
    }

    //print min
    fseek(f,sizeof(float)*((days*2)-4),SEEK_SET);
    fread(&d,sizeof(float),1,f);
    printf("Minimum Temperature on %d of %s = %.2f\n\n",date.dd,int_to_month(date.mm),d);

    //print max
    fseek(f,sizeof(float)*((days*2)-3),SEEK_SET);
    fread(&d,sizeof(float),1,f);
    printf("Maximum Temperature on %d of %s = %.2f\n\n",date.dd,int_to_month(date.mm),d);

    printf("%d\n",((days*2)-4));

    fclose(f);
}

void date_to_temp_txt(date date,char *filename){
    FILE    *f;
    int days,
        i;
    float d;

    days=0;
    for(i=1;i<date.mm;i++){
        days+= month_to_days(i);
    }
    days+=date.dd;

    f = fopen(filename,"r");
    if(f==NULL){
        fclose(f);
        printf("Error: %s",strerror(errno));
        return;
    }

    //print min
    for(i=0;i<((days*2)-3);i++)fscanf(f,"%f\n",&d);
    printf("Minimum Temperature on %d of %s = %.2f\n\n",date.dd,int_to_month(date.mm),d);

    fseek(f,0,SEEK_SET);

    //print max
    for(i=0;i<((days*2)-2);i++)fscanf(f,"%f\n",&d);
    printf("Maximum Temperature on %d of %s = %.2f\n\n",date.dd,int_to_month(date.mm),d);

    printf("%d\n",((days*2)-4));

    fclose(f);
}










