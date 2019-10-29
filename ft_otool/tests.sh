#!/bin/bash
make
OK=0
TOT=0
for filename in ../hell/*; do
	FOUND=0
	if [[ $@ == "-A" ]] && [[ $filename != *"lib"* ]]; then
		echo "TESTING $filename"
		MY_OTOOL=$( ./ft_otool $filename )
		if [[ $? -eq 139 ]]; then
			echo "CRASHED"
			exit 1
		fi
		REAL_OTOOL=$( otool -t $filename )
		DIFF=$( diff <( echo "$MY_OTOOL" ) <( echo "$REAL_OTOOL" ))
		if [[ $DIFF == "" ]] || ( [[ $MY_OTOOL == *"corrupted"* ]]  &&  [[ $REAL_OTOOL == "" ]] ) ; then
			echo "OK"
			OK=$((OK+1))
		fi
		if [[ $MY_OTOOL != *"not implemented"* ]]; then
			TOT=$((TOT+1))
		fi
	else
		if [[ $@ == "-64" ]] && [[ $filename == *"64"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_OTOOL=$( ./ft_otool $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_OTOOL=$( otool -t $filename )
			FOUND=1
		fi
		if [[ $@ == "-32" ]] && [[ $filename == *"32"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_OTOOL=$( ./ft_otool $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_OTOOL=$( otool -t $filename )
			FOUND=1
		fi
		if [[ $@ == "-fat" ]] && [[ $filename == *"fat"* ]] && [[ $filename != *"lib"* ]]; then
			echo "TESTING $filename"
			MY_OTOOL=$( ./ft_otool $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_OTOOL=$( otool -t $filename )
			FOUND=1
		fi
		if [[ $@ == "-lib" ]] && [[ $filename == *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_OTOOL=$( ./ft_otool $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_OTOOL=$( otool -t $filename )
			FOUND=1
		fi
		if [[ $@ == "-E" ]] && [[ $filename != *"64"* ]] && [[ $filename != *"32"* ]] && [[ $filename != *"lib"* ]] && [[ $filename != *"fat"* ]]; then
			echo "TESTING $filename"
			MY_OTOOL=$( ./ft_otool $filename )
			if [[ $? -eq 139 ]]; then
				echo "CRASHED"
				exit 1
			fi
			REAL_OTOOL=$( otool -t $filename )
			FOUND=1
		fi
		if [[ $FOUND == 1 ]]; then
			DIFF=$( diff <( echo "$MY_OTOOL" ) <( echo "$REAL_OTOOL" ))
			if [[ $DIFF == "" ]] || { [[ $DIFF == *"corrupted"* ]] && [[ $REAL_OTOOL == "" ]]; } ; then
				echo "OK"
				OK=$((OK+1))
			fi
			if [[ $MY_OTOOL != *"not implemented"* ]]; then
				TOT=$((TOT+1))
			fi
		fi

	fi

done
echo ""
echo "$OK / $TOT Successfull"
