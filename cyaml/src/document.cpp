#include "cyaml/cyaml.h"
#include "cyaml/internal/yaml.h"



namespace cyaml {


Document::ParsedResult Document::parse(const std::string& input) {
  // initialize
  yaml_parser_t parser;
  if(!yaml_parser_initialize(&parser)) {
    throw cyaml_error("parser initialize failed");
  }

  // parse
  yaml_document_t document;
  yaml_parser_set_input_string(&parser, (const unsigned char *)input.c_str(), input.size());
  if(!yaml_parser_load(&parser, &document)) {
    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    return ParsedResult{
      false, parser.problem, 
      parser.context_mark.line, parser.context_mark.column
    };
  }

  // parse to root
  yaml_node_t* r_node = yaml_document_get_root_node(&document);
  if(!r_node) {
    throw cyaml_error("get root failed");
  }
  root_ = new Node(&document, r_node);

  yaml_document_delete(&document);
  yaml_parser_delete(&parser);

  return ParsedResult{true, "", 0, 0};
}


}