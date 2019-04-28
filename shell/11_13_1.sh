#/bin/bash

path=/server/scripts
MAIL_GRUP=""
MAIL_GROUP=""
LOG_FILE="/tmp/web_check.log"

[ ! -d "$path" ] && mkdir -p $path
function UrlList() {
    cat>$path/domain.list<<EOF
    http://www.baidu.com
EOF
}

function CheckUrl() {
    FAILCOUNT=0
    for ((i=1;i<=3;i++))
    do
        wget -T 5 --tries=1 --spider $1 >/dev/null 2>&1        
        if [ $? -ne 0 ];then
            ((FAILCOUNT=FAILCOUNT+1))
        else
             break
        fi
    done
    echo $FAILCOUNT
    return $FAILCOUNT
}

function Mail() {
    local SUBJECT_CONTENT=$1
    for MAIL_USER in `echo MAIL_GROUP`
    do
        mail -s $SUBJECT_CONTENT $MAIL_USER <$LOG_FILE 
    done
}

function SendMsg() {
    echo "param:"$1
    if [ $1 -ge 3 ];then
        RETVAL=1
        NOWTIME=`date +"%Y-%m-%d %H:%M:%S"`
        SUBJECT_CONTENT="http://$1 is error,${NOWTIME}."
        echo ${NOWTIME} | tee $LOG_FILE
        Mail $SUBJECT_CONTENT
    else
        echo "http://$1 is ok."
        RETVAL=0
    fi
    return $RETVAL
}

function main() {
    UrlList
    for url in `cat $path/domain.list`
    do
        CheckUrl $url
        SendMsg $? $url
    done
}

main
