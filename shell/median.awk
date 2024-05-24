#!/usr/bin/awk --lint
{
	array[NR]=$1;
}
END {
	print("NR: " NR);
	if (NR % 2) {
		print (array[ (NR+1)/2 ]);
	} else {
		print( array[ (NR/2) ] + array[ (NR/2)+1 ]) / 2.0
	}
}
