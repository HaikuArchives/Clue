#!/bin/sh

CLUE="clue-2-1-0-alpha-zeta-1-2-0"

rm -rf $CLUE "$CLUE.zip"
mkdir $CLUE

mkdir "$CLUE/sample"
cp -R "../source/sample/*.[chr]*" "$CLUE/sample"

cp -R "../document/help" "$CLUE/Documentation"

ln -s "$HOME/config/lib" "$CLUE/Place lib$CLUE.so Here"

cp -R "../package/" $CLUE

cp "source/common/Clue.h" $CLUE

cp "../document/Read Me" $CLUE
cp "../Localized Strings" $CLUE

ls -l $CLUE

echo "$CLUE; An Excellent Debugging Server for Zeta.zip" > "$CLUE.zip.comment"
echo "." >> "$CLUE.zip.comment"
zip -r -9 -z -o -y "$CLUE.zip" $CLUE < "$CLUE.zip.comment"

rm -rf $CLUE
rm "$CLUE.zip.comment"

ls -l "$CLUE.zip"
