#include "kdb.h"
#include "string.h"


int main(int argc, char *argv[]) {
  // read : 0 , write : 1 , delete : -1, help : -100
  int mode = 0;
  std::string wopt = "-w";
  std::string dopt = "-d";
  std::string hopt = "-h";
  char* keyword = NULL;
  KDB* kdb = new KDB();
  for (int i = 1; i < argc ;i++) {
	if (wopt.compare(argv[i]) == 0) {
	  mode = 1;
	} else if (dopt.compare(argv[i]) == 0) {
	  mode = -1;
	} else if (hopt.compare(argv[i]) == 0) {
	  mode = -100;
	} else {
	  if (mode == 1) {
		if ((i+1) < argc) {
		  kdb->Put(argv[i], argv[i+1]);
		  i++;
		} else {
		  break;
		}

	  } else if (mode == -1) {
		kdb->Delete(argv[i]);
	  } else {
		keyword = argv[i];
		break;
	  }
	}
  }

  if (mode == 0) {
	kdb->Get(keyword);
  } else if (mode == -100) {
	printf("lkvs\n  usage\n\tno option : show key values. if specified argument, use for keyword at 1st argument.\n\t-w : add key value. ex -w key1 val1 key2 val2\n\t-d : delete specified keys. ex -d key1 key\n");
  }
  delete kdb;
  return 0;
}
