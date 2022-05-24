#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "BinarySearchTree.h"

#include <stdexcept>
#include <utility>

namespace bavykin
{
  template < typename K, typename V, typename Cmp = std::less< K > >
  class Dictionary
  {
  public:
    using iterator = typename BST< K, V, Cmp >::iterator;
    using const_iterator = typename BST< K, V, Cmp >::const_iterator;

    Dictionary(const std::string& name = "dictionary");
    Dictionary(const Dictionary& right);

    Dictionary& operator=(const Dictionary& right);
    V operator[](const K& key);
    template < typename Key, typename Val, typename Comp >
    friend std::ostream& operator<<(std::ostream& out, const Dictionary< Key, Val, Comp >& value);

    size_t size() const noexcept;
    void insert(const K& key, const V& value);
    void insert(const iterator&);
    iterator find(const K& key);
    bool contains(const K& key) const;
    void erase(const K& key);

    void changeName(const std::string& name);

    Dictionary getUnion(const Dictionary& right);
    Dictionary getIntersect(const Dictionary& right);
    Dictionary getComplement(const Dictionary& right);

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    BST< K, V, Cmp > m_Data;
    std::string m_Name;
  };
  template < typename K, typename V, typename Cmp = std::less< K > >
  using dictionary = Dictionary< K, V, Cmp >;

  template < typename Key, typename Val, typename Comp >
  std::ostream& operator<<(std::ostream& out, const Dictionary< Key, Val, Comp >& value)
  {
    if (value.size() == 0)
    {
      out << "<EMPTY>";
      return out;
    }

    out << value.m_Name;
    for (auto i = value.cbegin(); i != value.cend(); i++)
    {
      out << " " << i.m_Current->m_Content.first;
      out << " " << i.m_Current->m_Content.second;
    }

    return out;
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >::Dictionary(const std::string& name)
  {
    m_Data = BST< K, V, Cmp >();
    m_Name = name;
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >::Dictionary(const Dictionary& right)
  {
    m_Data = right.m_Data;
    m_Name = right.m_Name;
  }

  template < typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::changeName(const std::string& name)
  {
    m_Name = name;
  }

  template < typename K, typename V, typename Cmp >
  size_t Dictionary< K, V, Cmp >::size() const noexcept
  {
    return m_Data.size();
  }

  template < typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::insert(const K& key, const V& value)
  {
    m_Data.insert(std::make_pair(key, value));
  }

  template < typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::insert(const iterator& iter)
  {
    m_Data.insert(iter);
  }

  template < typename K, typename V, typename Cmp >
  bool Dictionary< K, V, Cmp >::contains(const K& key) const
  {
    if (m_Data.find(key) != nullptr)
    {
      return true;
    }

    return false;
  }

  template < typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::find(const K& key)
  {
    iterator searched = m_Data.find(key);

    if (searched != m_Data.end())
    {
      return searched;
    }

    throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
  }

  template < typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::erase(const K& key)
  {
    m_Data.erase(key);
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getUnion(const Dictionary& right)
  {
    Dictionary newDict(right);

    for (iterator i = begin(); i != end(); i++)
    {
      newDict.insert(i);
    }

    newDict.m_Name = m_Name;

    return newDict;
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getIntersect(const Dictionary& right)
  {
    Dictionary newDict(m_Name);
    Dictionary copiedRightDict(right);

    for (iterator i = begin(); i != end(); i++)
    {
      if (copiedRightDict.contains(i.m_Current->m_Content.first))
      {
        newDict.insert(i);
      }
    }

    return newDict;
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp > Dictionary< K, V, Cmp >::getComplement(const Dictionary& right)
  {
    Dictionary newDict(m_Name);
    Dictionary copiedRightDict(right);

    for (iterator i = begin(); i != end(); i++)
    {
      if (!copiedRightDict.contains(i.m_Current->m_Content.first))
      {
        newDict.insert(i);
      }
    }

    return newDict;
  }

  template < typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::begin()
  {
    return m_Data.begin();
  }

  template < typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::end()
  {
    return m_Data.end();
  }

  template < typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cbegin() const
  {
    return m_Data.cbegin();
  }

  template < typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cend() const
  {
    return m_Data.cend();
  }

  template < typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >& Dictionary< K, V, Cmp >::operator=(const Dictionary& right)
  {
    m_Data = right.m_Data;
    m_Name = right.m_Name;

    return *this;
  }

  template < typename K, typename V, typename Cmp >
  V Dictionary< K, V, Cmp >::operator[](const K& key)
  {
    return m_Data[key];
  }
}
#endif
