#!/bin/sh

RED="\033[0;31m"
GREEN="\033[0;32m"
END="\033[0m"

testdir="tests"
outdir="tests/output"
diffdir="tests/diff"
logdir="tests/logs"
timedir="tests/runtime"
incdir="includes/"
errlog="tests/err.log"
flags="-Wall -Werror -Wextra -std=c++98"

if [ -d "$outdir" ]; then
	rm -rf $outdir
fi

if [ -d "$diffdir" ]; then
	rm -rf $diffdir
fi

if [ -d "$logdir" ]; then
	rm -rf $logdir
fi

if [ -f "$errlog" ]; then
	rm $errlog
fi

mkdir -p "$outdir"
mkdir -p "$diffdir"
mkdir -p "$logdir"

calculate_time() {
	c=$(echo $b | tr 'a-z' 'A-Z')
	if [ -f "$outdir/ft_$b.out" ]; then
		if [ -s "$diffdir/$b.diff" ]; then
			printf "$c $RED===FAILED===$END\n"
			printf "(Check $diffdir/$b.diff for more info)\n"
		else
			printf "$c $GREEN===PASSED===$END\n"
			printf "Runtime FT :\n"
			time -p bash -c "for (( i=0; i<100; i++ )); do ./"$outdir/ft_$b.out" > "$logdir/ft_$b"; done;"
			printf "Runtime STD :\n"
			time -p bash -c "for (( i=0; i<100; i++ )); do ./"$outdir/std_$b.out" > "$logdir/std_$b"; done;"
		fi
	else
		printf "$c $RED===ERROR===$END\n"
		printf "(Check err.log for more info)\n"
	fi
}

run_all_tests() {
	b=$(basename "${f%_tests.cpp}")
	clang++ "$f" $flags -DNAMESPACE=ft -I$incdir -o "$outdir/ft_$b.out" 2>> $errlog
	clang++ "$f" $flags -DNAMESPACE=std -I$incdir -o "$outdir/std_$b.out" 2>> $errlog
	./"$outdir/ft_$b.out" > "$logdir/ft_$b" 2>> $errlog
	./"$outdir/std_$b.out" > "$logdir/std_$b" 2>> $errlog
	diff -u "$logdir/ft_$b" "$logdir/std_$b" > "$diffdir/$b.diff"
}

printf "\n"

for f in "$testdir"/*.cpp; do
	run_all_tests
	calculate_time
	printf "\n"
done

printf "\n"