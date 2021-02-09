# matrix-connected

Personal project composed of an ESP8266 (NodeMCU) and 8 led matrix (MAX72XX).
His goal is first of all to be a clock. Advanced features are coming along the way.

## Features

- Connected to internet (mode Access Point when no Wifi set)
- Clock (use NTP)
- Countdown
- Timer
- Dynamic message (support french accents)
- Notification (RTTTL sound + Led)

## Routes available

Every parameters are in query string.

- /intensity?val=[0-15]
- /notify?song=(on|off)
- /message/add?msg=XX
- /timer/(start|stop|restart)
- /countdown/(stop|restart) and /countdown/start?duration=XXSEC or /countdown/start?hour=XX&minute=XX&second=XX
- /matrixActivated?matrixActivated=(on|off) `enable of disable the system`
- /ram `Get the head free space`
- /ram2 `Get the head fragmentation percentage`
- /uptime `Get the uptime`
- /song?song=RTTTL_STRING `Play RTTTL song` Please be careful, there are memories leaks with this url

## Photos

Coming soon !