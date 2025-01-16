# low-latency-ipc

n=385 median=1272ns mean=1626445ns std=28579727ns 95%=37174ns 99%=1380130ns maximum=558607867ns

## 尝试

### 尝试1

使用共享内存 + semaphore，共享内存作为IPC比named pipe更加高效

### 尝试2

使用共享内存 + atomic + memory order，通过原子操作和memory order实现两者的同步

### 尝试3

使用共享内存 + atomic + memory order + 缓存对齐，加入缓存对齐，防止多核访问共享变量时因缓存行冲突导致性能下降。

### 尝试4

使用共享内存 + 无锁队列存储alice_to_bob信息和bob_to_alice信息

## 未实现的尝试

crc32存在硬件加速的校验和实现。
引入线程池机制，让bob可以并行处理多条信息。
当前消息是一条一条处理的，可以引入批处理机制，减少同步次数。