#ifndef _CO_COORDINATOR_H
#define _CO_COORDINATOR_H
/**
 * state: uninitialized, ready, exiting
 * protocol: CO_PROTO_TCP, CO_PROTO_UNIX, CO_PROTO_UNIXPACKET
 * address: TCP(host:port), UNIX(/path/to/file.socket)
 */
typedef enum {
    CO_STATE_UNINITIALIZED = 0x8745,
    CO_STATE_READY,
    CO_STATE_EXITING,
} coordinator_state;

typedef enum {
    CO_PROTO_TCP,
    CO_PROTO_UNIX,
    CO_PROTO_PROTO_UNIXPACKET,
} coordinator_protocol;

typedef struct
{
    volatile coordinator_state state;
    coordinator_protocol protocol;
    char address[504];
} coordinator_struct;
#define CO_SHM_KEY  "plcoordinator_shm"

#endif /* _CO_COORDINATOR_H */