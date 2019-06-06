#/bin/bash
#Rotate the Nginx logs to prevent a single logfile from consuming too much disk space.
LOGS_PATH=/usr/local/nginx/logs/history
if [ ! -d ${LOGS_PATH} ];then
    echo "the file:${LOGS_PATH} is not exist"
    mkdir ${LOGS_PATH}
    echo "create the file${LOGS_PATH} sucess"
fi
CUR_LOGS_PATH=/usr/local/nginx/logs
YESTERDAY=$(date -d "yesterday" +%Y-%m-%d)
mv ${CUR_LOGS_PATH}/access.log ${LOGS_PATH}/access_${YESTERDAY}.log
mv ${CUR_LOGS_PATH}/error.log ${LOGS_PATH}/error_${YESTERDAY}.log
## 向 Nginx 主进程发送 USR1 信号.USR1 信号是重新打开日志文件
kill -USR1 ${cat /usr/local/nginx/logs/nginx.pid}
