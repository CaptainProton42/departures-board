// Common station data structures shared by both data clients
#pragma once
#include <Arduino.h>

#define MAXBOARDMESSAGES 4
#define MAXMESSAGESIZE 400
#define MAXCALLINGSIZE 450
#define MAXBOARDSERVICES 9
#define MAXLOCATIONSIZE 45

#define OTHER 0
#define TRAIN 1
#define BUS 2

struct stnMessages {
    int numMessages;
    char messages[MAXBOARDMESSAGES][MAXMESSAGESIZE];
};

struct rdService {
    char sTime[6];
    char destination[MAXLOCATIONSIZE];
    char via[MAXLOCATIONSIZE];  // also used for line name for TfL
    char etd[11];
    char platform[4];
    bool isCancelled;
    bool isDelayed;
    int trainLength;
    byte classesAvailable;
    char opco[50];

    int serviceType;
    int timeToStation;  // Only for TfL
  };

  struct rdStation {
    char location[MAXLOCATIONSIZE];
    bool platformAvailable;
    int numServices;
    bool boardChanged;  // Only for TfL
    char calling[MAXCALLINGSIZE];   // Only store the calling stops for the first service returned
    char origin[MAXLOCATIONSIZE]; // Only store the origin for the first service returned
    char serviceMessage[MAXMESSAGESIZE];  // Only store the service message for the first service returned
    rdService service[MAXBOARDSERVICES];
  };
