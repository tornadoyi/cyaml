#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

struct  yaml_node_s;
struct  yaml_document_s;


namespace cyaml {

class cyaml_error : public std::runtime_error {
public:
  cyaml_error(const std::string& what_arg) : std::runtime_error(what_arg){}
  cyaml_error(const char* what_arg ) : std::runtime_error(what_arg){}
};


struct Node {
 public:
  static const Node empty_node;

  template<class T, typename VectorIterator, typename MapIterator>
  struct _Iterator {
   public:
    enum class Type { Empty = 0, Sequence, Mapping };

    typedef _Iterator<T, VectorIterator, MapIterator> Self;

    _Iterator() { type_ = Type::Empty; }

    _Iterator(const VectorIterator& v_it) { type_ = Type::Sequence; v_it_ = v_it; }

    _Iterator(const MapIterator& m_it) { type_ = Type::Mapping; m_it_ = m_it; }

    _Iterator(const _Iterator& other) 
    : type_(other.type_) 
    , v_it_(other.v_it_)
    , m_it_(other.m_it_) {
    }

    const T& operator*() {
      switch(type_) {
        case Type::Empty: { throw cyaml_error("sequence iterator only function *, current empty"); }
        case Type::Sequence: { return *(*v_it_); }
        case Type::Mapping: { throw cyaml_error("sequence iterator only function *, current mapping"); }
        default:
          throw cyaml_error("invalid iterator type " + std::to_string(int(type_)));
      }
    }

    MapIterator operator->(){
      switch(type_) {
        case Type::Empty: { throw cyaml_error("mapping iterator only function ->, current empty"); }
        case Type::Sequence: { throw cyaml_error("mapping iterator only function ->, current sequence"); }
        case Type::Mapping: { return m_it_; }
        default:
          throw cyaml_error("invalid iterator type " + std::to_string(int(type_)));
      }
    }

    Self& operator++() {
      switch(type_) {
        case Type::Empty: { throw cyaml_error("sequence or mapping iterator only function ->, current empty"); }
        case Type::Sequence: { ++v_it_; break; }
        case Type::Mapping: { ++m_it_; break; }
        default:
          throw cyaml_error("invalid iterator type " + std::to_string(int(type_)));
      }
      return *this;
    }

    Self operator++(int) {
      Self tmp(*this);
      ++(*this);
      return tmp;
    }

    Self& operator--() {
      switch(type_) {
        case Type::Empty: { throw cyaml_error("sequence or mapping iterator only function ->, current empty"); }
        case Type::Sequence: { --v_it_; break; }
        case Type::Mapping: { --m_it_; break; }
        default:
          throw cyaml_error("invalid iterator type " + std::to_string(int(type_)));
      }
      return *this;
    }

    Self operator--(int) {
      Self tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const _Iterator& other) {
      switch(type_) {
        case Type::Empty: { return other.type_ == Type::Empty; }
        case Type::Sequence: { return v_it_ == other.v_it_; }
        case Type::Mapping: { return m_it_ == other.m_it_; }
        default:
          throw cyaml_error("invalid iterator type " + std::to_string(int(type_)));
      }
    }

    bool operator!=(const _Iterator& other) {
      return !operator==(other);
    }
    Self operator=(const _Iterator& other) {
      type_ = other.type_;
      v_it_ = other.v_it_;
      m_it_ = other.m_it_;
      return *this;
    }

   protected:
    Type type_;
    VectorIterator v_it_;
    MapIterator m_it_;
  };

  typedef _Iterator<Node, typename std::vector<Node*>::iterator, typename std::unordered_map<std::string, Node*>::iterator>  iterator;
  typedef _Iterator<Node, typename std::vector<Node*>::const_iterator,  typename std::unordered_map<std::string, Node*>::const_iterator> const_iterator;

 public:
  enum class Type { Empty = 0, Scalar, Sequence, Mapping };

  Node();

  Node(yaml_document_s* d, yaml_node_s* n);

  ~Node() { reset(nullptr, nullptr); }

  Node(const Node&) = delete;

  Node &operator = (const Node&) = delete;

  void reset(yaml_document_s* d, yaml_node_s* n);

  Type type() const { return type_; }

  bool defined() const { return type_ != Type::Empty; }

  bool empty() const { return type_ == Type::Empty; }

  bool is_scalar() const { return type_ == Type::Scalar; }

  bool is_sequence() const { return type_ == Type::Sequence; }

  bool is_mapping() const { return type_ == Type::Mapping; }

  const Node& operator[](size_t index) ;

  const Node& operator[](const std::string& key) ;

  const Node& operator[](size_t index) const;

  const Node& operator[](const std::string& key) const;

  size_t size() const;

  iterator begin();

  const_iterator begin() const;

  iterator end();

  const_iterator end() const;

  const std::vector<std::string>& keys();

  template<typename T>
  T as() const;

  template<typename T>
  T as(const T&) const;

 protected:
  Type type_;
  std::string scalar_;
  std::vector<Node*> sequence_;
  std::unordered_map<std::string, Node*> mapping_; 
  std::vector<std::string> keys_;
};


struct Document {

 public:
  struct ParsedResult {
    bool success;
    std::string error;
    size_t line;
    size_t column;
  };
  

  Document();

  ~Document();

  Document(const Document&) = delete;

  Document &operator = (const Document&) = delete;

  ParsedResult parse(const std::string& input);

  Node& root() { return *root_; }

 protected:
  Node* root_;
};

}