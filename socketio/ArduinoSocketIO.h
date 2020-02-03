#include "WebSocketClient.h"
#include "WiFiNINA.h"
#include <vector>

#ifndef ArduinoSocketIO_h
#define ArduinoSocketIO_h

class ArduinoSocketIO {

  private:
    typedef void (*func)(String);
    WebSocketClient client;
    func *actions;
    int event_number = 0;
    int event_size;
    String *events;

  public:
  
    //Binds and creates a WebSocketClient to the class for later use.
    //Events is used to allocate an array for the amount of events
    //on this client
    ArduinoSocketIO(WiFiClient &wifi, char server[], int port, int event_count);
    
    //initializes the socket connection with the server
    int startConnection();

    int isConnected();

    //Keeps the socket alive by sending a message to the server
    void keepSocketAlive();

    //emit an event to the server with a message 
    void emit(String event, String message);

    //creates a socket trigger event. 
    void on(String event, func function);

    //listens for events
    void eventListener();

  };

#endif
