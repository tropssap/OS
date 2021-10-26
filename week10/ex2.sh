mkdir week01
mkdir week10
echo David > ./week01/file.txt
link ./week01/file.txt _ex2.txt
var="$(stat -c '%i' ./week01/file.txt)"
find ./week10/ -inum $var > ex2.txt
find ./week10/ -inum $var -exec rm {} \; >> ex2.txt
