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
errlog="err.log"
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
	if [ -f "$outdir/ft_$b.out" ]; then
		if [ -s "$diffdir/$b.diff" ]; then
			printf "$b $RED===FAILED===$END\n"
			printf "(Check $diffdir/$b.diff for more info)\n"
		else
			ftime=time -p bash -c "for (( i=0; i<500; i++ )); do ./"$outdir/ft_$b.out" > "$logdir/ft_$b"; done;"
			stime=time -p bash -c "for (( i=0; i<500; i++ )); do ./"$outdir/std_$b.out" > "$logdir/std_$b"; done;"
			if [ $((ftime/stime)) -gt $((20)) ]; then
				printf "$b $RED===FAILED-RUNTIME===$END\n"
			else
				printf "$b $GREEN===PASSED===$END\n"
			fi
		fi
	else
		printf "$b $RED===ERROR===$END\n"
		printf "(Check err.log for more info)\n"
	fi
}

run_all_tests() {
	b=$(basename "${f%.cpp}")
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
done

printf "\n"