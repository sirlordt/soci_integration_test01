#include <iostream>
#include <ctime>
#include <memory>

#include <cppdbc/Common.hpp>
//#include <cppdbc/drivers/mysql/MySQLConnection.hpp>
#include <cppdbc/Statement.hpp>
#include <cppdbc/DriverManager.hpp>

int main()
{

	try
  {

    const char *host = "127.0.0.1";
    const char *user = "root";
    const char *password = "dsistemas";
    const char *database = "TestDB";

    // CPPDBC::DriverManager::registerDriver( "mysql", []() {

    //   return std::make_shared<CPPDBC::MySQLConnection>();

    // } );

    std::shared_ptr<CPPDBC::Connection> mySQLDatabaseConnection01 = CPPDBC::DriverManager::getConnection( "mysql" );

    std::shared_ptr<CPPDBC::Connection> mySQLDatabaseConnection02 = CPPDBC::DriverManager::getConnection( "mysql" );

    if ( mySQLDatabaseConnection01->connect( host, user, password, database ) &&
         mySQLDatabaseConnection02->connect( host, user, password, database ) )
    {

      mySQLDatabaseConnection01->setAutoCommit( false );

      mySQLDatabaseConnection02->setAutoCommit( false );

		  std::cout << "Success Connected: " << database << std::endl;

      std::shared_ptr<CPPDBC::Statement> stmt_01 = mySQLDatabaseConnection01->createStatement();

      std::shared_ptr<CPPDBC::Statement> stmt_02 = mySQLDatabaseConnection01->createStatement();

      std::shared_ptr<CPPDBC::ResultSet> rs_01 = {};

      if ( stmt_01 ) {

        mySQLDatabaseConnection01->begin();

        stmt_01->execute( "CREATE TABLE IF NOT EXISTS bizCar( id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT )" );

        int64_t affectedRows = stmt_01->execute( "INSERT INTO bizCar( name, price ) VALUES( 'Audi', 52642 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        affectedRows = stmt_01->execute( "INSERT INTO bizCar( name, price ) VALUES( 'Mercedes', 57127 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        affectedRows = stmt_01->execute( "INSERT INTO bizCar( name, price ) VALUES( 'Skoda',9000 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        rs_01 = stmt_02->executeQuery( "Select * From bizCar" );

        while ( rs_01->next() ) {

          std::cout << "id: " << rs_01->getAsLong( "id" ) << std::endl;

        }

        mySQLDatabaseConnection01->rollback();

      }

      std::cin.ignore();

      /*
      int affectedRows = mySQLDatabaseConnection.execute( "CREATE TABLE IF NOT EXISTS bizCar( id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), price INT )" );

      //if ( affectedRows > 0 ) {

   		  std::cout << "Success Created Table: bizCar" << std::endl;

        affectedRows = mySQLDatabaseConnection.execute( "INSERT INTO bizCar( name, price ) VALUES( 'Audi', 52642 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        affectedRows = mySQLDatabaseConnection.execute( "INSERT INTO bizCar( name, price ) VALUES( 'Mercedes', 57127 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        affectedRows = mySQLDatabaseConnection.execute( "INSERT INTO bizCar( name, price ) VALUES( 'Skoda',9000 )" );

   		  std::cout << "Success Insert Record In Table: " << affectedRows << std::endl;

        if ( mySQLDatabaseConnection.query( "Select * From bizCar" ) ) {

          CPPDBC::DBRecord dbRecord = mySQLDatabaseConnection.fetchRow();

          const CPPDBC::DBFieldInfoList fieldInfoList = mySQLDatabaseConnection.fetchRowFieldInfo();

          // const CPPDBC::DBFieldNameList& fieldNames = mySQLDatabaseConnection.fetchRowFieldName();

          // const CPPDBC::DBFieldTypeList& fieldTypes = mySQLDatabaseConnection.fetchRowFieldType();

          //CPPDBC::SimpleDBRecord dbRecord1;

          //dbRecord1[ "1" ] = 10;

          //int c = std::any_cast<int>( dbRecord1[ "1" ] );

          for ( auto fieldInfo : fieldInfoList ) {

            if ( dbRecord[ fieldInfo.name ].has_value() ) {

              if ( CPPDBC::isLong( fieldInfo.type ) ) {

                std::cout << fieldInfo.name << ": " << std::any_cast<long>( dbRecord[ fieldInfo.name ] ) << std::endl;

              }
              else if ( CPPDBC::isString( fieldInfo.type ) ) {

                std::cout << fieldInfo.name << ": " << std::any_cast<std::string>( dbRecord[ fieldInfo.name ] ) << std::endl;

              }

            }
            else {

              std::cout << fieldInfo.name << ": NULL" << std::endl;

            }

          }

        }
        */


      //}

    }
    else {

      std::cout << "Error to Connect: " << mySQLDatabaseConnection01->getLastError() << std::endl;

    }

	}
	catch( std::exception const &e )
  {

		std::cout << "ERROR: " << e.what() << std::endl;
		return 1;

	}

	return 0;

}

