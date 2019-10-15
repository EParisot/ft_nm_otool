#! /bin/bash

echo "x64 TESTS :"
for binary in hell/64*; do
	echo -e "\t$binary"
	test0=`nm $binary`
	test1=`../ft_nm/ft_nm $binary`
	diff <( echo "$test0" ) <( echo "$test1" )
done
