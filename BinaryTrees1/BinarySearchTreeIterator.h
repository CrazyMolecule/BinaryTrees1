#ifndef BINARY_SEARCH_TREE_ITERATOR_H
#define BINARY_SEARCH_TREE_ITERATOR_H
#include "BinarySearchTreeNode.h"
#include <iterator>

namespace bavykin
{
  template < class T, bool isConst = false >
  class BinarySearchTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    using Node = BinarySearchTreeNode< T >;
    using iterator = BinarySearchTreeIterator< T, isConst >;
    using returntypePtr_t = std::conditional_t< isConst, const T*, T* >;
    using returntype_t = std::conditional< isConst, const T, T >;

    BinarySearchTreeIterator();
    BinarySearchTreeIterator(const BinarySearchTreeIterator& right);
    BinarySearchTreeIterator(Node* value);
    ~BinarySearchTreeIterator() = default;
    BinarySearchTreeIterator& operator=(const BinarySearchTreeIterator& value);
    bool operator==(const iterator& right) const;
    bool operator!=(const iterator& right) const;
    returntype_t& operator*() const;
    returntypePtr_t operator->() const;
    BinarySearchTreeIterator& operator++();
    const BinarySearchTreeIterator operator++(int);
    BinarySearchTreeIterator& operator--();
    const BinarySearchTreeIterator operator--(int);

    Node* m_Current;
  };

  template < class T, bool isConst >
  BinarySearchTreeIterator< T, isConst >::BinarySearchTreeIterator(): m_Current(nullptr)
  {
  }

  template < class T, bool isConst >
  BinarySearchTreeIterator< T, isConst >::BinarySearchTreeIterator(const BinarySearchTreeIterator& right):
    m_Current(right.m_Current)
  {
  }

  template < class T, bool isConst >
  BinarySearchTreeIterator< T, isConst >::BinarySearchTreeIterator(Node* value): m_Current(value)
  {
  }

  template < class T, bool isConst >
  BinarySearchTreeIterator< T, isConst >& BinarySearchTreeIterator< T, isConst >::operator=(
    const BinarySearchTreeIterator& value)
  {
    m_Current = value.m_Current;

    return *this;
  }

  template < class T, bool isConst >
  bool BinarySearchTreeIterator< T, isConst >::operator==(const iterator& right) const
  {
    return m_Current == right.m_Current;
  }

    template < class T, bool isConst >
  bool BinarySearchTreeIterator< T, isConst >::operator!=(const iterator& right) const
  {
    return !(*this == right);
  }

  template < class T, bool isConst >
  typename BinarySearchTreeIterator< T, isConst >::returntype_t& BinarySearchTreeIterator< T, isConst >::operator*()
    const
  {
    return m_Current->m_Content;
  }

  template < class T, bool isConst >
  typename BinarySearchTreeIterator< T, isConst >::returntypePtr_t BinarySearchTreeIterator< T, isConst >::operator->()
    const
  {
    return new T(m_Current->m_Content);
  }

  template < class T, bool isConst >
  typename BinarySearchTreeIterator< T, isConst >& BinarySearchTreeIterator< T, isConst >::operator++()
  {
    Node* right = m_Current->m_Right;

    if (right == nullptr)
    {
      right = m_Current->m_Parent;
      Node* last = m_Current;

      while (right != nullptr && right->m_Right == last)
      {
        last = right;
        right = right->m_Parent;
      }
    }
    else
    {
      while (right->m_Left != nullptr)
      {
        right = right->m_Left;
      }
    }

    m_Current = right;

    return *this;
  }

  template < class T, bool isConst >
  const typename BinarySearchTreeIterator< T, isConst > BinarySearchTreeIterator< T, isConst >::operator++(int)
  {
    iterator copy(*this);
    ++(*this);
    return copy;
  }

  template < class T, bool isConst >
  typename BinarySearchTreeIterator< T, isConst >& BinarySearchTreeIterator< T, isConst >::operator--()
  {
    Node* left = m_Current->m_Left;

    if (left == nullptr)
    {
      left = m_Current->m_Parent;
      Node* last = m_Current;

      while (left != nullptr && left->m_Left == last)
      {
        last = left;
        left = left->m_Parent;
      }
    }
    else
    {
      while (left->m_Right != nullptr)
      {
        left = left->m_Right;
      }
    }

    m_Current = left;

    return *this;
  }

  template < class T, bool isConst >
  const typename BinarySearchTreeIterator< T, isConst > BinarySearchTreeIterator< T, isConst >::operator--(int)
  {
    iterator copy(*this);
    --(*this);
    return copy;
  }
}

#endif
