#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H
#include "ForwardListNode.h"
#include <cassert>
#include <memory>

template < class T, bool isConst = false >
class ListIterator : public std::iterator< std::forward_iterator_tag, T >
{
public:
  using Node = ListNode< T >;
  using Iterator = ListIterator< T, isConst >;
  using returntypePtr_t = std::conditional_t< isConst, std::shared_ptr< const T >, std::shared_ptr< T > >;
  using returntype_t = std::conditional_t< isConst, const T, T >;

  ListIterator();
  ListIterator(std::shared_ptr< Node > pointer);
  ListIterator(const Iterator&) = default;
  Iterator& operator=(const Iterator&) = default;
  bool operator==(const Iterator&) const;
  bool operator!=(const Iterator&) const;
  returntype_t operator*() const;
  returntypePtr_t operator->() const;
  Iterator& operator++();
  Iterator operator++(int);

private:
  std::shared_ptr< Node > m_Current;
};

template < class T, bool isConst >
ListIterator< T, isConst >::ListIterator() : m_Current(nullptr) {}

template < class T, bool isConst >
ListIterator< T, isConst >::ListIterator(std::shared_ptr< Node > pointer) : m_Current(pointer) {}

template < class T, bool isConst >
bool ListIterator< T, isConst >::operator==(const ListIterator< T, isConst >& other) const
{
  return m_Current == other.m_Current;
}

template < class T, bool isConst >
bool ListIterator< T, isConst >::operator!=(const ListIterator< T, isConst >& other) const
{
  return !(*this == other);
}

template < class T, bool isConst >
typename ListIterator< T, isConst >::returntype_t ListIterator< T, isConst >::operator*() const
{
  assert(m_Current != nullptr);
  return m_Current->m_Data;
}

template < class T, bool isConst >
typename ListIterator< T, isConst >::returntypePtr_t ListIterator< T, isConst >::operator->() const
{
  assert(m_Current != nullptr);
  return std::make_shared< T >(m_Current->m_Data);
}

template < class T, bool isConst >
ListIterator< T, isConst >& ListIterator< T, isConst >::operator++()
{
  assert(m_Current != nullptr);
  m_Current = m_Current->m_PointerNext;
  return *this;
}

template < class T, bool isConst >
ListIterator< T, isConst > ListIterator< T, isConst >::operator++(int)
{
  ListIterator< T, isConst > temp(*this);
  operator++();
  return temp;
}
#endif
