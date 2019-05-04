rm -rf test/*.out
for file in test/*.in
do
	echo Running test ${file%.*}
	if dist/main < $file > ${file%.*}.out
	then echo \\t successfully.
	else echo \\t Runtime Error! && return 0
	fi
	if diff ${file%.*}.ans ${file%.*}.out
	then echo \\t Check passed.
	else echo \\t Wrong Answer! && return 0
	fi
done
