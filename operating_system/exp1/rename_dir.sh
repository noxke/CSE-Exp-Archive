#!/usr/bin/bash

path=$1

# 检查目录是否存在
# path末尾删除/
if [ -d "$path" ]
then	
	if [[ $path =~ .*/$ ]]
	then
		path=${path%/}
	fi
else
	echo "path error"
	exit 1
fi

datetime=`TZ="Asia/Shanghai"  date +%Y-%m-%d-%H-%M`

echo $datetime

# 遍历目录
for file in "$path"/*;
do
	# 只对文件进行操作
	if [ -f $file ]
	then
		# ls -lh $file
		# 识别文件末尾是否有时间后缀
		if ! echo "$file" | grep -qE "^.*(-[0-9]+){5}"
		then
			# 修改文件后缀
			mv $file "$file-$datetime"
		else
			# 为文件添加后缀
			file_name=`echo $file | sed -E 's/(-[0-9]+){5}$//'`
			mv $file "$file_name-$datetime"
		fi
	fi
done
