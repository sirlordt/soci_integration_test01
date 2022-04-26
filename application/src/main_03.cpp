#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>

#include <soci/soci.h>

#include <nanojson/nanojson.hpp>

#include <uuid_v4/uuid_v4.h>

#include "modules/common/common.hpp"

nanojson::element config_json;

int main( int argc, char *argv[] ) {

    const char *path = argv[ 0 ];

    std::cout << "Current path: " << path << std::endl;

    //split_filename( path );

    const std::string config_file_path = common::get_file_path( path ) + "config/main.json";

    std::cout << "Config File: " << config_file_path << std::endl;

    config_json = common::get_config( config_file_path );

    if ( config_json[ "endpoints_base_path" ].is_defined() )
    {
        std::cout << "config_json[ \"endpoints_base_path\" ] = " << config_json[ "endpoints_base_path" ].to_string() << std::endl;
    }

    if ( config_json[ "database" ][ "main" ].is_defined() )
    {

        auto database_main_config = config_json[ "database" ][ "main" ];

        std::cout << "config_json[ \"driver\" ] = " << database_main_config[ "driver" ].to_string() << std::endl;

        std::shared_ptr<soci::session> db_connection = common::make_db_connection( database_main_config );

        soci::transaction * transaction1 = db_connection->begin(); //( db_connection );

        //process_a not apply the transaction, is not local created
        common::process_a( transaction1 );

        transaction1->commit(); //Now the transaction is not active

        if ( transaction1 == db_connection->begin() ) {

          //Still work. process_a generate a local transaction by self,
          //and apply your local generated transaction
          common::process_a( transaction1 );

          //Still work. process_b generate a local transaction by self,
          //and pass to nested call in process_a, but process_a not apply that.
          //process_b must apply your local generated transaction
          common::process_b( transaction1 );

        }

        delete transaction1;

        soci::transaction transaction2 { *db_connection }; //( db_connection );

        common::process_c( &transaction2 );

        if ( &transaction2 == db_connection->current_transaction() ) {

            common::process_c( db_connection->current_transaction() );

            if ( &transaction2 == db_connection->begin() ) {

                common::process_c( db_connection->begin() );

            }

        }

        transaction2.rollback();

        if ( &transaction2 == db_connection->begin() &&
             db_connection->current_transaction()->by_session() == false ) {

            common::process_c( db_connection->begin() );

        }

        transaction2.rollback();

    }

}
