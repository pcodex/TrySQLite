// This program demonstrates the creation of a SQLite database using C++
// 25-Mar-2020
// Author : Prab

#include <iostream>
#include "sqlite3.h"
#include <string>
#include <vector>


using namespace std;

int cbfunct(void* unused, int noofcolumns, char** colvalues, char** colnames) {

	for (int i = 0; i < noofcolumns; ++i) {
      cout << colnames[i] << " : " << colvalues[i] << endl;
	}
	cout << endl;
	return 0;
}

int main()
{

	sqlite3* db;

	int rc;

	rc = sqlite3_open("personal.db", &db);

	if (rc) {
		cout << "Cannot open db " << sqlite3_errmsg(db)<<endl;
	}
	else {
		cout << "Database opened successfully\n";
	}

	vector<string> cmds = {
		"create table pmtab('FName' varchar(45), 'Last Name' varchar(45), Address varchar(100))",
		"insert into pmtab('FName', 'Last Name', Address) values ('John', 'Doe', '2181 Capitol Av. East Palo Alto')",
		"insert into pmtab('FName', 'Last Name', Address) values ('Prab', 'Rocker', '221 Baker St. West London')",
		"insert into pmtab('FName', 'Last Name', Address) values ('Alice', 'Bell', '1418 Collins St. Melbourne')",
		"delete from pmtab where FName = 'Prab'",
		"select * from pmtab",
		"insert into pmtab('FName', 'Last Name', Address) values ('Joe', 'Focker', '221 Baker St. West London')",
		"select * from pmtab",
		"update pmtab set Fname='Prab' where `Last Name`='Focker'",
		"select * from pmtab"
	};

	char* errmsg = 0;
	
	for (int i = 0; i < cmds.size(); ++i) {
	
		rc = sqlite3_exec(db, cmds[i].c_str(), cbfunct, 0, &errmsg);

		if (rc != SQLITE_OK) {
			cout << "\n SQL Failure " << errmsg;
			sqlite3_free(errmsg);
		}		
	}

	sqlite3_close(db);

	return 0;
}
