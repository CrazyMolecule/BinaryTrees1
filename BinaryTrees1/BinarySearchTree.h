#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "BinarySearchTreeIterator.h"
#include "BinarySearchTreeNode.h"
#include <exception>

namespace bavykin
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class BinarySearchTree
  {
  public:
    using content_type = std::pair< Key, Value >;
    using Node = typename BinarySearchTreeNode< content_type >;
    using iterator = BinarySearchTreeIterator< content_type, false >;
    using const_iterator = BinarySearchTreeIterator< content_type, true >;

    BinarySearchTree();
    BinarySearchTree(Compare comp);
    BinarySearchTree(const BinarySearchTree< Key, Value, Compare >& right);
    ~BinarySearchTree();

    BinarySearchTree< Key, Value, Compare >& operator=(const BinarySearchTree< Key, Value, Compare >& right);
    Value& operator[](const Key& value);

    void insert(const content_type& value);
    void insert(const iterator& value);
    void insert(const Key& value);
    void erase(const iterator& value);
    void erase(const Key& value);
    void clear();
    bool empty() const;
    size_t size() const;
    iterator find(const Key& value) const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    Node* m_Root;
    Compare m_Comp;

    void addNode(Node* value);
    void deleteNode(Node* value);
    void linkNodes(Node* value);
    void linkNodesFromBottom(Node* linkedNode, Node* parent);
    void makeEmpty(Node* deleteFrom);
    Node* findTheLeftmost();
    Node* findTheLeftmost() const;
    size_t getHeight(Node* value) const;
    Node* rotateLeft(Node* value);
    Node* rotateRight(Node* value);
    Node* insert(Node* parentNode, Node* insertedNode);
    Node* erase(Node* parentNode, Node* erasedNode);
    Node* balanceByNode(Node* value);
  };

  template < class Key, class Value, class Compare = std::less< Key > >
  using BST = BinarySearchTree< Key, Value, Compare >;

  template < class Key, class Value, class Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(): m_Root(nullptr), m_Comp(Compare())
  {
  }

  template < class Key, class Value, class Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(Compare comp): m_Root(nullptr), m_Comp(comp)
  {
  }

  template < class Key, class Value, class Compare >
  BinarySearchTree< Key, Value, Compare >::BinarySearchTree(const BinarySearchTree< Key, Value, Compare >& right):
    m_Root(nullptr),
    m_Comp(right.m_Comp)
  {
    for (const_iterator i = right.cbegin(); i != right.cend(); ++i)
    {
      insert(i.m_Current->m_Content);
    }
  }

  template < class Key, class Value, class Compare >
  BinarySearchTree< Key, Value, Compare >::~BinarySearchTree()
  {
    makeEmpty(m_Root);
  }

  template < class Key, class Value, class Compare >
  BinarySearchTree< Key, Value, Compare >& BinarySearchTree< Key, Value, Compare >::operator=(
    const BinarySearchTree< Key, Value, Compare >& right)
  {
    clear();

    for (const_iterator i = right.cbegin(); i != right.cend(); ++i)
    {
      insert(i.m_Current->m_Content);
    }

    m_Comp = right.m_Comp;

    return *this;
  }

  template < class Key, class Value, class Compare >
  Value& BinarySearchTree< Key, Value, Compare >::operator[](const Key& value)
  {
    iterator foundedElement = find(value);

    if (foundedElement == end())
    {
      insert(value);
      foundedElement = find(value);
    }

    return foundedElement->second;
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::insert(const iterator& value)
  {
    insert(value.m_Current->m_Content);
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::insert(const content_type& value)
  {
    iterator searched = find(value.first);
    if (searched != nullptr)
    {
      searched.m_Current->m_Content.second = value.second;
    }
    else
    {
      addNode(new Node(value));

      linkNodes(m_Root->m_Left);
      linkNodes(m_Root->m_Right);
    }
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::insert(const Key& value)
  {
    if (find(value) != nullptr)
    {
      return;
    }

    insert({ value, Value() });
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::erase(const iterator& value)
  {
    deleteNode(value.m_Current);
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::erase(const Key& value)
  {
    iterator searched = find(value);

    if (searched != end())
    {
      erase(searched);
    }
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::clear()
  {
    makeEmpty(m_Root);

    m_Root = nullptr;
  }

  template < class Key, class Value, class Compare >
  bool BinarySearchTree< Key, Value, Compare >::empty() const
  {
    return m_Root == nullptr;
  }

  template < class Key, class Value, class Compare >
  size_t BinarySearchTree< Key, Value, Compare >::size() const
  {
    return getHeight(m_Root);
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator BinarySearchTree< Key, Value, Compare >::find(
    const Key& value) const
  {
    Node* iterable = m_Root;

    while (iterable != nullptr && iterable->m_Content.first != value)
    {
      iterable = m_Comp(iterable->m_Content.first, value) ? iterable->m_Right : iterable->m_Left;
    }

    return iterator(iterable);
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator BinarySearchTree< Key, Value, Compare >::begin()
  {
    return iterator(findTheLeftmost());
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::iterator BinarySearchTree< Key, Value, Compare >::end()
  {
    return iterator(nullptr);
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_iterator BinarySearchTree< Key, Value, Compare >::cbegin()
    const
  {
    return const_iterator(findTheLeftmost());
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::const_iterator BinarySearchTree< Key, Value, Compare >::cend() const
  {
    return const_iterator(nullptr);
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::addNode(Node* value)
  {
    m_Root = insert(m_Root, value);
    m_Root->m_Parent = nullptr;
    linkNodesFromBottom(value, m_Root);
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::deleteNode(Node* value)
  {
    m_Root = erase(m_Root, value);

    if (m_Root != nullptr)
    {
      m_Root->m_Parent = nullptr;
    }
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::linkNodes(Node* value)
  {
    if (value == nullptr)
    {
      return;
    }

    linkNodes(value->m_Left);
    linkNodes(value->m_Right);
    linkNodesFromBottom(value, m_Root);
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::linkNodesFromBottom(Node* linkedNode, Node* parent)
  {
    if (linkedNode == nullptr)
    {
      return;
    }

    if (parent == nullptr)
    {
      linkedNode->m_Parent = nullptr;
    }
    else if (parent->m_Left == linkedNode || parent->m_Right == linkedNode)
    {
      linkedNode->m_Parent = parent;
    }
    else
    {
      linkNodesFromBottom(linkedNode, parent->m_Left);
      linkNodesFromBottom(linkedNode, parent->m_Right);
    }
  }

  template < class Key, class Value, class Compare >
  void BinarySearchTree< Key, Value, Compare >::makeEmpty(Node* deleteFrom)
  {
    if (deleteFrom == nullptr)
    {
      return;
    }

    makeEmpty(deleteFrom->m_Left);
    makeEmpty(deleteFrom->m_Right);
    delete deleteFrom;
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::findTheLeftmost()
  {
    Node* founded = m_Root;

    while (founded->m_Left != nullptr && founded != nullptr)
    {
      founded = founded->m_Left;
    }

    return founded;
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::findTheLeftmost()
    const
  {
    Node* founded = m_Root;

    while (founded != nullptr && founded->m_Left != nullptr)
    {
      founded = founded->m_Left;
    }

    return founded;
  }

  template < class Key, class Value, class Compare >
  size_t BinarySearchTree< Key, Value, Compare >::getHeight(Node* value) const
  {
    if (value == nullptr)
    {
      return 0;
    }

    return std::max(getHeight(value->m_Left), getHeight(value->m_Right)) + 1;
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::rotateRight(
    Node* value)
  {
    Node* newNode = value->m_Left;
    value->m_Left = newNode->m_Right;
    newNode->m_Right = value;

    return newNode;
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::rotateLeft(
    Node* value)
  {
    Node* newNode = value->m_Right;
    value->m_Right = newNode->m_Left;
    newNode->m_Left = value;

    return newNode;
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::insert(
    Node* parentNode, Node* insertedNode)
  {
    if (parentNode == nullptr)
    {
      return insertedNode;
    }

    if (m_Comp(insertedNode->m_Content.first, parentNode->m_Content.first))
    {
      parentNode->m_Left = insert(parentNode->m_Left, insertedNode);
    }
    else
    {
      parentNode->m_Right = insert(parentNode->m_Right, insertedNode);
    }

    return balanceByNode(parentNode);
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::erase(
    Node* parentNode, Node* erasedNode)
  {
    if (erasedNode == nullptr)
    {
      throw std::logic_error("Node was nullptr");
    }

    if (parentNode == nullptr)
    {
      return nullptr;
    }

    if (m_Comp(erasedNode->m_Content.first, parentNode->m_Content.first))
    {
      parentNode->m_Left = erase(parentNode->m_Left, erasedNode);
    }

    else if (m_Comp(parentNode->m_Content.first, erasedNode->m_Content.first))
    {
      parentNode->m_Right = erase(parentNode->m_Right, erasedNode);
    }
    else
    {
      Node* right = parentNode->m_Right;

      if (parentNode->m_Right == nullptr)
      {
        Node* left = parentNode->m_Left;
        delete parentNode;
        parentNode = left;
      }
      else if (parentNode->m_Left == nullptr)
      {
        delete parentNode;
        parentNode = right;
      }
      else
      {
        while (right->m_Left != nullptr)
        {
          right = right->m_Left;
        }

        parentNode->m_Content = right->m_Content;
        parentNode->m_Right = erase(parentNode->m_Right, right);
      }
    }

    return balanceByNode(parentNode);
  }

  template < class Key, class Value, class Compare >
  typename BinarySearchTree< Key, Value, Compare >::Node* BinarySearchTree< Key, Value, Compare >::balanceByNode(
    Node* value)
  {
    if (value == nullptr)
    {
      return value;
    }

    int height = getHeight(value->m_Left) - getHeight(value->m_Right);

    if (height > 1)
    {
      if (getHeight(value->m_Left) >= getHeight(value->m_Right))
      {
        return rotateRight(value);
      }

      value->m_Left = rotateLeft(value->m_Left);
      return rotateRight(value);
    }

    if (height < -1)
    {
      if (getHeight(value->m_Right) >= getHeight(value->m_Left))
      {
        return rotateLeft(value);
      }

      value->m_Right = rotateRight(value->m_Right);
      return rotateLeft(value);
    }

    return value;
  }
}
#endif
