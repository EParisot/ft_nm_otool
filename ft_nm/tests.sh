#!/bin/bash
make
for filename in ../ft_nm-ft_otool_binaire_de_test/hell/*; do
	if [[ $filename == *"64"* ]]; then
		diff <( ./ft_nm $filename ) <( nm $filename )
	fi
done
