cd $(dirname $0)
for file in ./*.input
do
	echo Running test ${file%.*}
	if ./main < $file > ${file%.*}.tmp
	then echo \\t Run completed.
	else echo \\t Runtime Error! && return 1
	fi
	if python3 checker.py ${file%.*}.tmp < $file
	then echo \\t Check passed.
	else echo \\t Wrong Answer! && return 1
	fi
done
