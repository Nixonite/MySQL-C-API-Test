//
//  main.cpp
//  FirstMySQL
//
//  Created by Allen Sarkisyan on 8/15/14.
//  Copyright (c) 2014 Allen Sarkisyan. All rights reserved.
//


#include <iostream>
#include <mysql.h>
#include <my_global.h>

int main(int argc, const char * argv[])
{
    MYSQL *con = mysql_init(NULL);
    
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    if (mysql_real_connect(con, "localhost", "root", "relativity300",
                           NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    if (mysql_query(con, "CREATE DATABASE testdb"))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    mysql_close(con);
    
    
    return 0;
}

