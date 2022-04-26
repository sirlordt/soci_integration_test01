#pragma once

#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>

#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include <nanojson/nanojson.hpp>

#include <uuid_v4/uuid_v4.h>

namespace common {

const std::string get_file_path( const std::string& file );
std::stringstream read_text_file_content( const std::string& path_file_to_read );
nanojson::element get_config( const std::string& config_path_file );

std::shared_ptr<soci::session> make_db_connection( nanojson::element config_json );

void process_a( soci::transaction * transaction );
void process_b( soci::transaction * transaction );
void process_c( soci::transaction * transaction );

}
