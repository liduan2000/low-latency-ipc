#include "common.h"

int main() {
    ExtendedSharedMemory *shm_ptr;
    int shm_fd;

    initialize_shared_memory(&shm_ptr, &shm_fd);

    while (true) {
        Message received_msg;
        while (!shm_ptr->alice_to_bob.try_dequeue(received_msg)) {
            _mm_pause();
        }

        Message* m1 = &received_msg;
        char* payload = m1->payload;
        assert(m1->checksum == crc32(m1));

        m1->payload[0]++;
        m1->checksum = crc32(&received_msg);

        while (!shm_ptr->bob_to_alice.try_enqueue(received_msg)) {
            _mm_pause();
        }
    }

    cleanup_resources(shm_ptr, shm_fd);
    return 0;
}