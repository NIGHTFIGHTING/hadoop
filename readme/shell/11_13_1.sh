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
            continue
        else
            ((FAILCOUNT=FAILCOUNT+1))
        fi
    done
    echo $FAILCOUNT
}

function main() {
    UrlList
    for url in `cat $path/domain.list`
    do
        CheckUrl $url
    done
}

main
