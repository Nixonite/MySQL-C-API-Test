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
#include <time.h>
#include <stdlib.h>
#include <sstream>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
    
}

int main(int argc, const char * argv[])
{
    MYSQL *con = mysql_init(NULL);
    srand(time(NULL));
    
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    if (mysql_real_connect(con, "localhost", "root", "rootpass",
                           NULL, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    if(mysql_query(con, "DROP DATABASE IF EXISTS test")){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    if(mysql_query(con, "CREATE DATABASE IF NOT EXISTS test")){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    if(mysql_query(con, "USE test")){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    if(mysql_query(con, "CREATE TABLE IF NOT EXISTS testtable(id INT NOT NULL, nums INT,PRIMARY KEY(ID));")){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    
    
    for(int i=1;i<100;i++){
        std::stringstream ss;
        ss << "INSERT INTO testtable(id,nums) VALUES (" << i << "," << rand()%100 << ");";
        if(mysql_query(con, ss.str().c_str())){
            fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
            exit(1);
        }
    }
    
    MYSQL_RES *result;
    mysql_query(con, "SELECT nums FROM testtable WHERE id=4;");
    result = mysql_store_result(con);
    MYSQL_ROW row = mysql_fetch_row(result);
    
    std::cout<< *row << std::endl;
    
    mysql_close(con);
    
    
    return 0;
}

