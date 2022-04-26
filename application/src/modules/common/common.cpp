
#include "common.hpp"

namespace common {

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

std::shared_ptr<soci::session> make_db_connection( nanojson::element database_main_config )
{

  std::shared_ptr<soci::session> result { nullptr };

  try
  {

    const std::string& driver = database_main_config[ "driver" ].to_string();

    std::ostringstream connectionString;

    connectionString << "db=" + database_main_config[ "database" ].to_string();

    connectionString << " user=" + database_main_config[ "user" ].to_string();

    connectionString << " password='" + database_main_config[ "password" ].to_string() << "'";

    connectionString << " host=" + database_main_config[ "host" ].to_string();

    if ( driver == "mysql" )
    {

      result = std::make_shared<soci::session>( soci::mysql, connectionString.str() );

    }

  }
  catch ( const std::exception& ex )
  {

    std::cout << "Exception: " << ex.what() << std::endl;

  }

  return result;

}

void process_a( soci::transaction * transaction )
{
  soci::transaction * transaction_ = transaction;

  bool is_local_transaction = false;

  try
  {

    if ( transaction_->is_active() == false ) //The transaction is not active
    {

      //transaction_ = new soci::transaction( transaction->current_session() ); //Generate new one
      //soci::session * current_session = transaction->current_session();

      transaction_ = transaction->current_session().begin(); //Generate new one

      // auto x = transaction->status();
      // auto y = transaction->by_session();

      is_local_transaction = true;

    }

    //Process data in db
    UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;

    //...
    std::string id = uuid_generator.getUUID().str();
    std::string first_name = "Process A1";
    std::string last_name = "Process A2";

    soci::statement st = ( transaction_->current_session().prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

    st.execute();

    if ( is_local_transaction == true ) //Only apply if is local transaction
    {

      transaction_->commit(); //Apply the local transaction

    }

  }
  catch ( const std::exception& ex )
  {

    std::cout << "Exception: " << ex.what() << std::endl;

    if ( transaction_->is_active() &&  //We save another nested try / catch
         is_local_transaction == true )
    {

      transaction_->rollback();

    }

  }

  // if ( is_local_transaction )
  // {
  //     delete transaction_;
  // }
}

void process_b( soci::transaction * transaction )
{

  soci::transaction * transaction_ = transaction;

  bool is_local_transaction = false;

  try
  {

    if ( transaction_->is_active() == false ) //The transaction is not active
    {

      //transaction_ = new soci::transaction( transaction->current_session() ); //Generate new one
      transaction_ = transaction->current_session().begin(); //Generate new one

      is_local_transaction = true;

    }

    UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;

    //Process data in db
    std::string id = uuid_generator.getUUID().str();
    std::string first_name = "Process B1";
    std::string last_name = "Process B2";

    soci::statement st = ( transaction_->current_session().prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

    st.execute();

    process_a( transaction_ ); //Pass the transaction. But process_a not apply the transaction because is still alive

    //More db stuff

    if ( transaction_->is_active() ) {

      id = uuid_generator.getUUID().str();
      first_name = "Process B3";
      last_name = "Process B4";

      st = ( transaction_->current_session().prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

      st.execute();

    }

    if ( is_local_transaction == true ) //Only apply if is local transaction
    {

      transaction_->commit(); //Apply the local transaction

    }

  }
  catch ( const std::exception& ex )
  {

    std::cout << "Exception: " << ex.what() << std::endl;

    if ( transaction_->is_active() &&  //We save another nested try / catch
         is_local_transaction == true )
    {

      transaction_->rollback();

    }

  }

  // if ( is_local_transaction )
  // {
  //     delete transaction_;
  // }
}

void process_c( soci::transaction * transaction )
{

  soci::transaction * transaction_ = transaction;

  bool is_local_transaction = false;

  try
  {

    if ( transaction_->is_active() == false ) //The transaction is not active
    {

      //transaction_ = new soci::transaction( transaction->current_session() ); //Generate new one
      transaction_ = transaction->current_session().begin(); //Generate new one

      is_local_transaction = true;

    }

    UUIDv4::UUIDGenerator<std::mt19937_64> uuid_generator;

    //Process data in db
    std::string id = uuid_generator.getUUID().str();
    std::string first_name = "Process C1";
    std::string last_name = "Process C2";

    soci::statement st = ( transaction_->current_session().prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

    st.execute();

    process_b( transaction_ ); //Pass the transaction. But process_a not apply the transaction because is still alive

    //More db stuff

    if ( transaction_->is_active() ) {

      id = uuid_generator.getUUID().str();
      first_name = "Process C3";
      last_name = "Process C4";

      st = ( transaction_->current_session().prepare << "Insert Into sysPerson(Id,FirstName,LastName) Values(:Id,:FirstName,:LastName)", soci::use( id ), soci::use( first_name ), soci::use( last_name ) );

      st.execute();

    }

    if ( is_local_transaction == true ) //Only apply if is local transaction
    {

      transaction_->commit(); //Apply the local transaction

    }

  }
  catch ( const std::exception& ex )
  {

    std::cout << "Exception: " << ex.what() << std::endl;

    if ( transaction_->is_active() &&  //We save another nested try / catch
         is_local_transaction == true )
    {

      transaction_->rollback();

    }

  }

  // if ( is_local_transaction )
  // {
  //     delete transaction_;
  // }
}

}
