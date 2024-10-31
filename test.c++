#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <chrono>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>

#include <atomic>

constexpr unsigned long long iterations = 1e10;  // より高い負荷
void* compute_task(void* arg) {
  double sum = 0.0;
  for (long long i = 1; i <= iterations; ++i) {
    // sum += std::sin(i) * std::cos(i) * std::sqrt(i);  // より複雑な計算
    sum += i % 100;  // 単純な計算
  }
  return nullptr;
}

// constexpr size_t array_size = 1e6;
// double shared_data[array_size];  // NUMAノード間で共有されるデータ

// void* compute_task(void* arg) {
//   double sum = 0.0;
//   for (long long i = 1; i <= iterations; ++i) {
//     size_t index = i % array_size;
//     // 共通データにアクセスし、読み書きする
//     std::atomic_thread_fence(std::memory_order_seq_cst);
//     shared_data[index] += std::sin(i) * std::cos(i) * std::sqrt(i);
//     std::atomic_thread_fence(std::memory_order_seq_cst);

//     sum += shared_data[index];
//   }
//   return nullptr;
// }

void run_test(int cpu1, int cpu2) {
  pthread_t thread1, thread2;

  // スレッドの属性を作成
  pthread_attr_t attr1, attr2;
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);

  // CPUセットを設定
  cpu_set_t cpuset1, cpuset2;
  CPU_ZERO(&cpuset1);
  CPU_ZERO(&cpuset2);
  CPU_SET(cpu1, &cpuset1);  // thread1をcpu1にバインド
  CPU_SET(cpu2, &cpuset2);  // thread2をcpu2にバインド

  // 属性にCPUセットを設定
  pthread_attr_setaffinity_np(&attr1, sizeof(cpu_set_t), &cpuset1);
  pthread_attr_setaffinity_np(&attr2, sizeof(cpu_set_t), &cpuset2);

  // テストの開始時間
  auto start = std::chrono::high_resolution_clock::now();

  // スレッドの作成と計算の実行
  pthread_create(&thread1, &attr1, compute_task, nullptr);
  pthread_create(&thread2, &attr2, compute_task, nullptr);

  // スレッドの終了を待機
  pthread_join(thread1, nullptr);
  pthread_join(thread2, nullptr);

  // テストの終了時間
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;

  // 結果の出力
  std::cout << "CPU1: " << cpu1 << ", CPU2: " << cpu2
            << ", Time taken: " << duration.count() << " seconds" << std::endl;

  // 属性の破棄
  pthread_attr_destroy(&attr1);
  pthread_attr_destroy(&attr2);
}

int main() {
  std::cout << "Testing performance with different CPU sets..." << std::endl;

  // 複数のタプルを保持するためのvectorを定義
  std::vector<std::tuple<std::string, int, int>> params = {
      {"同物理CPU", 0, 1},  {"同物理CPU", 46, 47}, {"異物理CPU", 0, 2},
      {"異物理CPU", 0, 46}, {"異NUMA", 0, 48},     {"異NUMA", 46, 95},
  };

  // vector内のタプルの内容を出力
  for (const auto& [title, one, two] : params) {
    std::cout << title << ", (" << one << ", " << two << ")" << std::endl;
    // 同じ物理CPUにバインド
    run_test(one, two);
  }

  std::cout << "=======================" << std::endl;

  // 複数のタプルを保持するためのvectorを定義
  std::vector<std::tuple<std::string, int, int>> params2 = {
      {"同物理CPU", 0, 56}, {"同物理CPU", 6, 54}, {"異物理CPU", 0, 2},
      {"異物理CPU", 0, 46}, {"異NUMA", 0, 1},     {"異NUMA", 46, 47},
  };

  // vector内のタプルの内容を出力
  for (const auto& [title, one, two] : params2) {
    std::cout << title << ", (" << one << ", " << two << ")" << std::endl;
    // 同じ物理CPUにバインド
    run_test(one, two);
  }

  std::cout << "=======================" << std::endl;

  //   // 複数のタプルを保持するためのvectorを定義
  //   std::vector<std::tuple<std::string, int, int>> params3 = {
  //       {"同物理CPU", 0, 0},  {"同物理CPU", 1, 1}, {"異物理CPU", 0, 1},
  //       {"異物理CPU", 0, 23}, {"異NUMA", 0, 47},   {"異NUMA", 23, 24},
  //   };

  //   // vector内のタプルの内容を出力
  //   for (const auto& [title, one, two] : params3) {
  //     std::cout << title << ", (" << one << ", " << two << ")" << std::endl;
  //     // 同じ物理CPUにバインド
  //     run_test(one, two);
  //   }

  return 0;
}