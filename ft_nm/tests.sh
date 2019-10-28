#!/bin/bash
make
OK=0
TOT=0
for filename in ../hell/*; do
	FOUND=0
	if [[ $@ == "-A" ]] && [[ $filename != *"lib"* ]]; then
		echo "TESTING $filename"
		MY_NM=$( ./ft_nm $filename )
		if [[ $? -eq 139 ]]; then
			echo "CRASHED"
			exit 1
		fi
		REAL_NM=$( nm $filename )
		DIFF=$( diff <( echo "$MY_NM" ) <( echo "$REAL_NM" ))
		if [[ $DIFF == "" ]] || ( [[ $MY_NM == *"corrupted"* ]]  &&  [[ $REAL_NM == "" ]] ) ; then
			echo "OK"
			OK=$((OK+1))
		fi
		if [[ $MY_NM != *"not implemented"* ]]; then
			TOT=$((TOT+1))
		fi
	else
		if [[ $@ == "-64" ]] && [[ $filename == *"64"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_NM=$( nm $filename )
			FOUND=1
		fi
		if [[ $@ == "-32" ]] && [[ $filename == *"32"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_NM=$( nm $filename )
			FOUND=1
		fi
		if [[ $@ == "-fat" ]] && [[ $filename == *"fat"* ]] && [[ $filename != *"lib"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_NM=$( nm $filename )
			FOUND=1
		fi
		if [[ $@ == "-lib" ]] && [[ $filename == *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_NM=$( nm $filename )
			FOUND=1
		fi
		if [[ $@ == "-E" ]] && [[ $filename != *"64"* ]] && [[ $filename != *"32"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_NM=$( ./ft_nm $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_NM=$( nm $filename )
			FOUND=1
		fi
		if [[ $FOUND == 1 ]]; then
			DIFF=$( diff <( echo "$MY_NM" ) <( echo "$REAL_NM" ))
			if [[ $DIFF == "" ]] || { [[ $DIFF == *"corrupted"* ]] && [[ $REAL_NM == "" ]]; } ; then
				echo "OK"
				OK=$((OK+1))
			fi
			if [[ $MY_NM != *"not implemented"* ]]; then
				TOT=$((TOT+1))
			fi
		fi

	fi

done
echo ""
echo "$OK / $TOT Successfull"
