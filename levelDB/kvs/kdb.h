#ifndef KDB_H
#define KDB_H

#include <cassert>
#include <iostream>
#include "leveldb/db.h"
#include "leveldb/comparator.h"

//int hello();

class KDBComparator : public leveldb::Comparator {
 public:
  /*
  KDBComparator();
  ~KDBComparator();
  */

  virtual int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const;
  virtual const char* Name() const;
  virtual void FindShortestSeparator(std::string*, const leveldb::Slice&) const;
  virtual void FindShortSuccessor(std::string*) const;

};

class KDB {

 public:
  KDB();
  ~KDB();

  bool Put(char* key, char* value);
  bool Get(char* key);
  bool Delete(char* key);

 private:
  leveldb::DB* db_;

};

#endif
