#include "common.h"

int main() {
    SharedMemory *shm_ptr;
    int shm_fd;

    initialize_shared_memory(&shm_ptr, &shm_fd);

    while (true) {
        // Wait for Alice
        while (!shm_ptr->alice_ready.load(std::memory_order_acquire)) {_mm_pause();}

        // Validate and modify the message
        // const Message *m1 = &shm_ptr->message;
        assert(shm_ptr->message.checksum == crc32(&shm_ptr->message));

        // Message *m2 = &shm_ptr->message;
        // memcpy(m2, m1, sizeof(Message));
        // memcpy(m2->payload, shm_ptr->payload, m1->payload_size());

        shm_ptr->payload[0]++;
        shm_ptr->message.checksum = crc32(&shm_ptr->message);

        // Notify Alice
        shm_ptr->alice_ready.store(false, std::memory_order_release);
        shm_ptr->bob_ready.store(true, std::memory_order_release);
    }

    cleanup_resources(shm_ptr, shm_fd);
    return 0;
}