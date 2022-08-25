#!/bin/bash

# 1. server, client build
clang ../samples/client/client.c -o client -Werror -Wextra
clang ../01_now_you_see_me/server.c -o server -Werror -Wextra

ret=$?
if [ $ret -eq 0 ]; then
  printf "build ok\n"
else
  printf "build ko\n"
  rm client* server*
  exit 1
fi

chmod +x server
chmod +x client

# 2. run test in 10s
./client > client.log &
export CLIENT_PID=$!
./server > server.log &
export SERVER_PID=$!
sleep 10
kill $SERVER_PID
kill $CLIENT_PID

# 3. diff check
diff client.log server.log

ret=$?
if [ $ret -eq 0 ]; then
  printf "diff ok\n"
else
  printf "diff ko\n"
  rm client* server*
  exit 1
fi

rm client* server*