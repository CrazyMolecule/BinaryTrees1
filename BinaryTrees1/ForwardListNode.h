#ifndef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H
#include <memory>

template< typename T >
struct ListNode
{
  T m_Data;
  std::shared_ptr< ListNode > m_PointerNext;

  ListNode(const T& data = T(), std::shared_ptr< ListNode > pNext = nullptr) : m_Data(data), m_PointerNext(pNext) {}
};
#endif
