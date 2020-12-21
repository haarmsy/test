#include "sqlite3.h"
#include <stdio.h>
#include <time.h>


int main(void)
{
    sqlite3 *db;
    char *err_msg = 0;
    char sql[1024];
    int i = 0;
    double result;
    time_t start, end;
    
    start = time(NULL);

    int rc = sqlite3_open("test.db", &db);
    
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    memset(sql, 0x00, 1024);
    sprintf(sql, "DROP TABLE IF EXISTS Logs;" 
                "CREATE TABLE Logs(Id INT, MAC INT, TYPE INT, REASON TEXT);");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    }


    for(i=0; i<100000; i++)
    {


    sprintf(sql, "INSERT INTO Logs VALUES(%d, %d, %d, 'show me the money show me the moneyshow me the moneyshow me the money');",
            i, i+1, i+2 );

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 

    if((i%1000)==0)
        printf(".");
    if((i%10000)==0)
        printf("@\n");    

    }
    
    sqlite3_close(db);

    end = time(NULL);

    result = (double)(end-start);

    printf("\n[%d] insert.... result time [%f]\n", i, result);
    
    return 0;
}