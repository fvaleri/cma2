#include <stdio.h>
#include <string.h>
#include <librdkafka/rdkafka.h>

#define BOOTSTRAP_SERVERS ":9092"
#define TOPIC "my-topic"

/*
 * Wrapper for the rd_kafka_producev() function, that queues a single
 * message with a specified key and value for sending to the broker.
 * This function does not block. We will later use rdkafka_flush()
 * to wait for completion of the send.
 */
void queue_for_send(rd_kafka_t *producer, const char *topic,
                    const char *key, const char *value) {
    rd_kafka_resp_err_t err = rd_kafka_producev(
        producer,
        RD_KAFKA_V_TOPIC(topic),
        RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
        RD_KAFKA_V_KEY((void*)key, strlen(key)),
        RD_KAFKA_V_VALUE((void*)value, strlen(value)),
        RD_KAFKA_V_OPAQUE(NULL),
        RD_KAFKA_V_END
    );
    if (err) {
        fprintf(stderr, "can't send: %s\n",
            rd_kafka_err2str (err));
    }
}

/*
 * Send messages to Kafka using rdkafka library.
 * dnf install librdkafka-devel
 * gcc -o bin/ksend src/ksend.c -lrdkafka
 */
int main(void) {
    char err[256]; // error buffer

    rd_kafka_conf_t *conf = rd_kafka_conf_new();
    rd_kafka_conf_set (conf, "bootstrap.servers", BOOTSTRAP_SERVERS, err, sizeof(err));
    rd_kafka_t *producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, err, sizeof (err));

    if (producer) {
        queue_for_send(producer, TOPIC, "mykey", "Hello");
        queue_for_send(producer, TOPIC, "mykey", "World");

        // wait for 10s for all  messages to be sent
        rd_kafka_flush(producer, 10000);

        // if there is anything left after 10s, we have an issue
        int unsent = rd_kafka_outq_len(producer);
        if (unsent > 0) {
            fprintf (stderr, "%d message(s) were not sent\n", unsent);
        }

        // the conf object is destroied by the producer object
        rd_kafka_destroy(producer);

    } else {
        fprintf(stderr, "can't create producer: %s\n", err);
    }
}
