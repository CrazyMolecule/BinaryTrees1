#ifndef BINARY_SEARCH_TREE_NODE_H
#define BINARY_SEARCH_TREE_NODE_H

namespace bavykin
{
  template < class T >
  class BinarySearchTreeNode
  {
  public:
    using Node = BinarySearchTreeNode;

    BinarySearchTreeNode();
    BinarySearchTreeNode(const T& right);

    T m_Content;
    Node* m_Left;
    Node* m_Right;
    Node* m_Parent;
  };

  template < class T >
  BinarySearchTreeNode< T >::BinarySearchTreeNode(): m_Left(nullptr), m_Right(nullptr), m_Parent(nullptr)
  {
  }

  template < class T >
  BinarySearchTreeNode< T >::BinarySearchTreeNode(const T& right):
    m_Content(right),
    m_Left(nullptr),
    m_Right(nullptr),
    m_Parent(nullptr)
  {
  }
}
#endif
