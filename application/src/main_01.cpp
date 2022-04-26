/**
* nanojson test code
*
* Copyright (c) 2016 tu-sa
*
* This software is released under the MIT License.
* http://opensource.org/licenses/mit-license.php
*/

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>

#include <soci/soci.h>
#include <soci/use.h>
#include <soci/into.h>
#include <soci/mysql/soci-mysql.h>

#include <fmt/printf.h>
//#include <nlohmann/json.hpp>

//#define RESTINIO_EXTERNAL_STRING_VIEW_LITE  1
//#define RESTINIO_EXTERNAL_OPTIONAL_LITE     1
//#define RESTINIO_EXTERNAL_VARIANT_LITE      1
//#define RESTINIO_EXTERNAL_EXPECTED_LITE     1

//#include <restinio/all.hpp>

#include "nanojson/nanojson.hpp"

#include "uuid_v4/uuid_v4.h"

nanojson::element config_json;

const std::string get_file_path( const std::string& file )
{
    std::string result = file;

    size_t found = file.find_last_of( "/\\" );

    if ( found != std::string::npos )
    {
        result = file.substr( 0, found ) + "/";
    }

    return result;
}

// void split_filename( const std::string& str )
// {

//   size_t found;
//   std::cout << "Splitting: " << str << std::endl;
//   found=str.find_last_of("/\\");
//   std::cout << " folder: " << str.substr(0,found) << std::endl;
//   std::cout << " file: " << str.substr(found+1) << std::endl;

// }

std::stringstream read_text_file_content( const std::string& path_file_to_read )
{
    std::stringstream result {};

    std::ifstream stream_file_input = {};

    try
    {
        stream_file_input = std::ifstream( path_file_to_read );

        if ( stream_file_input.is_open() )
        {
            std::string line {};

            while ( std::getline( stream_file_input, line ) )
            {
                result << line;
            }

            stream_file_input.close();
        }
    }
    catch ( const std::exception& ex )
    {
        std::cout << "Exception: " << ex.what() << std::endl;

        if ( stream_file_input.is_open() )
        {
            stream_file_input.close();
        }
    }

    return result;
}

nanojson::element get_config( const std::string& config_path_file )
{
    auto config_content = read_text_file_content( config_path_file );

    return nanojson::element::from_string( config_content.str() );
}

soci::session x;

void process_b( soci::transaction * trans )
{
    soci::transaction * local_transaction = trans;

    bool is_local_transaction = false;

    try
    {
        if ( local_transaction->is_active() == false ) //The transaction is not alive
        {
            local_transaction = trans->current_session().begin(); //new soci::transaction( x ); //Generate new one

            is_local_transaction = true;
        }

        //Process data in db

        //process_a( local_transaction );

        //More db stuff

        //...

        if ( is_local_transaction == true ) //Only apply if is local transaction
        {
            local_transaction->commit(); //Apply the local transaction
        }
    }
    catch ( ... )
    {
        if ( local_transaction->is_active() )  //We save another nested try / catch
        {
            local_transaction->rollback();
        }
    }

    if ( is_local_transaction )
    {
        delete local_transaction;
    }
}

int main( int argc, const char *argv[] )
{
    //#define LF "\n"

    const char *path = argv[ 0 ];

    std::cout << "Path: " << path << std::endl;

    //split_filename( path );

    const std::string config_file_path = get_file_path( path ) + "config/main.json";

    std::cout << "Config File: " << config_file_path << std::endl;

    config_json = get_config( config_file_path );

    if ( config_json[ "endpoints_base_path" ].is_defined() )
    {
        std::cout << "config_json[ \"endpoints_base_path\" ] = " << config_json[ "endpoints_base_path" ].to_string() << std::endl;
    }

    if ( config_json[ "database" ][ "main" ].is_defined() )
    {
        auto database_main_config = config_json[ "database" ][ "main" ];

        std::cout << "config_json[ \"driver\" ] = " << database_main_config[ "driver" ].to_string() << std::endl;

        //config_json[ "database" ][ "main1" ] < "{ x: 1, y: 1, z: 1 }";

        //char const* const connectString = argv[1];
        std::ostringstream connectionString;

        UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

        try
        {
            // const std::string& driver = database_main_config[ "driver" ].to_string();

            // connectionString << "db=" + database_main_config[ "database" ].to_string();

            // connectionString << " user=" + database_main_config[ "user" ].to_string();

            // connectionString << " password='" + database_main_config[ "password" ].to_string() << "'";

            // connectionString << " host=" + database_main_config[ "host" ].to_string();

            // std::shared_ptr<soci::session> db_connection = std::make_shared<soci::session>( soci::mysql, connectionString.str() );

            std::shared_ptr<soci::session> db_connection = common::make_db_connection( database_main_config );

            //soci::session sql( "mysql", "db=test user=root password='Ala ma kota'");
            //soci::session sql(connectString);

            std::string id { "" };
            std::string extraData { "" };

            //std::shared_ptr<soci::transaction> transaction { nullptr };

            soci::transaction* transaction = nullptr;

            try
            {
                //transaction = std::make_shared<soci::transaction>( *db_connection );
                transaction = db_connection->begin();
                transaction = db_connection->begin(); //Always return the same transaction object pointer. No memory leak

                //This is optional the db_connection take care of free the memory.
                delete transaction; //Is ok. db_connection internal transaction is now NULL too.

                transaction = db_connection->begin(); //Create new one. Now the address is diferent to previous ..->begin()

                //transaction.

                //db_connection << "Select Id, ExtraData From sysPerson", soci::into(id),soci::into(extraData);

                //int i = 0;

                //int id { 7 };
                std::string id = { "7" };

                //db_connection << "Select FirstName From sysPerson where Id != :id", soci::use( id, "id" );

                soci::rowset<soci::row> rs = ( db_connection->prepare << "Select * From sysPerson where Id != :id", soci::use( id, "id" ) );

                std::cout << "Press any key to continue" << std::endl;

                std::cin.ignore();

                // iteration through the resultset:
                for ( soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
                {
                    soci::row const& row = *it;

                    // dynamic data extraction from each row:
                    std::cout << "Id: " << row.get<std::string>( "Id" ) << std::endl
                              << "Name: " << row.get<std::string>( "FirstName" ) << " " << row.get<std::string>( "LastName" ) << std::endl
                              << "ExtraData: " << row.get<std::string>( "ExtraData" ) << std::endl;
                }

                id = uuidGenerator.getUUID().str();
                std::string first_name = "Tomás";
                std::string last_name = "Moreno";

                soci::statement st = ( db_connection->prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

                st.execute();

                transaction->commit();
            }
            catch ( soci::soci_error const& e )
            {
                transaction->rollback();

                std::cerr << "Failed to execute the query: "
                          << e.what() << "\n";
            }

            std::cout << "Successfully connected to \"" << connectionString.str() << "\", "
                      << "using \"" << db_connection->get_backend_name() << "\" backend.\n";

            std::cout << "Press any key to exit" << std::endl;

            std::cin.ignore();

            return EXIT_SUCCESS;
        }
        catch ( soci::soci_error const& e )
        {
            std::cerr << "Connection to \"" << connectionString.str() << "\" failed: "
                      << e.what() << "\n";
        }
        catch ( std::runtime_error const& e )
        {
            std::cerr << "Unexpected standard exception occurred: "
                      << e.what() << "\n";
        }
        catch ( ... )
        {
            std::cerr << "Unexpected unknown exception occurred.\n";
        }
    }

    /*
    std::ifstream input_stream_config_file( get_file_path( path ) + "config/main.json" );

    if ( input_stream_config_file.is_open() )
    {

      std::stringstream ss {}; // = std::stringstream( std::string( "{ \"key01\": \"value01\", \"key02\": \"value02\", \"key03\": { \"1\": 2 } }" ) );

      std::string line;

      while ( std::getline( input_stream_config_file, line ) )
      {

        ss << line;

      }

      config_json = nanojson::element::from_string( ss.str() );

      if ( config_json[ "base_path" ][ "ddd" ].is_defined() ) {

        std::cout << "config_json[ \"base_path\" ] = " << config_json[ "base_path" ].to_string() << std::endl;

      }

      /*
      if ( config_json[ "key01" ].is_defined() ) {

        std::cout << "e[ \"key01\" ] = " << config_json[ "key01" ].to_string() << std::endl;

      }

      if ( config_json[ "key02" ].is_defined() ) {

        std::cout << "e[ \"key02\" ] = " << config_json[ "key02" ].to_string() << std::endl;

      }

      if ( config_json[ "key03" ].is_defined() && config_json[ "key03" ].is_object() ) {

        std::cout << "e[ \"key03\" ][ \"1\" ] = " << config_json[ "key03" ][ "1" ].to_string() << std::endl;

      }

      input_stream_config_file.close();

    }
    */

    // std::stringstream ss = std::stringstream(std::string(
    // 	"[123, {"                                    LF
    // 	"a : \"あいう\\\\n\\tえお\", "                 LF
    // 	"  \t b : true, "                            LF
    // 	"     c : null, "                            LF
    // 	" /* start comment ..."                      LF
    // 	"     x : here is in block comment"          LF
    // 	"                  ... end comment */"       LF
    // 	"\"d\\u0001\" : false, "                     LF
    // 	"   // e is a test integer."                 LF
    // 	"   // f is a test floating."                LF
    // 	"e : 1234567890123456789, "                  LF
    // 	"f : -123.4567e+89, "	                     LF
    // 	"}  ]"));

    // std::cout << "input json: " << std::endl;
    // std::cout << ss.str() << std::endl;

    // std::cout << "parsed json:" << std::endl;
    // nanojson::element e = nanojson::element::from_string(ss.str());
    // std::cout << e.to_json_string() << std::endl;

    // std::cout << "values:" << std::endl;
    // if (e[1]["a"].is_defined()) { std::cout << "e[1][\"a\"] = " << e[1]["a"].to_string() << std::endl; }
    // if (e[1]["f"].is_defined()) { std::cout << "e[1][\"f\"] = " << e[1]["f"].to_string() << std::endl; }
    // if (e[1]["x"].is_defined()) { std::cout << "e[1][\"x\"] = " << e[1]["x"].to_string() << std::endl; }

    // std::cout << "e.size() = " << e.size() << std::endl;
    // if (e[1].is_defined()) { std::cout << "e[1].size() = " << e[1].size() << std::endl; }
    // if (e[1]["a"].is_defined()) { std::cout << "e[1][\"a\"].size() = " << e[1]["a"].size() << std::endl; }

    // std::cout << "input test json:" << std::endl;
    // try {
    // 	std::cin >> e;
    // }
    // catch (nanojson::nanojson_exception &)
    // {
    // 	std::cout << "il-formed json data." << std::endl;
    // 	e = nanojson::element::undefined();
    // }
    // std::cout << "parsed json:" << std::endl;
    // std::cout << e << std::endl;

    return 0;

}


/*
void process_a( soci::transaction * trans )
{
  soci::transaction * transaction_ = trans;

  bool is_local_transaction = false;

  try
  {
      if ( transaction_->is_active() == false ) //The transaction is not alive
      {
          transaction_ = new soci::transaction( trans.current_session() ); //Generate new one

          is_local_transaction = true;
      }

      //Process data in db

      //...

      if ( is_local_transaction == true ) //Only apply if is local transaction
      {
          transaction_->commit(); //Apply the local transaction
      }
  }
  catch ( ... )
  {
      if ( transaction_->is_active() &&  //We save another nested try / catch
           is_local_transaction == true )
      {
          transaction_->rollback();
      }
  }

  if ( is_local_transaction )
  {
      delete transaction_;
  }
}

void process_b( soci::transaction * trans )
{
  soci::transaction * transaction_ = trans;

  bool is_local_transaction = false;

  try
  {
      if ( transaction_->is_active() == false ) //The transaction is not alive
      {
          transaction_ = new soci::transaction( trans->current_session() ); //Generate new one

          is_local_transaction = true;
      }

      //Process data in db

      process_a( transaction_ ); //Pass the transaction. But process_a not apply the transaction because is still alive

      //More db stuff

      //...

      if ( is_local_transaction == true ) //Only apply if is local transaction
      {
          transaction_->commit(); //Apply the local transaction
      }
  }
  catch ( ... )
  {
      if ( transaction_->is_active() &&  //We save another nested try / catch
           is_local_transaction == true )
      {
          transaction_->rollback();
      }
  }

  if ( is_local_transaction )
  {
      delete transaction_;
  }
}

int main( int argv, char *argc[] ) {

  soci::session db_connection = ...;

  soci::transaction trans( db_connection );

  //process_a not apply the transaction, is not local created
  process_a( &trans );

  trans->commit(); //Now the transaction is not active

  //Still work. process_a generate a local transaction by self,
  //and apply your local generated transaction
  process_a( &trans );

  //Still work. process_b generate a local transaction by self,
  //and pass to nested call in process_a, but process_a not apply that.
  //process_b must apply your local generated transaction
  process_b( &trans );

}

*/
