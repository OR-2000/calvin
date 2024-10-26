#pragma once

#define MAX_ACTIVE_TXNS 2000  // default 2000
#define LOCK_BATCH_SIZE 100   // default 100

#define HOT 100  // unused

#define COLD_CUTOFF 990000  // default 990000

#define RW_SET_SIZE 1    // MUST BE EVEN, default 10
#define DB_SIZE 1000000  // default 1000000

#define NUM_CORE 36
#define NUM_THREADS (NUM_CORE * 2)  // ハイパースレッド
#define NUM_BACKGROUND_THREADS 4
#define NUM_WORKERS_CORE (NUM_CORE - NUM_BACKGROUND_THREADS)
// RunMultiplexer, RunSequencerWriter, RunSequencerReader, LockManagerThread
#define NUM_WORKERS (NUM_THREADS - NUM_BACKGROUND_THREADS)

#define MAX_LOCK_BATCH_SIZE 50000  // default 200
// Set batch size per 10 ms epoch , set it a little bigger than the actually
// throughput(200 means every second the sequencer creates 20K transactions)

#define MAX_FAILED_LOCK 1  // used for pdlr

#define SKEW 0.9