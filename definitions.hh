#pragma once

// ============== unused ==============
#define HOT 100
#define EXECUTION_DURATION 10
// ====================================

// ============== please don't change ==============
#define COLD_CUTOFF 1000000       // default 990000
#define MAX_LOCK_BATCH_SIZE 2000  // default 200(=>20K), 2000(200K)
// Set batch size per 10 ms epoch , set it a little bigger than the actually
// throughput(200 means every second the sequencer creates 20K transactions)
#define EPOCH_DURATION 0.01  // 0.01 is 10ms
// =================================================

// ============== server setting ==============
#define NUM_CORE 8
// RunMultiplexer is on core of NUM_CORE - 1
// RunSequencerWriter  is on core of  NUM_CORE - 2
// RunSequencerReader  is on core of NUM_CORE - 3
// LockManagerThread  is on core of NUM_CORE - 4

#define NUM_BACKGROUND_CORE 4
#define NUM_BACKGROUND_THREADS NUM_BACKGROUND_CORE
// NUM_BACKGROUND_THREADS are RunMultiplexer, RunSequencerWriter,
// RunSequencerReader, LockManagerThread

#define NUM_WORKERS_CORE (NUM_CORE - NUM_BACKGROUND_THREADS)
#define NUM_WORKERS (NUM_WORKERS_CORE)  // ハイパースレッド
// ==============================================

// ============== database setting ==============
#define DB_SIZE 1000000
#define LOCK_TABLE_SIZE 1000000  // accessed only by a lock manager
// ==============================================

// ============== workload setting ==============
#define RW_SET_SIZE 30  // MUST BE EVEN, default 10
#define SKEW 0.8        // manage contention
#define UNIFORM_KEY_SELECTION_RATIO 0
// 〇〇%のトランザクションがuniform accessする
// ==============================================

// ============== used for only calvin ==============
#define MAX_ACTIVE_TXNS 2000  // default 2000
#define LOCK_BATCH_SIZE 100   // default 100
// ==============================================

// ============== used for only pdlr ==============
#define MAX_FAILED_LOCK 100
// ==============================================

// calvin system default cpu affinity:
// RunWorkerThread:
//     if (i == 0 || i == 1)
//       CPU_SET(i, &cpuset);
//     else
//       CPU_SET(i+2, &cpuset);
// RunSequencerReader: 2
// RunMultiplexer: 3
// RunSequencerWriter: 6
// LockManagerThread: 7

#define SEQUENCER_WRITER_CORE 12
#define SEQUENCER_READER_CORE 4
#define MULTIPLEXER_CORE 6
#define MAIN_PROCESS_CORE 16
#define LOCK_MANAGER_CORE 14

// clang-format off
#define GET_WORKER_CORE(thread_id) ((thread_id) == 0 || (thread_id) == 1 ? (thread_id) * 2 : 4 + ((thread_id) * 2))
// clang-format on