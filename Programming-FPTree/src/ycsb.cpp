#include "fptree/fptree.h"
#include <leveldb/db.h>
#include <string>

#define KEY_LEN 8
#define VALUE_LEN 8
using namespace std;

const string workload = ""; // TODO: the workload folder filepath

const string load = workload + ""; // TODO: the workload_load filename
const string run  = workload + ""; // TODO: the workload_run filename

const int READ_WRITE_NUM = 0; // TODO: amount of operations

int main()
{        
    FPTree fptree(1028);
    uint64_t inserted = 0, queried = 0, t = 0;
    uint64_t* key = new uint64_t[2200000];
    bool* ifInsert = new bool[2200000];
	FILE *ycsb, *ycsb_read;
	char *buf = NULL;
	size_t len = 0;
    struct timespec start, finish;
    double single_time;

    printf("===================FPtreeDB===================\n");
    printf("Load phase begins \n");

    // TODO: read the ycsb_load

    clock_gettime(CLOCK_MONOTONIC, &start);

    // TODO: load the workload in the fptree

    clock_gettime(CLOCK_MONOTONIC, &finish);
	single_time = (finish.tv_sec - start.tv_sec) * 1000000000.0 + (finish.tv_nsec - start.tv_nsec);
    printf("Load phase finishes: %d items are inserted \n", inserted);
    printf("Load phase used time: %fs\n", single_time / 1000000000.0);
    printf("Load phase single insert time: %fns\n", single_time / inserted);

	printf("Run phase begins\n");

	int operation_num = 0;
    inserted = 0;		
    // TODO: read the ycsb_run
    clock_gettime(CLOCK_MONOTONIC, &start);

    // TODO: operate the fptree

	clock_gettime(CLOCK_MONOTONIC, &finish);
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Run phase finishes: %d/%d items are inserted/searched\n", inserted, operation_num - inserted);
    printf("Run phase throughput: %f operations per second \n", READ_WRITE_NUM/single_time);	
    
    // LevelDB
    printf("===================LevelDB====================\n");
    const string filePath = ""; // data storing folder(NVM)

    memset(key, 0, 2200000);
    memset(ifInsert, 0, 2200000);

    leveldb::DB* db;
    leveldb::Options options;
    leveldb::WriteOptions write_options;
    // TODO: initial the levelDB
    inserted = 0;
    printf("Load phase begins \n");
    // TODO: read the ycsb_read
    clock_gettime(CLOCK_MONOTONIC, &start);
    // TODO: load the levelDB
    clock_gettime(CLOCK_MONOTONIC, &finish);
	single_time = (finish.tv_sec - start.tv_sec) * 1000000000.0 + (finish.tv_nsec - start.tv_nsec);
    printf("Load phase finishes: %d items are inserted \n", inserted);
    printf("Load phase used time: %fs\n", single_time / 1000000000.0);
    printf("Load phase single insert time: %fns\n", single_time / inserted);

	printf("Run phase begin\n");
	operation_num = 0;
    inserted = 0;		
    // TODO: read the ycsb_run

    clock_gettime(CLOCK_MONOTONIC, &start);

    // TODO: run the workload_run in levelDB

	clock_gettime(CLOCK_MONOTONIC, &finish);
    fclose(ycsb_read);
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Run phase finishes: %d/%d items are inserted/searched\n", inserted, operation_num - inserted);
    printf("Run phase throughput: %f operations per second \n", READ_WRITE_NUM/single_time);	
    return 0;
}
