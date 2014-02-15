// This #include statement was automatically added by the Spark IDE.
#include "jsmnSpark.h"

#define TOKEN_EQ(t, tok_start, tok_end, tok_type) \
	((t).start == tok_start \
	&& (t).end == tok_end  \
	&& (t).type == (tok_type))

#define TOKEN_STRING(js, t, s) \
	(strncmp(js+(t).start, s, (t).end - (t).start) == 0 \
	&& strlen(s) == (t).end - (t).start)

#define TOKEN_PRINT(t) \
	Serial.print(", type: "); Serial.print((t).type); Serial.print(" size: "); Serial.print((t).size); \
	Serial.print(" start: "); Serial.print((t).start); Serial.print(" end: "); Serial.println((t).end)


void setup() {

	Serial.begin(9600);
}

unsigned long wait = millis();
unsigned long waittime = 10000L;
const char *js;

void loop() {
	int i, r;
	jsmn_parser p;
	jsmntok_t tok[10];
	char obj[20];
	
	// This is the full JSON test string - Array of one object containg 6 string objects
	js = "  [{\"id\":\"1\",\"timestamp\":\"1337\",\"username\":\"kaul\"}]";

	if (!Serial.available())
	    return;

    obj[0] = Serial.read();
    
	jsmn_init(&p);
	r = jsmn_parse(&p, js, tok, 10);
	if (r == JSMN_SUCCESS)
	    Serial.println("parsed successfuly");
	else {
	    Serial.println("parse failed");
	    return;
	}

	for (i = 0; i < 8; i++) {
		Serial.print("Token ");
		Serial.print(i);
		TOKEN_PRINT(tok[i]);
		delay(10);
	}
	if (tok[0].type == JSMN_ARRAY && tok[0].size == 1)
	    Serial.println("Valid array found");
	if (tok[1].type == JSMN_OBJECT && tok[1].size == 6);
	    Serial.println("Valid object in array found");
	if (tok[1].type == JSMN_OBJECT && tok[1].size == 6);
	    Serial.println("6 valid string types in object found");

	for (i = 2; i < (tok[1].size + 2); i++) {
		if (tok[i].type != JSMN_STRING)
		    Serial.println("error: expected string");
		else {
			strlcpy(obj, &js[tok[i].start], (tok[i].end - tok[i].start + 1));
			Serial.print(obj);
			Serial.print(", ");
		}
	}
	Serial.println(" ");
}
