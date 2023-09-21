#include "cyaml/cyaml.h"
#include "cyaml/internal/yaml.h"



namespace cyaml {

const Node Node::empty_node(nullptr, nullptr);


#define ASSERT_TYPE(T) if(!is_##T()) { throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: " + "##T"); }

Node::Node() : type_(Type::Empty){}

Node::Node(yaml_document_s* d, yaml_node_s* n) {
  reset(d, n);
}

void Node::reset(yaml_document_s* d, yaml_node_s* n) {
  // clean
  for(auto* node : sequence_) { delete(node); }
  sequence_.clear();
  for(auto&& [_, node] : mapping_) { delete(node); }
  mapping_.clear();

  // empty
  if(!d || !n) {
    type_ = Type::Empty;
    return;
  }

  switch(n->type) {
    case YAML_NO_NODE: {
      type_ = Type::Empty;
      break;
    }
    case YAML_SCALAR_NODE: {
      type_ = Type::Scalar;
      scalar_.assign((const char*)n->data.scalar.value, n->data.scalar.length);
      break;
    }
    case YAML_SEQUENCE_NODE: {
      type_ = Type::Sequence;
      yaml_node_item_t *i_n;
      sequence_.reserve(n->data.sequence.items.top - n->data.sequence.items.start + 1);
      for (i_n = n->data.sequence.items.start; i_n < n->data.sequence.items.top; i_n++) {
        if(yaml_node_t* next_n = yaml_document_get_node(d, *i_n)) {
          sequence_.push_back(new Node(d, next_n));
        }
      }
      break;
    }
    case YAML_MAPPING_NODE: {
      type_ = Type::Mapping;
      yaml_node_pair_t *i_p;
      for (i_p = n->data.mapping.pairs.start; i_p < n->data.mapping.pairs.top; i_p++) {
        std::string key;
        
        if(yaml_node_t* key_n = yaml_document_get_node(d, i_p->key)) {
          key.assign((const char*)key_n->data.scalar.value, key_n->data.scalar.length);
        } else {
          throw cyaml_error("missing key for mapping node");
        }
        if(yaml_node_t* val_n = yaml_document_get_node(d, i_p->value)) {
          mapping_[key] = new Node(d, val_n);
          keys_.push_back(key);
        } else {
          throw cyaml_error("missing value for mapping node");
        }
      }
      break;
    }
    default:
      throw cyaml_error("invalid type " + std::to_string(int(n->type)));
  }
}


const Node& Node::operator[](size_t index)  {
  ASSERT_TYPE(sequence);
  if(index >= sequence_.size()) {
    return empty_node;
  }
  return *sequence_[index];
}

const Node& Node::operator[](const std::string& key) {
  ASSERT_TYPE(mapping);
  auto it = mapping_.find(key);
  if(it == mapping_.end()) {
    return empty_node;
  }
  return *it->second;
}

const Node& Node::operator[](size_t index) const {
  ASSERT_TYPE(sequence);
  if(index >= sequence_.size()) {
    return empty_node;
  }
  return *sequence_[index];
}

const Node& Node::operator[](const std::string& key) const {
  ASSERT_TYPE(mapping);
  auto it = mapping_.find(key);
  if(it == mapping_.end()) {
    return empty_node;
  }
  return *it->second;
}

size_t Node::size() const {
  switch (type_) {
  case Type::Sequence: { return sequence_.size(); }
  case Type::Mapping: { return mapping_.size(); }
  case Type::Empty:
  case Type::Scalar:
  default:
    throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
  }
  throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
}

Node::iterator Node::begin() {
  switch (type_) {
  case Type::Sequence: { return iterator(sequence_.begin()); }
  case Type::Mapping: { return iterator(mapping_.begin()); }
  case Type::Empty:
  case Type::Scalar:
  default:
    throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
  }
  throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
}

Node::const_iterator Node::begin() const {
  switch (type_) {
  case Type::Sequence: { return const_iterator(sequence_.begin()); }
  case Type::Mapping: { return const_iterator(mapping_.begin()); }
  case Type::Empty:
  case Type::Scalar:
  default:
    throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
  }
  throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
}

Node::iterator Node::end() {
  switch (type_) {
  case Type::Sequence: { return iterator(sequence_.end()); }
  case Type::Mapping: { return iterator(mapping_.end()); }
  case Type::Empty:
  case Type::Scalar:
  default:
    throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
  }
  throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
}

Node::const_iterator Node::end() const {
  switch (type_) {
  case Type::Sequence: { return const_iterator(sequence_.end()); }
  case Type::Mapping: { return const_iterator(mapping_.end()); }
  case Type::Empty:
  case Type::Scalar:
  default:
    throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
  }
  throw cyaml_error("node type is" + std::to_string(int(type_)) + " expected: sequence, mapping");
}

const std::vector<std::string>& Node::keys() {
  ASSERT_TYPE(mapping);
  return keys_;
}


#define AS(F)  ASSERT_TYPE(scalar); return F(scalar_);

template<>
std::string Node::as<std::string>() const { ASSERT_TYPE(scalar); return scalar_; }

template<>
int Node::as<int>() const { AS(std::stoi); }

template<>
long Node::as<long>() const { AS(std::stol); }

template<>
unsigned long Node::as<unsigned long>() const { AS(std::stoul); }

template<>
long long Node::as<long long>() const { AS(std::stoll); }

template<>
unsigned long long Node::as<unsigned long long>() const { AS(std::stoull); }

template<>
float Node::as<float>() const { AS(std::stof); }

template<>
double Node::as<double>() const { AS(std::stod); }

template<>
long double Node::as<long double>() const { AS(std::stold); }

template<>
bool Node::as<bool>() const {
  ASSERT_TYPE(scalar);
  if(scalar_ == "true") return true;
  if(scalar_ == "false") return false;
  throw cyaml_error("type error, expected bool, scalar: " + scalar_);
}

#undef AS


#define AS_DFT(F, V)  if(empty()) { return V; }; ASSERT_TYPE(scalar); return F(scalar_);

template<>
std::string Node::as<std::string>(const std::string& v) const { if(empty()) { return v; }; ASSERT_TYPE(scalar); return scalar_; }

template<>
int Node::as<int>(const int& v) const { AS_DFT(std::stoi, v); }

template<>
long Node::as<long>(const long& v) const { AS_DFT(std::stol, v); }

template<>
unsigned long Node::as<unsigned long>(const unsigned long& v) const { AS_DFT(std::stoul, v); }

template<>
long long Node::as<long long>(const long long& v) const { AS_DFT(std::stoll, v); }

template<>
unsigned long long Node::as<unsigned long long>(const unsigned long long& v) const { AS_DFT(std::stoull, v); }

template<>
float Node::as<float>(const float& v) const { AS_DFT(std::stof, v); }

template<>
double Node::as<double>(const double& v) const { AS_DFT(std::stod, v); }

template<>
long double Node::as<long double>(const long double& v) const { AS_DFT(std::stold, v); }

template<>
bool Node::as<bool>(const bool& v) const {
  if(empty()) { return v; }
  ASSERT_TYPE(scalar);
  if(scalar_ == "true") return true;
  if(scalar_ == "false") return false;
  throw cyaml_error("type error, expected bool, scalar: " + scalar_);
}

#undef AS_DFT


#undef ASSERT_TYPE


}