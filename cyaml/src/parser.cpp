#include "cyaml/cyaml.h"
#include "cyaml/internal/yaml.h"



namespace cyaml {

Parser::Parser(){
  p_ = new yaml_parser_t();
  if(!yaml_parser_initialize(p_)) {
    throw cyaml_error("parser initialize failed");
  }
}

Parser::~Parser(){
  yaml_parser_delete(p_);
  delete(p_);
  p_ = nullptr;
}

bool Parser::parse(const std::string& input, Document& doc) {
  yaml_parser_set_input_string(p_, (const unsigned char *)input.c_str(), input.size());
  return yaml_parser_load(p_, doc.d_);
}

const char* Parser::error() const {
  return p_->problem;
}

size_t Parser::error_line() const {
  return p_->context_mark.line;
}

size_t Parser::error_column() const {
  return p_->context_mark.column;
}

}