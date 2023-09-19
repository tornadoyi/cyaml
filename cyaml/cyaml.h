#pragma once

#include <stdexcept>

struct yaml_node_s;
struct yaml_document_s;
struct yaml_parser_s;

namespace cyaml {

class cyaml_error : public std::runtime_error {
public:
  cyaml_error(const std::string& what_arg) : std::runtime_error(what_arg){}
  cyaml_error(const std::string&& what_arg) : std::runtime_error(what_arg){}
  cyaml_error(const char* what_arg ) : std::runtime_error(what_arg){}
};


struct Node {
 public:
  Node(yaml_document_s* d, yaml_node_s* n);

  ~Node() = default;

  bool empty() const;

  bool is_scalar() const;

  bool is_sequence() const;

  bool is_mapping() const;

  const Node operator[](size_t index) const;

  const Node operator[](const std::string& key) const;

  template<typename T>
  T as() const;

 protected:
  yaml_node_s* n_;
  yaml_document_s* d_;
};


struct Document {

 public:
  Document();

  ~Document();

  Node root() const;

 protected:
  yaml_document_s* d_;

 friend struct Parser;
};


struct Parser {

 public:
  Parser();

  ~Parser();

  bool parse(const std::string& input, Document& doc);

  const char* error() const;

  size_t error_line() const;

  size_t error_column() const;
  

 protected:
  yaml_parser_s* p_;
};


}