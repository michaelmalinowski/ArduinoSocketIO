#include "ArduinoSocketIO.h"

String * sortResponse(String allData){
    String event, payload;
    bool event_check = false;
    bool payload_check = false;
    for (int i = 0; i < strlen(allData); ++i){
        if ('[' == allData[i]){
            event_check = true;
        } else if (event_check && allData[i] == '\"'){
            event_check = false;
            payload_check = true;
            i += 2;
        } else if (payload_check && allData[i] == '\"'){
            Serial.println(event);
            Serial.println(payload);
            String response = [event, payload];
            return response;
        }
        if (event_check){
            event += allData[i];
        } else if (payload_check){
            payload += allData[i];
        }
    }
}

ArduinoSocketIO::ArduinoSocketIO(WiFiClient &wifi, char server[], int port, int event_count) : client(wifi, server, port){
    actions = new func [event_count];
    events = new String [event_count];
    event_size = event_count;
}

int ArduinoSocketIO::startConnection(){
    Serial.println("Connection is being established");
    this->client.begin("/socket.io/?transport=websocket");
    if (this->client.connected()){
        Serial.println("Connection is established");
        return 1;
    } else {
        Serial.println("Connection could not be established");
        return 0;
    }
}

int ArduinoSocketIO::isConnected(){
    if (this->client.connected()){
        return 1;
    } else {
        return 0;
    }
}

void ArduinoSocketIO::keepSocketAlive(){
    this->client.beginMessage(TYPE_TEXT);
    this->client.print("42[\"arduino\",\"Keep Arduino Alive\"]");
    this->client.endMessage();
}

void ArduinoSocketIO::emit(String event, String message){
    this->client.beginMessage(TYPE_TEXT);
    String msg = "42[\"";
    msg = msg + event + "\",\"";
    msg = msg + message + "\"]";
    this->client.print(msg);
    this->client.endMessage();
}

void ArduinoSocketIO::on(String event, func function){
    if (event_size > event_number){
        events[event_number] = event;
        actions[event_number] = function;
        Serial.print(event);
        Serial.println("is now an event");
    } else {
        Serial.println("Event limit has been reached");
    }
}

void ArduinoSocketIO::eventListener(){
    String data = "";
    //String event = {"",""};
    bool clean_message = false;
    while(this->isConnected()){
        byte b = this->client.read();
        int byte_num = int(b);
        //The filtering of characters is incomplete. WOnt work for an array.
        if (byte_num < 255 && byte_num > -1){
            char c = char(b);
            if (c == '4' || c == '2' || c == '[' || c == '\"' || clean_message){
                data += String(c);
                //Serial.println(data);
                if (data == "42[\""){
                    clean_message = true;
                }
                if (clean_message && c == ']'){
                    sortResponse(data);
                }
            } else {
                data = "";
            }
        } else {
            clean_message = false;
        }
    }
}
