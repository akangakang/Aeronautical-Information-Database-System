#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
struct datetime_t
{
    int year,month,day,hour,minute,second;
    bool operator==(const struct datetime_t &date2)
    {
        return year==date2.year && month==date2.month && day==date2.day && hour==date2.hour && minute==date2.minute && second==date2.second;
    }
    bool operator!=(const struct datetime_t &date2)
    {
        return !(*this==date2);
    }
    bool operator<(const struct datetime_t &date2)
    {
        if (year<date2.year) return true;
        if (year>date2.year) return false;
        if (month<date2.month) return true;
        if (month>date2.month) return false;
        if (day<date2.day) return true;
        if (day>date2.day) return false;
        if (hour<date2.hour) return true;
        if (hour>date2.hour) return false;
        if (minute<date2.minute) return true;
        if (minute>date2.minute) return false;
        return second<date2.second;
    }
    bool operator<=(const struct datetime_t &date2)
    {
        return *this<date2 || *this==date2;
    }
    bool operator>(const struct datetime_t &date2)
    {
        return !(*this<=date2);
    }
    bool operator>=(const struct datetime_t &date2)
    {
        return !(*this<date2);
    }
};
const struct datetime_t mindate={2010,1,1,0,0,0};
const struct datetime_t maxdate={2020,12,28,23,59,59};
const int N_administrator=50;
const int N_boardingPass=5000000;
const int N_customer=100;
const int N_flight=500;
const int N_groundService=50;
const int N_manage=100;
const int N_notification=100;
const int N_order=5000;
const int N_route=500;
const int N_take=1000;
struct datetime_t datetime(const struct datetime_t &from,const struct datetime_t &to,int form)
{
    struct datetime_t res;
    do
    {
        res.year=(from.year<=to.year?from.year+rand()%(to.year-from.year+1):2010+rand()%11);
        res.month=(from.month<=to.month?from.month+rand()%(to.month-from.month+1):1+rand()%12);
        res.day=(from.day<=to.day?from.day+rand()%(to.day-from.day+1):1+rand()%28);
        res.hour=(from.hour<=to.hour?from.hour+rand()%(to.hour-from.hour+1):rand()%24);
        res.minute=(from.minute<=to.minute?from.minute+rand()%(to.minute-from.minute+1):rand()%60);
        res.second=(from.second<=to.second?from.second+rand()%(to.second-from.second+1):rand()%60);
    }
    while (res<from || res>to);
    putchar('\"');
    if (form<=0)
    {
        printf("%d-",res.year);
        if (res.month<10) putchar('0');
        printf("%d-",res.month);
        if (res.day<10) putchar('0');
        printf("%d",res.day);
    }
    if (!form) putchar(' ');
    if (form>=0)
    {
        if (res.hour<10) putchar('0');
        printf("%d:",res.hour);
        if (res.minute<10) putchar('0');
        printf("%d:",res.minute);
        if (res.second<10) putchar('0');
        printf("%d",res.second);
    }
    putchar('\"');
    return res;
}
void number(int L,int R,int pre)
{
    printf("%d",L+rand()%(R-L+1));
    if (!pre) return;
    int power=1;
    for (int i=0;i<pre;++i) power*=10;
    printf(".%d",rand()%power);
}
void varchar(int len,bool letter)
{
    if (letter)
    {
        for (putchar('\"');len--;) putchar('a'+rand()%26);
        putchar('\"');
        return;
    }
    while (len--) putchar('0'+rand()%10);
}
int main()
{
    srand(time(0));
    struct datetime_t tmp;
    int i;
    freopen("data.sql","w",stdout);
    for (i=0;i<N_administrator;++i)
    {
        printf("insert into administrator(adminName) values(");
        varchar(30,true);
        puts(");");
    }
    for (i=0;i<N_customer;++i)
    {
        printf("insert into customer(money,customerName,phone) values(");
        number(0,10000,2);
        putchar(',');
        varchar(30,true);
        putchar(',');
        varchar(11,false);
        puts(");");
    }
    for (i=0;i<N_groundService;++i)
    {
        printf("insert into `ground service`(groundName) values(");
        varchar(30,true);
        puts(");");
    }
    for (i=0;i<N_route;++i)
    {
        printf("insert into route(departureTime,arrivalTime,departureAirport,arrivalAirport,planeId) values(");
        tmp=datetime(mindate,maxdate,1);
        putchar(',');
        datetime(tmp,maxdate,1);
        putchar(',');
        varchar(30,true);
        putchar(',');
        varchar(30,true);
        putchar(',');
        number(1,10000,0);
        puts(");");
    }
    for (i=0;i<N_flight;++i)
    {
        int status=rand()%3;
        printf("insert into flight(routeId,flightNumber,date,actualDeparture,actualArrival,customerCount,seatCount,isDelayed,isCancelled,firstClassPrice,businessClassPrice,economyClassPrice,status) values(");
        number(1,N_route,0);
        putchar(',');
        varchar(8,true);
        putchar(',');
        datetime(mindate,maxdate,-1);
        putchar(',');
        tmp=datetime(mindate,maxdate,0);
        putchar(',');
        datetime(tmp,maxdate,0);
        putchar(',');
        number(0,10,0);
        putchar(',');
        number(50,300,0);
        putchar(',');
        printf("%d",status==1);
        putchar(',');
        printf("%d",status==2);
        putchar(',');
        number(500,1000,2);
        putchar(',');
        number(400,500,2);
        putchar(',');
        number(300,400,2);
        putchar(',');
        if (!status) puts("\"normal\");");
        if (status==1) puts("\"delayed\");");
        if (status==2) puts("\"cancelled\");");
    }
    for (i=0;i<N_order;++i)
    {
        printf("insert into `order`(CustomerId,time) values(");
//        printf("insert into order(CustomerId,time) values(");
        if (rand()%10) putchar('1');
        else number(2,N_customer,0);
        putchar(',');
        datetime(mindate,maxdate,0);
        puts(");");
    }
    for (i=0;i<N_boardingPass;++i)
    {
        printf("insert into boardingPass(orderId,CustomerId,flightId,number,seat,type,price) values(");
        number(1,N_order,0);
        putchar(',');
        if (rand()%10) putchar('1');
        else number(2,N_customer,0);
        putchar(',');
        number(1,N_flight,0);
        putchar(',');
        varchar(20,true);
        putchar(',');
        number(1,10000,0);
        putchar(',');
        number(1,3,0);
        putchar(',');
        number(300,1000,2);
        puts(");");
    }
    for (i=0;i<N_manage;++i)
    {
        printf("insert into manage values(");
        number(1,N_flight,0);
        putchar(',');
        number(1,N_administrator,0);
        putchar(',');
        datetime(mindate,maxdate,0);
        putchar(',');
        int changedColumn=rand()%6;
        if (!changedColumn) printf("\"status\",");
        if (changedColumn==1) printf("\"firstClassPrice\",");
        if (changedColumn==2) printf("\"businessClassPrice\",");
        if (changedColumn==3) printf("\"economyClassPrice\",");
        if (changedColumn==4) printf("\"actualDeparture\",");
        if (changedColumn==5) printf("\"actualArrival\",");
        varchar(20,true);
        putchar(',');
        varchar(20,true);
        puts(");");
    }
    for (i=0;i<N_notification;++i)
    {
        printf("insert into notification values(");
        number(1,N_administrator,0);
        putchar(',');
        number(1,N_flight,0);
        putchar(',');
        number(1,N_customer,0);
        putchar(',');
        number(300,1000,2);
        putchar(',');
        datetime(mindate,maxdate,0);
        puts(");");
    }
    for (i=0;i<N_take;++i)
    {
        printf("insert into take values(");
        number(1,N_groundService,0);
        putchar(',');
        number(1,N_boardingPass,0);
        putchar(',');
        number(0,100,2);
        putchar(',');
        int isSafe=rand()%2;
        printf("%d,",isSafe);
        if (isSafe) printf("%d",rand()%2);
        else putchar('0');
        putchar(',');
        printf("%d);\n",rand()%2);
    }
    fclose(stdout);
    return 0;
}
