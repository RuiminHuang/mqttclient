/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-11 21:53:07
 * @LastEditTime : 2019-12-31 12:56:54
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include "mqttclient.h"

mqtt_client_t client;
client_init_params_t init_params;

void *mqtt_yield_thread(void *arg)
{
    int rc;
    while (1) {
        rc = mqtt_yield(&client, 10000);
        if (MQTT_RECONNECT_TIMEOUT_ERROR == rc) {
            LOG_E("%s:%d %s()..., mqtt reconnect timeout....", __FILE__, __LINE__, __FUNCTION__);
            // sleep(3);
        }
    }
    
    pthread_exit(NULL);
}

void *mqtt_unsubscribe_thread(void *arg)
{
    sleep(5);
    mqtt_unsubscribe(&client, "mqtt_topic");
    pthread_exit(NULL);
}

void *mqtt_publish_thread(void *arg)
{
    char buf[80] = { 0 };
    mqtt_message_t msg;
    memset(&msg, 0, sizeof(msg));
    sprintf(buf, "message: Hello World! his is a publish test...");
    
    msg.qos = 2;
    msg.payload = (void *) buf;
    msg.payloadlen = strlen(buf);
    while(1) {
        mqtt_publish(&client, "testtopic", &msg);
        mqtt_publish(&client, "mqtt_topic", &msg);
        mqtt_publish(&client, "mqtt_topic1/sdasd", &msg);
        sleep(2);
    }
}

int main(void)
{
    int res;
    error_t err;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    init_params.read_buf_size = 1024;
    init_params.write_buf_size = 1024;
    init_params.connect_params.network_params.addr = "129.204.201.235"; //"192.168.1.101";
    init_params.connect_params.network_params.port = 1883;
    init_params.connect_params.user_name = "jiejie";
    init_params.connect_params.password = "123456";
    init_params.connect_params.client_id = "clientid";
    init_params.connect_params.clean_session = 1;
    LOG_I("-------------------hello client----------------------");

    log_init();

    err = mqtt_init(&client, &init_params);
    LOG_E("err = %d",err);

    err = mqtt_connect(&client);
    LOG_E("err = %d",err);
    
    err = mqtt_subscribe(&client, "testtopic", 2, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic", 0, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic1/#", 0, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic2/+/abc", 1, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic2/+/dd", 1, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic2/123/dd", 0, NULL);
    err = mqtt_subscribe(&client, "mqtt_topic3/#", 2, NULL);
    LOG_E("err = %d",err);

    // res = pthread_create(&thread1, NULL, mqtt_yield_thread, NULL);
    // if(res != 0) {
    //     LOG_I("create thread1 fail");
    //     exit(res);
    // }

    res = pthread_create(&thread2, NULL, mqtt_unsubscribe_thread, NULL);
    if(res != 0) {
        LOG_I("create thread2 fail");
        exit(res);
    }
    
    res = pthread_create(&thread3, NULL, mqtt_publish_thread, NULL);
    if(res != 0) {
        LOG_I("create thread3 fail");
        exit(res);
    }

    while (1) {
        sleep(100);
    }
}