#!/bin/bash
make
OK=0
TOT=0
for filename in ../ft_nm-ft_otool_binaire_de_test/hell/*; do
	if [[ $@ == "-A" ]]; then
		echo "TESTING $filename"
		MY_NM=$( ./ft_nm $filename )
		if [[ $? -eq 139 ]]; then
			echo "CRASHED"
			exit 1
		fi
		DIFF=$( diff <( echo "$MY_NM" ) <( nm $filename ))
		if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]] ; then
			echo "OK"
			OK=$((OK+1))
		fi
		TOT=$((TOT+1))
	else
		if [[ $@ == "-64" ]] && [[ $filename == *"64"* ]] && [[ $filename != *"lib"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			DIFF=$( diff <( echo "$MY_NM" ) <( nm $filename ))
			if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]] ; then
				echo "OK"
				OK=$((OK+1))
			fi
			TOT=$((TOT+1))
		fi
		if [[ $@ == "-32" ]] && [[ $filename == *"32"* ]] && [[ $filename != *"lib"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			DIFF=$( diff <( echo "$MY_NM" ) <( nm $filename ))
			if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
				echo "OK"
				OK=$((OK+1))
			fi
			TOT=$((TOT+1))
		fi
		if [[ $@ == "-lib" ]] && [[ $filename == *"lib"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			DIFF=$( diff <( echo "$MY_NM" ) <( nm $filename ))
			if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
				echo "OK"
				OK=$((OK+1))
			fi
			TOT=$((TOT+1))
		fi
		if [[ $@ == "-E" ]] && [[ $filename != *"64"* ]] && [[ $filename != *"32"* ]] && [[ $filename != *"lib"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			DIFF=$(diff <( echo "$MY_NM" ) <( nm $filename ))
			if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
				echo "OK"
				OK=$((OK+1))
			fi
			TOT=$((TOT+1))
		fi
	fi

done
echo ""
echo "$OK / $TOT Successfull"
