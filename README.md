#GIT


//get updated files
git pull origin master (or git pull after using the push)

//push files to github
git push -u origin master (or git push after using this once)

//adds all files to be committed
git add .

//commits the changes, with message msg
git commit -m "msg"

//undoes the previous commit
git reset HEAD^

//undo uncommitted local changes to file
git checkout <file>