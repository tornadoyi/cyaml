#include "cyaml/cyaml.h"
#include "cyaml/internal/yaml.h"



namespace cyaml {

Document::Document(){
  d_ = new yaml_document_t();
}

Document::~Document(){
  yaml_document_delete(d_);
  delete(d_);
  d_ = nullptr;
}

Node Document::root() const {
  auto* n = yaml_document_get_root_node(d_);
  if(!n) {
    throw cyaml_error("get root failed");
  }
  return Node(d_, n);
}


}