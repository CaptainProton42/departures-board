/*
 * Departures Board (c) 2025-2026 Gadec Software
 *
 * TfL London Underground Client Library
 *
 * https://github.com/gadec-uk/departures-board
 *
 * This work is licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International.
 * To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/
 */
#pragma once
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <stationData.h>
#include <responseCodes.h>

#define MAXLINESIZE 20
#define UGMAXREADSERVICES 20

class TfLdataClient: public JsonListener {

    private:

        struct ugService {
            char destinationName[MAXLOCATIONSIZE];
            char lineName[MAXLINESIZE];
            int timeToStation;
        };

        struct ugStation {
            int numServices;
            ugService service[UGMAXREADSERVICES];
        };

        const char* apiHost = "api.tfl.gov.uk";
        const char* tflAttribution = "Powered by TfL Open Data";
        String currentKey = "";
        String currentObject = "";

        int id=0;
        bool maxServicesRead = false;
        bool boardChanged = false;
        ugStation xStation;
        stnMessages xMessages;

        bool pruneFromPhrase(char* input, const char* target);
        void replaceWord(char* input, const char* target, const char* replacement);
        static bool compareTimes(const ugService& a, const ugService& b);

    public:
        String lastErrorMsg = "";

        TfLdataClient();
        int fetchArrivals(rdStation *station, stnMessages *messages, const char *locationId, const char *lineId, const char *lineDirection, bool noMessages, String apiKey);
        void loadArrivals(rdStation *station, stnMessages *messages);

        virtual void whitespace(char c);
        virtual void startDocument();
        virtual void key(String key);
        virtual void value(String value);
        virtual void endArray();
        virtual void endObject();
        virtual void endDocument();
        virtual void startArray();
        virtual void startObject();
};