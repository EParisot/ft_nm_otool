#!/bin/bash
make
OK=0
TOT=0
for filename in ../ft_nm-ft_otool_binaire_de_test/hell/*; do
	if { [[ $@ == "-A" ]] || [[ $@ == "-64" ]]; } && [[ $filename == *"64"* ]] && [[ $filename != *"lib"* ]]; then
		echo "TESTING $filename"
		DIFF=$( diff <( ./ft_nm $filename ) <( nm $filename ))
		if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]] ; then
			OK=$((OK+1))
		fi
		TOT=$((TOT+1))
	fi
	if { [[ $@ == "-A" ]] || [[ $@ == "-32" ]]; } && [[ $filename == *"32"* ]] && [[ $filename != *"lib"* ]]; then
		echo "TESTING $filename"
		DIFF=$( diff <( ./ft_nm $filename ) <( nm $filename ))
		if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
			OK=$((OK+1))
		fi
		TOT=$((TOT+1))
	fi
	if { [[ $@ == "-A" ]] || [[ $@ == "-lib" ]]; } && [[ $filename == *"lib"* ]]; then
		echo "TESTING $filename"
		DIFF=$( diff <( ./ft_nm $filename ) <( nm $filename ))
		if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
			OK=$((OK+1))
		fi
		TOT=$((TOT+1))
	fi
	if { [[ $@ == "-A" ]] || [[ $@ == "-E" ]]; } && [[ $filename != *"64"* ]] && [[ $filename != *"32"* ]] && [[ $filename != *"lib"* ]]; then
		echo "TESTING $filename"
		DIFF=$(diff <( ./ft_nm $filename ) <( nm $filename ))
		if [[ $DIFF == "" ]] || [[ $DIFF == *"corrupted"* ]]; then
			OK=$((OK+1))
		fi
		TOT=$((TOT+1))
	fi

done
echo ""
echo "$OK / $TOT Successfull"
