#include "kdb.h"

/*
int hello() {
  leveldb::DB* db=NULL;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  leveldb::Slice key = "Hello";
  std::string val;
  status = db->Get(leveldb::ReadOptions(), key, &val);
  if(!status.ok()) std::cout<<status.ToString()<<std::endl;
  std::cout<<key.ToString()<< "[" <<val<< "]" <<std::endl;

  leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
	std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
  }
  assert(it->status().ok());
  delete it;

  delete db;
  return(0);
}

KDBComparator::KDBComparator() {}
KDBComparator::~KDBComparator() {}
*/


int KDBComparator::Compare(const leveldb::Slice& a, const leveldb::Slice& b) const {

  if (a == b) {
	return 0;
  }
  if (a == NULL) {
	return b == NULL ? 0 : 1;
  }
  if (b == NULL) {
	return -1;
  }

  //std::cout << "A:" << a.ToString() << ",B:" << b.ToString() << std::endl;

  return a.compare(b);
}

const char* KDBComparator::Name() const { return "KDBComparator"; }
void KDBComparator::FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
void KDBComparator::FindShortSuccessor(std::string*) const { }

KDB::KDB() {
  //KDBComparator cmp;
  leveldb::Options opt;
  opt.create_if_missing = true;
  //opt.comparator = &cmp;
  leveldb::DB::Open(opt, "/tmp/testdb", &db_);
}

KDB::~KDB() {
  delete db_;
}

bool KDB::Put(char* key, char* value) {
  return db_->Put(leveldb::WriteOptions(), key, value).ok();
}

bool KDB::Get(char * keyword) {
  bool flg = false;
  leveldb::Iterator* it = db_->NewIterator(leveldb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
	if (keyword != NULL) {
	  int pos = it->key().ToString().find(keyword);
	  if (pos != std::string::npos) {
		std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;		
	  }
	} else {
	  std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
	}
  }
  delete it;
  return flg;
}


bool KDB::Delete(char * key) {
  return db_->Delete(leveldb::WriteOptions(), key).ok();
}
