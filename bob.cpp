#include "common.h"

void send(const Message *message)
{
    static int fifo = 0;
    if (fifo == 0)
    {
        const char *filename = "bob_to_alice";
        if (access(filename, F_OK))
            mkfifo(filename, 0666);
        fifo = open(filename, O_WRONLY);
        assert(fifo != 0);
    }
    assert(write(fifo, message, message->size) == message->size);
}

const Message *recv()
{
    static int fifo = 0;
    if (fifo == 0)
    {
        const char *filename = "alice_to_bob";
        if (access(filename, F_OK))
            mkfifo(filename, 0666);
        fifo = open(filename, O_RDONLY);
        assert(fifo != 0);
    }
    static Message *m = (Message *)malloc(MESSAGE_SIZES[4]);
    assert(read(fifo, m, sizeof(Message)) == sizeof(Message));
    assert(read(fifo, m->payload, m->payload_size()) == m->payload_size());
    return m;
}

int main()
{
    Message *m2 = (Message *)malloc(MESSAGE_SIZES[4]);
    while (true)
    {
        const Message *m1 = recv();
        assert(m1->checksum == crc32(m1));
        memcpy(m2, m1, m1->size); // 拷贝m1至m2
        m2->payload[0]++;         // 第一个字符加一
        m2->checksum = crc32(m2); // 更新校验和
        send(m2);
    }

    return 0;
}