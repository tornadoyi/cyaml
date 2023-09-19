#include "cyaml/cyaml.h"
#include "cyaml/internal/yaml.h"



namespace cyaml {

Node::Node(yaml_document_s* d, yaml_node_s* n)
: d_(d), n_(n) {
}

bool Node::empty() const { return n_->type == YAML_NO_NODE; }

bool Node::is_scalar() const { return n_->type == YAML_SCALAR_NODE; }

bool Node::is_sequence() const { return n_->type == YAML_SEQUENCE_NODE; }

bool Node::is_mapping() const { return n_->type == YAML_MAPPING_NODE; }

template<>
int Node::as<int>() const {
  return 0;
}

}