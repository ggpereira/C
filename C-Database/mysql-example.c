#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>

/*
	Gabriel Gomes 
	Tested with Visual Studio Community 2017
*/

char passwd[128] = "passwd";

typedef struct
{
    char *query;
}db_query;


int connect_database(MYSQL *db) {

	if (mysql_real_connect(db, "localhost", "root", passwd, "pinkfloyd", 0, NULL, 0) == NULL)
	{
		printf("An Erro Ocurred in connection with database!\n");
		return 1;
	}
	return 0;
}

int start_database(MYSQL *db) 
{

    if(mysql_init(db) == NULL) 
    {
        printf("An Error Ocurred!\n");
        return 1;
    }

    /* Connect to database*/
    if(connect_database(db) == 1) 
    {
        return 1;
    } 

    printf("Database Started...\n");
    return 0;
}


void show_result(MYSQL_RES *rs)
{
	MYSQL_ROW row;
	unsigned long int rows, i;

	rows = (int) mysql_num_rows(rs);

	for (i = 0; i < rows; i++)
	{
		row = mysql_fetch_row(rs);
		fprintf(stdout, "Name: %s, Year: %s\n", row[1], row[2]);
	}
	mysql_free_result(rs);
}


int main()
{
	MYSQL db;
	MYSQL_RES *rs;
	db_query myQueries[2];

	
	start_database(&db);
	printf("-------------------------MYSQL DATABASE IN C program - EXAMPLE----------------------------------------------------\n");
	myQueries[0].query = "SELECT * FROM albums";

	puts(myQueries[0].query);
	printf("------------------------------------------\n");
	
	printf("Searching albums...\n");
	if (mysql_query(&db, myQueries[0].query))
	{
		printf("Error in Query\n");
		mysql_close(&db);
		exit(1);
	}

	if ((rs = mysql_store_result(&db)) == NULL)
	{
		printf("Unexpected Error in Result!\n");
		exit(1);
	}

	printf("%d fields encountered\n", mysql_field_count(&db));

	show_result(rs);

	mysql_close(&db);
	mysql_library_end();
	system("pause");
	return 0;
}
