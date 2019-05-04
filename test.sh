rm -rf test/**/*.out
for file in test/**/*.input
do
	echo Running test ${file%.*}
	if dist/main < $file > ${file%.*}.out
	then echo \\t successfully.
	else echo \\t Runtime Error! && return 1
	fi
	if python3 checker.py ${file%.*}.out ${file%.*}.output
	then echo \\t Check passed.
	else echo \\t Wrong Answer! && return 1
	fi
done
