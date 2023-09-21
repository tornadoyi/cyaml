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
    typedef _Iterator<T, VectorIterator, MapIterator> Self;

    _Iterator(const VectorIterator& v_it) { is_seq_ = true; v_it_ = v_it; }

    _Iterator(const MapIterator& m_it) { is_seq_ = false; m_it_ = m_it; }

    _Iterator(const _Iterator& other) 
    : is_seq_(other.is_seq_) 
    , v_it_(other.v_it_)
    , m_it_(other.m_it_) {
    }


    const T& operator*() {
      if(!is_seq_) { throw cyaml_error("only sequnence iterator can call *"); }
      return *(*v_it_);
    }

    MapIterator operator->(){
      if(is_seq_) { throw cyaml_error("only mapping iterator can call *"); }
      return m_it_;
    }

    Self& operator++() {
      if(is_seq_) { ++v_it_; } else { ++m_it_; }
      return *this;
    }

    Self operator++(int) {
      Self tmp(*this);
      ++(*this);
      return tmp;
    }

    Self& operator--() {
      if(is_seq_) { --v_it_; } else { --m_it_; }
      return *this;
    }

    Self operator--(int) {
      Self tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const _Iterator& other) {
      return is_seq_ ? v_it_ == other.v_it_ : m_it_ == other.m_it_;
    }

    bool operator!=(const _Iterator& other) {
      return !operator==(other);
    }
    Self operator=(const _Iterator& other) {
      is_seq_ = other.is_seq_;
      v_it_ = other.v_it_;
      m_it_ = other.m_it_;
      return *this;
    }

   protected:
    bool is_seq_;
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

  void reset(yaml_document_s* d, yaml_node_s* n);

  Type type() const { return type_; }

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
  

  Document() : root_(nullptr) {}

  ~Document() { delete(root_); root_ = nullptr; }

  ParsedResult parse(const std::string& input);

  Node& root() { return *root_; }

 protected:
  Node* root_;
};

}