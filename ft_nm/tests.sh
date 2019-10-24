#!/bin/bash
make
for filename in ../ft_nm-ft_otool_binaire_de_test/hell/*; do
	if { [[ $@ == "-A" ]] || [[ $@ == "-64" ]]; } && [[ $filename == *"64"* ]]; then
		echo "TESTING $filename"
		diff <( ./ft_nm $filename ) <( nm $filename )
	fi
	if { [[ $@ == "-A" ]] || [[ $@ == "-32" ]]; } && [[ $filename == *"32"* ]]; then
		echo "TESTING $filename"
		diff <( ./ft_nm $filename ) <( nm $filename )
	fi
done
